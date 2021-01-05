#ifndef BRANCHREGISTER_H_
#define BRANCHREGISTER_H_

#include"Branch.h"

using UGit::Branch;

namespace UGit{
	struct BranchRegister;

	// Precondicion: @branchRegister es una instancia valida.
	// Postcondicion: Agrega si no existe @item en @BranchRegister.
	void Add(BranchRegister* branchRegister, Branch* item);

	// Precondicion: @branchRegister es una instancia valida.
	// Postcondicion: Devuelve True si @item esta contenido en @branchRegister. Caso contrario retorna False.
	bool Contains(const BranchRegister* branchRegister, const Branch* item);

	// Precondicion: @branchRegister es una instancia valida.
	// Postcondicion: Devuelve la catidad de items de @branchRegister.
	int Count(const BranchRegister* branchRegister);

	// Precondicion: @branchRegister es una instancia valida.
	// Postcondicion: Devuelve branch si encuentra alguno que posee @name como nombre.
	//				  Caso contrario retorna Null.
	UGit::Branch* Get(const BranchRegister* branchRegister,string name);

	// Precondicion: ninguna.
	// Postcondicion: Devuelve true si encuentra alguno que posee @name como nombre.
	//				  Caso contrario retorna false.
	bool Exists(const BranchRegister* branchRegister,string branchName);

	// Precondicion:
	// Postcondicion: Libera todos los recursos asociados a branchRegister.
	void Destroy();

	// Precondicion: Ninguna
	// Postcondicion: 	Obtiene el BranchRegister actual como unica instancia
	BranchRegister* GetInstance();

	// Precondicion: @branchRegister es una instancia valida.
	// Postcondicion: 	Si @branchName pertence a @branchRegister lo elimina.
	void Remove(BranchRegister* branchRegister,Branch *item);


};


#endif
