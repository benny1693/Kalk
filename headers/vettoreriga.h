#ifndef VETTORERIGA_H
#define VETTORERIGA_H

#include "vettore.h"

class VettoreRiga : public Vettore {
public:
	VettoreRiga() = default;
	VettoreRiga(u_int);

	VettoreRiga(const VettoreRiga &) = default;
	VettoreRiga &operator=(const VettoreRiga &) = default;
	~VettoreRiga() = default;

	VettoreRiga *clona() const override;

	VettoreRiga *proiezione(const Vettore &) const override;
	double &operator()(u_int) const override;
	double &operator[](u_int) const override;

	VettoreRiga *formaDiGauss(u_int &) const override;
};

#endif // VETTORERIGA_H
