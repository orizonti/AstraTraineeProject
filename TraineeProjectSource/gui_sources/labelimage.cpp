#include "CommonHeaders.h"
#include "labelimage.h"
#include "qevent.h"
#include "qdebug.h"

LabelImage::LabelImage(QWidget *parent)
	: AdjustableLabel(parent)
{
	
}

LabelImage::~LabelImage()
{
}

void LabelImage::mouseMoveEvent(QMouseEvent * ev)
{
	
	double x = ev->x();
	double y = ev->y();
	qInfo()<<"[LABEL   ]" << "POS MOVE - " << x << y;

	emit SignalMovePos(x,y);
	
}

void LabelImage::mousePressEvent(QMouseEvent * ev)
{
	
	X_Pressed = ev->x()*2;
	Y_Pressed = ev->y()*2;
	qInfo() <<"[LABEL    ]"<< "POS PRESS - " << X_Pressed << Y_Pressed;

	emit SignalPressedPos(X_Pressed,Y_Pressed);
	
}


