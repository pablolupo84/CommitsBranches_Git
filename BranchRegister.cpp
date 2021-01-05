#include "Lista.h"
#include "BranchRegister.h"
#include "Branch.h"

UGit::BranchRegister* Create();

UGit::BranchRegister* uniqueInstanceBranch=Create();

struct UGit::BranchRegister{
	UndavList::List* list;
};

UGit::BranchRegister* UGit::GetInstance(){
	return uniqueInstanceBranch;
}

UGit::BranchRegister* Create(){
	UGit::BranchRegister* branchRegister = new UGit::BranchRegister;
	branchRegister->list = UndavList::CreateListEmpty();
	return branchRegister;
}

void UGit::Add(UGit::BranchRegister* branchRegister, Branch* item){
	if(!Contains(branchRegister, item )){
		UndavList::AddToBegin(branchRegister->list,item);
	}
}

bool UGit::Contains(const UGit::BranchRegister* branchRegister, const Branch* item){
	bool contiene = false;
	UndavList::IteratorListitems::Iterator* iterador = UndavList::IteratorListitems::Begin(branchRegister->list);
	while(!UndavList::IteratorListitems::IsTheEnd(iterador)&& !contiene){
		Branch* itemActual = (Branch*)UndavList::IteratorListitems::ObtainsItem(iterador);
		if(UGit::Equals(itemActual, item)){
			contiene = true;
		}
		UndavList::IteratorListitems::Next(iterador);
	}
	UndavList::IteratorListitems::Destroy(iterador);
	return contiene;
}

int UGit::Count(const UGit::BranchRegister* branchRegister){
	return UndavList::Count(branchRegister->list);
}

void UGit::Remove(UGit::BranchRegister* branchRegister,Branch *item){
	UndavList::RemoveItem(branchRegister->list,item);
}

UGit::Branch* UGit::Get(const UGit::BranchRegister* branchRegister,string name){
	bool encontrado=false;
	UGit::Branch* auxiliar=NULL;
	UndavList::IteratorListitems::Iterator* iterador=UndavList::IteratorListitems::Begin(branchRegister->list);
	while(!UndavList::IteratorListitems::IsTheEnd(iterador) && encontrado!=true){
		UGit::Branch* branchActual= (UGit::Branch*)UndavList::IteratorListitems::ObtainsItem(iterador);
		encontrado=UGit::GetName(branchActual)==name;
		if(encontrado){
			auxiliar=branchActual;
		}
		UndavList::IteratorListitems::Next(iterador);
	}
	UndavList::IteratorListitems::Destroy(iterador);
	return auxiliar;
}

void UGit::Destroy(){
	if(uniqueInstanceBranch!=NULL){
		UndavList::Destroy(uniqueInstanceBranch->list);
		delete(uniqueInstanceBranch);
		uniqueInstanceBranch=NULL;
	}
}

bool UGit::Exists(const BranchRegister* branchRegister,string branchName){
	return UGit::Get(branchRegister,branchName)!=NULL;
}
