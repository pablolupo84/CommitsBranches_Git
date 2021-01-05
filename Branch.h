#ifndef BRANCH_H_
#define BRANCH_H_

#include <string>
#include "Commit.h"

using UGit::Commit;
using std::string;

namespace UGit{
	struct Branch;

	 //Precondicion: Ninguna
	 //Postcondicion: Crea una instancia valida de Branch que tiene como ultimo commit a @commit
	Branch* CreateBranch(string name, Commit* commit);

	 //Precondicion: @branch es una instancia valida
	 //Postcondicion: Devuelve el nombre del Branch.
	string GetName(const Branch* branch);

	 //Precondicion: @branch es una instancia valida
	 //Postcondicion: Devuelve el ultimo commit de @branch
	Commit* GetLastCommit(const Branch* branch);

	//Precondicion: @branch es una instancia valida
	//Postcondicion: Cambia el ultimo commit de @branch por @commit
	void SetLastCommit(Branch* branch, Commit* commit);

	//Precondicion: @branch es una instancia valida
	//Postcondicion: Libera todos los recursos asociados a branch
	void Destroy(Branch* branch);

	 //Precondicion: @branch1 y @branch2 son instancias validas.
	 //Postcondicion: Devuelve True si son iguales. Parametro que indica igualdad -> nombre.
	 //				  Caso contrario retorna False
	bool Equals(const Branch* branch1,const Branch* branch2);
}

#endif


