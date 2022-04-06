#ifndef LABELIMAGE_H
#define LABELIMAGE_H


class LabelImage : public QLabel
{
	Q_OBJECT

public:
	LabelImage(QWidget *parent);
	~LabelImage();
	int X_Pressed = 0;
	int Y_Pressed = 0;

protected:
	void mousePressEvent(QMouseEvent * ev);
	void mouseMoveEvent(QMouseEvent * ev);
	


	

	


signals:
	void SignalPressedPos(int,int);
	void SignalMovePos(int,int);
	
};

#endif // LABELIMAGE_H
