#pragma once
//#include<iostream>
#include<vector>
#include<string>
#include <random>
#include <cmath>
#include<ctime>
//#include"function.h"
//#include"bcrypt/BCrypt.hpp"
//#include"internet.h"
#include"group.h"
#include"data.h"
#include"to_getin.h"
//#include"recving.h"
#include"store.h"
#include"bind.h"
#include"bc/bcrypt.h"
//#include"../bcrypt/BCrypt.hpp"
#define SKIPMAX 10
using namespace std;


//class skipstring_lyh {
//public:
//	skipstring_lyh(string d) { data = d; }
//	string data;
//	skipstring_lyh* next[SKIPMAX] = { 0 };
//};

//class bind_lyh;

class sqq_user_lyh;
class swebo_user_lyh;
class swechat_user_lyh;
class sqq_group_lyh;
class swebo_group_lyh;
class swechat_group_lyh;

//togetΪ�������ݣ����ڸ��ͻ��˷�����Ϣ
int randomnum(int digits);
int random_level();
//skipstring_lyh* BuildUpdate(skipstring_lyh* head, int level, string K, skipstring_lyh* update[]);


//string���skip��

//user�࣬userΪ���࣬Ϊÿ���û��Ļ�����Ϣ���򿪷�����ʱ������//////////////////////////////////////////////////////

class user_lyh {
public:
	friend class bind_lyh;
	friend class data_lyh;
	user_lyh(string Id, string Name, string Birth, string Useage, string Place, string Key,int w) :ID(Id), name(Name), birth(Birth), useage(Useage), place(Place),way(w) {
		//strcpy(key, Key.c_str());
		key = Key;
	}
	virtual ~user_lyh() {}
	//����Ϊ��������
	int _way() { return way; }
	string _ID() { return ID; }
	string _name() { return name; }
	string _birth() { return birth; }
	string _useage() { return useage; }
	string _place() { return place; }
	int _iflogin() { return iflogin; }
	//����Ϊ��Ϣ���
	virtual void addnews(std::string);
	virtual void addnews(std::string,time_t);
	virtual void sendnews(message_lyh &mess);
	virtual void addapply(std::string);
	virtual void sendapply(message_lyh& mess);
	virtual int iff_news();
	//����Ϊ����&Ⱥ���
	virtual user_lyh* find(string& str) { return nullptr; };
	virtual group_lyh* findgroup(string& str) { return nullptr; };

	virtual void show_bind(message_lyh& mess);
	virtual int check_key(string);//��ȷ����1,���󷵻�0
	virtual void set_name(string,string);
	virtual void set_birth(string,string);
	virtual void set_place(string,string);
	virtual int set_key(string, string);
	virtual void show_friend(message_lyh& message);
	virtual void show_group(message_lyh& message);
	virtual void add_friend(string);
	virtual void add_group(string);
	virtual void del_friend(string);
	virtual void del_group(string);
	virtual int if_friend(string);//stringΪ���룬intΪ�ڼ������������򷵻�NULL
	virtual int if_group(string);
	virtual int with_log() { return 0; };
	virtual void with_bind();
	bind_lyh* my_bind();
	static int set_bind(bind_lyh*,string a, string b );
	virtual int join_bind(bind_lyh*, string) {return 0;};
	virtual void creat_bind(string);
	virtual void del_bind(int) {};
	virtual int num_bind();
	virtual string id_bind(int a);
	virtual int upload(string a);//
	virtual void download();
	//stringΪ����
	virtual void del_account(string);
	//����Ϊ����
	hash_lyh friends;
	hash_lyh groups;
protected:
	const int way;
	char iflogin = 0;
	const string ID;//6λ
	string name;//���20λ
	string birth;//8λ
	const string useage;//8λ
	string place;//���40λ
	string key;//
	//vector<string> friends;
	//vector<string> groups;
	//skipstring_lyh* friends=NULL;//��¼id
	//int friend_level = 1;
	//int friend_num;
	
	/*skipstring_lyh* groups;
	int group_level = 1;
	int group_num;*/
	
	bind_lyh* bind = NULL;
	int bind_num;
	//leader_lyh* leader;
	//functions_lyh function;
	to_getin news;
	to_getin apply;
	//vector
};
class qq_lyh :public user_lyh {
public:
	qq_lyh(string Id, string Name, string Birth, string Useage, string Place, string Key) :user_lyh(Id, Name, Birth, Useage, Place, Key,1) {}
	~qq_lyh() {}
	int join_bind(bind_lyh*, string);
	int with_log();
	void del_bind(int);
	void creat_bind(string);
	int upload(string a);
	user_lyh* find(string& str);
	group_lyh* findgroup(string& str);
protected:
	//leader_lyh* manager;

};
class webo_lyh :public user_lyh {
public:
	webo_lyh(string Id, string Name, string Birth, string Useage, string Place, string Key) : user_lyh(Id, Name, Birth, Useage, Place, Key,2) {}
	//
	int with_log();
	int join_bind(bind_lyh*, string);
	void del_bind(int);
	void creat_bind(string);
	int upload(string a);
	user_lyh* find(string& str);
	group_lyh* findgroup(string& str);
	//

protected:


};
class wechat_lyh :public user_lyh {
public:
	wechat_lyh(string Id, string Name, string Birth, string Useage, string Place, string Key) :user_lyh(Id, Name, Birth, Useage, Place, Key,3) {}
	~wechat_lyh() {}
	int join_bind(bind_lyh*, string);
	void del_bind(int);
	void creat_bind(string);
	user_lyh* find(string& str);
	group_lyh* findgroup(string& str);
protected:

};
//bind�࣬һ��󶨵��˻���ָͬ��һ��bind��.��� 1��qq 2��wechat////////////////////////////////////////////




