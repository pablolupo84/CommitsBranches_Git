#include "User.h"
using std::string;
using UUser::User;

struct UUser::User{
	string nickname;
	string name;
	string lastname;
};

UUser::User* UUser::CreateUser(string nickName){
	User* user=new User;
	user->nickname=nickName;
	user->name="";
	user->lastname="";
	return user;
}

string UUser::GetNickName(const User* user){
	return user->nickname;
}

string UUser::GetLastName(const User* user){
	return user->lastname;
}

string UUser::GetName(const User* user){
	return user->name;
}

void UUser::SetName(User* user, string name){
	user->name=name;
}

void UUser::SetLastName(User* user, string lastName){
	user->lastname=lastName;
}

void UUser::DestroyUser(User* user){
	delete(user);
}
