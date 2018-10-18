#include "../headers/calculator.h"
#include <QApplication>
#include <string>
using namespace std;

int main(int argc, char *argv[]){
		QApplication a(argc, argv);
		Calculator Kalk;

		Kalk.show();

		return a.exec();
}

