#include "Commit.h"
#include "Branch.h"

using UGit::Commit;
using std::string;

struct UGit::Branch{
	string name;
	Commit* last;
};

UGit::Branch* UGit::CreateBranch(string name, Commit* commit){
	UGit::Branch* branch=new UGit::Branch;
	branch->name=name;
	branch->last=commit;
	return branch;
}

string UGit::GetName(const Branch* branch){
	return branch->name;
}

UGit::Commit* UGit::GetLastCommit(const Branch* branch){
	return branch->last;
}

void UGit::SetLastCommit(Branch* branch, Commit* commit){
	branch->last=commit;
}

bool UGit::Equals(const Branch* branch1,const Branch* branch2){
	return GetName(branch1)==GetName(branch2);
}

void UGit::Destroy(Branch* branch){
	delete branch;
}
