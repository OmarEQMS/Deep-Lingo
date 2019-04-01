#pragma once
/*
cout << "Token(" << Tokens[Programa->children[0]->data->token->token] << ") ";
cout << "Reglas(" << Reglas[Programa->children[0]->data->regla->regla] << ") ";
cout << "E[" << estados.back() << "] ";
cout << "ACC" << endl;
cout << "D(" << accion.numero << ")" << endl;
cout << "R(" << accion.numero << ")" << endl;
*/

AccionSintactico SigAccion(int estado) {
	int indice = 0;
	if (Programa->children[0]->data->tipo == Programa->children[0]->data->Token) {
		indice = Programa->children[0]->data->token->token;
	}else if(Programa->children[0]->data->tipo == Programa->children[0]->data->Regla) {
		indice = Tokens.size() + Programa->children[0]->data->regla->regla;
	}
	return Sintactico[estado][indice];
}

void AutomataSintactico() {
	//Programa - Cadena de Entrada
	NodoPrograma* pila = new NodoPrograma();
	vector<int> estados;
	estados.push_back(0);
	bool fin = false;

	while (!fin) {
		AccionSintactico accion = SigAccion(estados.back());
		if (accion.accion == AccionSintactico::Acceptable) {
			Programa = pila;
			fin = true;
		} else if (accion.accion == AccionSintactico::Desplazate) {
			estados.push_back(accion.numero);
			pila->AddChild(Programa->children[0], pila->children.size());
			Programa->RemoveChild(0);
		} else if (accion.accion == AccionSintactico::Reduce) {
			ReduccionRegla reduccion = SintacticoReglas[accion.numero];
			int cantReglas = reduccion.definicion.size();
			int cantPila = pila->children.size();
			if (cantPila - cantReglas < 0) { cout << "Hubo un Error, no se pudo simplificar , tamaños diferentes" << endl; Programa = pila; fin = true; break; }

			bool iguales = true;
			for (int i = cantPila - cantReglas; i < cantPila; i++) {
				if ((pila->children[i]->data->tipo == pila->children[i]->data->Regla) && (reduccion.definicion[i - cantPila + cantReglas].tipo == reduccion.definicion[i - cantPila + cantReglas].Regla)) {
					if ((pila->children[i]->data->regla->regla != reduccion.definicion[i - cantPila + cantReglas].index)) {
						iguales = false;
					}
				}else if ((pila->children[i]->data->tipo == pila->children[i]->data->Token) && (reduccion.definicion[i - cantPila + cantReglas].tipo == reduccion.definicion[i - cantPila + cantReglas].Token)) {
					if (pila->children[i]->data->token->token != reduccion.definicion[i - cantPila + cantReglas].index) {
						iguales = false;
					}
				}
			}
			if (!iguales) { cout << "Hubo un Error, no se pudo simplificar, tokens no iguales" << endl; Programa = pila; fin = true; break; }

			//Todo perfecto para reducir
			//Voy a agregar los N de la pila como hijos de regla en el mismo orden al inicio
			NodoPrograma* regla = new NodoPrograma(new CodigoRegla(reduccion.regla));
			for (int i = cantPila - cantReglas; i < cantPila; i++) {
				estados.pop_back(); //Popeo la misma cantidad de atributos
				regla->AddChild(pila->children[cantPila - cantReglas], i - cantPila + cantReglas); //Siempre meto el mismo, porque siempre borro el mismo
				pila->RemoveChild(cantPila - cantReglas);
			}
			Programa->AddChild(regla, 0);
		} else if (accion.accion == AccionSintactico::Error) {
			cout << "Hubo un Sintax Error, no se esperaba este caracter " << endl;
			fin = true;
		}

	}
		
}