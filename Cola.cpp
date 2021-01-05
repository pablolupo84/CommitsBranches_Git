#include <iostream>
#include "Cola.h"


struct NodoCola{
	NodoCola* siguiente;
	void* item;
};

struct UndavCola::Cola{
	NodoCola *ultimo; // O(1) en la primitiva Encolar
	NodoCola *primero;// Frente de la cola O(1) para la primitiva Desencolar
};

UndavCola::Cola* UndavCola::CrearCola(){
	Cola* nuevaCola = new Cola;
	nuevaCola->primero = nuevaCola->ultimo = NULL;
	return nuevaCola;
}

NodoCola* CrearUltimoNodo(void* item){
	NodoCola* nodo = new NodoCola;
	nodo->item =  item;
	nodo->siguiente = NULL;
	return nodo;
}

// O(1)
void UndavCola::Encolar(Cola* cola, void* item){
	NodoCola* nuevoUltimo = CrearUltimoNodo(item);
	if(EstaVacia(cola)){
		cola->primero=nuevoUltimo;
	}else{
		cola->ultimo->siguiente=nuevoUltimo;
	}
	cola->ultimo=nuevoUltimo;
}

// Desencolar
void* UndavCola::Desencolar(Cola* cola){
	void* item = NULL;

	if(!EstaVacia(cola)){
		NodoCola* nuevoPrimero = cola->primero->siguiente;
		item = cola->primero->item;
		delete cola->primero;
		cola->primero = nuevoPrimero;
		if(cola->primero == NULL){
			cola->ultimo = NULL;
		}
	}
	return item;
}


bool UndavCola::EstaVacia(const Cola* cola){
	return cola->primero == NULL;
}

void UndavCola::Destruir(Cola* cola){
	NodoCola* iterador=cola->primero;
	while(iterador!=NULL){
		NodoCola* auxiliar = iterador;
		iterador = iterador->siguiente;
		delete auxiliar;
	}
}
