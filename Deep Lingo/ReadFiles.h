#pragma once

vector<string> Tokens;
vector<string> palabras_reservadas;

vector<vector<int>> matrizLexico;
vector<int> estadoToken;
string programa;

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

void ReadFileLexico() {
	int i = 0, j = 0;
	ifstream archivo("matrizLexico.txt");
	string fila, celda, dato;
	if (archivo.is_open()) {
		i = 0;
		while (getline(archivo, fila)) {
			istringstream SSfila(fila);
			matrizLexico.resize(i + 1);
			j = 0;
			while (getline(SSfila, celda, '\t')) {
				matrizLexico[i].resize(j + 1);
				matrizLexico[i][j] = stoi(celda);
				j++;
			}
			i++;
		}
		archivo.close();
	}
}

void ReadFileTokens() {
	int i = 0, j = 0;
	ifstream archivo("tokens.txt");
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