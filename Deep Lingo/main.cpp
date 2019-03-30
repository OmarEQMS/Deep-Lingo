#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
#include "Tokens.h"
#include "ReadFiles.h"
#include "Lexico.h"

/*
//4 archivos que definen el lexico
vector<vector<int>> matrizLexico;
vector<string> Tokens; vector<int> estadoToken;
vector<string> palabras_reservadas;
string programa;

//Resultados
vector<CodigoToken> codigoTokenizado;
vector<Identificadores> tablaIdentificadores;
*/

void main() {
	ReadFilePrograma();
	ReadFileLexico();
	ReadFileTokens();
	ReadFilePalabrasReservadas();

	AutomataLexico();
	cout << "Tokens: " << endl;
	for (int i = 0; i < Tokens.size(); i++) {
		cout << "  [" << i << "] " << Tokens[i] << endl;
	}

	cout << endl << "Codigo Tokenizado: " << endl;
	for (int i = 0; i < codigoTokenizado.size(); i++) {
		cout << "  [" << i << "] " << codigoTokenizado[i].token << "=" << Tokens[codigoTokenizado[i].token] << " (" << codigoTokenizado[i].linea << ", " << codigoTokenizado[i].columna << "): " << programa.substr(codigoTokenizado[i].index, codigoTokenizado[i].longitud) << endl;
	}
	cout << endl << "Tabla de Identificadores" << endl;
	for (int i = 0; i < tablaIdentificadores.size(); i++) {
		cout << "  [" << i << "] " << tablaIdentificadores[i].identificador << "(" << tablaIdentificadores[i].indexCodigo << "): " << tablaIdentificadores[i].tipo << endl;
	}
	cout << endl;

	system("pause");
}