#include <ctime>
#include <unistd.h>

#include "Context.h"
#include "Commit.h"
#include "CommitBag.h"
#include "DateTime.h"
#include "User.h"

using namespace UContext;

using std::string;
using UDateTime::DateTime;
using UUser::User;
using UGit::UCommitBagIterator::CommitBagIterator;

typedef UGit::UCommitBagIterator::CommitBagIterator* Iterador;

struct UGit::Commit{
	string message;
	string HashCode;
	DateTime* dateTime;
	User* user;
	Commit* parent;
};

string ShortHashCode(string hashcode);
string CreateHashCode(int longitud);
unsigned int InicializarSemilla();

unsigned int InicializarSemilla(){
	srand(time(NULL));
	return rand();
}

const unsigned int MAX_HASH_CODE=40;
unsigned int semillaRandom=InicializarSemilla();

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
	for (int i = 0; i < longitud; ++i){
		hashcode += alphanum[rand() % (sizeof(alphanum) - 1)];
	}
	return hashcode;
}

UGit::Commit* UGit::CreateCommit(UGit::Commit* parent, string message){
	UGit::Commit* commit = new UGit::Commit;
	commit->HashCode=CreateHashCode(MAX_HASH_CODE);
	commit->dateTime=UContext::GetNow();
	commit->user=UContext::GetCurrentUser();
	commit->message=message;
	commit->parent=parent;
	return commit;
}

UGit::Commit* UGit::CreateCommit(void* parents, string message){
	UGit::Commit* commit = new UGit::Commit;
	commit->HashCode=CreateHashCode(MAX_HASH_CODE);
	commit->dateTime=UContext::GetNow();
	commit->user=UContext::GetCurrentUser();
	commit->message=message;
	commit->parent=(UGit::Commit*)UGit::CreateBag();
	UGit::UCommitBagIterator::CommitBagIterator* Iterador = UGit::UCommitBagIterator::Begin((UGit::CommitBag*)parents);
	while(UGit::UCommitBagIterator::IsEnd(Iterador)){
		UGit::Add((UGit::CommitBag*)commit->parent,(UGit::Commit*)Iterador);
		UGit::UCommitBagIterator::Next(Iterador);
	}
	UGit::UCommitBagIterator::DestroyIterator(Iterador);
	return commit;
}

UDateTime::DateTime* UGit::GetDate(const UGit::Commit* commit){
	return commit->dateTime;
}

UUser::User* UGit::GetAuthor(const UGit::Commit* commit){
	return commit->user;
}

string UGit::GetMessage(const UGit::Commit* commit){
	return commit->message;
}

void* UGit::GetParents(const UGit::Commit* commit){
	return commit->parent;
}

string UGit::GetHashCode(const UGit::Commit* commit){
	return commit->HashCode;
}

string UGit::GetShortHashCode(const UGit::Commit* commit){
	return ShortHashCode(commit->HashCode);
}

void UGit::DestroyCommit(UGit::Commit* commit){
	UDateTime::DestroyDateTime(commit->dateTime);
	delete commit;
}
