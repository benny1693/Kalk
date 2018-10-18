#ifndef PARSER_H
#define PARSER_H

#include "matrice.h"
#include "matricediagonale.h"
#include "matricequadrata.h"
#include "vettore.h"
#include "vettorecolonna.h"
#include "vettoreriga.h"


#include <string>

using std::string;

class Parser {
private:
	string oper;
	u_int righe,colonne;

public:
	Parser(string i);

	bool controllaStringa();
	Matrice* identifica();
};

#endif // PARSER_H
