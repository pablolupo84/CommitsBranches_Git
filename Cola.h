#ifndef COLA_H_
#define COLA_H_

namespace UndavCola{
	struct Cola;
	Cola* CrearCola();
	// O(1)
	void Encolar(Cola* cola, void* item);
	// O(1)
	// FIFO
	void* Desencolar(Cola* cola);
	bool EstaVacia(const Cola* cola);
	void Destruir(Cola* cola);
}




#endif /* COLA_H_ */
