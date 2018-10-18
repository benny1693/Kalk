#include "../headers/erroreunario.h"

ErroreUnario::ErroreUnario() : Errore (), righe(-1), colonne(-1) {}

ErroreUnario::ErroreUnario(string m, int r, int c)
		: Errore(m), righe(r), colonne(c) {}

int ErroreUnario::mostraRighe() const { return righe; }

int ErroreUnario::mostraColonne() const { return colonne; }
