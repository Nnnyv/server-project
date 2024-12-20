#pragma once
#include<WinSock2.h>
#include <WS2tcpip.h> 
#pragma comment(lib,"WS2_32")
#include<thread>
#include<stdio.h> 
#include<iostream>
#include<fstream>
#include<filesystem>
#include<string>
#include<ctime>
#include<vector>
#include<thread>
#include <chrono>
#include<ctime>
#include <conio.h>
#include"user.h"
#include"internet.h"
using std::string;
class data_lyh {
public:
	data_lyh();
	int start();
	int write();
private:
	std::fstream file;
	int alluse(const char name[], int way);
	int oneuse(int way);
	int allfriend(const char name[], int way);
	int onefriendqq();
	int onefriendwebo();
	int onefriendwechat();
	int allgroup(const char name[], int way);
	int onegroupqq();
	int onegroupwebo();
	int onegroupwechat();
	int allbind(const char name[]);
	int onebind();
	int allgroupnumber(const char name[], int way);
	int onegroupnumberqq();
	int onegroupnumberwebo();
	int onegroupnumberwechat();
	int allnews(const char name[], int way);
	int onenewsqq(message_lyh& mess);
	int onenewswebo(message_lyh& mess);
	int onenewswechat(message_lyh& mess);
	void saveqqBaseData(const string& filename);
	void saveweboBaseData(const string& filename);
	void savewechatBaseData(const string& filename);
	void saveqqGroup(const string& filename);
	void saveweboGroup(const string& filename);
	void savewechatGroup(const string& filename);
	void saveBind(const string& filename);
	void savenewsqq(const string& filename);
	void savenewswebo(const string& filename);
	void savenewswechat(const string& filename);
	void saveqqfriend(const string& filename);
	void savewebofriend(const string& filename);
	void savewechatfriend(const string& filename);
};

int flashdata(data_lyh* data);