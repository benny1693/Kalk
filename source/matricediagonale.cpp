#include "../headers/matricediagonale.h"

MatriceDiagonale::MatriceDiagonale(u_int ordine) : MatriceQuadrata(ordine) {}

MatriceDiagonale::MatriceDiagonale(const MatriceQuadrata& M) : MatriceQuadrata (M.getRighe()) {
	for (u_int i = 0; i < M.getRighe(); i++)
		(*this)(i,i) = M(i,i);
}

MatriceDiagonale *MatriceDiagonale::clona() const {
	return new MatriceDiagonale(*this);
}

double MatriceDiagonale::determinante() const {
	double det = 1;
	for (u_int i = 0; i < getRighe(); i++)
		det *= (*this)(i, i);

	return det;
}

MatriceDiagonale *MatriceDiagonale::inversa() const {
	MatriceDiagonale *M = clona();

	double det = determinante();

	if (det == 0.)
		throw ErroreUnario("Matrice non invertibile",getRighe(),getColonne());

	for (u_int i = 0; i < getRighe(); i++)
		(*M)(i, i) = 1 / (*M)(i, i);

	return M;
}

MatriceDiagonale *MatriceDiagonale::formaDiGauss(u_int &scambi) const {
	scambi = 0;
	return clona();
}
