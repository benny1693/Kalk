#include "../headers/calculator.h"
#include "../headers/menu.h"

std::regex Calculator::rx("([ \f\t\v]*[+|-]{0,1}[ \f\t\v]*([0-9]+[.][0-9]+|[0-9]+)[ \f\t\v]*(,|;)[ \f\t\v]*)*[ \f\t\v]*[+|-]{0,1}[ \f\t\v]*([0-9]+[.][0-9]+|[0-9]+)[ \f\t\v]*[;]{0,1}");

Calculator::Calculator(QWidget *parent) : QWidget(parent), controller(new Controller(this)){
    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    addMenu(mainLayout);
    addScreens(mainLayout);
    addButtons(mainLayout);

    setLayout(mainLayout);
    setWindowTitle(tr("Helu"));

    firstOperand->setFocus();

    QFile file(QString("../Kalk/qss/style.qss"));
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, "error", file.errorString());
    }else{
        QString styleSheet = QLatin1String(file.readAll());
        setStyleSheet(styleSheet);
    }

    help();
}

Calculator::~Calculator(){
    if(controller) delete controller;
    if(firstOperand) delete firstOperand;
    if(secondOperand) delete secondOperand;
    if(result) delete result;
}


/* SLOT ############################################################################################### */
void Calculator::digitClicked(){
    Button* clickedButton = qobject_cast<Button*>(sender());
    QString element = clickedButton->text();

    if(element == "Nuova riga") element = ";";

    if(firstOperand->hasFocus()){
        firstOperand->setText(firstOperand->text() + element);
    }else{
        secondOperand->setText(secondOperand->text() + element);
    }
}

void Calculator::clearClicked(){
    result->clear();
}

void Calculator::warning(const QString &nameApp, const QString &nameWarning){
    QMessageBox::warning(
        this,
        nameApp,
        nameWarning
    );
}

void Calculator::resultOperation(const QString& resPrint, const QString& e){
    QString equal = e;
    result->clear();
    result->setText(resPrint + equal);

    equal.remove(0, 3);
    equal.remove(equal.size()-1, 1);
    firstOperand->setText(equal);
    firstOperand->setFocus();
    secondOperand->clear();
    int bottom = result->verticalScrollBar()->maximum();
    result->verticalScrollBar()->setValue(bottom);
}

void Calculator::save(){
    QString nomeFile = QFileDialog::getSaveFileName(this, tr("Salva il File"), "",
                                                    tr("File di Testo (*.txt);;Word Document (*.docx)"));
		QFile file(nomeFile);

    if (file.open(QIODevice::ReadWrite)) {
        QTextStream out(&file);
        out << result->toPlainText();
        out.flush();
    }
}

void Calculator::help(){
    QFile file(QString("../Kalk/info.txt"));

    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, "error", file.errorString());
    }else{
        QTextStream in(&file);
        QString line;
        while(!in.atEnd()) {
            line += in.readLine() + "\n";
        }
        file.close();
        QMessageBox* help = new QMessageBox(QMessageBox::Information,
                    "Informazioni", line, QMessageBox::NoButton, this);
        help->setTextFormat(Qt::RichText);
        help->show();
    }
}

/* END SLOT ############################################################################################### */

void Calculator::addMenu(QGridLayout* mainLayout){
    QMenuBar* menuBar = new QMenuBar();
    QMenu *fileMenu = new QMenu(tr("File"), menuBar);
    QAction *help = new QAction(tr("Help"), menuBar);
    menuBar->addMenu(fileMenu);
    menuBar->addAction(help);
    QAction* save = new QAction(tr("Save"), fileMenu);
    connect(save, &QAction::triggered, this, &Calculator::save);
    connect(help, &QAction::triggered, this, &Calculator::help);
    save->setShortcuts(QKeySequence::Save);
    fileMenu->addAction(save);

    QVBoxLayout* menu = new QVBoxLayout();
    menu->addWidget(menuBar);
    mainLayout->addLayout(menu, 0, 0, 1, 7);
}

void Calculator::addScreens(QGridLayout* mainLayout){
    firstOperand = new QLineEdit();
    firstOperand->setPlaceholderText("Primo operando");

    secondOperand = new QLineEdit();
    secondOperand->setPlaceholderText("Secondo operando");

    int operandHeight = 40;
    firstOperand->setMinimumHeight(operandHeight);
    firstOperand->setTextMargins(10,0,0,0);
    secondOperand->setMinimumHeight(operandHeight);
    secondOperand->setTextMargins(10,0,0,0);

    result = new QTextEdit();
    result->setReadOnly(true);
    result->setMinimumHeight(200);

    QVBoxLayout *lay = new QVBoxLayout();
    lay->addWidget(result);

    mainLayout->addLayout(lay, 1, 0, 1, 8);
    mainLayout->addWidget(firstOperand, 2, 0, 1, 4);
    mainLayout->addWidget(secondOperand, 2, 5, 1, 4);
}

void Calculator::addButtons(QGridLayout* mainLayout){
    for (int i = 0; i < 10; ++i) {
        digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));
    }

    Button *pointButton = createButton(tr("."), SLOT(digitClicked()));
    Button *commaButton = createButton(tr(","), SLOT(digitClicked()));
    Button *semicolonButton = createButton(tr("Nuova riga"), SLOT(digitClicked()));
    Button *clearButton = createButton(tr("Clear"), SLOT(clearClicked()));

    ButtonOp *plusButton = createButtonOp(tr("+"), SLOT(plusClicked()));
    ButtonOp *minusButton = createButtonOp(tr("-"), SLOT(minusClicked()));
    ButtonOp *timesButton = createButtonOp(tr("\303\227"), SLOT(timesClicked()));
    ButtonOp *projButton = createButtonOp(tr("Proj"), SLOT(projectionClicked()));
    ButtonOp *determinantButton = createButtonOp(tr("Det"), SLOT(determinantClicked()));
    ButtonOp *inverseButton = createButtonOp(tr("Inv"), SLOT(inverseClicked()));
    ButtonOp *transposeButton = createButtonOp(tr("Trasp"), SLOT(transposeClicked()));
    ButtonOp *gaussButton = createButtonOp(tr("Gauss"), SLOT(gaussClicked()));
    gaussButton->setToolTip(tr("Trasformazione in forma di Gauss"));
    ButtonOp *equiNumButton = createButtonOp(tr("Norma"), SLOT(normaClicked()));


    for (int i = 1; i < 10; ++i) {
        int row = ((9 - i) / 3) + 3;
        int column = ((i - 1) % 3) + 1;
        mainLayout->addWidget(digitButtons[i], row, column);
    }

    mainLayout->addWidget(pointButton, 6, 1);
    mainLayout->addWidget(digitButtons[0], 6, 2);
    mainLayout->addWidget(commaButton, 6, 3);

    mainLayout->addWidget(plusButton, 4, 5);
    mainLayout->addWidget(minusButton, 5, 5);
    mainLayout->addWidget(timesButton, 6, 5);

    mainLayout->addWidget(projButton, 6, 7);
    mainLayout->addWidget(determinantButton, 5, 6);
    mainLayout->addWidget(gaussButton, 4, 7);
    mainLayout->addWidget(transposeButton, 4, 6);
    mainLayout->addWidget(inverseButton, 5, 7);
    mainLayout->addWidget(equiNumButton, 6, 6);
    mainLayout->addWidget(clearButton, 3, 7);
    mainLayout->addWidget(semicolonButton, 3, 5, 1, 2);
}

QString Calculator::getFirstOperand() const{
    return firstOperand->text();
}

QString Calculator::getSecondOperand() const{
    return secondOperand->text();
}

QString Calculator::getResult() const{
    return result->toPlainText();
}

std::regex Calculator::getRegExp() const{
    return rx;
}

Button* Calculator::createButton(const QString &text, const char *member){
    Button* button = new Button(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

ButtonOp* Calculator::createButtonOp(const QString &text, const char *member){
    ButtonOp* buttonOp = new ButtonOp(text);
    connect(buttonOp, SIGNAL(clicked()), controller, member);
    return buttonOp;
}
