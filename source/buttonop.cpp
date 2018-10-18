#include "../headers/buttonop.h"

ButtonOp::ButtonOp(const QString& text, QWidget* parent) : Button(text, parent){
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setText(text);
}
