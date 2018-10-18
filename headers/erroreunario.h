#ifndef ERROREUNARIO_H
#define ERROREUNARIO_H

#include "errore.h"

class ErroreUnario : public Errore {
private:
	int righe, colonne;

public:
	ErroreUnario();
	ErroreUnario(string, int, int);

	int mostraRighe() const;
	int mostraColonne() const;
};

#endif // ERROREUNARIO_H
