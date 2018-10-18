#include "../headers/errore.h"

Errore::Errore(string m) : motivo(m) {}

string Errore::mostraMotivo() const { return motivo; }
