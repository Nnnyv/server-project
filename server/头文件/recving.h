#pragma once
#include<thread>
#include"internet.h"
#include"user.h"



class recving_lyh {
public:
	static int main(SOCKET socket);
	recving_lyh(SOCKET soc) :message(soc) {
		socket = soc;
	}
	int start();

private:
	user_lyh* use;
	message_lyh message;
	SOCKET socket;
	static int SHOW;
	//user_lyh* finduser(string &str);
	//group_lyh* findgroup(string& str);
	int doit();
	int login();
	int send();
	int checkfriend();//0 0 1
	int addfriend();//0 0 2
	int delfriend();//0 0 3
	int chatfriend();//0 0 4
	int applyfriend();//0 0 6
	int checkgroup();//0 1 1
	int addgroup();//0 1 2
	int deletegroup();//0 1 3
	int chatgroup();//0 1 4
	int managegroup();//0 1 6
	int newmanagergroup_qq(std::string &gid);
	int delmanagergroup_qq(std::string &str);
	int kickgroup_leader(std::string& id);
	int checkgroup_leader(std::string& gid);
	int cnamegroup_leader(std::string& gid);
	int ckindqqgroup_leader(std::string& gid);
	int kickgroup_manager(std::string& gid);
	int checkgroup_manager(std::string& gid);
	int cnamegroup_manager(std::string& gid);
	int creatgroup();// 0 1 11
	int pullgroup();// 0 1 17
	int songroup();//0 1 13
	int dataset();//0 2 1
	int setname();
	int setbirth();
	int setplace();
	int bindset();
	int delset();
};