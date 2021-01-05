#include "Branch.h"
#include "BranchRegister.h"
#include "Git.h"
#include "Lista.h"
#include "CommitBag.h"
#include "CommitGraph.h"
#include "BFS.h"
#include <iostream>


using UBfs::RecorridoAnchura;
using UGit::Branch;
using UGit::Git;
using UGit::GitEvent;
using UndavList::List;
using UGitCommitGraph::CommitGraph;

struct UGit::Git{
	UndavList::List* listaHooksBranchs;
	UndavList::List* listahooksCommits;
	UGitCommitGraph::CommitGraph* commitGraph;
};

UGit::CommitBag* garbageCollector = UGit::CreateBag();
UGitCommitGraph::CommitGraph* commitGraph = UGitCommitGraph::Create();


/*Funciones auxiliares*/
void CollectCommit(void* commit);
void FreeGarbageCollector();
void ShowLog(Commit* commit);

//Precondicion: @lista es una instancia valida , @item es una instancia valida
//Postcondicion: ejecuta todos los punteros a funciones con los parametros item.
void RunHooks(UndavList::List* list,void * item){
	UndavList::IteratorListitems::Iterator* iterador=UndavList::IteratorListitems::Begin(list);
	while(!UndavList::IteratorListitems::IsTheEnd(iterador)){
		UGit::Hook miHook= (UGit::Hook)UndavList::IteratorListitems::ObtainsItem(iterador);
		miHook(item);
		UndavList::IteratorListitems::Next(iterador);
	}
	UndavList::IteratorListitems::Destroy(iterador);
}

UGit::Git* UGit::CreateGit(){
	UGit::Git* git = new UGit::Git;
	git->listaHooksBranchs=UndavList::CreateListEmpty();
	git->listahooksCommits=UndavList::CreateListEmpty();
	git->commitGraph=UGitCommitGraph::Create();
	return git;
}

UGit::Branch* UGit::CreateBranch(Git* git, string branchName, Branch* baseBranch){
	UGit::Branch* myBranch=NULL;
	UGit::BranchRegister* instance = UGit::GetInstance();
	if(!UGit::Get(instance,branchName)){
		myBranch=(baseBranch!=NULL)?UGit::CreateBranch(branchName,UGit::GetLastCommit(baseBranch)):UGit::CreateBranch(branchName,NULL);
		UGit::Add(instance,myBranch);
		RunHooks(git->listaHooksBranchs,myBranch);
	}
	return myBranch;
}

void UGit::DeleteBranch(Git* git, string branchName){
	UGit::BranchRegister* instance = UGit::GetInstance();
	UGit::Remove(instance,UGit::Get(instance,branchName));
}

UGit::Commit* UGit::NewCommit(Git* git, string branchName, string message){
	UGit::Commit* myCommit=NULL;
	UGit::BranchRegister* instance = UGit::GetInstance();
	UGit::Branch* myBranch=UGit::Get(instance,branchName);
	if(myBranch!=NULL){
		UGit::Commit* myLastCommit=UGit::GetLastCommit(myBranch);
		myCommit=UGit::CreateCommit(myLastCommit,message);
		UGitCommitGraph::Connect(git->commitGraph,myCommit,myLastCommit);
		SetLastCommit(myBranch,myCommit);
		CollectCommit(myCommit);
		RunHooks(git->listahooksCommits,myCommit);
	}
	return myCommit;
}

void UGit::AddHook(Git* git, UGit::GitEvent event, Hook hook){
	switch (event){
		case UGit::GitEvent::NewBranchCreated:
												UndavList::Add(git->listaHooksBranchs,(void*)hook);
												break;
		case UGit::GitEvent::NewCommitAdded:
												UndavList::Add(git->listahooksCommits,(void*)hook);
												break;
	}
}

bool IsEqualsCommit(Branch *from, Branch *to) {
    string commitFrom = GetLastCommit(to) == NULL ? "" : GetHashCode(GetLastCommit(to));
    string commitTo = GetLastCommit(from) == NULL ? "" : GetHashCode(GetLastCommit(from));
    return commitFrom==commitTo;
}

void UGit::Merge(Git* git, string from, string to){
	UGit::BranchRegister* instance = UGit::GetInstance();
	if(UGit::Get(instance,from)!=NULL && UGit::Get(instance,to)!=NULL && IsEqualsCommit(UGit::Get(instance,from),UGit::Get(instance,to))!=true){
			UGit::CommitBag* parents= UGit::CreateBag();
			Commit* commitFrom=UGit::GetLastCommit(UGit::Get(instance,from));
			Commit* commitTo=UGit::GetLastCommit(UGit::Get(instance,to));
			UGit::Add(parents,commitFrom);
			UGit::Add(parents,commitTo);

			string message="branch [" + UGit::GetName(UGit::Get(instance,from))+"]" + " merged on [" + UGit::GetName(UGit::Get(instance,to)) +"]";
			UGit::Commit* myCommit = UGit::CreateCommit(parents,message);
			UGit::SetLastCommit(UGit::Get(instance,to),myCommit);

			UGitCommitGraph::Connect(git->commitGraph, myCommit,commitFrom);
			UGitCommitGraph::Connect(git->commitGraph, myCommit,commitTo);
			RunHooks(git->listahooksCommits,myCommit);
		}
}

void UGit::LogGraph(Git *git, string branchName, bool oneLine) {
    if (UGit::Exists(UGit::GetInstance(),branchName)) {
    	UGit::Branch * branch = UGit::Get(UGit::GetInstance(),branchName);
    	Commit * lastCommit = UGit::GetLastCommit(branch);
    	UGitCommitGraph::print(git->commitGraph);
    	UBfs::Crear(git->commitGraph, lastCommit, ShowLog);
    }
}

void UGit::Destroy(Git* git){
	UndavList::Destroy(git->listaHooksBranchs);
	UndavList::Destroy(git->listahooksCommits);
	FreeGarbageCollector();
	delete git;
}

void CollectCommit(void* commit){
    if(commit!=NULL){
        UGit::Add(garbageCollector, (Commit*) commit);
    }
}

void FreeGarbageCollector(){
    if(garbageCollector!=NULL){
        UGit::UCommitBagIterator::CommitBagIterator* iterator = UGit::UCommitBagIterator::Begin(garbageCollector);
        while(!UGit::UCommitBagIterator::IsEnd(iterator)){
            Commit* commit = UGit::UCommitBagIterator::GetCommit(iterator);
            UGit::DestroyCommit(commit);
            UGit::UCommitBagIterator::Next(iterator);
        }
        UGit::UCommitBagIterator::DestroyIterator(iterator);
        UGit::DestroyBag(garbageCollector);
        garbageCollector = NULL;
    }
}

void ShowLog(Commit* commit){
    Commit * myCommit = commit;
    std::cout << "Commit " << UGit::GetHashCode(myCommit) << " (branch)" <<std::endl;
    std::cout << "Author: " << UUser::GetNickName(UGit::GetAuthor(myCommit)) <<std::endl;
    std::cout << "Date: " << UDateTime::ToFormat(UGit::GetDate(myCommit), UDateTime::DDMMYYYY_HHmmss) <<std::endl;
    std::cout << "\t " << UGit::GetMessage(myCommit) << std::endl;
}
