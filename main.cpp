#include <iostream>
#include <string>
#include "Git.h"
#include "Branch.h"
#include "Commit.h"
#include "Context.h"
#include "DateTime.h"


using std::string;
using namespace std;

// HOOKS
void LogCommit(void* commit);
void LogBranch(void* branch);

const char Numbers[7]="123456";
const int ChangesByBranch = 6;
void AddAllDeveloperFeatureChanges(UGit::Git* git, string branchNames[], int count);
void AddChanges(UGit::Git* git, string branchName);
void AddHotFixes(UGit::Git* git, string branchName);
UGit::Git* BuildGitEnvironment();
Branch** CreateBranches(UGit::Git* git, Branch* baseBranch, string branchNames[], int count);
void PrepareRelease(UGit::Git* git, Branch* releaseBranch, Branch** featureBranches, int featureBranchCount);

void testUserRandom();

int main() {
	UGit::Git* git = BuildGitEnvironment();
	Branch* head = UGit::CreateBranch(git, "master", NULL);
	string Features[3]={"Login", "Alta investigadores", "Reporte investigadores"};
	Branch** featureBranches = CreateBranches(git, head, Features, 3);
	AddHotFixes(git, "master");
	AddAllDeveloperFeatureChanges(git, Features, 3);
	PrepareRelease(git, head, featureBranches, 3);
	UGit::LogGraph(git, "master", false);
	UGit::Destroy(head);
	UGit::Destroy(git);
	return 0;
}

void PrepareRelease(UGit::Git* git, Branch* releaseBranch, Branch** featureBranches, int featureBranchCount){
	for(int i=0; i < featureBranchCount; ++i){
		UGit::Merge(git, UGit::GetName(featureBranches[i]), UGit::GetName(releaseBranch));
		UGit::DeleteBranch(git, UGit::GetName(featureBranches[i]));
	}
}

UGit::Git* BuildGitEnvironment(){
	UGit::Git* git = UGit::CreateGit();
	UGit::AddHook(git, UGit::GitEvent::NewBranchCreated, LogBranch);
	UGit::AddHook(git, UGit::GitEvent::NewCommitAdded, LogCommit);

	return git;
}

Branch** CreateBranches(UGit::Git* git, Branch* baseBranch, string branchNames[], int count){
	Branch** branches = new Branch*[count];
	for(int i=0; i<3; ++i){
		branches[i] = UGit::CreateBranch(git, branchNames[i], baseBranch);
	}

	return branches;
}

void AddAllDeveloperFeatureChanges(UGit::Git* git, string branchNames[], int count){
	for(int i=0; i<count; ++i){
		AddChanges(git, branchNames[i]);
	}
}

void LogCommit(void* commit){
	if(commit!=NULL){
		cout<<"commit "<<UGit::GetShortHashCode((Commit*)commit)<<" \""<<UGit::GetMessage((Commit*)commit)<<"\"";
		cout<<endl;
	}
}

void LogBranch(void* branch){
	if(branch!=NULL){
		cout<<"Se creo el branch ["<<UGit::GetName((Branch*)branch)<<"]"<<endl;
	}
}

void AddChanges(UGit::Git* git, string branchName){
	for(int i = 0; i<ChangesByBranch;++i){
		string commitMessage = "Cambio #";
		commitMessage+= Numbers[i];
		commitMessage+= (" en " + branchName);
		UGit::NewCommit(git, branchName, commitMessage);
	}
}

void AddHotFixes(UGit::Git* git, string branchName){
	for(int i = 0; i<ChangesByBranch;++i){
		string commitMessage = "Hot fix #";
		commitMessage+=" Hot fix #";
		commitMessage+=Numbers[i];
		commitMessage+=(" en " + branchName);
		UGit::NewCommit(git, branchName, commitMessage);
	}
}

void testUserRandom(){
	string test=UUser::GetNickName(UContext::GetCurrentUser());
	cout<<test<<endl;
}
