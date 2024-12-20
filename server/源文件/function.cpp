#include"../Í·ÎÄ¼þ/function.h"
using namespace std;
	string function_lyh::describe() {
		return description;
	}
	function_lyh::function_lyh(string a) {
		description = a;
	}
	string description;
	functions_lyh::functions_lyh() {}
	int functions_lyh::add(function_lyh* a) {
		all.push_back(a);
		return all.size() - 1;
	}
	string functions_lyh::del(int a) {
		if (a >= all.size()) {
			return 0;
		}
		else {
			string str = all[a]->describe();
			all.erase(all.begin() + a);
			return str;
		}
	}
	string functions_lyh::work(int a,int b) {
		if (a >= all.size()) {
			return 0;
		}
		else {
			all[a]->work(b);
			return all[a]->describe();
		}
	}
