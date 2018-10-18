#ifndef VETTORE_H
#define VETTORE_H

#include "matrice.h"
#include <cmath>

class Vettore : public Matrice {
public:
	Vettore() = default;
	Vettore(u_int, u_int);

	Vettore(const Vettore &) = default;
	Vettore &operator=(const Vettore &) = default;
	~Vettore() = default;

	double norma() const;
	virtual Vettore *proiezione(const Vettore &) const = 0;
	virtual double &operator()(u_int) const = 0;
	virtual double &operator[](u_int) const = 0;
};

#endif // VETTORE_H
