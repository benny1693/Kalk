#ifndef BUTTONOP_H
#define BUTTONOP_H

#include "button.h"

class ButtonOp : public Button{
    Q_OBJECT
public:
    ButtonOp(const QString &text, QWidget *parent = 0);
};

#endif // BUTTONOP_H
