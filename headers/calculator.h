#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "button.h"
#include "buttonop.h"
#include "controller.h"

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QScrollBar>
#include <QTextStream>
#include <QMessageBox>
#include <sstream>

class Controller;

class Calculator : public QWidget{
    Q_OBJECT
private:
    Controller* controller;

    Button* createButton(const QString&, const char*);
    ButtonOp* createButtonOp(const QString&, const char*);
    QLineEdit* firstOperand;
    QLineEdit* secondOperand;
    QTextEdit* result;

    Button* digitButtons[10];
    static std::regex rx;

    void addMenu(QGridLayout*);
    void addScreens(QGridLayout*);
    void addButtons(QGridLayout*);

private slots:
    void digitClicked();
    void clearClicked();
    void save();
    void help();

public:
    Calculator(QWidget* =0);
		~Calculator();
    void resultOperation(const QString&, const QString&);
    void warning(const QString&, const QString&);
    QString getFirstOperand() const;
    QString getSecondOperand() const;
    QString getResult() const;
    std::regex getRegExp() const;
};

#endif // CALCULATOR_H
