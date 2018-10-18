#include "../headers/controller.h"
#include "../headers/calculator.h"

Controller::Controller(Calculator* c) : model(new Modello()), view(c){}

Controller::~Controller(){
    if(model) delete model;
}

bool Controller::checkOperand(const QString& operand) const{
    std::regex regx = view->getRegExp();
    return regex_match(operand.toStdString(), regx);
}

bool Controller::checkWarningOneOperand() const{
    bool sent = false;
    if((view->getFirstOperand() != "" && view->getSecondOperand() != "") ||
            (view->getFirstOperand() == "" && view->getSecondOperand() == "")){
        view->warning("Attenzione!", "Immettere un operando");
        sent = true;
    }else if(!checkOperand(view->getFirstOperand()) && !checkOperand(view->getSecondOperand())){
        view->warning("Attenzione!", "Sequenza caratteri non valida");
        sent = true;
    }

    return sent;
}

bool Controller::checkWarningTwoOperand() const{
    bool sent = false;
    if(view->getFirstOperand() == "" || view->getSecondOperand() == ""){
        view->warning("Attenzione!", "Immettere due operandi");
        sent = true;
    }else if(!checkOperand(view->getFirstOperand()) || !checkOperand(view->getSecondOperand())){
        view->warning("Attenzione!", "Sequenza caratteri non valida");
        sent = true;
    }

    return sent;
}

std::string Controller::deleteSpace(string s){
    std::regex temp("[ \f\t\v]");
    return std::regex_replace(s, temp, "");

}

void Controller::plusClicked(){
    if(!checkWarningTwoOperand()){
        QString equal = " = ";
        std::stringstream res;
        std::stringstream first(deleteSpace(view->getFirstOperand().toStdString()));
        std::stringstream second(deleteSpace(view->getSecondOperand().toStdString()));

        try{
            model->input(first, second);
            res = model->somma();
            equal.append((res.str()).c_str());
            view->resultOperation(
                        view->getResult() + "(" + first.str().c_str() + ") + (" + second.str().c_str() + ")",
                        equal.append("\n")
            );
        }
        catch(ErroreBinario e){ view->warning("Attenzione!", QString::fromStdString(e.mostraMotivo())); }
        catch(Errore e){ view->warning("Attenzione!", QString::fromStdString(e.mostraMotivo())); }
    }
}

void Controller::timesClicked(){
    if(!checkWarningTwoOperand()){
        QString equal = " = ";
        std::stringstream res;
        std::stringstream first(deleteSpace(view->getFirstOperand().toStdString()));
        std::stringstream second(deleteSpace(view->getSecondOperand().toStdString()));

        try{
            model->input(first, second);
            res = model->prodotto();
            equal.append((res.str()).c_str());
            view->resultOperation(
                        view->getResult() + "(" + first.str().c_str() + ") \303\227 (" + second.str().c_str() + ")",
                        equal.append("\n")
            );
        }
        catch(ErroreBinario e){ view->warning("Attenzione!", QString::fromStdString(e.mostraMotivo())); }
        catch(Errore e){ view->warning("Attenzione!", QString::fromStdString(e.mostraMotivo())); }
    }
}

void Controller::minusClicked(){
    if(!checkWarningTwoOperand()){
        QString equal = " = ";
        std::stringstream res;
        std::stringstream first(deleteSpace(view->getFirstOperand().toStdString()));
        std::stringstream second(deleteSpace(view->getSecondOperand().toStdString()));
        model->input(first, second);
        try{
            res = model->differenza();
            equal.append((res.str()).c_str());
            view->resultOperation(
                        view->getResult() + "(" + first.str().c_str() + ") - (" + second.str().c_str() + ")",
                        equal.append("\n")
            );
        }
        catch(ErroreBinario e){ view->warning("Attenzione!", QString::fromStdString(e.mostraMotivo())); }
        catch(Errore e){ view->warning("Attenzione!", QString::fromStdString(e.mostraMotivo())); }
    }
}

void Controller::transposeClicked(){
    if(!checkWarningOneOperand()){
        QString equal = " = ";
        std::stringstream res;
        std::stringstream first(deleteSpace(view->getFirstOperand().toStdString()));
        std::stringstream second(deleteSpace(view->getSecondOperand().toStdString()));
        if(view->getFirstOperand() != ""){
            model->input(first);
        }else{
            model->input(second);
        }

        try{
            res = model->trasposta();

            equal.append((res.str()).c_str());
            view->resultOperation(
                        view->getResult() + "Trasp(" + first.str().c_str() + ")",
                        equal.append("\n")
            );
        }catch(ErroreUnario e){ view->warning("Attenzione!", QString::fromStdString(e.mostraMotivo())); }
        catch(Errore e){ view->warning("Attenzione!", QString::fromStdString(e.mostraMotivo())); }
    }
}

void Controller::inverseClicked(){
    if(!checkWarningOneOperand()){
        QString equal = " = ";
        std::stringstream res;
        std::stringstream first(deleteSpace(view->getFirstOperand().toStdString()));
        std::stringstream second(deleteSpace(view->getSecondOperand().toStdString()));

        if(view->getFirstOperand() != ""){
            model->input(first);
        }else{
            model->input(second);
        }

        try{
            res = model->inversa();

            equal.append((res.str()).c_str());
            view->resultOperation(
                        view->getResult() + "Inv(" + first.str().c_str() + second.str().c_str() + ")",
                        equal.append("\n")
            );
        }catch(ErroreUnario e){ view->warning("Attenzione!", QString::fromStdString(e.mostraMotivo())); }
        catch(Errore e){ view->warning("Attenzione!", QString::fromStdString(e.mostraMotivo())); }
    }
}

void Controller::gaussClicked(){
    if(!checkWarningOneOperand()){
        QString equal = " = ";
        std::stringstream res;
        std::stringstream first(deleteSpace(view->getFirstOperand().toStdString()));
        std::stringstream second(deleteSpace(view->getSecondOperand().toStdString()));
        u_int scambi = 0;
        if(view->getFirstOperand() != ""){
            model->input(first);
        }else{
            model->input(second);
        }

        try{
            res = model->Gauss(scambi);

            equal.append((res.str()).c_str());
            view->resultOperation(
                        view->getResult() + "Gauss(" + first.str().c_str() + ")",
                        equal.append("\n")
            );
            QMessageBox* info = new QMessageBox(QMessageBox::Information,
                                                "Info",
                                                "Numero scambi: " + QString::number(scambi));
            info->show();
        }catch(ErroreUnario e){ view->warning("Attenzione!", QString::fromStdString(e.mostraMotivo())); }
        catch(Errore e){ view->warning("Attenzione!", QString::fromStdString(e.mostraMotivo())); }
    }
}

void Controller::determinantClicked(){
    if(!checkWarningOneOperand()){
        QString equal = " = ";
        std::stringstream res;
        std::stringstream first(deleteSpace(view->getFirstOperand().toStdString()));
        std::stringstream second(deleteSpace(view->getSecondOperand().toStdString()));
        if(view->getFirstOperand() != ""){
            model->input(first);
        }else{
            model->input(second);
        }

        try{
            res = model->determinante();

            equal.append((res.str()).c_str());
            view->resultOperation(
                        view->getResult() + "Det(" + first.str().c_str() + second.str().c_str() + ")",
                        equal.append("\n")
            );
        }catch(ErroreUnario e){ view->warning("Attenzione!", QString::fromStdString(e.mostraMotivo())); }
        catch(Errore e){ view->warning("Attenzione!", QString::fromStdString(e.mostraMotivo())); }
    }
}

void Controller::normaClicked(){
    if(!checkWarningOneOperand()){
        QString equal = " = ";
        std::stringstream res;
        std::stringstream first(deleteSpace(view->getFirstOperand().toStdString()));
        std::stringstream second(deleteSpace(view->getSecondOperand().toStdString()));
        if(view->getFirstOperand() != ""){
            model->input(first);
        }else{
            model->input(second);
        }

        try{
            res = model->norma();

            equal.append((res.str()).c_str());
            view->resultOperation(
                        view->getResult() + "Norma(" + first.str().c_str() + second.str().c_str() + ")",
                        equal.append("\n")
            );
        }catch(ErroreUnario e){ view->warning("Attenzione!", QString::fromStdString(e.mostraMotivo())); }
        catch(Errore e){ view->warning("Attenzione!", QString::fromStdString(e.mostraMotivo())); }
    }
}

void Controller::projectionClicked(){
    if(!checkWarningTwoOperand()){
        QString equal = " = ";
        std::stringstream res;
        std::stringstream first(deleteSpace(view->getFirstOperand().toStdString()));
        std::stringstream second(deleteSpace(view->getSecondOperand().toStdString()));

        try{
            model->input(first, second);
            res = model->proiezione();

            equal.append((res.str()).c_str());
            view->resultOperation(
                        view->getResult() + "Proj((" + first.str().c_str() + ") | (" + second.str().c_str() + "))",
                        equal.append("\n")
            );
        }catch(ErroreUnario e){ view->warning("Attenzione!", QString::fromStdString(e.mostraMotivo())); }
        catch(Errore e){ view->warning("Attenzione!", QString::fromStdString(e.mostraMotivo())); }
    }
}
