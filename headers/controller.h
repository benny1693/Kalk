#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "modello.h"

#include <QObject>
#include <QString>
#include <sstream>
#include <regex>

class Calculator;
class Modello;

class Controller : public QObject{
    Q_OBJECT
private:
    Modello* model;
    Calculator* view;

		std::regex rx;

		bool checkOperand(const QString&) const;
    bool checkWarningOneOperand() const;
    bool checkWarningTwoOperand() const;
    std::string deleteSpace(std::string);

public slots:
    void plusClicked();
    void timesClicked();
    void minusClicked();

    void transposeClicked();
    void inverseClicked();
    void gaussClicked();
    void determinantClicked();
    void normaClicked();
    void projectionClicked();

public:
		Controller(Calculator* = 0, Modello* = 0);
    ~Controller();

		void setModel(Modello*);
		void setView(Calculator*);
		void setRegex(string);
};

#endif // CONTROLLER_H
