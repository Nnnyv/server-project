#include"../Í·ÎÄ¼þ/to_getin.h"
using namespace std;
void hash_lyh::add(string value) {
	if (find(value) == 1)return;
	int a = stoi(value);
	every.insert(a);
}
void hash_lyh::del(string value) {
	int a = stoi(value);
	every.erase(a);
}
int hash_lyh::find(string value) {
	int a = stoi(value);
	return every.find(a) != every.end();
}

getin_lyh::getin_lyh(string str):data(str) {
	TIME = time(0);
}
getin_lyh::getin_lyh(string str, time_t ti) {
	data = str;
	TIME = ti;
}
getin_lyh::~getin_lyh() {};
int getin_lyh::add(getin_lyh* pi) {
	if (next == NULL) {
		next = pi;
		return 1;
	}
	else {
		return 0;
	}
}
void getin_lyh::load(message_lyh& mess) {
	mess.reload(data);
	mess.add_num(ctime(&TIME));
}
void getin_lyh::take(string& str) {
	str = data;
}
void to_getin::take(string &str) {
	top()->take(str);
	pop();
}
void to_getin::add(string a) {
	getin_lyh* pi = new getin_lyh(a);
	if (tail != NULL) { tail->add(pi); }
	else {
		head = pi;
		tail = pi;
	}
}
void to_getin::add(string a,time_t ti) {
	getin_lyh* pi = new getin_lyh(a,ti);
	if (tail != NULL) { tail->add(pi); }
	else {
		head = pi;
		tail = pi;
	}
}
void to_getin::pop() {
	getin_lyh* pi = head;
	head = head->nextone();
	if (head == NULL)tail = NULL;
	free(pi);
}
getin_lyh* to_getin::top() {
	return head;
	
}
void to_getin::send(message_lyh &mess) {
	top()->load(mess);
	mess.send();
	pop();
}
int to_getin::iff() {
	if (head == NULL)return 0;
	else return 1;
}




	//toget_in_lyh::toget_in_lyh(string typ, string a, toget_in_lyh* nextone) {
	//	type = typ;
	//	str = a;
	//	time(&TIME);
	//	next = nextone;
	//}
	//const string toget_in_lyh::show() {
	//	return str;
	//}
	//time_t toget_in_lyh::shoutime() {
	//	return TIME;
	//}


	//toget_lyh::toget_lyh() {}
	//void  toget_lyh::add(string typ, string a) {
	//	toget_in_lyh* temp;
	//	temp = head;
	//	head = new toget_in_lyh(typ, a, temp);
	//}
