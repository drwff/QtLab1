#include "Filter.h"
#include "Filter.h"
template <class T>
T clamp(T v, int max, int min)
{
	if (v > max) return max;
	else if (v < min) return min;
	return v;
}
QImage Invert_filter::calculateNewImagePixMap(const QImage &photo, int radius)
{
	QImage result_Image(photo);
	for (int x=0; x<photo.width();x++)
		for (int y = 0; y < photo.height(); y++)
		{
			QColor photo_color = photo.pixelColor(x, y);
			photo_color.setRgb(255 - photo_color.red(),
				               255 - photo_color.green(),
				               255 - photo_color.blue());
			result_Image.setPixelColor(x, y, photo_color);
		}
	return result_Image;
}
QImage Matrix_filter::calculateNewImagePixMap(const QImage & photo, int radius)
{
	QImage result_Image(photo);
	for (int x = 0; x < photo.width(); x++) {
		for (int y = 0; y < photo.height(); y++)
		{
			QColor photo_color = calculateNewPixelColor(photo, x, y, radius);

			result_Image.setPixelColor(x, y, photo_color);
		}
	}
	return result_Image;
}
QColor Matrix_filter::calculateNewPixelColor(QImage photo, int x, int y, int radius)
{
	int returnR = 0;
	int returnG = 0;
	int returnB = 0;
	int size = 2 * radius + 1;
	for (int i = -radius; i <= radius; i++)
	{
		for (int j = -radius; j <= radius; j++)
		{
			int idx = (i + radius)*size + j + radius;
			QColor color = photo.pixelColor(clamp <int>(x + j, photo.width() - 1, 0), clamp<int>(y + i, photo.height() - 1, 0));
			returnR += color.red()*vector[idx];
			returnG += color.green()*vector[idx];
			returnB += color.blue()*vector[idx];
		}
	}
	return QColor(clamp(returnR, 255, 0), clamp(returnG, 255, 0), clamp(returnB, 255, 0));
}

void Gaussian_blur_filter::createGaussianVector(int radius, int sigma)
{
	mRadius = radius;
	const unsigned int size = 2 * mRadius + 1;
	float norm = 0;
	vector = new float[size*size];
	for (int i = -mRadius; i <= mRadius; i++)
	{
		for (int j = -mRadius; j <= mRadius; j++)
		{
			int idx = (i + mRadius)*size + j + mRadius;
			vector[idx] = exp(-(i * i + j * j) / (sigma * sigma));
			norm += vector[idx];
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			vector[i*size + j] /= norm;
		}
	}
}

QImage GrayScaleFilter::calculateNewImagePixMap(const QImage & photo, int radius)
{
	QImage result_Image(photo);
	for (int x = 0; x < photo.width(); x++)
		for (int y = 0; y < photo.height(); y++)
		{
			QColor photo_color = photo.pixelColor(x, y);
			int R = photo_color.red();
			int G = photo_color.green();
			int B = photo_color.blue();
			float intensive = 0.36*R + 0.53*G + 0.11*B;
			photo_color.setRgb(intensive, intensive, intensive);
			result_Image.setPixelColor(x, y, photo_color);
		}
	return result_Image;
}

QImage Sepi::calculateNewImagePixMap(const QImage & photo, int radius)
{
	int k = 5;
	QImage result_Image(photo);
	for (int x = 0; x < photo.width(); x++)
		for (int y = 0; y < photo.height(); y++)
		{
			QColor photo_color = photo.pixelColor(x, y);
			float R = photo_color.red();
			float G = photo_color.green();
			float B = photo_color.blue();
			float intensive = 0.36*R + 0.53*G + 0.11*B;
			R = intensive + 2 * k;
			G = intensive + 0,5 * k;
			B = intensive -1 * k;
			photo_color.setRgb(clamp(R,255,0), clamp(G, 255, 0),clamp(B, 255, 0));
			result_Image.setPixelColor(x, y, photo_color);
		}
	return result_Image;
}

QImage Shine::calculateNewImagePixMap(const QImage & photo, int radius)
{
	int k =125;
	QImage result_Image(photo);
	for (int x = 0; x < photo.width(); x++)
		for (int y = 0; y < photo.height(); y++)
		{
			QColor photo_color = photo.pixelColor(x, y);
			float R = photo_color.red() + k;
			float G = photo_color.green() + k;
			float B = photo_color.blue() + k;
			photo_color.setRgb(clamp(R, 255, 0), clamp(G, 255, 0), clamp(B, 255, 0));
			result_Image.setPixelColor(x, y, photo_color);
		}
	return result_Image;
}

QImage Tisnenie::calculateNewImagePixMap(const QImage & photo)
{
	QImage result_Image(photo);
	for (int x = 0; x < photo.width(); x++) {
		for (int y = 0; y < photo.height(); y++)
		{
			QColor photo_color = calculateNewPixelColor(photo, x, y);

			result_Image.setPixelColor(x, y, photo_color);
		}
	}
	return result_Image;
}

QColor Tisnenie::calculateNewPixelColor(QImage photo, int x, int y)
{
	int returnR = 0;
	int returnG = 0;
	int returnB = 0;
	int size = 3;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			int idx = (i + 1)*size + j + 1;
			QColor color = photo.pixelColor(clamp <int>(x + j, photo.width() - 1, 0), clamp<int>(y + i, photo.height() - 1, 0));
			returnR += color.red()*vector[idx];
			returnG += color.green()*vector[idx];
			returnB += color.blue()*vector[idx];
		}
	}
	int res = returnR + returnG + returnB + 40;
	return QColor(clamp(res, 255, 0), clamp(res, 255, 0), clamp(res, 255, 0));
}

QImage PerenosPovorot::move(const QImage & photo, int delta)
{
	QImage result_Image(photo.width()+delta,photo.height(),QImage::Format_RGB32);
	for (int x = 0; x < photo.width(); x++)
		for (int y = 0; y < photo.height(); y++)
		{
			QColor photo_color = photo.pixelColor(x, y);
			int newx = x + delta;
			int newy = y;
			result_Image.setPixelColor(newx, newy, photo_color);
		}
	return result_Image;
}

QImage PerenosPovorot::turn(const QImage & photo, int gradus)
{
	float PI = 3.14159265359;
	QImage result_Image(photo.width(), photo.height(), QImage::Format_RGB32);
	int x0 = photo.width() / 2;
	int y0 = photo.height() / 2;
	int s = sin(gradus*PI / 180);
	int c = cos(gradus*PI / 180);
	for (int x = 0; x < photo.width(); x++)
		for (int y = 0; y < photo.height(); y++)
		{
			QColor photo_color = photo.pixelColor(x, y);
			int newx = (x - x0)*c - (y - y0)*s + x0;
			int newy = (x - x0)*s + (y - y0)*c + y0;
			result_Image.setPixelColor(clamp(newx, photo.width()-1,0), clamp(newy, photo.height()-1, 0), photo_color);
		}
	return result_Image;
}

QImage Volni::calculateNewImagePixMap(const QImage & photo,int radius)
{
	float PI = 3.14159265359;
	QImage result_Image(photo.width(), photo.height(), QImage::Format_RGB32);
	for (int x = 0; x < photo.width(); x++)
		for (int y = 0; y < photo.height(); y++)
		{
			QColor photo_color = photo.pixelColor(x, y);
			int newx = x + 20 * sin(2 * PI*y / 60);
			int newy = y;
			result_Image.setPixelColor(clamp(newx, photo.width() - 1, 0), newy, photo_color);
		}
	return result_Image;
}

QImage Median::calculateNewImagePixMap(const QImage & photo, int radius)
{
	QImage result_Image(photo);
	for (int x = 0; x < photo.width(); x++) {
		for (int y = 0; y < photo.height(); y++)
		{
			QColor photo_color = calculateNewPixelColor(photo, x, y, radius);

			result_Image.setPixelColor(x, y, photo_color);
		}
	}
	return result_Image;
}

QColor Median::calculateNewPixelColor(QImage photo, int x, int y,int radius)
{
	int size = 2 * radius + 1;
	int v1[49];
	int v2[49];
	int v3[49];
	for (int i = -radius; i <= radius; i++)
	{
		for (int j = -radius; j <= radius; j++)
		{
			int idx = (i + radius)*size + j + radius;
			QColor color = photo.pixelColor(clamp <int>(x + j, photo.width() - 1, 0), clamp<int>(y + i, photo.height() - 1, 0));
			v1[idx]=color.red();
			v2[idx]=color.green();
			v3[idx]=color.blue();
		}
	}
	std::sort(v1, v1 + size * size);
	std::sort(v2, v2 + size * size);
	std::sort(v3, v3 + size * size);
	return QColor(v1[(size*size)/2], v2[(size*size) / 2], v3[(size*size) / 2]);
}

QImage Linrast::calculateNewImagePixMap(const QImage & photo, int radius)
{
	QImage result_Image(photo.width(), photo.height(), QImage::Format_RGB32);
	int Rm = 255;
	int Gm = 255;
	int Bm = 255;
	int GM = 0;
	int BM = 0;
	int RM = 0;
	for (int x = 0; x < photo.width(); x++)
		for (int y = 0; y < photo.height(); y++)
		{
			QColor color = photo.pixelColor(x, y);
			if (color.red() < Rm)
			{
				Rm = color.red();
			}
			if (color.green() < Gm)
			{
				Gm = color.green();
			}
			if (color.blue() < Bm)
			{
				Bm = color.blue();
			}
			if (color.red() > RM)
			{
				RM = color.red();
			}
			if (color.green() > GM)
			{
				GM = color.green();
			}
			if (color.blue() > BM)
			{
				BM = color.blue();
			}
		}

	for (int x = 0; x < photo.width(); x++)
		for (int y = 0; y < photo.height(); y++)
		{
			QColor color = photo.pixelColor(x, y);
			int R_ = (color.red() - Rm) * 255 / (RM - Rm);
			int G_ = (color.green() - Gm) * 255 / (GM - Gm);
			int B_ = (color.blue() - Bm) * 255 / (BM - Bm);
			color.setRgb(clamp(R_, 255, 1), clamp(G_, 255, 1), clamp(B_, 255, 1));
			result_Image.setPixelColor(x,y,color);
		}
	return result_Image;
}

QImage Otrazenie::calculateNewImagePixMap(const QImage & photo, int radius)
{
	QImage result_Image(photo.width(), photo.height(), QImage::Format_RGB32);
	int GM = 0;
	int BM = 0;
	int RM = 0;
	for (int x = 0; x < photo.width(); x++)
		for (int y = 0; y < photo.height(); y++)
		{
			QColor color = photo.pixelColor(x, y);
			if (color.red() > RM)
			{
				RM = color.red();
			}
			if (color.green() > GM)
			{
				GM = color.green();
			}
			if (color.blue() > BM)
			{
				BM = color.blue();
			}
		}

	for (int x = 0; x < photo.width(); x++)
		for (int y = 0; y < photo.height(); y++)
		{
			QColor color = photo.pixelColor(x, y);
			int R_ = color.red()* 255 / RM;
			int G_ = color.green() * 255 / GM;
			int B_ = color.blue() * 255 / BM;
			color.setRgb(clamp(R_, 255, 1), clamp(G_, 255, 1), clamp(B_, 255, 1));
			result_Image.setPixelColor(x, y, color);
		}
	return result_Image;
}
