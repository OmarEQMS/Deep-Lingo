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

void RecorrerArbol(NodoPrograma* nodo, int nivel) {
	for (int i = 0; i < nivel; i++) { cout << "   |"; }

	if (nodo->data->tipo == CodigoReglaToken::Token) {
		cout << "-[Token] " << (nodo->data->token->indexIdentificador!=-1 ? ("[" + to_string(nodo->data->token->indexIdentificador) + "]"): "") << " : " << Tokens[nodo->data->token->token] << "[" << nodo->data->token->token << "] (" << nodo->data->token->linea << ", " << nodo->data->token->columna << "): " << nodo->data->token->ValorLexico() << endl;
	} else if (nodo->data->tipo == CodigoReglaToken::Regla) {
		cout << "-[Regla] : " << Reglas[nodo->data->regla->regla] << "[" << nodo->data->regla->regla << "]" << endl;
	} else if (nodo->data->tipo == CodigoReglaToken::Raiz) {
		cout << "Soy Raiz" << endl;
	}

	for (int i = 0; i < nodo->children.size(); i++) {
		RecorrerArbol(nodo->children[i], nivel + 1);
	}
}

void main() {
	ReadFiles();
	UnicodeCharacter();
	AutomataLexico();
	EliminarComentarios();
	AutomataSintactico();

	RecorrerArbol(Programa, 0);

	cout << endl << "Tabla de Identificadores" << endl;
	for (int i = 0; i < TablaIdentificadores.size(); i++) { //Un identificador forzosamente apuntara a un token
		cout << "  [" << i << "]" << TablaIdentificadores[i].token->ValorLexico() << " : " << TablaIdentificadores[i].tipo << endl;
	}
	cout << endl;

	system("pause");
}