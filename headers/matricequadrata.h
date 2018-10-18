#ifndef MATRICEQUADRATA_H
#define MATRICEQUADRATA_H

#include "matrice.h"
#include <cmath>

class MatriceQuadrata : public Matrice {
private:
	static MatriceQuadrata identita(u_int);

public:
	MatriceQuadrata() = default;
	MatriceQuadrata(u_int);

	MatriceQuadrata(const MatriceQuadrata &) = default;
	MatriceQuadrata &operator=(const MatriceQuadrata &) = default;
	~MatriceQuadrata() = default;

	MatriceQuadrata *clona() const override;

	virtual double determinante() const;
	virtual MatriceQuadrata *inversa() const;
};
#endif // MATRICEQUADRATA_H
