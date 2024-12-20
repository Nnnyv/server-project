
#include"../Í·ÎÄ¼þ/store.h"
using namespace std;
	void sqq_user_lyh::putin(user_lyh* newone) {
		int num = stoi(newone->_ID());
		every[num] = newone;
	}
	user_lyh* sqq_user_lyh::find(string ID) {
		int id = stoi(ID);
		return every[id];
	}
	void sqq_user_lyh::del(string ID) {
		int id = stoi(ID);
		user_lyh* temp = every[id];
		free(temp);
		every[id] = NULL;
	}
	void sqq_user_lyh::allnull() {
		for (auto& i : every) {
			i = nullptr;
		}
	}

	void swebo_user_lyh::putin(user_lyh* newone) {
		int num = stoi(newone->_ID());
		every[num] = newone;
	}
	user_lyh* swebo_user_lyh::find(string ID) {
		int id = stoi(ID);
		return every[id];
	}
	void swebo_user_lyh::del(string ID) {
		int id = stoi(ID);
		user_lyh* temp = every[id];
		free(temp);
		every[id] = NULL;
	}
	void swebo_user_lyh::allnull() {
		for (auto& i : every) {
			i = nullptr;
		}
	}

	void swechat_user_lyh::putin(user_lyh* newone) {
		int num = stoi(newone->_ID());
		every[num] = newone;
	}
	user_lyh* swechat_user_lyh::find(string ID) {
		int id = stoi(ID);
		return every[id];
	}
	void swechat_user_lyh::del(string ID) {
		int id = stoi(ID);
		user_lyh* temp = every[id];
		free(temp);
		every[id] = NULL;
	}
	void swechat_user_lyh::allnull() {
		for (auto& i : every) {
			i = nullptr;
		}
	}

	void sqq_group_lyh::putin(group_lyh* newone) {
		int num = stoi(newone->_ID());
		every[num] = newone;
	}
	group_lyh* sqq_group_lyh::find(string ID) {
		int id = stoi(ID);
		return every[id];
	}
	void sqq_group_lyh::del(string ID) {
		int id = stoi(ID);
		group_lyh* temp = every[id];
		free(temp);
		every[id] = NULL;
	}
	void sqq_group_lyh::allnull() {
		for (auto& i : every) {
			i = nullptr;
		}
	}

	void swebo_group_lyh::putin(group_lyh* newone) {
		int num = stoi(newone->_ID());
		every[num] = newone;
	}
	group_lyh* swebo_group_lyh::find(string ID) {
		int id = stoi(ID);
		return every[id];
	}
	void swebo_group_lyh::del(string ID) {
		int id = stoi(ID);
		group_lyh* temp = every[id];
		free(temp);
		every[id] = NULL;
	}
	void swebo_group_lyh::allnull() {
		for (auto& i : every) {
			i = nullptr;
		}
	}

	void swechat_group_lyh::putin(group_lyh* newone) {
		int num = stoi(newone->_ID());
		every[num] = newone;
	}
	group_lyh* swechat_group_lyh::find(string ID) {
		int id = stoi(ID);
		return every[id];
	}
	void swechat_group_lyh::del(string ID) {
		int id = stoi(ID);
		group_lyh* temp = every[id];
		free(temp);
		every[id] = NULL;
	}
	void swechat_group_lyh::allnull() {
		for (auto& i : every) {
			i = nullptr;
		}
	}

	user_lyh* sqq_user_lyh::every[1000000] = { NULL };
	user_lyh* swebo_user_lyh::every[1000000] = { NULL };
	user_lyh* swechat_user_lyh::every[1000000] = { NULL };
	group_lyh* sqq_group_lyh::every[10000000] = { NULL };
	group_lyh* swebo_group_lyh::every[10000000] = { NULL };
	group_lyh* swechat_group_lyh::every[10000000] = { NULL };


user_lyh* finduser(std::string str, int way) {
	user_lyh* pi = NULL;
	if (way == 1) {
		pi = sqq_user_lyh::find(str);
	}
	else if (way == 2) {
		pi = swebo_user_lyh::find(str);
	}
	else if (way == 3) {
		pi = swechat_user_lyh::find(str);
	}
	return pi;
}
group_lyh* findgroup(std::string str, int way) {
	if (way == 1) {
		return sqq_group_lyh::find(str);
	}
	else if (way == 2) {
		return swebo_group_lyh::find(str);
	}
	else if (way == 3) {
		return swechat_group_lyh::find(str);
	}
}

