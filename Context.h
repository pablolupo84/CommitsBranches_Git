#ifndef CONTEXT_H_
#define CONTEXT_H_

#include "User.h"
#include "DateTime.h"
using UUser::User;
using UDateTime::DateTime;


namespace UContext{

	// Precondicion: Ninguna
	// Postcondicion: Obtiene el usuario actual. Debe devolver un usuario random de entre 5.
	User* GetCurrentUser();

	// Precondicion: Ninguna
	// Postcondicion: Devuelve siempre un Fecha y hora distinta superior a la ultima dada
	DateTime* GetNow();

	// Precondicion: Ninguna
	// Postcondicion: Libera todos los recursos asociados al contexto
	void DestroyContext();
}

#endif
