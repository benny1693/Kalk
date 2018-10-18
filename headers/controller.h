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
    Controller(Calculator*);
    ~Controller();
};

#endif // CONTROLLER_H
