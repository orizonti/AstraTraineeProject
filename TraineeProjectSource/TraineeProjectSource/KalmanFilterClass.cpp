#include "KalmanFilterClass.h"

ONNXSession SinusFilter::ProcessSession;

using namespace std;
std::string tensor_type_names[20] = {
        std::string("ONNX_TENSOR_ELEMENT_DATA_TYPE_UNDEFINED"),
        std::string("ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT"),
        std::string("ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT8"),
        std::string("ONNX_TENSOR_ELEMENT_DATA_TYPE_INT8"),
        std::string("ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT16"),
        std::string("ONNX_TENSOR_ELEMENT_DATA_TYPE_INT16"),
        std::string("ONNX_TENSOR_ELEMENT_DATA_TYPE_INT32"),
        std::string("ONNX_TENSOR_ELEMENT_DATA_TYPE_INT64"),
        std::string("ONNX_TENSOR_ELEMENT_DATA_TYPE_STRING"),
        std::string("ONNX_TENSOR_ELEMENT_DATA_TYPE_BOOL"),
        std::string("ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT16"),
        std::string("ONNX_TENSOR_ELEMENT_DATA_TYPE_DOUBLE"),
        std::string("ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT32"),
        std::string("ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT64"),
        std::string("ONNX_TENSOR_ELEMENT_DATA_TYPE_COMPLEX64"),
        std::string("ONNX_TENSOR_ELEMENT_DATA_TYPE_COMPLEX128"),
        std::string("ONNX_TENSOR_ELEMENT_DATA_TYPE_BFLOAT16")
};
ONNXSession::~ONNXSession()
{
for(const char* node_name : input_node_names)
    allocator.Free(const_cast<void*>(reinterpret_cast<const void*>(node_name)));
}


QPair<double, double> operator/(QPair<double, double> x, double devider)
{
    x.first = (x.first / devider);
    x.second = (x.second / devider);
    return x;
}

//=================================
KalmanFilterClass::KalmanFilterClass()
{
	Initialaize();
	Eigen::Matrix<float, 2, 1> Vec; Vec << 0,0;
	OutputSerieses.resize(2);
	OutputSerieses[0].assign(INPUT_SIZE,0);
	OutputSerieses[1].assign(INPUT_SIZE,0);
	SetControlVec(Vec);


    DirectFilter = new SinusFilter; DirectFilter->InitFilter(INPUT_SIZE);
    thread_to_direct_filter = new QThread;
    DirectFilter->moveToThread(thread_to_direct_filter);
    thread_to_direct_filter->start();
    QObject::connect(this, SIGNAL(SendCoordToPerform(QPair<double,double>)),DirectFilter,SLOT(SlotSetCoord(QPair<double,double>)),Qt::QueuedConnection);
}

Eigen::Matrix<float, 2, 1> KalmanFilterClass::FilterCoord(Eigen::Matrix<float, 2, 1> MeasureVec)
{
	QDebugStream cout(std::cout);

	//GET CURRENT ESTIMATE STATE COORD
	MeasureVecError = MeasureVec - H1*ExtrapolateState;           //Преобразованное наблюдение
	EstimateState = ExtrapolateState + KK*MeasureVecError;      //Коррекция вектора состояния  
	ExtrapolateStateCov = (I - KK*H1)*ExtrapolateStateCov;
	//=====================================================

	//GET CURRENT ESTIMATE STATE COORD
	ExtrapolateState = F1*EstimateState + B1*ControlVek;           //Экстраполяция вектора состояния
	ExtrapolateStateCov = F1*ExtrapolateStateCov*F1T + ControlNoizeCov;  //Экстраполяция ковариации ошибки
    KalmanErrorCov = H1*ExtrapolateStateCov*H1T + MeasureNoizeCov;   //Ковариации ошибки оценки калмана

	KK = ExtrapolateStateCov*H1T*(KalmanErrorCov).inverse();
	//=====================================================
	return EstimateState;
}

void KalmanFilterClass::LoadInitSerieses(vector<double> series, vector<double> series2)
{
    QPair<double, double> coord;
    for (int n = 0; n < series.size(); n++)
    {
        coord.first = series[n]; coord.second = series2[n];

          coord >> FilteredDerivative;

        //coord >> AmplitudeNormalization.direct() >> DirectFilter >> coord;
        //coord >> AmplitudeNormalization.inverse() >> coord;
                 
        AppendOutputToStore(coord);
    }
}
void KalmanFilterClass::AppendOutputToStore(QPair<double, double> coord)
{
    OutputSerieses[0].push_back(coord.first);
    OutputSerieses[1].push_back(coord.second);

    if (OutputSerieses[0].size() > INPUT_SIZE)
    {
        OutputSerieses[0].erase(OutputSerieses[0].begin());
        OutputSerieses[1].erase(OutputSerieses[1].begin());
    }
}

void KalmanFilterClass::AppendOutputToStore(float first, float second)
{
    OutputSerieses[0].push_back(first);
    OutputSerieses[1].push_back(second);

    if (OutputSerieses[0].size() > INPUT_SIZE)
    {
        OutputSerieses[0].erase(OutputSerieses[0].begin());
        OutputSerieses[1].erase(OutputSerieses[1].begin());
    }
}

void KalmanFilterClass::SetCoord(QPair<double,double> Coord)
{

    //qDebug() << "KALMAN FILTER THREAD - " << this->thread();
    Eigen::Matrix<float, 2, 1> MeasureVec;
    MeasureVec << Coord.first, Coord.second;

    INPUT_COORD = Coord; FilteredDerivative.FILTER_ENABLED = this->FILTER_ENABLED;
    INPUT_COORD >> FilteredDerivative;

    SetControlVec(FilteredDerivative.GetCoord());
    auto output = FilterCoord(MeasureVec);
    AppendOutputToStore(output(0, 0),output(1, 0));

    //INPUT_COORD = Coord;
    //Coord >> AmplitudeNormalization.direct() >> Coord; emit SendCoordToPerform(Coord);
    //DirectFilter->GetCoord() >> AmplitudeNormalization.inverse() >> Coord;
    //AppendOutputToStore(Coord);
}

QPair<double, double> KalmanFilterClass::GetCoord()
{
    if(FILTER_ENABLED && OutputSerieses[0].size() > 1)
    return QPair<double, double>(OutputSerieses[0].back(), OutputSerieses[1].back());


    return INPUT_COORD;
}


QPair<double, double> KalmanFilterClass::GetVelocityEstimate()
{
	return GetCoord();
}

QPair<double, double> KalmanFilterClass::GetExtrapolateStep()
{

	 std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint = std::chrono::high_resolution_clock::now();
	 double StepPeriod = std::chrono::duration<double>((TimePoint - TimeFromLastCommand)).count();

	 StepPeriod = 0;

     LastStepToEngine = QPair<double, double>(-EstimateState(0, 0) - EstimateState(2, 0)*StepPeriod , EstimateState(1, 0) + EstimateState(3, 0)*StepPeriod);

	 return LastStepToEngine;
}


void KalmanFilterClass::SetControlErrorVariance(float variance)
{
	COV_CONTROL = variance; 
	ControlNoizeCov << variance, 0,
					   0, variance;
	KK.fill(0);
}
void KalmanFilterClass::SetMeasureErrorVariance(float variance)
{
	COV_MEASURE = variance;
	MeasureNoizeCov << variance, 0,
					   0, variance;
	KK.fill(0);
}

void KalmanFilterClass::Initialaize()
{
	QDebugStream cout(std::cout);
	 F1 << 1,0,
	       0,1;

	 B1 << Tp,0,
	       0,Tp;
	        
	 F1T = F1.transpose();

	 H1 << 1,0,
	       0,1;
	 H1T = H1.transpose();


	MeasureNoizeCov << 0.3,0,
		               0,0.3;
	ControlNoizeCov << 0.06,0, 
		               0,0.06;

	ExtrapolateStateCov << 0,0,
		                   0,0;
		 KalmanErrorCov << 0,0,
						   0,0;

//===============================
	 KK << 0,0,
		   0,0;
	 I  << 1,0, 
	       0,1;
//===============================
	ControlVek << 0,
		          0;
 EstimateState << 0,
				  0;
 ExtrapolateState << 0,
				     0;
	MeasureVec << 0,
				  0;
PredictStateError << 0,
		             0;
//===============================
//	std::cout << "-------------\n";
//	std::cout << "EstimateState \n";
//	std::cout << EstimateState <<"\n";
//	std::cout << "-------------\n";}
}

void KalmanFilterClass::SetInterval(float Interval)
{
	Tp = Interval;	
	Initialaize();
}

void KalmanFilterClass::SetControlVec(Eigen::Matrix<float, 2, 1> Control)
{
	ControlVek = Control;
}

void KalmanFilterClass::SetControlVec(double velx, double vely)
{
	ControlVek << velx, 
		          vely;
}

void KalmanFilterClass::SetControlVec(QPair<double,double> ControlVec)
{
    ControlVek << ControlVec.first,
                  ControlVec.second;
}

void Derivative::SetCoord(QPair<double,double> Coord)
{
	 std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint = std::chrono::high_resolution_clock::now();
	 double StepPeriod = std::chrono::duration<double>((TimePoint - TimeFromLastCommand)).count();
	 TimeFromLastCommand = TimePoint;
	 //qDebug() << "DERIVATIVE SET COORD PERIOD - " << StepPeriod*1000 << " ms " << StepPeriod << "s";

	 INPUT_COORD = Coord;
	 StepPeriod = 0.0025;
	 DerivativeCoord = (INPUT_COORD - PreviousCoord)/StepPeriod;
	 PreviousCoord = INPUT_COORD;

     if (flag_smoothe)
     {
		 Buffer.erase(Buffer.begin()); Buffer.push_back(DerivativeCoord);
		 DerivativeCoord.first = 0; DerivativeCoord.second = 0;
		 for(auto Coord: Buffer) DerivativeCoord = DerivativeCoord + Coord;   DerivativeCoord = DerivativeCoord/Buffer.size();
     }



    InputSeriesesDisp[0].push_back(DerivativeCoord.first);  InputSeriesesDisp[1].push_back(DerivativeCoord.second);
	InputSerieses[0].push_back(DerivativeCoord.first);  InputSerieses[1].push_back(DerivativeCoord.second);

    if(FILTER_ENABLED) {DerivativeCoord >> AmplitudeNormalization.direct() >>  DerivativeCoord;  emit SendCoordToPerform(DerivativeCoord);};


        if(InputSeriesesDisp.size() > INPUT_SIZE)
		for(auto& Series: InputSeriesesDisp)
			Series.erase(Series.begin());

        if(InputSerieses.size() > INPUT_SIZE)
		for(auto& Series: InputSerieses)
			Series.erase(Series.begin());
}

void SinusFilter::SlotSetCoord(QPair<double,double> Coord) {SetCoord(Coord);};
void Derivative::SlotGetOutputCoord(QPair<double,double> Coord)
{
  //qDebug() << "SLOT GET COORD FROM FILTER";
  Coord >> AmplitudeNormalization.inverse() >> Coord;
  InputSeriesesFiltered[0].push_back(DerivativeCoord.first);  InputSeriesesFiltered[1].push_back(DerivativeCoord.second);

    if(InputSeriesesFiltered.size() > INPUT_SIZE)
    { 
		for(auto& Series: InputSeriesesFiltered)
			Series.erase(Series.begin());
    }
}


Derivative::~Derivative()
{

	QObject::disconnect(this, SIGNAL(SendCoordToPerform(QPair<double,double>)),filter,SLOT(SlotSetCoord(QPair<double,double>)));
	QObject::disconnect(filter,SIGNAL(SignalOutputCoord(QPair<double,double>)),this,SLOT(SlotGetOutputCoord(QPair<double,double>)));
	filter->deleteLater();
	thread_to_filter->deleteLater();
}
Derivative::Derivative() : QObject()
{
qRegisterMetaType<QPair<double,double>>("QPair<double,double>");
Buffer.assign(5,QPair<double,double>(0,0));
InputSerieses.resize(2);
InputSeriesesDisp.resize(2);
InputSeriesesFiltered.resize(2);

filter = new SinusFilter; filter->InitFilter(INPUT_SIZE);
thread_to_filter = new QThread;
filter->moveToThread(thread_to_filter);
thread_to_filter->start(QThread::HighPriority);

QObject::connect(this, SIGNAL(SendCoordToPerform(QPair<double,double>)),filter,SLOT(SlotSetCoord(QPair<double,double>)),Qt::QueuedConnection);
QObject::connect(filter,SIGNAL(SignalOutputCoord(QPair<double,double>)),this,SLOT(SlotGetOutputCoord(QPair<double,double>)),Qt::QueuedConnection);
};


QPair<double,double> Derivative::GetCoord()
{
    if(FILTER_ENABLED && InputSeriesesFiltered[0].size() > 1)
    return QPair<double,double>(InputSeriesesFiltered[0].back(),InputSeriesesFiltered[1].back());

    return INPUT_COORD;
}

void ONNXSession::InitONNXSession(int input_size, int batch_size)
{
    qDebug() << "================================";
    qDebug() << "ONNX SESSION INIT";
    SessionInit = true;
    INPUT_VECTOR_SIZE = input_size;
    BATCH_SIZE = batch_size;

    //const auto& api = Ort::GetApi();

    session_options.SetIntraOpNumThreads(2);
    session_options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_EXTENDED);
    session_options.SetExecutionMode(ORT_PARALLEL);
    //session_options.AppendExecutionProvider_CUDA(cuda_opt); cuda_opt.device_id = 0;
    session = Ort::Session(env, modelPath, session_options);



    auto providers = Ort::GetAvailableProviders();
    for(std::string& provider: providers) qDebug() << "AVAILABLE PROVIDER  - " << QString::fromStdString(provider);


    // print number of model input nodes
    size_t num_input_nodes = session.GetInputCount();

    // iterate over all input nodes
    for (int i = 0; i < num_input_nodes; i++)
    {
        // print input node names
        char* input_name = session.GetInputName(i, allocator);  qDebug() << QString("Input %1 : name=%2 ").arg(i).arg(input_name);
        input_node_names.push_back(input_name);

        // print input node types
        Ort::TypeInfo type_info = session.GetInputTypeInfo(i); auto tensor_info = type_info.GetTensorTypeAndShapeInfo();

        ONNXTensorElementDataType type = tensor_info.GetElementType();
        qDebug() << QString("Input %1 : type=%2 :name=%3 ").arg(i).arg(type).arg(tensor_type_names[type].c_str());

        // print input shapes/dims
        input_node_dims = tensor_info.GetShape(); qDebug() << QString("Input %1 : num_dims=%2 ").arg(i).arg(input_node_dims.size());

        for (size_t j = 0; j < input_node_dims.size(); j++) qDebug() << QString("Input %1 : dim %2 = %3").arg(i).arg(j).arg(input_node_dims[j]);

    }

    input_node_dims[0] = INPUT_VECTOR_SIZE;
    input_node_dims[1] = BATCH_SIZE;
    input_node_dims[2] = 1;
    input_tensor_size = INPUT_VECTOR_SIZE * BATCH_SIZE * 1;   // use OrtGetTensorShapeElementCount() to get official size!
    qDebug() << "================================";
}

void SinusFilter::SetInput(vector<vector<float>> Serieses)
{
    //qDebug() << "SINUS FILTER SET INPUT SIZE - " << Serieses[0].size();
    InputSerieses = Serieses;
    auto& input_tensor_size = ProcessSession.input_tensor_size;
    auto& dims = ProcessSession.input_node_dims;
    auto memory_info = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);

    InputTensors[0] = (Ort::Value::CreateTensor<float>(memory_info, InputSerieses[0].data(), input_tensor_size, dims.data(), dims.size()));
    InputTensors[1] = (Ort::Value::CreateTensor<float>(memory_info, InputSerieses[1].data(), input_tensor_size, dims.data(), dims.size()));

    
    double value = 0;
    float* floatarr = OutputTensors[0][0].GetTensorMutableData<float>(); value = floatarr[INPUT_SIZE - 1];
    if(OutputSerieses[0].size() >= INPUT_SIZE) {OutputSerieses[0].push_back(value); OutputSerieses[0].erase(OutputSerieses[0].begin());};
    floatarr = OutputTensors[1][0].GetTensorMutableData<float>();  value = floatarr[INPUT_SIZE - 1];
    if(OutputSerieses[1].size() >= INPUT_SIZE) {OutputSerieses[1].push_back(floatarr[INPUT_SIZE-1]); OutputSerieses[1].erase(OutputSerieses[1].begin());};
}

void SinusFilter::SetCoord(QPair<double,double> Coord)
{

    //qDebug() << "SINUS FILTER THREAD - " << this->thread();
    InputSerieses[0].push_back(Coord.first);
    InputSerieses[1].push_back(Coord.second);
    if (InputSerieses[0].size() < INPUT_SIZE) return;

    InputSerieses[0].erase(InputSerieses[0].begin());
    InputSerieses[1].erase(InputSerieses[1].begin());

    auto& input_tensor_size = ProcessSession.input_tensor_size;
    auto& dims = ProcessSession.input_node_dims;
    auto memory_info = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);

    try
    {
    InputTensors[0] = (Ort::Value::CreateTensor<float>(memory_info, InputSerieses[0].data(), input_tensor_size, dims.data(), dims.size()));
    InputTensors[1] = (Ort::Value::CreateTensor<float>(memory_info, InputSerieses[1].data(), input_tensor_size, dims.data(), dims.size()));

    OutputTensors[0] = ProcessSession.Process(InputTensors[0]);
    OutputTensors[1] = ProcessSession.Process(InputTensors[1]);
    }
	catch (const Ort::Exception& exception)
    {
        qDebug() << "ERROR RUN - :" << exception.what() << " " << exception.GetOrtErrorCode() << endl;
    }


    mutex_coord_access.lock();
    double value = 0;
    if (OutputSerieses[0].size() < INPUT_SIZE)
    {
		float* floatarr = OutputTensors[0][0].GetTensorMutableData<float>(); 
		for (int n = 0; n < INPUT_SIZE; n++) { value = floatarr[n]; OutputSerieses[0].push_back(value);};

			   floatarr = OutputTensors[1][0].GetTensorMutableData<float>(); 
		for(int n = 0; n < INPUT_SIZE; n++) { value = floatarr[n]; OutputSerieses[1].push_back(value);};
    }

    if (OutputSerieses[0].size() >= INPUT_SIZE)
    {
		float* floatarr = OutputTensors[0][0].GetTensorMutableData<float>(); value = floatarr[INPUT_SIZE-1];
		OutputSerieses[0].push_back(value); OutputSerieses[0].erase(OutputSerieses[0].begin());

		floatarr = OutputTensors[1][0].GetTensorMutableData<float>(); value = floatarr[INPUT_SIZE-1];
		OutputSerieses[1].push_back(value); OutputSerieses[1].erase(OutputSerieses[1].begin());
    }
    mutex_coord_access.unlock();

    emit SignalOutputCoord(QPair<double,double>(OutputSerieses[0].back(),OutputSerieses[1].back()));
}


QPair<double, double> SinusFilter::GetCoord()
{
    auto coord = QPair<double, double>(0,0);

    mutex_coord_access.lock();
    if (OutputSerieses[0].size() >= INPUT_SIZE)
         coord = QPair<double, double>(OutputSerieses[0].back(), OutputSerieses[1].back());
    mutex_coord_access.unlock();

    return coord;
}

vector<Ort::Value> ONNXSession::Process(const Ort::Value& InputTensor)
{
    const char* output_node_name = session.GetOutputName(0,allocator);
    const char* input_node_name = session.GetInputName(0,allocator);

    auto output = session.Run(runOptions, &input_node_name, &InputTensor, 1, &output_node_name, 1);
    return output;


}
//void InitFilter(int size);







void SinusFilter::InitFilter(int size)
{
	qDebug() << "INIT SINUS FILTER" << size;
    INPUT_SIZE = size;
	InputSerieses.push_back(vector<float>());
	InputSerieses.push_back(vector<float>());
	OutputSerieses.push_back(vector<double>());
	OutputSerieses.push_back(vector<double>());
    InputTensors.push_back(Ort::Value(nullptr));
    InputTensors.push_back(Ort::Value(nullptr));
    OutputTensors.resize(2);

    //this->InputSerieses[0].assign(size,0);
    //this->InputSerieses[1].assign(size,0);

    //this->OutputSerieses[0].assign(size,0);
    //this->OutputSerieses[1].assign(size,0);

	if(!ProcessSession.SessionInit) ProcessSession.InitONNXSession(size,1);
}

SignalNormalization& SignalNormalization::direct()
{
    this->is_inverse = false; return *this;
}

SignalNormalization& SignalNormalization::inverse()
{
    this->is_inverse = true; return *this;
}

SignalNormalization& operator>>(SignalNormalization& normalization, vector<vector<double>>& Serieses)
{
    double first, second;
    for (int n = 0; n < normalization.INPUT_SIZE; n++)
    {
        first = (*normalization.input_serieses)[0][n];
        second = (*normalization.input_serieses)[1][n];
      
		if (normalization.is_inverse)
		{
			Serieses[0].push_back(normalization.MAX_FIRST*first/normalization.OUTPUT_AMPLITUDE); 
            Serieses[1].push_back(normalization.MAX_SECOND*second/normalization.OUTPUT_AMPLITUDE);

			if (Serieses[0].size() > normalization.INPUT_SIZE) Serieses[0].erase(Serieses[0].begin());
			if (Serieses[1].size() > normalization.INPUT_SIZE) Serieses[1].erase(Serieses[1].begin());
		}

		if (!normalization.is_inverse)
		{
			Serieses[0].push_back(normalization.OUTPUT_AMPLITUDE*first/normalization.MAX_FIRST); 
            Serieses[1].push_back(normalization.OUTPUT_AMPLITUDE*second/normalization.MAX_SECOND);

			if (Serieses[0].size() > normalization.INPUT_SIZE) Serieses[0].erase(Serieses[0].begin());
			if (Serieses[1].size() > normalization.INPUT_SIZE) Serieses[1].erase(Serieses[1].begin());
		}
    }
    return normalization;
}

SignalNormalization& operator>>(vector<vector<double>>& Serieses, SignalNormalization& normalization)
{
    normalization.input_serieses = &Serieses;
    return normalization;
}
void SignalNormalization::SetCoord(double first, double second)
{
    if (is_inverse)
    {
		SeriesFirstInverse.push_back(first/OUTPUT_AMPLITUDE); SeriesSecondInverse.push_back(second/OUTPUT_AMPLITUDE);
		SeriesFirstInverse.erase(SeriesFirstInverse.begin()); SeriesSecondInverse.erase(SeriesSecondInverse.begin());
        return;
    }

    if (first > MAX_FIRST) MAX_FIRST = first;
    if (second > MAX_SECOND) MAX_SECOND = second;

    SeriesFirst.push_back(first/MAX_FIRST); SeriesSecond.push_back(second/MAX_SECOND);
    SeriesFirst.erase(SeriesFirst.begin()); SeriesSecond.erase(SeriesSecond.begin());
}

void SignalNormalization::SetCoord(QPair<double, double> Coord)
{
    SetCoord(Coord.first, Coord.second);
}
QPair<double, double> SignalNormalization::GetCoord()
{
    auto output = QPair<double, double>(SeriesFirst.back() * OUTPUT_AMPLITUDE, SeriesSecond.back() * OUTPUT_AMPLITUDE);
    if (is_inverse) output = QPair<double, double>(SeriesFirstInverse.back() * MAX_FIRST, SeriesSecondInverse.back() * MAX_SECOND);

    return output;
}

SignalNormalization::SignalNormalization()
{
	SeriesFirst.assign(INPUT_SIZE,0);
	SeriesSecond.assign(INPUT_SIZE,0);
	SeriesFirstInverse.assign(INPUT_SIZE,0);
	SeriesSecondInverse.assign(INPUT_SIZE,0);
}
SignalNormalization::SignalNormalization(SignalNormalization& copy)
{
 	 INPUT_SIZE = copy.INPUT_SIZE;
	 OUTPUT_AMPLITUDE = copy.OUTPUT_AMPLITUDE;
	 MAX_FIRST = copy.MAX_FIRST;
	 MAX_SECOND = copy.MAX_SECOND;
	 SeriesFirst = copy.SeriesFirst;
	 SeriesSecond = copy.SeriesFirst;
	 SeriesFirstInverse = copy.SeriesFirstInverse;
	 SeriesSecondInverse = copy.SeriesFirstInverse;
}
void KalmanFilterClass::EnableFiltering(bool FLAG)
{
  FILTER_ENABLED = FLAG;
  FilteredDerivative.FILTER_ENABLED = FLAG;
  FilteredDerivative.filter->FILTER_ENABLED = FLAG;
  DirectFilter->FILTER_ENABLED = FLAG;
}
