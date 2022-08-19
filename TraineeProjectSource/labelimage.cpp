#include "stdafx.h"
#include "labelimage.h"
#include "qevent.h"
#include "qdebug.h"

LabelImage::LabelImage(QWidget *parent)
	: QLabel(parent)
{
	
}

LabelImage::~LabelImage()
{
}

void LabelImage::mouseMoveEvent(QMouseEvent * ev)
{
	
	double x = ev->x();
	double y = ev->y();
	qDebug() << "POS MOVE - " << x << y;

	emit SignalMovePos(x,y);
	
}

void LabelImage::mousePressEvent(QMouseEvent * ev)
{
	
	X_Pressed = ev->x()*2;
	Y_Pressed = ev->y()*2;
	qDebug() << "POS PRESS - " << X_Pressed << Y_Pressed;

	emit SignalPressedPos(X_Pressed,Y_Pressed);
	
}


