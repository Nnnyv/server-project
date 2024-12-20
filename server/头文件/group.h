#pragma once
#include"user.h"
#include"to_getin.h"
#include"store.h"

using namespace std;

class sqq_user_lyh;
class swebo_user_lyh;
class swechat_user_lyh;
class sqq_group_lyh;
class swebo_group_lyh;
class swechat_group_lyh;

class group_lyh;
class qqgroup_lyh;
class webogroup_lyh;
class wechatgroup_lyh;
//class studyqqgroup_lyh;
//class workqqgroup_lyh;

class user_lyh;
class group_lyh {
public:
	friend class data_lyh;
	//friend leader_lyh;
	group_lyh(string id) :ID(id) {};
	group_lyh(group_lyh* gro) :ID(gro->ID) {
		way = gro->way;
		apply = gro->apply;
		name = gro->name;
		everyone = gro->everyone;
		leader = gro->leader;
		//wait = gro->wait;
		//gro->everyone = NULL;
		//gro->wait = NULL;
	}
	virtual ~group_lyh() {};
	virtual string _ID();
	virtual string _name();
	virtual user_lyh* findm(string) { return nullptr; };
	virtual int find(string);
	//virtual int join(string) {};
	virtual int iff_leader(string a) {
		if (a == leader) {
			return 1;
		}
		else return 0;
	}
	virtual int iff_manager(string a) {
		return 0;
	};
	////////////////以下为消息相关
	//virtual void addnews(std::string);
	virtual void sendnews(string str);
	virtual void addapply(std::string);
	virtual void sendapply(message_lyh& mess);
	virtual void with_delone(std::string);
	//1 set_name 2 add 3 kick 4addm 5 delm 6 del 7ckind
	virtual int leader_do(string id, string key, int choose, string str );//1 set_name 2 add 3 kick 4addm 5 delm 6 del 7ckind
	virtual int manager_do(string id, string key, int choose, string str) { return 1; }
	/// //////////特殊功能群
	virtual group_lyh* toStudyGroup() { return nullptr; };
	virtual group_lyh* toWorkGroup() { return nullptr; };
	virtual group_lyh* toFamilyGroup() { return nullptr; };
	virtual int set_leader(string id) {
		if (leader == "") {
			leader = id; return 1;
		}
		else {
			return 0;
		}
	}
	virtual int sendhomework() { return 0; };
	virtual int sethomework(string home) { return 0; };
	virtual int ckind(string kind) { return 0; };
	virtual group_lyh* clone() {
		return new group_lyh(*this);
	};
	hash_lyh everyone;
protected:

	virtual void addm(string newone) {};
	virtual void delm(string delee) {};

	virtual void del() {
		free(this);
	};
	virtual void set_name(string na) {
		name = na;
	};
	virtual void add(string);
	virtual void kick(string);

	int way;
	//to_getin news;
	to_getin apply;
	const string ID;
	string name;
	/*skipstring_lyh* everyone;
	int everyone_level = 1;
	int everyone_num;*/
	
	string leader = "";
	vector<string> manager = {"\0"};
	//waitting_lyh* wait = NULL;
};
class qqgroup_lyh :public group_lyh {
public:
	qqgroup_lyh(string id);
	~qqgroup_lyh() {

	}
	virtual int iff_manager(string a) {
		for (auto& aa : manager) {
			if (aa == a) {
				return 1;
			}
		}
		return 0;
	}
	virtual group_lyh* clone() {
		return new qqgroup_lyh(*this);
	}
	virtual int manager_do(string id, string key, int choose, string str = "");
	virtual int ckind(string kind);
	virtual group_lyh* toqqGroup();
	virtual group_lyh* toWorkGroup();
	virtual group_lyh* toStudyGroup();
protected:
	/*virtual vector<string> qq_copy1() {
		return manager;
	}
	virtual  int qq_copy2() {
		return managernum;
	}
	virtual int qq_copy3() {
		return type;
	}*/
	virtual void addm(string newone) {
		if (managernum >= 8)return;
		manager.push_back(newone);
		managernum++;
	}
	virtual void delm(string delone) {
		int a = 0;
		while (a < managernum) {
			if (manager[a] == delone) {
				manager.erase(manager.begin() + a);
			}
			a++;
		}
	}
	
	int managernum = 0;
	int type = 0;
	//int specific_type;
	//specific_lyh* specific;
};

class studyqqgroup_lyh :public qqgroup_lyh {
public:
	studyqqgroup_lyh(string id) :qqgroup_lyh(id) {
		type = 1;
	}
	virtual group_lyh* clone() {
		return new studyqqgroup_lyh(*this);
	}
	virtual int sendhomework() {
		sendnews(homework);
		return 1;
	}
	virtual int sethomework(string home) {
		homework = home;
		return 1;
	}
	virtual group_lyh* toqqGroup();
	virtual group_lyh* toWorkGroup();
	virtual group_lyh* toStudyGroup();
protected:
	string homework = "";
};
class workqqgroup_lyh :public qqgroup_lyh {
public:
	workqqgroup_lyh(string id) :qqgroup_lyh(id) {
		type = 2;
	}
	virtual group_lyh* clone() {
		return new workqqgroup_lyh(*this);
	}
	virtual int sendhomework() {
		sendnews(homework);
		return 1;
	}
	virtual int sethomework(string home) {
		homework = home;
		return 1;
	}
	group_lyh* toqqGroup() { return new qqgroup_lyh(ID); }
	group_lyh* toWorkGroup() { return new workqqgroup_lyh(*this); }
	group_lyh* toStudyGroup() { return new studyqqgroup_lyh(ID); }
protected:
	string homework = "";
};

class webogroup_lyh :public group_lyh {
public:
	webogroup_lyh(string id);
	~webogroup_lyh() {}
	virtual group_lyh* clone() {
		return new webogroup_lyh(*this);
	}
protected:

};
class wechatgroup_lyh :public group_lyh {
public:
	wechatgroup_lyh(string id);
	~wechatgroup_lyh() {}
	virtual group_lyh* clone() {
		return new wechatgroup_lyh(*this);
	}
protected:

};

