#include "../headers/vettoreriga.h"

VettoreRiga::VettoreRiga(u_int col) : Vettore(1, col) {}

VettoreRiga *VettoreRiga::clona() const { return new VettoreRiga(*this); }

VettoreRiga *VettoreRiga::proiezione(const Vettore &V) const {
	if (!ugualiDimensioni(V))
		throw ErroreBinario("Dimensioni incompatibili",getRighe(),getColonne(),V.getRighe(),V.getColonne());

	Matrice M = (*this) * V.trasposizione(); // Il risultato sarà una matrice 1x1

	double no = norma();
	double coefficiente = M(0, 0) / (no*no);

	VettoreRiga *risultato = clona();
	for (u_int i = 0; i < getColonne(); i++)
		(*risultato)(i) *= coefficiente * (*risultato)(i);

	return risultato;
}

double &VettoreRiga::operator()(u_int i) const {
	return Matrice::operator()(0, i);
}

double &VettoreRiga::operator[](u_int i) const {
	return Matrice::operator()(0, i);
}

VettoreRiga *VettoreRiga::formaDiGauss(u_int &scambi) const {
	scambi = 0;
	return clona();
}
