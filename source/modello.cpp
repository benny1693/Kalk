#include "../headers/modello.h"

Modello::Modello() : operando1(0), operando2(0) {}

Modello::~Modello() {
	if (operando1)
		delete operando1;
	if (operando2)
		delete operando2;
}

void Modello::convertiInDiag(Matrice *&operando) {
	MatriceQuadrata *M = dynamic_cast<MatriceQuadrata *>(operando);
	if (M && isDiagonale(M)) {
		operando = new MatriceDiagonale(*M);
		delete M;
	}
}

void Modello::input(stringstream &op) {
	if (operando1)
		delete operando1;
	if (operando2)
		delete operando2;

	operando2 = 0;

	Parser P(op.str());

	operando1 = P.identifica();
	if (!operando1)
		throw Errore("Errore di input");

	op >> *operando1;

	convertiInDiag(operando1);
}

void Modello::input(stringstream &op1, stringstream &op2) {
	if (operando1)
		delete operando1;
	if (operando2)
		delete operando2;

	Parser P[2] = {Parser(op1.str()), Parser(op2.str())};

	operando1 = P[0].identifica();
	operando2 = P[1].identifica();
	if (!operando2)
		throw Errore(
				"Errore di input nel secondo operando: numero di colonne sbagliato");

	if (!operando1)
		throw Errore(
				"Errore di input nel primo operando: numero di colonne sbagliato");

	// operando1 != 0 && operando2 != 0

	op1 >> *operando1;
	op2 >> *operando2;
	convertiInDiag(operando1);
	convertiInDiag(operando2);
}

bool Modello::isDiagonale(MatriceQuadrata *M) {
	bool diag = true;
	u_int ordine = M->getRighe();
	for (u_int i = 0; i < ordine && diag; i++)
		for (u_int j = 0; j < ordine && diag; j++)
			if (i != j && (*M)(i, j) != 0.)
				diag = false;
	// diag = ((i / ordine == i % ordine) || ((*M)(i / ordine, i % ordine) ==
	// 0.));

	return diag;
}

stringstream Modello::somma() const {
	stringstream ss("");
	try {
		ss << *operando1 + *operando2;
	} catch (ErroreBinario) {
		throw;
	}
	return ss;
}

stringstream Modello::differenza() const {
	stringstream ss("");
	try {
		ss << *operando1 - *operando2;
	} catch (ErroreBinario) {
		throw;
	}
	return ss;
}

stringstream Modello::prodotto() const {
	stringstream ss("");
	try {
		ss << *operando1 * *operando2;
	} catch (ErroreBinario) {
		throw;
	}
	return ss;
}

stringstream Modello::trasposta() const {
	stringstream ss;
	ss << operando1->trasposizione();
	return ss;
}

stringstream Modello::Gauss(u_int &scambi) const {
	stringstream ss("");
	scambi = 0;

	Matrice *M = (operando1->formaDiGauss(scambi));
	ss << *M;
	delete M;

	return ss;
}

stringstream Modello::determinante() const {
	stringstream ss;
	MatriceQuadrata *M = dynamic_cast<MatriceQuadrata *>(operando1);

	if (!M)
		throw Errore("Operazione non disponibile");

	ss << M->determinante();
	return ss;
}

stringstream Modello::inversa() const {
	stringstream ss("");
	MatriceQuadrata *M = dynamic_cast<MatriceQuadrata *>(operando1);

	if (!M)
		throw Errore("Operazione non disponibile");

	try {
		M = M->inversa();
		ss << *M;
		delete M;
	} catch (ErroreUnario) {
		throw;
	}

	return ss;
}

stringstream Modello::norma() const {

	stringstream ss;
	Vettore *V = dynamic_cast<Vettore *>(operando1);

	if (!V)
		throw Errore("Operazione non disponibile");

	ss << V->norma();

	return ss;
}

stringstream Modello::proiezione() const {
	stringstream ss;
	Vettore *V1 = dynamic_cast<Vettore *>(operando1);
	Vettore *V2 = dynamic_cast<Vettore *>(operando2);

	if (!V1 || !V2)
		throw Errore("Operazione non disponibile");

	try {
		V1 = V1->proiezione(*V2);
	} catch (ErroreBinario) {
		throw;
	}

	ss << *V1;
	delete V1;
	return ss;
}
