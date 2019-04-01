#pragma once

//Programa
void ReadFilePrograma() {
	programa = "";
	ifstream archivo("programa.txt");
	if (archivo.is_open()) {
		char buffer[4096];
		while (archivo.read(buffer, sizeof(buffer)))
			programa.append(buffer, sizeof(buffer));
		programa.append(buffer, archivo.gcount());
		programa = programa + '\0';
		archivo.close();
	}
}

//Lexico
void ReadFileLexico() {
	int i = 0, j = 0;
	ifstream archivo("Lexico.txt");
	string fila, celda;
	if (archivo.is_open()) {
		i = 0;
		while (getline(archivo, fila)) {
			istringstream SSfila(fila);
			Lexico.resize(i + 1);
			j = 0;
			while (getline(SSfila, celda, '\t')) {
				Lexico[i].resize(j + 1);
				Lexico[i][j] = stoi(celda);
				j++;
			}
			i++;
		}
		archivo.close();
	}
}

void ReadFileTokens() {
	int i = 0, j = 0;
	ifstream archivo("LexicoTokens.txt");
	string fila, celda;
	if (archivo.is_open()) {
		i = 0;
		while (getline(archivo, fila)) {
			istringstream SSfila(fila);
			Tokens.resize(i + 1);
			estadoToken.resize(i + 1);
			j = 0;
			while (getline(SSfila, celda, '\t')) {
				if (j == 0) { if (celda != "") { Tokens[i] = celda; } else { j = 3; } }
				if (j == 1) { estadoToken[i] = stoi(celda); }
				j++;
			}
			if (j == 2) { i++; }
		}
		archivo.close();
	}
}

void ReadFilePalabrasReservadas() {
	ifstream archivo("palabras_reservadas.txt");
	string fila;
	if (archivo.is_open()) {
		while (getline(archivo, fila)) {
			palabras_reservadas.push_back(fila);
		}
		archivo.close();
	}
}


//Sintactivo
void ReadFileSintactico() {
	int i = 0, j = 0;
	ifstream archivo("Sintactico.txt");
	string fila, celda;
	if (archivo.is_open()) {
		i = 0;
		while (getline(archivo, fila)) {
			istringstream SSfila(fila);
			Sintactico.resize(i + 1);
			j = 0;
			while (getline(SSfila, celda, '\t')) {
				Sintactico[i].resize(j + 1);
				if (celda == "") {
					Sintactico[i][j].accion = Sintactico[i][j].Error;
					Sintactico[i][j].numero = -1;
				} else if (celda.substr(0, 1) == "a") {
					Sintactico[i][j].accion = Sintactico[i][j].Acceptable;
					Sintactico[i][j].numero = 0;
				} else if (celda.substr(0, 1) == "r") {
					Sintactico[i][j].accion = Sintactico[i][j].Reduce;
					Sintactico[i][j].numero = stoi(celda.substr(1, celda.length()));
				} else if (celda.substr(0, 1) == "s") {
					Sintactico[i][j].accion = Sintactico[i][j].Desplazate;
					Sintactico[i][j].numero = stoi(celda.substr(1, celda.length()));
				}
				j++;
			}
			i++;
		}
		archivo.close();
	}
}

void ReadFileSintacticoReglas() {
	int i = 0, j = 0, k = 0;
	ifstream archivo("SintacticoReglas.txt");
	string fila, celda, dato;
	if (archivo.is_open()) {
		i = 0;
		while (getline(archivo, fila)) {
			istringstream SSfila(fila);
			SintacticoReglas.resize(i + 1);
			j = 0;
			while (getline(SSfila, celda, '\t')) {
				if (j == 0) {
					SintacticoReglas[i].regla = stoi(celda);
				}else if (j == 1) {
					k = 0;
					istringstream SScelda(celda);										
					while (getline(SScelda, dato, ' ')) {
						if (dato.substr(0, 1) == "r") {
							SintacticoReglas[i].definicion.resize(k + 1);
							SintacticoReglas[i].definicion[k].tipo = SintacticoReglas[i].definicion[k].Regla;
							SintacticoReglas[i].definicion[k].index = stoi(dato.substr(1, dato.length()));
						}else if (dato.substr(0, 1) == "t") {
							SintacticoReglas[i].definicion.resize(k + 1);
							SintacticoReglas[i].definicion[k].tipo = SintacticoReglas[i].definicion[k].Token;
							SintacticoReglas[i].definicion[k].index = stoi(dato.substr(1, dato.length()));
						}
						k++;
					}
				}
				j++;
			}
			i++;
		}
		archivo.close();
	}
}

void ReadFileReglas() {
	ifstream archivo("reglas.txt");
	string fila;
	if (archivo.is_open()) {
		while (getline(archivo, fila)) {
			Reglas.push_back(fila);
		}
		archivo.close();
	}
}

//Todos
void ReadFiles() {
	//General
	ReadFilePrograma();
	//Lexico
	ReadFileLexico();
	ReadFileTokens();
	ReadFilePalabrasReservadas();
	//Sintactico
	ReadFileSintactico();
	ReadFileSintacticoReglas();
	ReadFileReglas();
}