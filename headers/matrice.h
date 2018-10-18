#ifndef MATRICE_H
#define MATRICE_H

#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>

#include "errore.h"
#include "errorebinario.h"
#include "erroreunario.h"

class Matrice {
	friend std::istream &operator>>(std::istream &, const Matrice &);
private:
	u_int righe;
	u_int colonne;
	double *matrice;

	double *copia() const;

public:
	Matrice();
	Matrice(u_int, u_int);

	Matrice(const Matrice &);
	Matrice &operator=(const Matrice &);
	virtual ~Matrice();

	virtual Matrice *clona() const;

	u_int getRighe() const;
	u_int getColonne() const;
	double &operator()(u_int, u_int) const;

	Matrice operator+(const Matrice &) const;
	Matrice operator-(const Matrice &) const;
	Matrice operator*(const Matrice &)const;

	Matrice trasposizione() const;
	virtual Matrice *formaDiGauss(u_int &) const;

	bool ugualiDimensioni(const Matrice &) const;
	void scambioRighe(u_int, u_int) const;
	void sottrazioneRighe(u_int, u_int, double) const;
	u_int maxColonna(u_int, u_int) const;
};

std::ostream &operator<<(std::ostream &, const Matrice &);

std::istream &operator>>(std::istream &, const Matrice &);

#endif // MATRICE_H
