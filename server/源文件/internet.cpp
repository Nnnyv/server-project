#include"../Í·ÎÄ¼þ/internet.h"
using namespace std;
//message_lyh() {};
message_lyh::message_lyh(SOCKET soc, string a) :all(a) {
	socket = soc;
}
message_lyh::message_lyh(SOCKET soc) {
	socket = soc;
}
message_lyh::message_lyh(int) {};
int message_lyh::waitsending() {
	int num = 0;
	while (1) {
		if (RECVING == 1) {
			this_thread::sleep_for(chrono::seconds(1));
			num++;
			if (num == 15) {
				cout << "waitting..." << endl;
				num = 0;
			}
		}
		else {
			return 1;
		}
	}
}
int message_lyh::waitrecving() {
	int num = 0;
	while (1) {
		if (SENDING == 1) {
			this_thread::sleep_for(chrono::seconds(1));
			num++;
			if (num == 15) {
				cout << "waitting..." << endl;
				num = 0;
			}
		}
		else {
			return 1;
		}
	}
}
int message_lyh::waitboth() {
	int num = 0;
	while (1) {
		if (RECVING == 1 || SENDING == 1) {
			this_thread::sleep_for(chrono::seconds(1));
			num++;
			if (num == 15) {
				cout << "waitting..." << endl;
				num = 0;
			}
		}
		else {
			return 1;
		}
	}
}
int message_lyh::send1() {
	if (SENDING == 1) {
		return 0;
	}
	else {
		SENDING = 1;
		return 1;
	}
}
int message_lyh::send0() {
	if (SENDING == 0) {
		return 0;
	}
	else {
		SENDING = 0;
		return 1;
	}
}
int message_lyh::recv1() {
	if (RECVING == 1) {
		return 0;
	}
	else {
		RECVING = 1;
		return 1;
	}
}
int message_lyh::recv0() {
	if (RECVING == 0) {
		return 0;
	}
	else {
		RECVING = 0;
		return 1;
	}
}
int message_lyh::setsocket(SOCKET soc) {
	socket = soc;
	return 1;
}

int message_lyh::sign(string str) {
	int n = ::send(socket, str.c_str(), 3, 0);
	return n;
}
int message_lyh::recvsign() {
	clear();
	int a = ::recv(socket, &signal[0], 3, 0);
	return a;
}
char* const message_lyh::nowsignal() {
	return signal;
}
void message_lyh::reload(string a) {
	all = a;
}
void message_lyh::add(string a) {
	all += a;
}
void message_lyh::add_num(string a) {
	char temp = a.size();
	all += temp;
	all += a;
}
void message_lyh::add_end() {
	all += '\0';
}
int message_lyh::send() {
	char length[3];
	length[2] = all.size() % 128;
	length[1] = (all.size() / 128) % 128;
	length[0] = (all.size() / 128) / 128;
	int iff;
	iff = ::send(socket, length, 3, 0);
	if (iff == SOCKET_ERROR) {
		return SOCKET_ERROR;
	}
	return ::send(socket, all.c_str(), all.size(), 0);
}
int message_lyh::recv() {
	clear();
	char length[3];
	int leng = 0;
	int iff;
	iff = ::recv(socket, length, 3, 0);
	if (iff == SOCKET_ERROR) {
		return SOCKET_ERROR;
	}
	leng += length[2];
	leng += length[1] * 128;
	leng += length[0] * 16384;
	vector<char>tmp;
	tmp.resize(leng + 1);
	int bytes;
	bytes = ::recv(socket, tmp.data(), leng + 1, 0);
	all = string(tmp.begin(), tmp.begin() + bytes);
	return bytes;
}
void message_lyh::putout_num(int space = 0) {
	int temp = 0, temp1 = 0;
	while (all[temp] != 0) {
		cout.write(&all[0] + temp + 1, all[temp]);
		temp1++;
		if (temp1 >= space) {
			cout << endl;
			temp1 = 0;
		}
		else cout << "  ";
		temp += all[temp] + 1;
	}
}
string message_lyh::str() {
	return all;
}
void message_lyh::clear() {
	all.clear();
}
void message_lyh::replace() {
	now = 0;
}
string message_lyh::word() {
	int a = all[now];
	if (a == '\0') {
		return "";
	}
	int b = now;
	now= b + a + 1;
	return all.substr(b+1, a);
}