#include <string.h>
#include "User.h"
using std::string;
using UUser::User;

struct UUser::User{
	string nickname;
	string nombre;
	string apellido;
};

// Precondicion: Ninguna
// Postdondicion: Crea una instancia valida de un User el cual tiene como nick name @nickName y
// un string vacio como nombre y como apellido
UUser::User* UUser::CreateUser(string nickName){
	User* user=new User;
	user->nickname=nickName;
	user->nombre="";
	user->apellido="";

	return user;
}

// Precondicion: @user es una instancia valida
// Postcondicion: Devuelve el nick name de @user
string UUser::GetNickName(const User* user){
	return user->nickname;
}

// Precondicion: @user es una instancia valida
// Postcondicion: Devuelve el apellido de @user
string UUser::GetLastName(const User* user){
	return user->apellido;
}

// Precondicion: @user es una instancia valida
// Postcondicion: Devuelve el nombre de @user
string UUser::GetName(const User* user){
	return user->nombre;
}

// Precondicion: @user es una instancia valida
// Postcondicion: Cambia el nombre de @user por @name
void UUser::SetName(User* user, string name){
	user->nombre=name;
}

// Precondicion: @user es una instancia valida
// Postcondicion: Cambia el pellido de @user por @apellido
void UUser::SetLastName(User* user, string lastName){
	user->apellido=lastName;
}

// Precondicion: @user es una instancia valida
// Postcondicion: Libera todos los recursos asociados a @user
void UUser::DestroyUser(User* user){
	if (user!=NULL){
		delete(user);
	}
}
