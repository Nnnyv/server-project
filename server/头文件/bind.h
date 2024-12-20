#pragma once
#include"user.h"
//#include"internet.h"
using namespace std;
class user_lyh;

class bind_lyh {
public:
	friend class data_lyh;
	bind_lyh() {};
	~bind_lyh() {};
	//第一个string为要添加的账号，第二个为密码;return -1 未找到，0 密码错误， 1 成功

	int add(string, string, int);
	//int为选择
	void del(int);
	//0为空
	int num();
	void show(message_lyh& mess);
	int with_friend();
	string qq = "0";
	string wechat = "0";
protected:
	static bind_lyh* set_bind(string a, string b);
	int number = 0;

};

