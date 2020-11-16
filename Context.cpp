#include "DateTime.h"
#include "Context.h"
#include "User.h"
#include <iostream>

using UUser::User;
using UDateTime::DateTime;

UUser::User* uniqueInstance= UUser::CreateUser("@srcoco");

// Precondicion: Ninguna
// Postcondicion: Obtiene el usuario actual.
// Para la entrega actual debe crear un unico usuario
// y siempre debe devolver esa misma instancia de usuario
UUser::User* UContext::GetCurrentUser(){
	return uniqueInstance;
}

// Precondicion: Ninguna
// Postcondicion: Libera todos los recursos asociados al contexto
UDateTime::DateTime* UContext::GetNow(){
	return UDateTime::Now();
}

// Precondicion: Ninguna
// Postcondicion: Libera todos los recursos asociados al contexto
void UContext::DestroyContext(){
	uniqueInstance=NULL;
}
