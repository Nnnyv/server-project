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
	//��һ��stringΪҪ��ӵ��˺ţ��ڶ���Ϊ����;return -1 δ�ҵ���0 ������� 1 �ɹ�

	int add(string, string, int);
	//intΪѡ��
	void del(int);
	//0Ϊ��
	int num();
	void show(message_lyh& mess);
	int with_friend();
	string qq = "0";
	string wechat = "0";
protected:
	static bind_lyh* set_bind(string a, string b);
	int number = 0;

};

