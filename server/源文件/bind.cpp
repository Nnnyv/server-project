#include"../头文件/bind.h"
using namespace std;
//下为bind类
bind_lyh* bind_lyh::set_bind(string a, string b) {
	bind_lyh* bind = new bind_lyh;
	if (a != "")bind->qq = a;
	if (b != "")bind->wechat = b;
	return bind;
}
int bind_lyh::add(string account, string K, int choose) {
	if (choose == 1) {
		user_lyh* temp;
		temp = sqq_user_lyh::find(account);
		if (temp == NULL)return -1;
		int tempi = temp->check_key(K);
		if (tempi == 0)return 0;
		else {
			if (qq == "0")number++;
			qq = account;
			return 1;
		}
	}
	if (choose == 2) {
		user_lyh* temp = swechat_user_lyh::find(account);
		if (temp == NULL)return -1;
		int tempi = temp->check_key(K);
		if (tempi == 0)return 0;
		else {
			if (wechat == "0")number++;
			wechat = account;
			number++;
			return 1;
		}
	}
}
void bind_lyh::del(int choose) {
	if (choose == 1) {
		if (qq == "0") {}
		else {
			qq = "0";
			number--;
		}
	}
	else if (choose == 2) {
		if (qq == "0") {}
		else {
			wechat = "0";
			number--;
		};
		if (number == 0) {
			delete this;
		}
	}
}
int bind_lyh::num() {
	return number;
}
void bind_lyh::show(message_lyh& mess) {
	mess.clear();
	mess.add_num(qq);
	mess.add_num(wechat);
}
int bind_lyh::with_friend() {
	if (qq == "0" || wechat == "0") {
		return 0;
	}
	user_lyh* q, * wb, * wc;
	string tmp;
	q = finduser(qq, 1);
	wb = finduser(qq, 2);
	wc = finduser(wechat, 3);
	hash_lyh *ha=&finduser(qq, 1)->friends;
	for(int i:ha->every) {
		tmp = finduser(to_string(i), 1)->bind->wechat;
		if (finduser(tmp, 3)->if_friend(wechat) == 0) {
			finduser(tmp, 3)->add_friend(wechat);
			wc->add_friend(tmp);
		}
		tmp = to_string(i);
		if (finduser(tmp, 2)->if_friend(qq) == 0) {
			finduser(tmp, 2)->add_friend(qq);
			wb->add_friend(tmp);
		}
	}

	ha = &finduser(qq, 2)->friends;
	for (int i : ha->every) {
		tmp = finduser(to_string(i), 2)->bind->wechat;
		if (finduser(tmp, 3)->if_friend(wechat) == 0) {
			finduser(tmp, 3)->add_friend(wechat);
			wc->add_friend(tmp);
		}
		tmp = to_string(i);
		if (finduser(tmp, 1)->if_friend(qq) == 0) {
			finduser(tmp, 1)->add_friend(qq);
			q->add_friend(tmp);
		}
	}

	ha = &finduser(wechat, 3)->friends;
	for (int i : ha->every) {
		tmp = finduser(to_string(i), 3)->bind->qq;
		if (finduser(tmp, 1)->if_friend(qq) == 0) {
			finduser(tmp, 1)->add_friend(qq);
			q->add_friend(tmp);
		}
		if (finduser(tmp, 2)->if_friend(qq) == 0) {
			finduser(tmp, 2)->add_friend(qq);
			wb->add_friend(tmp);
		}
	}

}