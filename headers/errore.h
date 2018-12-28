#ifndef ERRORE_H
#define ERRORE_H

#include <exception>
#include <string>

using std::string;

class Errore : public std::exception {
private:
	string motivo;

public:
	Errore(string = "");

	string mostraMotivo() const;

	virtual ~Errore() = default;
};

#endif // ERRORE_H
