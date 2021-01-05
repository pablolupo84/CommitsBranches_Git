#ifndef COMMITBAG_H_
#define COMMITBAG_H_

#include "Commit.h"

namespace UGit{
	struct CommitBag;

	//Precondicion: -
	//Postcondicion: -
	CommitBag* CreateBag();

	//Precondicion: -
	//Postcondicion: -
	void Add(CommitBag* bag, Commit* commit);

	//Precondicion: -
	//Postcondicion: -
	int Count(CommitBag* bag);

	//Precondicion: -
	//Postcondicion: -
	void DestroyBag(CommitBag* bag);

	namespace UCommitBagIterator{
		struct CommitBagIterator;
		CommitBagIterator* Begin(CommitBag* bag);
		void Next(const CommitBagIterator* bagIterator);
		bool IsEnd(const CommitBagIterator* bagIterator);
		Commit* GetCommit(CommitBagIterator* bagIterator);
		void DestroyIterator(CommitBagIterator* commit);
	}
}

#endif
