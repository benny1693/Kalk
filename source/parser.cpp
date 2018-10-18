#include "../headers/parser.h"

Parser::Parser(string i) : oper(i), righe(0), colonne(0) {}

bool Parser::controllaStringa() {

	righe = 1;
	colonne = 1;

	for (u_int i = 0; i < oper.size() && oper[i] != ';'; i++)
		if (oper[i] == ',')
			colonne++;

	u_int col = 1;
	bool ok = true;

	for (u_int j = 0; j < oper.size() && ok; j++) {
		if (oper[j] == ',')
			col++;
		if (oper[j] == ';') {
			ok = (col == colonne);
			col = 1;
			righe++;
		}
	}

	ok = (col == colonne);

	return ok;
}

Matrice *Parser::identifica() {
	if (!controllaStringa())
		return 0;

	if (righe > 1 && colonne > 1) {
		if (righe == colonne)
			return new MatriceQuadrata(righe);
		else { // righe > 1 && colonne > 1 && righe != colonne
			return new Matrice(righe, colonne);
		}
	} else {
		// righe <= 1 || colonne <= 1 -> righe == 1 || colonne == 1
		if (righe == 1)
			return new VettoreRiga(colonne);
		else
			return new VettoreColonna(righe);
	}
}
