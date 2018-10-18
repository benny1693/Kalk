#ifndef VETTORECOLONNA_H
#define VETTORECOLONNA_H

#include "vettore.h"

class VettoreColonna : public Vettore {
public:
	VettoreColonna() = default;
	VettoreColonna(u_int);

	VettoreColonna(const VettoreColonna &) = default;
	VettoreColonna &operator=(const VettoreColonna &) = default;
	~VettoreColonna() = default;

	VettoreColonna *clona() const override;

	VettoreColonna *proiezione(const Vettore &) const override;
	double &operator()(u_int) const override;
	double &operator[](u_int) const override;

	VettoreColonna *formaDiGauss(u_int &) const override;
};

#endif // VETTORECOLONNA_H
