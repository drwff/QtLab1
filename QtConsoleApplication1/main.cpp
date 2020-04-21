#include <QtCore/QCoreApplication>
#include<QImage>
#include <iostream>
#include "Filter.h"
using namespace std;
int main(int argc, char *argv[])
{
	string s;
	QImage photo;

	int radius;
	//cin >> radius;

	for (int i = 0; i < argc; i++)
	{
		if ((!strcmp(argv[i], "-p")) && (i + 1 < argc))
		{
			s = argv[i + 1];
		}
	}
	photo.load(QString(s.c_str()));
	photo.save("Starting.JPG");


	
	Invert_filter *invert = new Invert_filter();
	QImage invertImage = invert->calculateNewImagePixMap(photo, 0);
	invertImage.save("Invert.jpg");

	Blur_filter *blur = new Blur_filter();
	QImage BlurImage = blur->calculateNewImagePixMap(photo, 1);
	BlurImage.save("Blur.jpg");

	Gaussian_blur_filter *blur2 = new  Gaussian_blur_filter();
	QImage BlurImage2 = blur2->calculateNewImagePixMap(photo, 5);
	BlurImage2.save("Blur2.jpg");

	GrayScaleFilter *gray2 = new  GrayScaleFilter();
	QImage GrayImage2 = gray2->calculateNewImagePixMap(photo, 0);
	GrayImage2.save("WB.jpg");

	Sepi *sepi = new Sepi();
	QImage SepiImage =sepi->calculateNewImagePixMap(photo, 0);
	SepiImage.save("Sepi.jpg");

	Shine *shine = new Shine();
	QImage ShineImage = shine->calculateNewImagePixMap(photo, 0);
	ShineImage.save("Shine.jpg");

	Sobel *sob = new Sobel();
	QImage SobelImage = sob->calculateNewImagePixMap(photo, 1);
	SobelImage.save("Sobel.jpg");

	Rezkost *rez = new Rezkost();
	QImage RezImage = rez->calculateNewImagePixMap(photo, 1);
	RezImage.save("Rezkost.jpg");

	Tisnenie *tis = new Tisnenie();
	QImage TisImage = tis->calculateNewImagePixMap(photo);
	TisImage.save("Tisnenie.jpg");

	PerenosPovorot *p = new PerenosPovorot();
	QImage perenos = p->move(photo,100);
	perenos.save("Perenos.jpg");

	PerenosPovorot *pov = new PerenosPovorot();
	QImage povorot = pov->turn(photo, 180);
	povorot.save("Povorot.jpg");

	Volni *v = new Volni();
	QImage volni = v->calculateNewImagePixMap(photo, 0);
	volni.save("Volni.jpg");

	Rezkost *rez2 = new Rezkost(1);
	QImage RezImage2 = rez2->calculateNewImagePixMap(photo, 1);
	RezImage2.save("Rezkost2.jpg");

	Median *m = new Median();
	QImage MedImage = m->calculateNewImagePixMap(photo, 2);
	MedImage.save("Median.jpg");

	Linrast *l = new Linrast();
	QImage LinImage = l->calculateNewImagePixMap(photo, 0);
	LinImage.save("Linalrast.jpg");

	Otrazenie *o = new Otrazenie();
	QImage OtImage = o->calculateNewImagePixMap(photo, 0);
	OtImage.save("Otrazenie.jpg");
}
