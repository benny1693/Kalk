#include "../headers/errorebinario.h"

ErroreBinario::ErroreBinario() : ErroreUnario (), righe(-1), colonne(-1) {}

ErroreBinario::ErroreBinario(string m, int r1, int c1, int r2, int c2)
		: ErroreUnario(m, r1, c1), righe(r2), colonne(c2) {}

int ErroreBinario::mostraRigheSec() const { return righe; }

int ErroreBinario::mostraColonneSec() const { return colonne; }
