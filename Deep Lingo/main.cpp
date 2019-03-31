#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
#include "Tokens.h" //Meramente IDs
#include "Reglas.h" //Meramente IDs
#include "Structs.h" //Structuras y variables globales
#include "ReadFiles.h" //Lectura de txts
#include "Lexico.h"	//AutomataLexico
#include "Sintactico.h"	//Automata Sintactico

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
	ReadFiles();
	AutomataLexico();


	cout << "Tokens: " << endl;
	for (int i = 0; i < Tokens.size(); i++) {
		cout << "  [" << i << "] " << Tokens[i] << endl;
	}

	cout << endl << "Codigo Tokenizado: " << endl;
	for (int i = 0; i < CodigoTokenizado.size(); i++) {
		cout << "  [" << i << "] [" << CodigoTokenizado[i].indexIdentificador << "] : " << Tokens[CodigoTokenizado[i].token] << "[" << CodigoTokenizado[i].token << "] (" << CodigoTokenizado[i].linea << ", " << CodigoTokenizado[i].columna << "): " << CodigoTokenizado[i].ValorLexico() << endl;
	}
	cout << endl << "Tabla de Identificadores" << endl;
	for (int i = 0; i < TablaIdentificadores.size(); i++) {
		cout << "  [" << i << "] [" << TablaIdentificadores[i].indexCodigo << "] " << CodigoTokenizado[TablaIdentificadores[i].indexCodigo].ValorLexico() << " : " << TablaIdentificadores[i].tipo << endl;
	}
	cout << endl;

	system("pause");
}