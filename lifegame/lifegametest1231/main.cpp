#include <QtGui/QGuiApplication>
#include "load.h"
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{                        
	QApplication app(argc, argv);                   
	Load *start = new Load();
	start->show();
	return app.exec();                            
	
}

