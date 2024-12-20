#pragma once
#include<iostream>
#include<vector>
#include"user.h"
class function_lyh {
public:
	virtual int work(int a) = 0;
	virtual int works(string);
	std::string describe();
	virtual ~function_lyh() {};
protected:
	function_lyh(std::string);
	std::string description;
};
class functions_lyh {
public:
	functions_lyh();
	int add(function_lyh* a);
	std::string del(int a);
	std::string work(int a,int b);
private:
	vector<function_lyh*> all;
};
class studygroup_1_lyh :public function_lyh {
public:
	studygroup_1_lyh(string id,int w) :function_lyh(id),way(w) {}
	int work(int a) {
		if (a == 1) {
			work1();
		}
		return 1;
	}
	int works(string str) {
		say = str;
	}
protected:
	int work1() {
		findgroup(description, way)->sendnews(say);
	}
	string say="";
	int way;
};