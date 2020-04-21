#pragma once
#include<QImage>
class Filter
{
public:
	Filter() {};
	~Filter() {};
	virtual QImage calculateNewImagePixMap(const QImage &photo, int radius) = 0;
};


class Invert_filter :public Filter
{
public:
	Invert_filter() {};
	~Invert_filter() {};
	QImage calculateNewImagePixMap(const QImage &photo, int radius);
};

class Matrix_filter :public Filter
{
public:
	float * vector;
	int mRadius;
	Matrix_filter(int radius = 1) :mRadius(radius) {};
	QImage calculateNewImagePixMap(const QImage &photo, int radius);
	QColor calculateNewPixelColor(QImage photo, int x, int y, int radius);
};

class Blur_filter :public Matrix_filter
{
public:
	Blur_filter()
	{
		int size = 2 * mRadius + 1;
		vector = new float[size*size];
		for (int i=0;i<size;i++)
			for (int j = 0; j < size; j++)
			{
				vector[i*size + j] = 1.0f / (size*size);
			}
	}
};

class Gaussian_blur_filter :public Matrix_filter
{
public:
	Gaussian_blur_filter() 
	{
		createGaussianVector(5, 2);
	}
	~Gaussian_blur_filter() {};
	void createGaussianVector(int radius, int sigma);
};

class GrayScaleFilter :public Filter
{
public:
	GrayScaleFilter() {};
	~GrayScaleFilter() {};
	QImage calculateNewImagePixMap(const QImage &photo, int radius);
};

class Sepi :public Filter
{
public:
	Sepi() {};
	~Sepi() {};
	QImage calculateNewImagePixMap(const QImage &photo, int radius);
};

class Shine :public Filter
{
public:
	Shine() {};
	~Shine() {};
	QImage calculateNewImagePixMap(const QImage &photo, int radius);
};

class Sobel :public Matrix_filter
{
public:
	Sobel()
	{
		vector = new float[9];
		vector[0] = -1;
		vector[1] = -2;
		vector[2] = -1;
		vector[3] = vector[4]= vector[5]=0;
		vector[6] = 1;
		vector[7] = 2;
		vector[8] = 1;
	}
};

class Rezkost :public Matrix_filter
{
public:
	Rezkost()
	{
		vector = new float[9];
		vector[0] = vector[2] = vector[6] = vector[8]=0;
		vector[1] = vector[3] = vector[5] = vector[7] = -1;
		vector[4] = 5;
	}
	Rezkost(int k)
	{
		vector = new float[9];
		vector[0] = vector[2] = vector[6] = vector[8] = -1;
		vector[1] = vector[3] = vector[5] = vector[7] = -1;
		vector[4] = 9;
	}
};

class Tisnenie :public Matrix_filter
{
public:
	Tisnenie()
	{
		vector = new float[9];
		vector[0] = vector[2] = vector[4] = vector[6] = vector[8]=0;
		vector[1] = vector[3] = 1.f/4;
		vector[5] = vector[7] = -1.f/4;
	}
	QImage calculateNewImagePixMap(const QImage &photo);
	QColor calculateNewPixelColor(QImage photo, int x, int y);
};

class PerenosPovorot:public Filter
{
public:
	QImage calculateNewImagePixMap(const QImage &photo, int radius) {
		QImage res(photo);
		return photo;
	}
	PerenosPovorot() {};
	~PerenosPovorot() {};
	QImage move(const QImage &photo, int delta);
	QImage turn(const QImage &photo, int gradus);
};

class Volni :public Filter
{
public:
	Volni() {};
	~Volni() {};
	QImage calculateNewImagePixMap(const QImage &photo,int radius);
};

class Median : public Matrix_filter
{
public:
	Median() {};
	~Median() {};
	QImage calculateNewImagePixMap(const QImage &photo,int radius);
	QColor calculateNewPixelColor(QImage photo, int x, int y,int radius);
 };

class Linrast : public Filter
{
public:
	Linrast() {};
	~Linrast() {};
	QImage calculateNewImagePixMap(const QImage &photo, int radius);
};

class Otrazenie : public Filter
{
public:
	Otrazenie() {};
	~Otrazenie() {};
	QImage calculateNewImagePixMap(const QImage &photo, int radius);
};
