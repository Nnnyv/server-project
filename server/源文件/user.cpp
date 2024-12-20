#pragma once
#include"../头文件/user.h"
#define SKIPMAX 10

using namespace std;


////////////////////////////////////////////以下为函数实现///////////////////////////////////////////////////////////

//skipstring_lyh* BuildUpdate(skipstring_lyh* head, int level, string K, skipstring_lyh* update[]) {
//	//在表中查找K并构建update表
//	skipstring_lyh* p = head;
//	for (int i = level - 1; i >= 0; i--) { 
//		while (p->next[i] != NULL && p->next[i]->data < K)
//			p = p->next[i];
//		update[i] = p;
//	}
//	p = p->next[0];
//	if (p != NULL && p->data == K)
//		return p;
//	return NULL;
//}



int random_level() {
	//以1/2概率向上生长，确定向上插入多少层
	int newlevel = 1;
	while (rand() % 2 == 0 && newlevel < SKIPMAX)
		newlevel++;
	return newlevel;
}
int randomnum(int digits) {
	if (digits <= 0) {
		throw std::invalid_argument("位数必须大于 0");
	}

	// 计算最小值和最大值
	int minValue = std::pow(10, digits - 1);
	int maxValue = std::pow(10, digits) - 1;

	// 随机数生成器
	std::random_device rd;                     // 真随机种子
	std::mt19937 generator(rd());              // 随机数引擎
	std::uniform_int_distribution<long long> distribution(minValue, maxValue); // 均匀分布

	// 生成随机数
	return distribution(generator);
}
//以下为store类

//以下为user类
//消息相关

void user_lyh::addnews(string str) {
	news.add(str);
}
void user_lyh::addnews(string str, time_t ti) {
	news.add(str, ti);
}
void user_lyh::sendnews(message_lyh& mess) {
	news.send(mess);
}
int user_lyh::iff_news() {
	return news.iff();
}
void user_lyh::addapply(string str) {
	apply.add(str);
}
void user_lyh::sendapply(message_lyh& mess) {
	apply.send(mess);
}


 int user_lyh::check_key(string a) {
	 //if (key == bcrypt::generateHash(a))return 1;
	 return bcrypt::validatePassword(a, key);
 }
 void user_lyh::set_name(string K,string a) {
	 if (check_key(K) == 0)return;
	 name = a;
 }
void user_lyh::set_birth(string K,string a) {
	if (check_key(K) == 0)return;
	birth = a;
 }
void user_lyh::set_place(string K,string a) {
	if (check_key(K) == 0)return;
	place = a;
}
int user_lyh::set_key(string a, string b) {
	if (key != b) {
		return 0;
	}
	else {
		//strcpy(key, a.c_str());
		key = a;
		return 1;
	}
}
int user_lyh::upload(string a) {
	if (check_key(a) == 1) {
		this->iflogin = 1;
		return 1;
	}
	return 0;
}
//void user_lyh::add_friend(string a) {
//	skipstring_lyh* update[SKIPMAX] = { 0 };
//	skipstring_lyh* p = BuildUpdate(friends, friend_level, a, update); //在表中查找并构建update表
//		if (p != NULL) return; //已有， 无需重复插入
//		int newlevel = random_level(); //确定向上插几层
//		if (newlevel > friend_level) { //比原来层数还高，更新level和update值
//			for (int i = friend_level; i < newlevel; i++)
//				update[i] = friends;
//			friend_level = newlevel;
//		}
//		p = new skipstring_lyh(a); //创建新结点
//		for (int i = 0; i < newlevel; i++) { //自下而上逐层插入结点
//			p->next[i] = update[i]->next[i];
//			update[i]->next[i] = p;
//		}
//		friend_num++;
// } 
void user_lyh::add_friend(string a) {
	friends.add(a);
}
//void user_lyh::add_group(string a) {
//	skipstring_lyh* update[SKIPMAX] = { 0 };
//	skipstring_lyh* p = BuildUpdate(groups, group_level, a, update); //在表中查找并构建update表
//	if (p != NULL) return; //已有， 无需重复插入
//	int newlevel = random_level(); //确定向上插几层
//	if (newlevel > group_level) { //比原来层数还高，更新level和update值
//		for (int i = group_level; i < newlevel; i++)
//			update[i] = groups;
//		group_level = newlevel;
//	}
//	p = new skipstring_lyh(a); //创建新结点
//	for (int i = 0; i < newlevel; i++) { //自下而上逐层插入结点
//		p->next[i] = update[i]->next[i];
//		update[i]->next[i] = p;
//	}
//	group_num++;
// }
void user_lyh::add_group(string a) {
	groups.add(a);
}
//void user_lyh::del_friend(string a) {
//	skipstring_lyh* update[SKIPMAX] = { 0 };
//	skipstring_lyh* p = BuildUpdate(friends, friend_level, a, update); //在表中查找并构建update表
//		if (p == NULL) return; //表中未找到结点， 无需删除
//		for (int i = 0; i < friend_level; i++) { //自底向上逐层拆下结点p
//			if (update[i]->next[i] != p) break;
//			update[i]->next[i] = p->next[i];
//		}
//		delete p;
//		while (friend_level > 0 && friends->next[friend_level - 1] == NULL) //删除后可能造成某些层变为空
//			friend_level--;
//		friend_num--;
// }
void user_lyh::del_friend(string a) {
	friends.del(a);
}
//void user_lyh::del_group(string a) {
//	skipstring_lyh* update[SKIPMAX] = { 0 };
//	skipstring_lyh* p = BuildUpdate(groups, group_level, a, update); //在表中查找并构建update表
//	if (p == NULL) return; //表中未找到结点， 无需删除
//	for (int i = 0; i < group_level; i++) { //自底向上逐层拆下结点p
//		if (update[i]->next[i] != p) break;
//		update[i]->next[i] = p->next[i];
//	}
//	delete p;
//	while (group_level > 0 && groups->next[group_level - 1] == NULL) //删除后可能造成某些层变为空
//		group_level--;
//	group_num--;
//}
void user_lyh::del_group(string a) {
	groups.del(a);
}

//int user_lyh::if_friend(string a) {
//	skipstring_lyh* p = friends;
//	for (int i = friend_level; i >= 0; i--) { //控制p下降
//		while (p->next[i] != NULL && p->next[i]->data < a) //控制p右移
//			p = p->next[i];
//	}
//	p = p->next[0]; //p右移一位指向结点K
//	if (p != NULL && p->data == a) { 
//		return 1;
//	}
//	return 0;
// }
int user_lyh::if_friend(string a) {
	return friends.find(a);
}
//int user_lyh::if_group(string a) {
//	skipstring_lyh* p = friends;
//	for (int i = friend_level; i >= 0; i--) { //控制p下降
//		while (p->next[i] != NULL && p->next[i]->data < a) //控制p右移
//			p = p->next[i];
//	}
//	p = p->next[0]; //p右移一位指向结点K
//	if (p != NULL && p->data == a) {
//		return 1;
//	}
//	return 0;
//}
int user_lyh::if_group(string a) {
	return groups.find(a);
}

//void user_lyh::show_friend(message_lyh& message) {
//	skipstring_lyh* fri = friends;
//	if (way == 1) {
//		while (fri != NULL) {
//			message.add_num(fri->data);
//			message.add_num(sqq_user_lyh::find(fri->data)->_name());
//			fri = fri->next[0];
//		}
//	}
//	else if (way == 2) {
//		while (fri != NULL) {
//			message.add_num(fri->data);
//			message.add_num(swebo_user_lyh::find(fri->data)->_name());
//			fri = fri->next[0];
//		}
//	}
//	else if (way == 3) {
//		while (fri != NULL) {
//			message.add_num(fri->data);
//			message.add_num(swechat_user_lyh::find(fri->data)->_name());
//			fri = fri->next[0];
//		}
//	}
//}
void user_lyh::show_friend(message_lyh& message) {
	if (way == 1) {
		for(int i : friends.every) {
			message.add_num(to_string(i));
			message.add_num(sqq_user_lyh::find(to_string(i))->_name());
		}
	}
	else if (way == 2) {
		for (int i : friends.every) {
			message.add_num(to_string(i));
			message.add_num(swebo_user_lyh::find(to_string(i))->_name());
		}
	}
	else if (way == 3) {
		for (int i : friends.every) {
			message.add_num(to_string(i));
			message.add_num(swechat_user_lyh::find(to_string(i))->_name());

		}
	}
}
//void user_lyh::show_group(message_lyh& message) {
//	skipstring_lyh* fri = groups;
//	if (way == 1) {
//		while (fri != NULL) {
//			message.add_num(fri->data);
//			message.add_num(sqq_group_lyh::find(fri->data)->_name());
//			fri = fri->next[0];
//		}
//	}
//	else if (way == 2) {
//		while (fri != NULL) {
//			message.add_num(fri->data);
//			message.add_num(swebo_group_lyh::find(fri->data)->_name());
//			fri = fri->next[0];
//		}
//	}
//	else if (way == 3) {
//		while (fri != NULL) {
//			message.add_num(fri->data);
//			message.add_num(swechat_group_lyh::find(fri->data)->_name());
//			fri = fri->next[0];
//		}
//	}
//}
void user_lyh::show_group(message_lyh& message) {
	if (way == 1) {
		for (int i : groups.every) {
			message.add_num(to_string(i));
			message.add_num(sqq_group_lyh::find(to_string(i))->_name());
		}
	}
	else if (way == 2) {
		for (int i : groups.every) {
			message.add_num(to_string(i));
			message.add_num(swebo_group_lyh::find(to_string(i))->_name());
		}
	}
	else if (way == 3) {
		for (int i : groups.every) {
			message.add_num(to_string(i));
			message.add_num(swechat_group_lyh::find(to_string(i))->_name());
		}
	}
}

void user_lyh::creat_bind(string){}
int user_lyh::set_bind(bind_lyh* bind,string a="", string b="") {
	if (a != "") {
		sqq_user_lyh::find(a)->bind = bind;
	}
	if (b != "") {
		swebo_user_lyh::find(a)->bind = bind;
	}
	return 1;
}
int user_lyh::num_bind() {
	return bind_num;
}
void user_lyh::show_bind(message_lyh& mess) {
	bind->show(mess);
}
bind_lyh* user_lyh::my_bind() {
	return bind;
}
void user_lyh::with_bind(){
	bind->with_friend();
}
string user_lyh::id_bind(int a) {
	if (a == 1) {
		return bind->qq;
	}
	else if (a == 2) {
		return bind->wechat;
	}
}
void user_lyh::download() {}
void user_lyh::del_account(string a) {}


group_lyh* qq_lyh::findgroup(string& str) {
	return sqq_group_lyh::find(str);
}
group_lyh* webo_lyh::findgroup(string& str) {
	return swebo_group_lyh::find(str);
}
group_lyh* wechat_lyh::findgroup(string& str) {
	return swechat_group_lyh::find(str);
}


user_lyh* qq_lyh::find(string& str) {
	return sqq_user_lyh::find(str);
}
user_lyh* webo_lyh::find(string& str) {
	return swebo_user_lyh::find(str);
}
user_lyh* wechat_lyh::find(string& str) {
	return swechat_user_lyh::find(str);
}