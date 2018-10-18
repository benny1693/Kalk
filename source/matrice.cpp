#include "../headers/matrice.h"

Matrice::Matrice() : righe(0), colonne(0), matrice(0) {}

Matrice::Matrice(u_int r, u_int c) : righe(r), colonne(c) {
	if (r * c == 0) {
		righe = colonne = 0;
		matrice = 0;
		throw ErroreUnario("Dimensioni errate", r, c);
	}
	matrice = new double[r * c];
	for (u_int i = 0; i < r * c; i++)
		matrice[i] = 0;
}

double *Matrice::copia() const {
	double *C = new double[righe * colonne];
	for (u_int i = 0; i < righe * colonne; i++)
		C[i] = matrice[i];
	return C;
}

Matrice::Matrice(const Matrice &M)
		: righe(M.righe), colonne(M.colonne), matrice(M.copia()) {}

Matrice &Matrice::operator=(const Matrice &M) {
	if (this != &M) {
		if (matrice)
			delete[] matrice;
		righe = M.righe;
		colonne = M.colonne;
		matrice = M.copia();
	}
	return *this;
}

Matrice::~Matrice() {
if (matrice)
    delete[] matrice;
}

Matrice *Matrice::clona() const { return new Matrice(*this); }

u_int Matrice::getRighe() const { return righe; }

u_int Matrice::getColonne() const { return colonne; }

double &Matrice::operator()(u_int i, u_int j) const {
	return matrice[i * colonne + j];
}

Matrice Matrice::operator+(const Matrice &M) const {
	if (!ugualiDimensioni(M))
		throw ErroreBinario("Dimensioni incompatibili", righe, colonne, M.righe,
												M.colonne);

	Matrice risultato(*this);
	for (u_int i = 0; i < righe * colonne; i++) {
		risultato.matrice[i] += M.matrice[i];
		if (std::abs(risultato.matrice[i]) < 1e-8)
			risultato.matrice[i] = 0;
	}
	return risultato;
}

Matrice Matrice::operator-(const Matrice &M) const {
	if (!ugualiDimensioni(M))
		throw ErroreBinario("Dimensioni incompatibili", righe, colonne, M.righe,
												M.colonne);

	Matrice risultato(*this);
	for (u_int i = 0; i < righe * colonne; i++) {
		risultato.matrice[i] -= M.matrice[i];
		if (std::abs(risultato.matrice[i]) < 1e-8)
			risultato.matrice[i] = 0;
	}
	return risultato;
}

Matrice Matrice::operator*(const Matrice &M) const {
	if (colonne != M.righe)
		throw ErroreBinario("Dimensioni incompatibili", righe, colonne, M.righe,
												M.colonne);

	Matrice risultato(righe, M.colonne);

	for (u_int i = 0; i < risultato.righe; i++)
		for (u_int j = 0; j < risultato.colonne; j++) {
			risultato(i, j) = 0;
			for (u_int k = 0; k < colonne; k++) {
				risultato(i, j) += (*this)(i, k) * M(k, j);
				if (std::abs(risultato(i,j)) < 1e-8)
					risultato(i,j) = 0;
			}
		}
	return risultato;
}

Matrice Matrice::trasposizione() const {
	Matrice risultato(colonne, righe);

	for (u_int i = 0; i < colonne; i++)
		for (u_int j = 0; j < righe; j++)
			risultato(i, j) = (*this)(j, i);

	return risultato;
}

Matrice *Matrice::formaDiGauss(u_int &scambi) const {
	Matrice *risultato = clona();
	u_int max;
	scambi = 0;
	u_int riga = 0;
	for (u_int i = 0; i < colonne - 1; i++) {
		max = risultato->maxColonna(riga, i);
		if ((*risultato)(max, i) != 0.) {
			if (max != riga) {
				risultato->scambioRighe(riga, max);
				scambi++;
			}
			for (u_int j = riga + 1; j < righe; j++)
				risultato->sottrazioneRighe(
						riga, j, ((*risultato)(j, i)) / ((*risultato)(riga, i)));
			riga++;
		}
	}
	return risultato;
}

bool Matrice::ugualiDimensioni(const Matrice &M) const {
	return (righe == M.righe) && (colonne == M.colonne);
}

void Matrice::scambioRighe(u_int riga1, u_int riga2) const {
	double temp;
	for (u_int i = 0; i < colonne; i++) {
		temp = matrice[riga1 * colonne + i];
		matrice[riga1 * colonne + i] = matrice[riga2 * colonne + i];
		matrice[riga2 * colonne + i] = temp;
	}
}

void Matrice::sottrazioneRighe(u_int riga1, u_int riga2,
															 double moltiplicatore) const {
	for (u_int i = 0; i < colonne; i++) {
		matrice[riga2 * colonne + i] -=
				matrice[riga1 * colonne + i] * moltiplicatore;

		if (std::abs(matrice[riga2 * colonne + i]) < 1e-8)
			matrice[riga2 * colonne + i] = 0.;
	}
}

u_int Matrice::maxColonna(u_int riga, u_int col) const {
	u_int max = riga;
	for (u_int i = riga + 1; i < righe; i++)
		if (std::abs(matrice[i * colonne + col]) >
				std::abs(matrice[max * colonne + col]))
			max = i;

	return max;
}

std::ostream &operator<<(std::ostream &os, const Matrice &M) {
	for (u_int i = 0; i < M.getRighe() - 1; i++) {
		for (u_int j = 0; j < M.getColonne() - 1; j++)
			os << M(i, j) << ",";
		os << M(i, M.getColonne() - 1) << ";";
	}

	for (u_int j = 0; j < M.getColonne() - 1; j++)
		os << M(M.getRighe() - 1, j) << ",";

	os << M(M.getRighe() - 1, M.getColonne() - 1);

	return os;
}

std::istream &operator>>(std::istream &is, const Matrice &M) {
	for (u_int i = 0; i < M.getRighe() * M.getColonne() - 1; i++) {
		is >> M.matrice[i];
		is.get();
	}
	is >> M.matrice[M.getRighe() * M.getColonne() - 1];

	return is;
}
