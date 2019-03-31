#pragma once

//Programa
string programa; //Programa

//Estructuras
enum AccionLexico { Reset, Avanza, Comienza };

struct Identificador { //Parametros de la tabla de simbolos
public:
	string tipo; int indexCodigo;
	Identificador() {}
	Identificador(int index) { indexCodigo = index; }
};
struct CodigoToken { //Parametros para ubicar una parte del programa y referencarlos al index de la lista de tokens
public:
	int token; int linea; int columna; int index; int longitud; int indexIdentificador = -1;
	CodigoToken() {}
	CodigoToken(int tok, int lin, int col, int idx, int lon) { token = tok; linea = lin; columna = col; index = idx; longitud = lon; }
	void SetID(int id) { indexIdentificador = id; }
	string ValorLexico() { return programa.substr(index, longitud); }
};


struct ReglaToken { //Parametros para poder tener un String con Tokens y Reglas al mismo tiempo (Reduccion Reglas)
	enum Tipo { Regla, Roken };
	int index; //String de Reglas o Tokens
	Tipo tipo;
};
struct AccionSintactico { //Asociacion de Accion con estado o regla para Tabla Sintactica
	enum TipoAccion { Acceptable, Desplazate, Reduce, Error };
	TipoAccion accion = TipoAccion::Error;
	//Estado o Regla reduccion
	int numero = -1; 
};


struct CodigoRegla { //Parametros para ubicar una regla de la lista de reglas
	int regla; //valex, profundidad
};
struct CodigoReglaToken { //Parametros para poder tener una pila con CodigoTokenizado y CodigoReglamentado al mismo tiempo
	enum Tipo { CodigoRegla, CodigoToken };
	int index; //CodigoTokenizado y CodigoReglamentado
	Tipo tipo;
};


struct NodoSintactico {
	CodigoReglaToken* data;
	NodoSintactico** children;
};


//Variables
//Read Files
vector<string> Tokens; //String de Tokens
vector<string> Reglas; //String de Reglas
vector<string> palabras_reservadas; //String de Plabras Reserc¿vadas

vector<vector<int>> Lexico; //Matriz del Lexico
vector<int> estadoToken; //Para poder ver los estados finales y aceptables

vector<vector<AccionSintactico>> Sintactico; //Matriz del sintactico
vector<vector<ReglaToken>> SintacticoReglas; //Para poder aplicar las reducciones

//Resultado Lexico
vector<CodigoToken> CodigoTokenizado; //Codigo Tokenizado
vector<Identificador> TablaIdentificadores; //Tabla Identificadores

//Resultado Sintactico
vector<CodigoRegla> CodigoReglamentado; //Codigo Tokenizado
NodoSintactico* ArbolSintactico;

//Lexico + Sintactico
vector<CodigoReglaToken> Codigo;