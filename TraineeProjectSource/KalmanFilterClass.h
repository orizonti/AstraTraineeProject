#pragma once

#include <iostream>
#include "DebugStream.h"
#include "PassTwoCoordClass.h"
#include <Eigen/Eigen>
#include <chrono>
#include <QDebug>
#include <onnxruntime_cxx_api.h>
#include <onnxruntime_c_api.h>
#include <QThread>
#include <QObject>
#include <QMutex>



#define FILTER_SIZE 20

class ONNXSession
{
public:
    ONNXSession() {qDebug() <<  "CREATE ONNX SESSION";};
    ~ONNXSession();
    int INPUT_VECTOR_SIZE = FILTER_SIZE;
    int BATCH_SIZE = 1;
	bool SessionInit = false;

    //const ORTCHAR_T* modelPath = "/home/spp/DEVELOPMENT/NN_MODELS/GRU_120_3_18F.onnx";
    const ORTCHAR_T* modelPath = "/home/broms/Yandex.Disk/PROJECTS/MATLAB_PROJECTS/GRU_120_3_18F.onnx";
    Ort::Env env = Ort::Env(ORT_LOGGING_LEVEL_FATAL, "example-model-explorer");
    Ort::RunOptions runOptions;
    Ort::SessionOptions session_options;
    Ort::Session session = Ort::Session(nullptr);
    Ort::AllocatorWithDefaultOptions allocator;
    OrtCUDAProviderOptions cuda_opt;
    std::vector<const char*> input_node_names;
    std::vector<int64_t> input_node_dims;
    size_t input_tensor_size;

    std::vector<Ort::Value> Process(const Ort::Value& InputTensor);

    void InitONNXSession(int input_size, int batch_size);
};

class SignalNormalization : public PassTwoCoordClass
{
public:
	SignalNormalization();
	SignalNormalization(SignalNormalization& copy);
	int INPUT_SIZE = FILTER_SIZE;
	int OUTPUT_AMPLITUDE = 16;
	double MAX_FIRST = 1;
	double MAX_SECOND = 1;
	std::vector<double> SeriesFirst;
	std::vector<double> SeriesSecond;
	std::vector<double> SeriesFirstInverse;
	std::vector<double> SeriesSecondInverse;

	bool is_inverse = false;
	SignalNormalization& inverse();
	SignalNormalization& direct();

	void SetCoord(QPair<double, double> Coord);
	void SetCoord(double first, double second);
	QPair<double, double> GetCoord();

	std::vector<std::vector<double>>* input_serieses;

	friend SignalNormalization& operator>>(std::vector<std::vector<double>>& Serieses, SignalNormalization& normalization);
	friend SignalNormalization& operator>>(SignalNormalization& normalization, std::vector<std::vector<double>>& Serieses);

};

class SinusFilter : public QObject, public PassTwoCoordClass
{
	Q_OBJECT
public:

    int INPUT_SIZE;
    static ONNXSession ProcessSession;
    bool FILTER_ENABLED = false;

    QMutex mutex_coord_access;
    void SetInput(std::vector<std::vector<float>> InputSerieses);
    void SetCoord(QPair<double,double> Coord);

	QPair<double, double> GetCoord();

    std::vector<std::vector<float>> InputSerieses;
    std::vector<std::vector<double>> OutputSerieses;

    std::vector<Ort::Value> InputTensors;
    std::vector<std::vector<Ort::Value>> OutputTensors;
	void InitFilter(int size);
public slots:
	void SlotSetCoord(QPair<double,double> Coord);

signals:
	void SignalOutputCoord(QPair<double,double>);
};

class Derivative : public QObject, public PassTwoCoordClass
{
Q_OBJECT
public:
	Derivative();
	~Derivative();
	bool flag_smoothe = true;
	QThread* thread_to_filter;
	bool FILTER_ENABLED = false;
	QPair<double,double> INPUT_COORD;

	int INPUT_SIZE = FILTER_SIZE;
	void SetCoord(QPair<double,double> Coord);
	QPair<double,double> GetCoord();

	double max_first = 1;
    double max_second = 1;
	SignalNormalization AmplitudeNormalization;

    QPair<double,double> PreviousCoord = QPair<double,double>(0,0);
    QPair<double,double> DerivativeCoord = QPair<double,double>(0,0);

	std::vector<std::vector<float>> InputSerieses;

    std::vector<std::vector<qreal>> InputSeriesesFiltered;
	std::vector<std::vector<qreal>> InputSeriesesDisp;

	SinusFilter* filter;


    std::chrono::time_point<std::chrono::high_resolution_clock> TimeFromLastCommand;
    double Tp = 0.002;
    std::vector<QPair<double,double>> Buffer;

public slots:
	void SlotGetOutputCoord(QPair<double,double> Coord);
signals:
	void SendCoordToPerform(QPair<double,double>);
};


class KalmanFilterClass :public QObject,public PassTwoCoordClass
{
    Q_OBJECT
public:
	KalmanFilterClass();

	int StateDimension = 2;
	int INPUT_SIZE = FILTER_SIZE;
	QPair<double,double> INPUT_COORD;
	bool FILTER_ENABLED = false;

	SignalNormalization AmplitudeNormalization;

	SinusFilter* DirectFilter;
	QThread* thread_to_direct_filter;
	Derivative FilteredDerivative;

	Eigen::Matrix<float, 2, 1> FilterCoord(Eigen::Matrix<float, 2, 1> MeasureVec);

	void LoadInitSerieses(std::vector<double> series, std::vector<double> series2);

	void SetCoord(QPair<double, double> Coord);
    void SetControlErrorVariance(float X_V, float Y_V);
	void AppendOutputToStore(QPair<double,double> coord);
	void AppendOutputToStore(float first, float second);
	QPair<double,double> GetCoord();

	QPair<double, double> LastStepToEngine;


	QPair<double, double> GetVelocityEstimate();
	QPair<double, double> GetExtrapolateStep();
    	
	std::chrono::time_point<std::chrono::high_resolution_clock> TimeFromLastCommand;

	float Tp = 0.0025;
	float COV_MEASURE = 0.3;
	float COV_CONTROL = 0;


	Eigen::Matrix< float, 2, 2 > F1;   //model dinamic x = x-1*F1 + v*B
	Eigen::Matrix< float, 2, 2 > F1T;
	Eigen::Matrix< float, 2, 2 > B1;   //control matrix = Tp

	Eigen::Matrix< float, 2, 2 > H1;   //measure matrix measure = real H = 1
	Eigen::Matrix< float, 2, 2 > H1T;

	Eigen::Matrix< float, 2, 2 > MeasureNoizeCov; // measure noize covariance
	Eigen::Matrix< float, 2, 2 > ControlNoizeCov; // process noize cov

	Eigen::Matrix< float, 2, 2 > ExtrapolateStateCov; // Extrapolate vector error covariance
	Eigen::Matrix< float, 2, 2 > KalmanErrorCov; // kalman error covariance


	Eigen::Matrix< float, 2, 1 > ControlVek; // velocity
	Eigen::Matrix< float, 2, 1 > EstimateState;
	Eigen::Matrix< float, 2, 1 > ExtrapolateState;
	Eigen::Matrix< float, 2, 1 > MeasureVec; //Measures
	Eigen::Matrix< float, 2, 1 > PredictStateError;
	Eigen::Matrix< float, 2, 1 > MeasureVecError; //Measures

	Eigen::Matrix< float, 2, 2 > KK; //kalman koeff
	Eigen::Matrix< float, 2, 2 > I;  //unit matrix 1 1

	std::vector<std::vector<double>> OutputSerieses;


	void SetControlErrorVariance(float variance);
	void SetMeasureErrorVariance(float variance);

	void Initialaize();
	void SetInterval(float Interval);
	void SetControlVec(Eigen::Matrix< float, 2, 1 > Control);
	void SetControlVec(double velx, double vely);
    void SetControlVec(QPair<double,double> ControlVec);
    void EnableFiltering(bool FLAG);

	friend PassTwoCoordClass& operator >>(QPair<double, double> Coord, PassTwoCoordClass& Reciever);
	friend PassTwoCoordClass& operator >>(PassTwoCoordClass& Sender, PassTwoCoordClass& Reciever);
	friend PassTwoCoordClass& operator >> (PassTwoCoordClass& Sender, QPair<double, double>& Coord);


signals:
void SendCoordToPerform(QPair<double,double> Coord);

};
