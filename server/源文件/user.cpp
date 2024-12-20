#pragma once
#include"../ͷ�ļ�/user.h"
#define SKIPMAX 10

using namespace std;


////////////////////////////////////////////����Ϊ����ʵ��///////////////////////////////////////////////////////////

//skipstring_lyh* BuildUpdate(skipstring_lyh* head, int level, string K, skipstring_lyh* update[]) {
//	//�ڱ��в���K������update��
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
	//��1/2��������������ȷ�����ϲ�����ٲ�
	int newlevel = 1;
	while (rand() % 2 == 0 && newlevel < SKIPMAX)
		newlevel++;
	return newlevel;
}
int randomnum(int digits) {
	if (digits <= 0) {
		throw std::invalid_argument("λ��������� 0");
	}

	// ������Сֵ�����ֵ
	int minValue = std::pow(10, digits - 1);
	int maxValue = std::pow(10, digits) - 1;

	// �����������
	std::random_device rd;                     // ���������
	std::mt19937 generator(rd());              // ���������
	std::uniform_int_distribution<long long> distribution(minValue, maxValue); // ���ȷֲ�

	// ���������
	return distribution(generator);
}
//����Ϊstore��

//����Ϊuser��
//��Ϣ���

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
//	skipstring_lyh* p = BuildUpdate(friends, friend_level, a, update); //�ڱ��в��Ҳ�����update��
//		if (p != NULL) return; //���У� �����ظ�����
//		int newlevel = random_level(); //ȷ�����ϲ弸��
//		if (newlevel > friend_level) { //��ԭ���������ߣ�����level��updateֵ
//			for (int i = friend_level; i < newlevel; i++)
//				update[i] = friends;
//			friend_level = newlevel;
//		}
//		p = new skipstring_lyh(a); //�����½��
//		for (int i = 0; i < newlevel; i++) { //���¶�����������
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
//	skipstring_lyh* p = BuildUpdate(groups, group_level, a, update); //�ڱ��в��Ҳ�����update��
//	if (p != NULL) return; //���У� �����ظ�����
//	int newlevel = random_level(); //ȷ�����ϲ弸��
//	if (newlevel > group_level) { //��ԭ���������ߣ�����level��updateֵ
//		for (int i = group_level; i < newlevel; i++)
//			update[i] = groups;
//		group_level = newlevel;
//	}
//	p = new skipstring_lyh(a); //�����½��
//	for (int i = 0; i < newlevel; i++) { //���¶�����������
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
//	skipstring_lyh* p = BuildUpdate(friends, friend_level, a, update); //�ڱ��в��Ҳ�����update��
//		if (p == NULL) return; //����δ�ҵ���㣬 ����ɾ��
//		for (int i = 0; i < friend_level; i++) { //�Ե����������½��p
//			if (update[i]->next[i] != p) break;
//			update[i]->next[i] = p->next[i];
//		}
//		delete p;
//		while (friend_level > 0 && friends->next[friend_level - 1] == NULL) //ɾ����������ĳЩ���Ϊ��
//			friend_level--;
//		friend_num--;
// }
void user_lyh::del_friend(string a) {
	friends.del(a);
}
//void user_lyh::del_group(string a) {
//	skipstring_lyh* update[SKIPMAX] = { 0 };
//	skipstring_lyh* p = BuildUpdate(groups, group_level, a, update); //�ڱ��в��Ҳ�����update��
//	if (p == NULL) return; //����δ�ҵ���㣬 ����ɾ��
//	for (int i = 0; i < group_level; i++) { //�Ե����������½��p
//		if (update[i]->next[i] != p) break;
//		update[i]->next[i] = p->next[i];
//	}
//	delete p;
//	while (group_level > 0 && groups->next[group_level - 1] == NULL) //ɾ����������ĳЩ���Ϊ��
//		group_level--;
//	group_num--;
//}
void user_lyh::del_group(string a) {
	groups.del(a);
}

//int user_lyh::if_friend(string a) {
//	skipstring_lyh* p = friends;
//	for (int i = friend_level; i >= 0; i--) { //����p�½�
//		while (p->next[i] != NULL && p->next[i]->data < a) //����p����
//			p = p->next[i];
//	}
//	p = p->next[0]; //p����һλָ����K
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
//	for (int i = friend_level; i >= 0; i--) { //����p�½�
//		while (p->next[i] != NULL && p->next[i]->data < a) //����p����
//			p = p->next[i];
//	}
//	p = p->next[0]; //p����һλָ����K
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