#include "../headers/matricequadrata.h"

MatriceQuadrata MatriceQuadrata::identita(u_int ordine) {
	MatriceQuadrata risultato(ordine);
	for (u_int i = 0; i < ordine; i++)
		risultato(i, i) = 1;

	return risultato;
}

MatriceQuadrata::MatriceQuadrata(u_int ordine) : Matrice(ordine, ordine) {}

MatriceQuadrata *MatriceQuadrata::clona() const {
	return new MatriceQuadrata(*this);
}

double MatriceQuadrata::determinante() const {
	u_int scambi = 0;
	Matrice* M = formaDiGauss(scambi);
	double det = std::pow(-1, scambi);
	for (u_int i = 0; i < getRighe(); i++)
		det *= (*M)(i, i);

	delete M;

	return det;
}

MatriceQuadrata *MatriceQuadrata::inversa() const {
	double det = determinante();

	if (det == 0.)
		throw ErroreUnario("Matrice non invertibile",getRighe(),getColonne());

	u_int ordine = getColonne();
	MatriceQuadrata temp(*this);
	MatriceQuadrata *I = identita(ordine).clona();

	double moltiplicatore;
	u_int max;
	for (u_int i = 0; i < ordine; i++) {
		max = temp.maxColonna(i, i);
		if (max != i) {
			temp.scambioRighe(i, max);
			I->scambioRighe(i, max);
		}
		for (u_int j = 0; j < ordine; j++)
			if (j != i) {
				moltiplicatore = temp(j, i) / temp(i, i);
				I->sottrazioneRighe(i, j, moltiplicatore);
				temp.sottrazioneRighe(i, j, moltiplicatore);
			}
	}

	for (u_int i = 0; i < ordine; i++) {
		for (u_int j = 0; j < ordine; j++) {
			(*I)(i, j) /= temp(i, i);
		}
		temp(i, i) = 1;
	}

	return I;
}
