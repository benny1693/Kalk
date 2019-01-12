#include "../headers/calculator.h"
#include "../headers/modello.h"
#include "../headers/controller.h"

#include <QApplication>
#include <string>
using namespace std;

int main(int argc, char *argv[]){
		QApplication a(argc, argv);

		Modello m;
		Controller controller;
		Calculator Kalk;

		controller.setModel(&m);
		controller.setView(&Kalk);

		Kalk.show();

		return a.exec();
}

