#pragma once
#include<iostream>
#include<ctime>
#include"internet.h"
//class toget_in_lyh {
//public:
//	toget_in_lyh(string typ, string a, toget_in_lyh* nextone);
//	const string show();
//	time_t shoutime();
//protected:
//	string type;
//	string str;
//	time_t TIME;
//	toget_in_lyh* next;
//};
//
//class toget_lyh {
//public:
//	toget_lyh();
//	void add(string typ, string a);
//	string takeone();
//	string pop();
//protected:
//	toget_in_lyh* head = NULL;
//};
#include <unordered_set>
using std::string;
class hash_lyh {
public:
	void add(string value);

	void del(string value);

	int find(string value);

	/*void printAll() {
		for (int value : table) {
			cout << value << " ";
		}
		cout << endl;
	}*/

	std::unordered_set<int> every;  // ¹þÏ£±í´æ´¢ÕûÊý

};

using std::string;
class getin_lyh {
public:
	friend class data_lyh;
	getin_lyh(std::string);
	getin_lyh(std::string, time_t);
	~getin_lyh();
	int add(getin_lyh*);
	getin_lyh* nextone(){
		return next;
	}
	void load(message_lyh& mess);
	void take(string& str);
private:
	std::string data;
	time_t TIME;
	getin_lyh* next=NULL;
};
class to_getin {
public:
	friend class data_lyh;
	to_getin() {};
	virtual ~to_getin() {};
	void add(std::string);
	void add(std::string, time_t);
	void send(message_lyh &mess);
	void take(std::string &str);
	int iff();
protected:
	//std::string take();
	getin_lyh* top();
	void pop();
private:
	getin_lyh* head=NULL;
	getin_lyh* tail = NULL;
};