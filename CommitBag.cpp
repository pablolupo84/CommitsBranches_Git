#include "Commit.h"
#include "CommitBag.h"
#include "Lista.h"

using UGit::Commit;
using UGit::UCommitBagIterator::CommitBagIterator;
using UndavList::List;
typedef UndavList::IteratorListitems::Iterator* Iterator;


struct UGit::CommitBag{
	UndavList::List * listaBag;
};

UGit::CommitBag* UGit::CreateBag(){
	UGit::CommitBag* bag = new CommitBag;
	bag->listaBag=UndavList::CreateListEmpty();
	return bag;
}

void UGit::Add(CommitBag* bag, Commit* commit){
	UndavList::AddToEnd(bag->listaBag,commit);
}

int UGit::Count(CommitBag* bag){
	return UndavList::Count(bag->listaBag);
}

void UGit::DestroyBag(CommitBag* bag){
	UndavList::Destroy(bag->listaBag);
	delete bag;
}

struct UGit::UCommitBagIterator::CommitBagIterator {
	Iterator iterator;
};

CommitBagIterator* UGit::UCommitBagIterator::Begin(UGit::CommitBag *bag) {
    CommitBagIterator * iterator = new CommitBagIterator;
    iterator->iterator = UndavList::IteratorListitems::Begin(bag->listaBag);
    return iterator;
}

void UGit::UCommitBagIterator::Next(const CommitBagIterator* bagIterator){
	UndavList::IteratorListitems::Next(bagIterator->iterator);
}

bool UGit::UCommitBagIterator::IsEnd(const CommitBagIterator *bagIterator) {
    return UndavList::IteratorListitems::IsTheEnd(bagIterator->iterator);
}

UGit::Commit* UGit::UCommitBagIterator::GetCommit(CommitBagIterator *bagIterator) {
    return (UGit::Commit *)UndavList::IteratorListitems::ObtainsItem(bagIterator->iterator);
}

void UGit::UCommitBagIterator::DestroyIterator(CommitBagIterator *bagIterator) {
	UndavList::IteratorListitems::Destroy(bagIterator->iterator);
	delete bagIterator;
}
