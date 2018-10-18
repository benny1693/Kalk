#ifndef MODELLO_H
#define MODELLO_H

#include "matrice.h"
#include "matricediagonale.h"
#include "matricequadrata.h"
#include "vettore.h"
#include "vettorecolonna.h"
#include "vettoreriga.h"

#include "errore.h"
#include "errorebinario.h"
#include "erroreunario.h"

#include "parser.h"

#include <sstream>
#include <string>

using std::stringstream;

class Modello {
private:
	Matrice *operando1;
	Matrice *operando2;

	static bool isDiagonale(MatriceQuadrata *);
	static void convertiInDiag(Matrice*& operando);
public:
	Modello();
	~Modello();

	void input(stringstream &);
	void input(stringstream &, stringstream &);
	stringstream somma() const;
	stringstream differenza() const;
	stringstream prodotto() const;
	stringstream trasposta() const;
	stringstream Gauss(u_int &) const;
	stringstream determinante() const;
	stringstream inversa() const;
	stringstream norma() const;
	stringstream proiezione() const;
};

#endif // MODELLO_H
