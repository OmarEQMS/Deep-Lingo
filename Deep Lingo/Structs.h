#pragma once

//Programa
string programa; //Programa

//Estructuras PROGRAMA
struct CodigoToken { //Parametros para ubicar una parte del programa y referencarlos al index de la lista de tokens
public:
	int token; int linea; int columna; int index; int longitud; int indexIdentificador = -1;
	CodigoToken() {}
	CodigoToken(int tok, int lin, int col, int idx, int lon) { token = tok; linea = lin; columna = col; index = idx; longitud = lon; }
	void SetID(int id) { indexIdentificador = id; }
	string ValorLexico() { return programa.substr(index, longitud); }
};
struct CodigoRegla { //Parametros para ubicar una regla de la lista de reglas
	int regla; //valex, profundidad
	CodigoRegla() {}
	CodigoRegla(int r) { regla = r; }
};
struct CodigoReglaToken { //Parametros para poder tener una pila con CodigoToken y CodigoRegla al mismo tiempo
	enum Tipo { Regla, Token, Raiz };
	CodigoRegla* regla;
	CodigoToken* token;
	Tipo tipo;
	CodigoReglaToken(CodigoRegla* r) { regla = r; token = NULL; tipo = Regla; }
	CodigoReglaToken(CodigoToken* t) { regla = NULL; token = t; tipo = Token; }
	CodigoReglaToken() { tipo = Raiz; }
};
struct NodoPrograma {
	CodigoReglaToken* data;
	vector<NodoPrograma*> children;
	NodoPrograma(CodigoRegla* r) { data = new CodigoReglaToken(r); }
	NodoPrograma(CodigoToken* t) { data = new CodigoReglaToken(t); }
	NodoPrograma() { data = new CodigoReglaToken(); }
	void RemoveChild(int index) {
		for (int i = index; i < children.size() - 1; i++) {
			children[i] = children[i + 1];
		}
		children.pop_back();
	}
	void AddChild(NodoPrograma* child, int index) {
		children.resize(children.size() + 1);
		for (int i = children.size() - 2; i >= index; i--) {
			children[i + 1] = children[i];
		}
		children[index] = child;
	}
};

//Tabla Identificadores
struct Identificador { //Parametros de la tabla de simbolos
public:
	string tipo; CodigoToken* token;
	Identificador() {}
	Identificador(CodigoToken* t) { token = t; }
};

//Acciones del Lexico 
enum AccionLexico { Reset, Avanza, Comienza };

//Structras para Sintactico
struct ReglaToken {
	enum Tipo { Regla, Token };
	int index; //String de Reglas o Tokens
	Tipo tipo;
};
struct ReduccionRegla {
	int regla;
	vector<ReglaToken> definicion;
};
struct AccionSintactico { //Asociacion de Accion con estado o regla para Tabla Sintactica
	enum TipoAccion { Acceptable, Desplazate, Reduce, Error };
	TipoAccion accion = TipoAccion::Error;
	//Estado o Regla reduccion
	int numero = -1; 
};



//Variables
//Read Files
vector<string> Tokens; //String de Tokens
vector<string> Reglas; //String de Reglas
vector<string> palabras_reservadas; //String de Plabras Reserc¿vadas

//Automata Lexico
vector<vector<int>> Lexico; //Matriz del Lexico
vector<int> estadoToken; //Para poder ver los estados finales y aceptables

//Automata Sintactico
vector<vector<AccionSintactico>> Sintactico; //Matriz del sintactico
vector<ReduccionRegla> SintacticoReglas; //Para poder aplicar las reducciones

//Lexico + Sintactico
vector<Identificador> TablaIdentificadores; //Tabla Identificadores
NodoPrograma* Programa =  new NodoPrograma(); //Codigo Tokenizado +  Reglamentado
