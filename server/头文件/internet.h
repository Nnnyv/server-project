#pragma once
#include<WinSock2.h>
#include <WS2tcpip.h> 
#pragma comment(lib, "ws2_32.lib")
//#pragma comment(lib,"WS2_32")
#include<stdio.h> 
#include<iostream>
#include<string>
#include<ctime>
#include<vector>
#include<mutex>
#include<ctime>
#include <conio.h>

//#include"data.h"

class message_lyh {
public:
	//message_lyh() {};
	message_lyh(SOCKET, std::string);
	message_lyh(SOCKET);
	message_lyh(int);
	int waitsending();
	int waitrecving();
	int waitboth();
	int send1();
	int send0();
	int recv1();
	int recv0();
	int setsocket(SOCKET);
	//int sign(char a[]);
	int sign(std::string);
	int recvsign();
	char* const nowsignal();
	void reload(std::string);
	void add(std::string);
	void add_num(std::string);
	void add_end();
	int send();
	int recv();
	void putout_num(int);
	std::string str();
	void clear();
	void replace();
	std::string word();
private:
	int RECVING=0;
	int SENDING=0;
	SOCKET socket;
	std::string all;
	char signal[3];
	int now = 0;
};
