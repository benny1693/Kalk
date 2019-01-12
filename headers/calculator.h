#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "button.h"
#include "buttonop.h"
#include "controller.h"

#include <QAction>
#include <QFile>
#include <QFileDialog>
#include <QGridLayout>
#include <QLineEdit>
#include <QMenuBar>
#include <QMessageBox>
#include <QScrollBar>
#include <QTextEdit>
#include <QTextStream>
#include <QWidget>
#include <sstream>

class Controller;

class Calculator : public QWidget {
	Q_OBJECT
private:
	Controller *controller;

	QLineEdit *firstOperand;
	QLineEdit *secondOperand;
	QTextEdit *result;

	Button *digitButtons[10];
	Button *pointButton;
	Button *commaButton;
	Button *semicolonButton;
	Button *clearButton;

	ButtonOp *plusButton;
	ButtonOp *minusButton;
	ButtonOp *timesButton;
	ButtonOp *projButton;
	ButtonOp *determinantButton;
	ButtonOp *inverseButton;
	ButtonOp *transposeButton;
	ButtonOp *gaussButton;
	ButtonOp *equiNumButton;

	void connectOpButtons();

	void addMenu(QGridLayout *);
	void addScreens(QGridLayout *);
	void addButtons(QGridLayout *);

private slots:
	void digitClicked();
	void clearClicked();
	void save();
	void help();

public:
	Calculator(QWidget * = 0, Controller * = 0);
	~Calculator();
	void resultOperation(const QString &, const QString &);
	void warning(const QString &, const QString &);
	QString getFirstOperand() const;
	QString getSecondOperand() const;
	QString getResult() const;
	std::regex getRegExp() const;
	void setController(Controller *);
};

#endif // CALCULATOR_H
