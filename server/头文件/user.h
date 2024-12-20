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

//toget为缓存内容，用于给客户端发送信息
int randomnum(int digits);
int random_level();
//skipstring_lyh* BuildUpdate(skipstring_lyh* head, int level, string K, skipstring_lyh* update[]);


//string类的skip表

//user类，user为基类，为每个用户的基本信息。打开服务器时即存在//////////////////////////////////////////////////////

class user_lyh {
public:
	friend class bind_lyh;
	friend class data_lyh;
	user_lyh(string Id, string Name, string Birth, string Useage, string Place, string Key,int w) :ID(Id), name(Name), birth(Birth), useage(Useage), place(Place),way(w) {
		//strcpy(key, Key.c_str());
		key = Key;
	}
	virtual ~user_lyh() {}
	//以下为基本操作
	int _way() { return way; }
	string _ID() { return ID; }
	string _name() { return name; }
	string _birth() { return birth; }
	string _useage() { return useage; }
	string _place() { return place; }
	int _iflogin() { return iflogin; }
	//以下为消息相关
	virtual void addnews(std::string);
	virtual void addnews(std::string,time_t);
	virtual void sendnews(message_lyh &mess);
	virtual void addapply(std::string);
	virtual void sendapply(message_lyh& mess);
	virtual int iff_news();
	//以下为好友&群相关
	virtual user_lyh* find(string& str) { return nullptr; };
	virtual group_lyh* findgroup(string& str) { return nullptr; };

	virtual void show_bind(message_lyh& mess);
	virtual int check_key(string);//正确返回1,错误返回0
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
	virtual int if_friend(string);//string为号码，int为第几个，若超过则返回NULL
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
	//string为密码
	virtual void del_account(string);
	//以下为功能
	hash_lyh friends;
	hash_lyh groups;
protected:
	const int way;
	char iflogin = 0;
	const string ID;//6位
	string name;//最多20位
	string birth;//8位
	const string useage;//8位
	string place;//最多40位
	string key;//
	//vector<string> friends;
	//vector<string> groups;
	//skipstring_lyh* friends=NULL;//记录id
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
//bind类，一起绑定的账户共同指向一个bind类.添加 1：qq 2：wechat////////////////////////////////////////////




