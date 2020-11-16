#include "Context.h"
#include "Commit.h"
#include "DateTime.h"
#include "User.h"
#include <string>
#include <ctime>
#include <unistd.h>
#include <iostream>

using namespace UContext;

using std::string;
using UDateTime::DateTime;
using UUser::User;


struct UGit::Commit{
	string message;
	string HashCode;
	DateTime* dateTime;
	User* user;
	Commit* parent;
};

const unsigned int MAX_HASH_CODE=40;

//Declaraciones de Funciones Auxiliares a utilziar
string ShortHashCode(string hashcode);
string CreateHashCode(int longitud);

// Precondicion: @hashcode es un hashcode
// Postcondicion: Devuelve los primero ocho caracteres del hash code
string ShortHashCode(string hashcode){
    return hashcode.substr(0,8);
}


// Precondicion: @longitud es el tamanio del hashCode
// Postcondicion: Retorna un string alfapnumerico de @longitud como tamanio.
string CreateHashCode(int longitud){
	string hashcode;
	static const char alphanum[] ="0123456789abcdefghijklmnopqrstuvwxyz";
	srand(rand());
	for (int i = 0; i < longitud; ++i){
		hashcode += alphanum[rand() % (sizeof(alphanum) - 1)];
	}
	return hashcode;
}


// Precondicion: Ninguna
// Postdondicion: Crea una instancia valida de un Commit el cual debe tener
// - Un commit predecesor (@parent) el cual puede ser NULL
// - Un mensaje (@message) que describe los objetivos de los cambios que se hicieron en el commit
// - Un HashCode que por ahora sera simplemente un codigo alfanumerico de 40 caracteres randoms, los caracteres deben estar en minusculas
// - Una fecha y hora actual del momento de creacion obtenida de Context.h
// - El usuario que se encuentra en el contexto de la operacion obtenido de Context.h
UGit::Commit* UGit::CreateCommit(UGit::Commit* parent, string message){
	UGit::Commit* commit = new UGit::Commit;

	commit->HashCode=CreateHashCode(MAX_HASH_CODE);
	commit->dateTime=UContext::GetNow();
	commit->user=UContext::GetCurrentUser();
	commit->message=message;
	commit->parent=parent;

	return commit;
}

// Precondicion: @commit es una intancia valida
// Postcondicion: Devuelve la fecha y hora de creacion del @commit
UDateTime::DateTime* UGit::GetDate(const UGit::Commit* commit){

	return commit->dateTime;
}

// Precondicion: @commit es una intancia valida
// Postcondicion: Devuelve el usuario autor del @commit
UUser::User* UGit::GetAuthor(const UGit::Commit* commit){

	return commit->user;
}

// Precondicion: @commit es una intancia valida
// Postcondicion: Devuelve el mensaje asociado al @commit
string UGit::GetMessage(const UGit::Commit* commit){

	return commit->message;
}

// Precondicion: @commit es una intancia valida
// Postcondicion: Devuelve el commit predecesor de @commit
UGit::Commit* UGit::GetParent(const UGit::Commit* commit){

	return commit->parent;
}

// Precondicion: @commit es una intancia valida
// Postcondicion: Devuelve el hash code de @commit
string UGit::GetHashCode(const UGit::Commit* commit){

	return commit->HashCode;
}

// Precondicion: @commit es una intancia valida
// Postcondicion: Devuelve los primero ocho caracteres del hash code de @commit //8
string UGit::GetShortHashCode(const UGit::Commit* commit){

	return ShortHashCode(commit->HashCode);
}

// Precondicion: @commit es una intancia valida
// Postcondicion: Libera todos los recursos asociados de @commit
void UGit::DestroyCommit(UGit::Commit* commit){
	if(commit!=NULL){
		delete commit;
	}
}
