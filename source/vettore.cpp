#include "../headers/vettore.h"

Vettore::Vettore(u_int r, u_int c) : Matrice(r, c) {}

double Vettore::norma() const {
	double somma = 0;
	for (u_int i = 0; i < getColonne() + getRighe() -1; i++)
		somma = somma + (*this)(i) * (*this)(i);
	return std::sqrt(somma);
}
