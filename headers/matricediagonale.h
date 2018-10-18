#ifndef MATRICEDIAGONALE_H
#define MATRICEDIAGONALE_H

#include "matricequadrata.h"

class MatriceDiagonale : public MatriceQuadrata {
public:
	MatriceDiagonale() = default;
	MatriceDiagonale(u_int);

	MatriceDiagonale(const MatriceDiagonale &) = default;
	explicit MatriceDiagonale(const MatriceQuadrata &);
	MatriceDiagonale &operator=(const MatriceDiagonale &) = default;
	~MatriceDiagonale() = default;

	MatriceDiagonale *clona() const override;

	double determinante() const override;
	MatriceDiagonale *inversa() const override;
	MatriceDiagonale *formaDiGauss(u_int &) const override;
};

#endif // MATRICEDIAGONALE_H
