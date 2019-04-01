#pragma once

void UnicodeCharacter() { //Ejecutar antes del lexico
	for (int i = 0; i < programa.length() - 8; i++) {
		if (programa.substr(i, 2) == "\\u") {
			unsigned int character; stringstream ss;
			ss << hex << programa.substr(i+2, 6); ss >> character;
			// output it as a signed type
			if (character < 32 || character > 126) {
				character = '?';
			}
			programa = programa.substr(0, i) + (char)character + programa.substr(i + 8, programa.length() - i - 8);
		}
	}
}

//Metodos
//Salir -1 , Error -2, Sigue >0, Omite =0 
int SiguienteEstado(int estadoActual, char caracter) {
	int carac = -1;
	carac = (caracter != '\0') ? (caracter != '\n') ? (caracter != '\t') ? caracter - 32 + 3 : 2 : 1 : 0;
	if ((carac >= 99) || (carac < 0)) { return -2; }
	return Lexico[estadoActual][carac]; //Regreso el siguiente estado
}
int ValidarEstadoToken(string texto, int estado) { //Regreso el token
	int token = -1;
	for (int i = 0; i < estadoToken.size(); i++) {
		if (estado == estadoToken[i]) {
			token = i;
			if (token == IDENTIFIER) { //Si es identificdor, busco si es palabra reservada
				for (int j = 0; j < palabras_reservadas.size(); j++) {
					if (texto == palabras_reservadas[j]) { token = j+1; } //Palabra Reservada
				}
			}
		}
	}
	return token;
}

//Automata
void AutomataLexico() {
	//Variables que me ayudan a recorrer mi automata
	string texto = ""; 
	int indexPrograma = 0; int estado = 0;  int sigEstado; int sigIndex;
	int linea = 0; int columna = 0; //Actuales
	int localIndex = 0; int localColumna = 0; int localLinea = 0; int localLongitud = 0; //Guardadas
	AccionLexico accion;

	while (programa.length() != indexPrograma) {
		sigEstado = SiguienteEstado(estado, programa[indexPrograma]);

		if (sigEstado == -2) {						//Error de Caracter
			cout << "ERROR Caracter no valido en " << linea << ", " << columna << endl;
			accion = AccionLexico::Reset;
		} else if (sigEstado == -1) {				//Si el estado es -1
			int tokenID = ValidarEstadoToken(texto, estado);
			if (tokenID != -1) {						//encontre un token, lo guardo
				CodigoToken* token = new CodigoToken(tokenID, localLinea, localColumna, localIndex, localLongitud);
				Programa->AddChild(new NodoPrograma(token), Programa->children.size());
				if (tokenID == IDENTIFIER) { //Si es identificador lo agrego a la tabla
					TablaIdentificadores.push_back(*(new Identificador(token)));
					token->SetID(TablaIdentificadores.size() - 1);
				}
				accion = AccionLexico::Comienza;
			} else {									//De seguro hubo un error, token no valido
				cout << "ERROR Detectado en " << linea << ", " << columna << endl;
				accion = AccionLexico::Reset;
			}
		} else if (sigEstado == 0) {					//Espacios o saltos de linea, avanzo sin detectar
			accion = AccionLexico::Reset;
		} else {										//Si no es menor a 0, me sigo moviendo
			accion = AccionLexico::Avanza;
		}

		//Sigo recorriendo		
		if (accion == AccionLexico::Comienza) {
			columna = columna;
			linea = linea;
			localColumna = columna;
			localLinea = linea;
			texto = "";
			localLongitud = 0;
			estado = 0;
			indexPrograma = indexPrograma;
			localIndex = indexPrograma;
		} else if (accion == AccionLexico::Reset) {
			columna = (programa[indexPrograma] == '\n') ? 0 : columna + 1;
			linea = (programa[indexPrograma] == '\n') ? linea + 1 : linea;
			localColumna = columna;
			localLinea = linea;
			texto = "";
			localLongitud = 0;
			estado = 0;
			indexPrograma = indexPrograma + 1;
			localIndex = indexPrograma;
		} else if (accion == AccionLexico::Avanza) {
			columna = (programa[indexPrograma] == '\n') ? 0 : columna + 1;
			linea = (programa[indexPrograma] == '\n') ? linea + 1 : linea;
			localColumna = localColumna;
			localLinea = localLinea;
			texto = texto + programa[indexPrograma];
			localLongitud = localLongitud + 1;
			estado = sigEstado;
			indexPrograma = indexPrograma + 1;
			localIndex = localIndex;
		}

	}

	CodigoToken* token = new CodigoToken(FIN, linea, columna, localIndex, 0);
	Programa->AddChild(new NodoPrograma(token), Programa->children.size());

}


void EliminarComentarios() { //Se tiene que hacer despues del lexico
	for (int i = 0; i < Programa->children.size(); i++) {
		if (Programa->children[i]->data->token->token == SHORT_COMMENT || Programa->children[i]->data->token->token == LARGE_COMMENT) {
			Programa->RemoveChild(i);
			i--;
		}
	}
}