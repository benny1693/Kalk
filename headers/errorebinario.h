#ifndef ERROREBINARIO_H
#define ERROREBINARIO_H

#include "erroreunario.h"

class ErroreBinario : public ErroreUnario {
private:
	int righe, colonne;

public:
	ErroreBinario();
	ErroreBinario(string, int, int, int, int);
	int mostraRigheSec() const;
	int mostraColonneSec() const;
};

#endif // ERROREBINARIO_H
