//—труктура, определ€юща€ кадр изображени€ с камеры
#pragma once
//#include <qpoint.h>
//#include <opencv2\core\core.hpp>


struct ImageStruct
{
	int x_size;
	int y_size;
	int X1 = 0;
	int Y1 = 0;
	int X2 = 0;
	int Y2 = 0;
	int X3 = 0;
	int Y3 = 0;
	int Y4 = 0;
	int X4 = 0;
	unsigned char* p_image = 0;
};
