#include "../headers/vettorecolonna.h"
VettoreColonna::VettoreColonna(u_int rig) : Vettore(rig, 1) {}

VettoreColonna *VettoreColonna::clona() const {
	return new VettoreColonna(*this);
}

VettoreColonna *VettoreColonna::proiezione(const Vettore &V) const {
	if (!ugualiDimensioni(V))
		throw ErroreBinario("Dimensioni incompatibili",getRighe(),getColonne(),V.getRighe(),V.getColonne());

	Matrice M = V.trasposizione() * (*this); // Il risultato sarà una matrice 1x1

	double no = norma();
	double coefficiente = M(0, 0) / (no*no);

	VettoreColonna *risultato = clona();
	for (u_int i = 0; i < getRighe(); i++)
		(*risultato)[i] *= coefficiente * (*risultato)[i];

	return risultato;
}

double &VettoreColonna::operator()(u_int i) const {
	return Matrice::operator()(i, 0);
}

double &VettoreColonna::operator[](u_int i) const {
	return Matrice::operator()(i, 0);
}

VettoreColonna *VettoreColonna::formaDiGauss(u_int &scambi) const {
	scambi = 0;

	VettoreColonna *risultato = clona();
	u_int max = risultato->maxColonna(0, 0);

	if (max != 0)
		scambi++;

	risultato[0] = risultato[max];

	for (u_int i = 1; i < getRighe(); i++)
		risultato[i] = 0;

	return risultato;
}
