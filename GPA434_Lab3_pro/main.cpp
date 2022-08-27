#include "GPA434_Lab3_pro.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);

	QApplication a(argc, argv);
	GPA434_Lab3_pro w;
	w.show();
	return a.exec();
}
