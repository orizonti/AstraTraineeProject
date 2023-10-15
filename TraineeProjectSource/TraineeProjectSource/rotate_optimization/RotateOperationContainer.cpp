
#include "RotateOperationContainer.h"
#include <DebugStream.h>
#include <QFile>

using namespace torch::indexing;

int RotateOperationContainer::CALIBRATION_COUNT = 120;
TestDataVectorsContainer::TestDataVectorsContainer()
{

	TestCoordVectorInput.resize(RotateOperationContainer::CALIBRATION_COUNT+1);
	TestCoordVectorInput[0] = QPair<double,double>(0,0);
	int NumberPoints = TestCoordVectorInput.size();
	int CurrentPoint = 0;
	int Radius = 80;
	auto GenerateCircle = [NumberPoints,CurrentPoint,Radius]() mutable -> QPair<double,double>
	{
        double current_angle = CurrentPoint*2*M_PI/NumberPoints;
		QPair<double,double> PointOnCircle; PointOnCircle.first = Radius*std::cos(current_angle); PointOnCircle.second = Radius*std::sin(current_angle);
		CurrentPoint++;
		//Radius = Radius + 10;
		return PointOnCircle;

	};
    std::generate(TestCoordVectorInput.begin()+1,TestCoordVectorInput.end(),GenerateCircle);
  
    CurrentTestCoord = TestCoordVectorInput.begin();
}

void TestDataVectorsContainer::reset()
{
    CurrentTestCoord = TestCoordVectorInput.begin();
}


QPair<double,double> AccumulateDataFilter::GetCoord()
{
	return LastInputFirst;
}
void AccumulateDataFilter::SetCoord(QPair<double, double> Coord)
{
	auto ZeroCoord = QPair<double,double>(0,0);
	if(WaitInputCoord != ZeroCoord)
	{
		if(channel_counter == 1)
		{
			Coord.first = Coord.first - OutputFirstCenter.first; Coord.second = Coord.second - OutputFirstCenter.second;  

			if(CheckCoordMatch(Coord,WaitInputCoord))
			{
				AvarageOutputFirst.first += Coord.first/avarage_window_size;
				AvarageOutputFirst.second += Coord.second/avarage_window_size;
			    qDebug()<<"Input - " << Coord << "Avarage - " << AvarageOutputFirst << " counter - " << accumulate_counter;
			    channel_counter++;
			}

			return;
		};

		if(channel_counter == 2)
		{
			Coord.first = Coord.first - OutputSecondCenter.first; Coord.second = Coord.second - OutputSecondCenter.second; 

			AvarageOutputSecond.first += Coord.first/avarage_window_size;
			AvarageOutputSecond.second += Coord.second/avarage_window_size;
			accumulate_counter++;
			channel_counter--;
		}
    }
    // accumulate data to calc center positions

	if(WaitInputCoord == ZeroCoord && channel_counter == 1)
	{
		OutputFirstCenter.first += Coord.first/avarage_window_size;
		OutputFirstCenter.second += Coord.second/avarage_window_size;
		channel_counter++;
		return;
	}

	if(WaitInputCoord == ZeroCoord && channel_counter == 2)
	{
		OutputSecondCenter.first += Coord.first/avarage_window_size;
		OutputSecondCenter.second += Coord.second/avarage_window_size;
		
		accumulate_counter++; channel_counter--;
	}
    //==================================================================

	if(accumulate_counter == avarage_window_size)
		flag_filter_open = true;
}

void AccumulateDataFilter::WaitCoord(QPair<double,double> coord)
{
  WaitInputCoord = coord;
  flag_filter_open = false;
  accumulate_counter = 0;
  pass_counter = 0;
}

AccumulateDataFilter& operator>>(QPair<double, double> coord, AccumulateDataFilter& Filter)
{
	Filter.SetCoord(coord);
	return Filter;
}

std::pair<double,double> AccumulateDataFilter::GetFirstOutput()
{
	auto output_coord = std::make_pair(AvarageOutputFirst.first,AvarageOutputFirst.second);
	AvarageOutputFirst = QPair<double,double>(0,0);
  	return output_coord;
}

std::pair<double,double> AccumulateDataFilter::GetSecondOutput()
{
	flag_filter_open = false;  // close filter when two output coords is passed
	pass_counter++;
	auto output_coord = std::make_pair(AvarageOutputSecond.first,AvarageOutputSecond.second);
	AvarageOutputSecond = QPair<double,double>(0,0);
	return output_coord;
}

RotateDataMeasureEngine& operator>>(QPair<double, double> coord, RotateDataMeasureEngine& MeasureEngine)
{
    MeasureEngine.CurrentMeasureCoordAbs = coord;
	return MeasureEngine;
}

void operator>>(RotateDataMeasureEngine& MeasureEngine, RotateOperationContainer& RotateContainer)
{

	MeasureEngine.CurrentMeasureCoordAbs >> MeasureEngine.DataFilter >> RotateContainer;

	if(MeasureEngine.DataFilter.pass_counter > 0)
	MeasureEngine.SwitchToNextTestCoord();
}
	
void operator>>(AccumulateDataFilter& Filter, RotateOperationContainer& RotateContainer)
{
	if (Filter.flag_filter_open)
	{
	//qDebug() << "Pass";
		if(Filter.WaitInputCoord == QPair<double,double>(0,0))
		{
			qDebug() << "Center point 1 - " << Filter.OutputFirstCenter;
			qDebug() << "Center point 2 - " << Filter.OutputSecondCenter;
			Filter.pass_counter++; Filter.flag_filter_open = false;
			return;
		}; // when pass_counter > 0 measures switch to next coord

		RotateContainer.AppendInputData(Filter.GetFirstOutput());
		RotateContainer.AppendInputData(Filter.GetSecondOutput());
	}
}


void RotateDataMeasureEngine::SwitchToNextTestCoord()
{
	DataFilter.WaitCoord(DataVectors.GetTestCoord());
}


QPair<double, double> TestDataVectorsContainer::GetTestCoord()
{
		auto LastCoord = *CurrentTestCoord;
		CurrentTestCoord++; if (CurrentTestCoord == TestCoordVectorInput.end()) { CurrentTestCoord = TestCoordVectorInput.begin();};
		return LastCoord;
}

AccumulateDataFilter::AccumulateDataFilter()
{
}

void AccumulateDataFilter::reset()
{
	 flag_filter_open = false;
	accumulate_counter = 0;
	pass_counter = 0;

	LastInputFirst = QPair<double,double>(0,0);
	WaitInputCoord = LastInputFirst;

	AvarageOutputFirst = LastInputFirst;
	AvarageOutputSecond = LastInputFirst;
}

RotateDataMeasureEngine::RotateDataMeasureEngine()
{
	SwitchToNextTestCoord();
}

void RotateDataMeasureEngine::Reset()
{
	this->DataVectors.reset();
	SwitchToNextTestCoord();
}

void RotateOperationContainer::ConvertOperationToMatrix(pair<RotateAxis,torch::Tensor>& Operation, torch::Tensor& Matrix)
{

	if(Operation.first == x_axis)
     Matrix = torch::sin(Operation.second) * x_sin + torch::cos(Operation.second) * x_cos + x_rotate_matrix_empty;
	if(Operation.first == y_axis)
     Matrix = torch::sin(Operation.second) * y_sin + torch::cos(Operation.second) * y_cos + y_rotate_matrix_empty;
	if(Operation.first == z_axis)
     Matrix = torch::sin(Operation.second) * z_sin + torch::cos(Operation.second) * z_cos + z_rotate_matrix_empty;
}



bool AccumulateDataFilter::CheckCoordMatch(QPair<double, double> Coord,QPair<double,double> AimCoord)
{
		double diff_x = Coord.first - AimCoord.first;
		double diff_y = Coord.second - AimCoord.second;
		double norm = std::hypot(diff_x, diff_y);
		//qDebug() << "Check coord in filter - " << Coord << " aim coord - " << AimCoord << " norm - " << norm;

		if (norm < 1)
			return true;
		else
			return false;

}

void RotateOperationContainer::UpdateCommonMatrix()
{

    CommonMatrix = ones_matrix;
	RotateOperationMatrixSequense.clear();

	for(auto Operation : RotateOperationSequenseTensor)
	{
		RotateOperationMatrixSequense.push_back(ones_matrix);
		ConvertOperationToMatrix(Operation,RotateOperationMatrixSequense.back());
	    CommonMatrix = torch::matmul(RotateOperationMatrixSequense.back(), CommonMatrix);	
	}

	CommonMatrixInverse = torch::inverse(CommonMatrix);
	CommonSubMatrix = CommonMatrix.index({Slice(0,2),Slice(0,2)});
	CommonSubMatrixInverse = torch::inverse(CommonSubMatrix);
	
}
	
void RotateOperationContainer::AppendOperation(pair<RotateAxis,double> Operation)
{
    this->RotateOperationSequense.push_back(Operation);
    auto angle_radian = torch::tensor({Operation.second*3.14/180}, torch::TensorOptions().dtype(torch::kFloat32));
	this->RotateOperationSequenseTensor.push_back(pair<RotateAxis,torch::Tensor>(Operation.first,angle_radian));

	UpdateCommonMatrix();
}

pair<torch::Tensor,torch::Tensor> RotateOperationContainer::ConvertInputCoord(vector<pair<double,double>> test_input ,vector<pair<double,double>> test_output, bool z_signs_inverse)
{
	int measure_count = test_input.size();
    //qDebug() << "Measure count - " << measure_count;
	vector<float> norms; norms.resize(measure_count); auto current_norm = norms.begin(); 

	int counter = 0;
	for(auto& coord: test_output)
	{
	   *current_norm = pow(coord.first,2) + pow(coord.second,2);
	   //qDebug() << "Norm - " << *current_norm << " | " << counter++ << " coord " << coord;
	   current_norm++;
	}

	

	vector<float>::iterator max_element_first = max_element(norms.begin(), norms.end() - norms.size()/2);
	vector<float>::iterator min_element_first = min_element(max_element_first, max_element_first + norms.size()/4);
	vector<float>::iterator max_element_second = max_element(min_element_first, min_element_first + norms.size()/4);
	//qDebug() << "Max norm1 - " << *max_element_first << " max norm2 - " << *max_element_second;
	int pos_max_norm1 = distance(norms.begin(),max_element_first);
	int pos_max_norm2 = distance(norms.begin(),max_element_second);


	vector<pair<double,double>> input_filtered_negative;
	vector<pair<double,double>> output_filtered_negative;

	vector<pair<double,double>> input_filtered_positive;
	vector<pair<double,double>> output_filtered_positive;
	for(int n = 0; n < measure_count; n++)
	{
	  int length = std::abs(pos_max_norm1 - n);
	  int length2 = std::abs(pos_max_norm2 - n);

	      //if(length < 2 || length2 < 2)
		  //qDebug() << "NORM - " << norms[n]<< n << " - ";

		if(n > pos_max_norm1 && n < pos_max_norm2 && (length > 2 && length2 > 2))
		{
	      input_filtered_positive.push_back(test_input[n]);
	      output_filtered_positive.push_back(test_output[n]);
		  //qDebug() << "NORM - " << norms[n]<< n << " * ";
		}

		if(n < pos_max_norm1 || n > pos_max_norm2 && (length > 2 && length2 > 2))
		{
	      input_filtered_negative.push_back(test_input[n]);
	      output_filtered_negative.push_back(test_output[n]);

		  //qDebug() << "NORM - " << norms[n] << n;
		}
	}

	vector<pair<double,double>> processed_input = input_filtered_positive;
	vector<pair<double,double>> processed_output = output_filtered_positive;

	if(z_signs_inverse)
	{
	processed_input = input_filtered_negative;
	processed_output = output_filtered_negative;
	}

    measure_count = processed_input.size();
	torch::Tensor input_matrix = torch::ones({3,measure_count});
	torch::Tensor output_matrix = torch::ones({3,measure_count});

	//qDebug() << "START - " << pos_max_norm1 << " END - " << pos_max_norm2 << "COUNT - " << measure_count;

	              for(int n = 0; n < measure_count; n++)
	              {
					  float vector[] = {processed_input[n].first, processed_input[n].second, 0};
					  input_matrix.index({Slice(None),Slice(n,n+1)}) = torch::from_blob(vector,{3,1});

                      //calc vector z component manually because from camera gets only x y  
                      float norm = *torch::norm(input_matrix.index({Slice(None),Slice(n,n+1)}),2,0).data_ptr<float>(); 
                      double z_component =  std::sqrt(std::pow(norm,2) - std::pow(processed_output[n].first,2) - std::pow(processed_output[n].second,2)); 
                      //qDebug() << "Z component - " << floor(z_component*3) << n+1;
					  float vector_output[3] = {processed_output[n].first, processed_output[n].second, z_component};
					  output_matrix.index({Slice(None),Slice(n,n+1)}) = torch::from_blob(vector_output,{3,1});
	              }
				  output_matrix = torch::nan_to_num(output_matrix, 0);
				  return std::make_pair(input_matrix,output_matrix);
}

torch::Tensor RotateOperationContainer::FitToTestVectors(vector<pair<double,double>> test_input, vector<pair<double,double>> test_output, float gamma, float speed, int number_iteration)
{
	auto test_data = ConvertInputCoord(test_input,test_output,false);

	return FitToTestVectors(test_data.first,test_data.second,gamma,speed, number_iteration);
	
}

torch::Tensor RotateOperationContainer::FitToTestVectors(torch::Tensor test_input, torch::Tensor test_output, float gamma, float speed, int number_iteration)
{

	        torch::Tensor loss;
            vector<float> momentums; momentums.resize(3); auto current_momentum = momentums.begin();
			momentums[0] = 0; momentums[1] = 0; momentums[2] = 0;

			//std::cout << " LOSS - ";
			for (int n = 0; n <= number_iteration; n++)
			{

			 for(auto& rotate_operation: RotateOperationSequenseTensor)
			 rotate_operation.second.set_requires_grad(true);
			 //std::cout <<n << " | axis - "<< rotate_operation.first << " angle - " << (*rotate_operation.second[0].data_ptr<float>()*(1/3.14) * 180) << std::endl;

			 UpdateCommonMatrix();

			auto output = torch::matmul(CommonMatrix, test_input);
			auto error_output = output - test_output;
			auto distance = torch::norm(error_output,2,0);
			loss = torch::sum(torch::pow(distance, 2))/float(distance.numel());
			loss.backward();

			//if(n%50 == 0 && loss.data_ptr<float>()[0] > 0.00001)
			//std::cout<< setprecision(3) << loss.data_ptr<float>()[0] << " | ";

			 for(auto& angle_rotate: RotateOperationSequenseTensor)
			 angle_rotate.second.set_requires_grad(false);

			 for(auto& rotate_operation: RotateOperationSequenseTensor)
			 {
			 *current_momentum = *current_momentum*gamma + speed*rotate_operation.second.grad().data_ptr<float>()[0]; 
			 rotate_operation.second = rotate_operation.second - *current_momentum; 
			 current_momentum++; if(current_momentum == momentums.end()) {current_momentum =  momentums.begin();};
			 }
			}

			 for(int n = 0; n < RotateOperationSequense.size(); n++)
				 RotateOperationSequense[n].second = *RotateOperationSequenseTensor[n].second[0].data_ptr<float>() * 180/3.14;

			return loss;
}




//	qDebug() << "Output test vectors - " << output_to_optimize_rotation;


void RotateOperationContainer::FindArbitraryRotationToVectors(vector<pair<double,double>> test_input, vector<pair<double,double>> test_output)
{
	QDebugStream cout(std::cout);
	qDebug() << "FIND ARBITRARY ROTATION TO VECTORS";
	vector<RotateOperationContainer> RotateVariants;

			qDebug() << "===============================================";
			qDebug() << "Base test points - " << test_input;
			qDebug() << "Remote test points - " << test_output;
			qDebug() << "===============================================";


		auto CalcCoordSystemScaleParameter = [](vector<pair<double,double>> test_input, vector<pair<double,double>> test_output) -> double
		{
		vector<double> test_output_norm_massive; test_output_norm_massive.resize(test_input.size());
		double input_norm = std::hypot(test_input[0].first,test_input[0].second);

		for(int number = 0; number < test_output_norm_massive.size(); number++)
		{
			test_output_norm_massive[number] = pow(test_output[number].first,2) + pow(test_output[number].second,2);
		}
		auto max_value_norm = *std::max_element(test_output_norm_massive.begin(),test_output_norm_massive.end());
		return std::sqrt(max_value_norm/(input_norm*input_norm));
		};

		pixel_scale_remote_to_local = CalcCoordSystemScaleParameter(test_input, test_output);
		this->system_transform_scale = pixel_scale_remote_to_local;
		qDebug() << "        SYSTEM SCALE " << pixel_scale_remote_to_local;
		////convert remote coord to base coord system scale

		for (auto& Coord : test_output)
		{
			Coord.first  /= pixel_scale_remote_to_local;
			Coord.second /= pixel_scale_remote_to_local;
		}

    vector<vector<RotateAxis>> Sequenses;
	                 Sequenses.push_back({z_axis,x_axis,y_axis}); 
	                 Sequenses.push_back({z_axis,y_axis,x_axis}); 

	                 Sequenses.push_back({y_axis,x_axis,z_axis}); 
	                 Sequenses.push_back({y_axis,z_axis,x_axis}); 

	                 Sequenses.push_back({x_axis,y_axis,z_axis}); 
	                 Sequenses.push_back({x_axis,z_axis,y_axis}); 


    
    vector<float> Losses;

	auto test_data = ConvertInputCoord(test_input,test_output,false);
	auto test_data_inverse_z = ConvertInputCoord(test_input,test_output,true);


	//qDebug() << "====================================";
	//std::cout << "Tensor input - "<< std::endl << test_data.first << std::endl;
	//std::cout << "Tensor output - " << std::endl<< setprecision(3) << test_data.second<< std::endl;
	//qDebug() << "====================================";


	for(auto Sequence: Sequenses)
	{
	float speed = 0.0000002;
	float momentum = 0.9;
	float number_iteration = 9000;
	RotateOperationContainer Rotate;
	                         Rotate.AppendOperation(pair<RotateAxis,double>(Sequence.at(0),0));
	                         Rotate.AppendOperation(pair<RotateAxis,double>(Sequence.at(1),0));
	                         Rotate.AppendOperation(pair<RotateAxis,double>(Sequence.at(2),0));

							 RotateVariants.push_back(Rotate);

		qDebug() << "CHECK - " << RotateVariants.back().RotationToString().c_str();
	    auto Loss = RotateVariants.back().FitToTestVectors(test_data.first,test_data.second,momentum,speed, number_iteration);
		Losses.push_back(*Loss.data_ptr<float>());
		RotateVariants.back().system_transform_scale = pixel_scale_remote_to_local;

							 RotateVariants.push_back(Rotate);
	         Loss = RotateVariants.back().FitToTestVectors(test_data_inverse_z.first,test_data_inverse_z.second,momentum,speed, number_iteration);
		Losses.push_back(*Loss.data_ptr<float>());
		RotateVariants.back().system_transform_scale = pixel_scale_remote_to_local;
	}

	for(int n = 0; n<Losses.size(); n++)
		qDebug() << "Loss - " << Losses[n] << QString(RotateVariants[n].RotationToString().c_str());

	auto min = min_element(Losses.begin(),Losses.end());
	int number_min_loss = distance(Losses.begin(),min);


	this->CopyRotation(RotateVariants[number_min_loss]);
	qDebug()  << "OPT MATRIX BEST ROTATION" << endl;
	std::cout  << RotationToString() << endl;
	std::cout  << MatrixToString() << endl;
	
	SaveMeasureDataToFile(QString("E:/TrainerData/RotateMatrixOutput.txt"));
	qDebug()  << "=================================================================================" << endl;

	RotationValid = true;
	this->Inverse();

}


torch::Tensor RotateOperationContainer::ConvertInput(torch::Tensor& Input)
{
torch::Tensor output;

	QDebugStream cout(std::cout);
		 float x = Input.data_ptr<float>()[0];
		 float y = Input.data_ptr<float>()[1];
		 float z = Input.data_ptr<float>()[2];

if(!is_rotation_inverse)
output = torch::matmul(CommonMatrix, Input);	

if(is_rotation_inverse)
output = torch::matmul(CommonMatrixInverse, Input);	

return output;
}
RotateOperationContainer::RotateOperationContainer(const RotateOperationContainer& CopyContainer) : RotateOperationContainer()
{
	this->CopyRotation(CopyContainer);
}

void RotateOperationContainer::CopyRotation(const RotateOperationContainer& CopyContainer)
{
	CommonMatrix = CopyContainer.CommonMatrix;
	CommonMatrixInverse = CopyContainer.CommonMatrixInverse;
	CommonSubMatrix = CopyContainer.CommonSubMatrix;
	CommonSubMatrixInverse = CopyContainer.CommonSubMatrixInverse;
	
	RotateOperationSequense = CopyContainer.RotateOperationSequense;
	RotateOperationMatrixSequense = CopyContainer.RotateOperationMatrixSequense;
	RotateOperationSequenseTensor = CopyContainer.RotateOperationSequenseTensor;
	OutputCoord = CopyContainer.OutputCoord;
	InputCoord = CopyContainer.InputCoord;

	pixel_scale_remote_to_local = CopyContainer.pixel_scale_remote_to_local;
	system_transform_scale = CopyContainer.system_transform_scale;
	is_rotation_inverse = CopyContainer.is_rotation_inverse;
	//=====================================================
}

RotateOperationContainer::RotateOperationContainer()
{
	Reset();
}

void RotateOperationContainer::Reset()
{
	input_to_optimize_rotation.clear();
	output_to_optimize_rotation.clear();
	MeasureFilter.Reset();

	counter_test = 0; // to delete
	RotationValid = false;
	system_transform_scale = 1;
	pixel_scale_remote_to_local = 1;

     ones_matrix = torch::tensor({ {1,0,0},{0,1,0},{0,0,1} }, torch::TensorOptions().dtype(torch::kFloat32));
     CommonMatrix = ones_matrix;;
     x_sin = torch::tensor({ {0,0,0},{0,0,-1},{0,1,0} }, torch::TensorOptions().dtype(torch::kFloat32));
     x_cos = torch::tensor({ {0,0,0},{0,1, 0},{0,0,1} }, torch::TensorOptions().dtype(torch::kFloat32));

     y_sin = torch::tensor({ {0,0,1},{0,0,0},{-1,0,0} }, torch::TensorOptions().dtype(torch::kFloat32));
     y_cos = torch::tensor({ {1,0,0},{0,0, 0},{0,0,1} }, torch::TensorOptions().dtype(torch::kFloat32));

     z_sin = torch::tensor({ {0,-1,0},{1,0,0},{0,0,0} }, torch::TensorOptions().dtype(torch::kFloat32));
     z_cos = torch::tensor({ {1, 0,0},{0,1,0},{0,0,0} }, torch::TensorOptions().dtype(torch::kFloat32));

     x_rotate_matrix_empty = torch::tensor({ {1,0,0},{0,0,0},{0,0,0} }, torch::TensorOptions().dtype(torch::kFloat32));
     y_rotate_matrix_empty = torch::tensor({ {0,0,0},{0,1,0},{0,0,0} }, torch::TensorOptions().dtype(torch::kFloat32));
     z_rotate_matrix_empty = torch::tensor({ {0,0,0},{0,0,0},{0,0,1} }, torch::TensorOptions().dtype(torch::kFloat32));

	 InputCoord = torch::zeros({3,1},torch::TensorOptions().dtype(torch::kFloat32));
	 OutputCoord = torch::zeros({3,1},torch::TensorOptions().dtype(torch::kFloat32));
}

string RotateOperationContainer::MatrixToString()
{
    std::ostringstream out;
    out.precision(5);
	out << this->CommonMatrix;

	return out.str();
}

string RotateOperationContainer::RotationToString(vector<pair<RotateAxis,double>> Sequence)
{
    std::ostringstream out;
    out.precision(4);
	for(auto Rotation: Sequence)
	{
	  if(Rotation.first == x_axis)	
		out << " x_axis ";
	  if(Rotation.first == y_axis)	
		out << " y_axis ";
	  if(Rotation.first == z_axis)	
		out << " z_axis ";

	    out <<std::setw(7)<< Rotation.second;
	}
	return out.str();
}

string RotateOperationContainer::RotationToString()
{
	return RotationToString(RotateOperationSequense);
}

void RotateOperationContainer::AppendInputData(pair<double,double> test_coord)
{
		 //input_to_optimize_rotation.push_back(std::make_pair(test_coord.first-InputCoordCenter.first,test_coord.first-InputCoordCenter.second));

	  if (input_to_optimize_rotation.size() == output_to_optimize_rotation.size())
	  {
		 //input_to_optimize_rotation.push_back(std::make_pair(std::round(test_coord.first),std::round(test_coord.second)));
		 input_to_optimize_rotation.push_back(std::make_pair(test_coord.first,test_coord.second));
		  qDebug() << "append - " << input_to_optimize_rotation.back();
	  }
	  else
	  {
		 output_to_optimize_rotation.push_back(test_coord);

		  qDebug() << "append - " << output_to_optimize_rotation.back() << " counter - " << ++counter_test;
	  }

	 if(IsDataFull()) this->FindArbitraryRotationToVectors(input_to_optimize_rotation, output_to_optimize_rotation);
}


void RotateOperationContainer::SetCoord(QPair<double, double> Coord)
{
		 InputCoord[0] = Coord.first;
		 InputCoord[1] = Coord.second;
		 InputCoord[2] = 0;


		 if(is_rotation_inverse)
		 InputCoord[2] = CalcVirtualZComponent(Coord);

                               
							   //QDebugStream cout(std::cout);
							   //qDebug() << "Rotate vector input ";
							   //std::cout << InputVector << endl;
							   //qDebug() << "Z_Coeff - " << Z_Coeff;
         OutputCoord = this->ConvertInput(InputCoord);

		 if(!is_rotation_inverse)
		 OutputCoord = OutputCoord*system_transform_scale;

		 if(is_rotation_inverse)
		 OutputCoord = OutputCoord/system_transform_scale;


		 float x = OutputCoord.data_ptr<float>()[0];
		 float y = OutputCoord.data_ptr<float>()[1];
		 float z = OutputCoord.data_ptr<float>()[2];
		 //float norm = sqrt(x*x + y*y);

//		 if(z > 0)
//	     qDebug()<< "Set coord z - "  << std::floor(z)<<" number -"  << ++counter_test;
//
//		 if(z < 0)
//	     qDebug()<< "Set coord z - "  << std::floor(z)<<" number -"  << ++counter_test << " * ";

}

QPair<double, double> RotateOperationContainer::GetCoord()
{
	return QPair<double, double>(this->OutputCoord.data_ptr<float>()[0], this->OutputCoord.data_ptr<float>()[1]);
}


void RotateOperationContainer::Inverse()
{
	//flag needed only to calculate z_component when used inverse rotation
	is_rotation_inverse = !is_rotation_inverse;
}

//void RotateOperationContainer::operator=(RotateOperationContainer & Rotation)
//{
//	CommonMatrixInverse = torch::inverse(CommonMatrix);
//}
//void RotateOperationContainer::operator=(RotateOperationContainer && Rotation)
//{
//}

double RotateOperationContainer::CalcVirtualZComponent(QPair<double,double> InputCoord)
{

	torch::Tensor InputCoordTensor = torch::tensor({InputCoord.first,InputCoord.second}, torch::TensorOptions().dtype(torch::kFloat32)).t();
	torch::Tensor OutputCoordTensor = torch::tensor({0,0,0}, torch::TensorOptions().dtype(torch::kFloat32)).t();

	OutputCoordTensor.index({Slice(0,2)}) = torch::matmul(CommonSubMatrixInverse,InputCoordTensor);

	OutputCoordTensor = torch::matmul(CommonMatrix,OutputCoordTensor);
	auto VectorValues = OutputCoordTensor.data_ptr<float>();

	//qDebug() << "Input coord inverse - " << VectorValues[0] << VectorValues[1] << VectorValues[2];
	return OutputCoordTensor.data_ptr<float>()[2];
}

void RotateOperationContainer::SetRotateMatrix(torch::Tensor RotateMatrix)
{
	   CommonMatrix = RotateMatrix;
	   CommonMatrixInverse = torch::inverse(CommonMatrix);
	   CommonSubMatrix = CommonMatrix.index({Slice(0,2),Slice(0,2)});
	   CommonSubMatrixInverse = torch::inverse(CommonSubMatrix);
}

void RotateOperationContainer::SaveMeasureDataToFile(QString FileName)
{
    qDebug() << "Save data to file - " << FileName ;
    QFile data(FileName);
    data.open(QFile::WriteOnly); data.flush();


	QString outString;
	QTextStream out(&outString);

	out <<"MATRIX" << endl;
	out << this->MatrixToString().c_str() << endl;
	out <<"===========================================================" << endl;
	out <<"ROTATION" << endl;
	out << this->RotationToString().c_str() << endl;
	out <<"===========================================================" << endl;
	out << "SCALE            " << system_transform_scale << endl;
	out <<"===========================================================" << endl;
	out << "MEASURE_NUMBER   " << input_to_optimize_rotation.size() << endl;
	out <<"===========================================================" << endl;

	out << qSetFieldWidth(20) << Qt::right << "Base point" << "Rotate point" << "" << endl;
	out << qSetFieldWidth(10) << Qt::right << " x " << " y " << " x " << " y " << endl;

	for(int n = 0; n < input_to_optimize_rotation.size(); n++)
	{
       out << input_to_optimize_rotation[n].first << input_to_optimize_rotation[n].second 
		   << output_to_optimize_rotation[n].first << output_to_optimize_rotation[n].second << endl;
	}


	data.write(outString.toUtf8());
	data.close();
}


void RotateOperationContainer::LoadRotationFromFile(QString FileName)
{

	 QDebugStream cout(std::cout);
     QFile data(FileName);
	 data.open(QFile::ReadOnly); 

	 if(!data.isOpen())
		 return;

     QTextStream in_stream(&data);
	 QString header = in_stream.readLine();

	 rotate_matrix[9] = {0};

	 for(auto& value: rotate_matrix)
		 in_stream >> value; 
	 in_stream.readLine(); in_stream.readLine(); in_stream.readLine(); in_stream.readLine();
     //=================================================================
	 std::vector<pair<RotateAxis,double>> rotate_operation; 
	 QString axis_string;  RotateAxis axis = x_axis; double angle_degree_value = 0;

	 for(int n = 1; n <=3; n++)
	 {
	 in_stream >> axis_string; in_stream >> angle_degree_value;
	 axis = x_axis; if(axis_string == "y_axis"){axis = y_axis;}; if(axis_string == "z_axis"){axis = z_axis;}; 
	 rotate_operation.push_back(make_pair(axis,angle_degree_value));
	 }
     //=================================================================
	 int number_measure = 0;
	 in_stream.readLine(); in_stream.readLine();

	 in_stream >> header >> this->system_transform_scale; pixel_scale_remote_to_local = system_transform_scale;
	 in_stream.readLine(); in_stream.readLine();
	 in_stream >> header; in_stream >> number_measure;
	 in_stream.readLine(); in_stream.readLine(); in_stream.readLine(); in_stream.readLine();

	 std::vector<pair<double,double>> input_measures; input_measures.resize(number_measure);
	 std::vector<pair<double,double>> output_measures; output_measures.resize(number_measure);

	 for(int n=0; n < number_measure; n++)
	 {
        in_stream >> input_measures[n].first; in_stream >> input_measures[n].second;
        in_stream >> output_measures[n].first; in_stream >> output_measures[n].second;
	 }

	 qDebug() << "===================================================";
	 qDebug() << "                  LOAD ROTATION FROM FILE - " << FileName << endl;

	 CommonMatrix = torch::from_blob(rotate_matrix,{3,3}); 
	 CommonMatrixInverse = torch::inverse(CommonMatrix);
	 CommonSubMatrix = CommonMatrix.index({Slice(0,2),Slice(0,2)});
	 CommonSubMatrixInverse = torch::inverse(CommonSubMatrix);
	 RotationValid = true;

     std::cout << "SCALE - " << system_transform_scale << endl;
	 std::cout << "ROTATION - " << RotationToString(rotate_operation).c_str() << endl;
	 std::cout << "MATRIX - " << endl << this->MatrixToString().c_str() << endl;
	 //std::cout << "NUMBER MEASURE - " << number_measure << endl;
	 //std::cout << "LOAD MEASURES INPUT  - " << input_measures  << endl;
	 //std::cout << "LOAD MEASURES OUTPUT - " << output_measures << endl;
	 qDebug() << "===================================================";
}

bool RotateOperationContainer::isValid()
{
return RotationValid;
}
