#include"../头文件/group.h"
using namespace std;
//以下为group类
//1 set_name 2 add 3 kick 4addm 5 delm 6 del 7ckind
int group_lyh::leader_do(string id, string key, int choose, string str ) {
	if (leader != id) return 0;
	if (sqq_user_lyh::find(leader)->check_key(key) == 0)return 0;
	if (choose == 1) {
		set_name(str);
	}
	else if (choose == 2) {
		add(str);
	}
	else if (choose == 3) {
		kick(str);
	}
	else if (choose == 4) {
		addm(str);
	}
	else if (choose == 5) {
		delm(str);
	}
	else if (choose == 6) {
		del();
		return 1;
	}
	else if (choose == 6) {
		return ckind(str);
	}
	return 1;
}
//1 set_name 2 add 3 kick
int qqgroup_lyh::manager_do(string id, string key, int choose, string str) {
	if (iff_manager(id) == 0)return 0;
	if (sqq_user_lyh::find(key)->check_key(key) == 0)return 0;
	if (choose == 1) {
		set_name(str);
	}
	else if (choose == 2) {
		add(str);
	}
	else if (choose == 3) {
		kick(str);
	}
}
string group_lyh::_name() {
	return name;
}
string group_lyh::_ID() {
	return ID;
}
//void group_lyh::add(string id) {
//	skipstring_lyh* update[SKIPMAX] = { 0 };
//	skipstring_lyh* p = BuildUpdate(everyone, everyone_level, id, update); //在表中查找并构建update表
//	if (p != NULL) return; //已有， 无需重复插入
//	int newlevel = random_level(); //确定向上插几层
//	if (newlevel > everyone_level) { //比原来层数还高，更新level和update值
//		for (int i = everyone_level; i < newlevel; i++)
//			update[i] = everyone;
//		everyone_level = newlevel;
//	}
//	p = new skipstring_lyh(id); //创建新结点
//	for (int i = 0; i < newlevel; i++) { //自下而上逐层插入结点
//		p->next[i] = update[i]->next[i];
//		update[i]->next[i] = p;
//	}
//	everyone_num++;
//}
void group_lyh::add(string id) {
	everyone.add(id);
}
//void group_lyh::kick(string id) {
//	skipstring_lyh* update[SKIPMAX] = { 0 };
//	skipstring_lyh* p = BuildUpdate(everyone, everyone_level, id, update); //在表中查找并构建update表
//	if (p == NULL) return; //表中未找到结点， 无需删除
//	for (int i = 0; i < everyone_level; i++) { //自底向上逐层拆下结点p
//		if (update[i]->next[i] != p) break;
//		update[i]->next[i] = p->next[i];
//	}
//	delete p;
//	while (everyone_level > 0 && everyone->next[everyone_level - 1] == NULL) //删除后可能造成某些层变为空
//		everyone_level--;
//	everyone_num--;
//	if (find(id) != NULL) {
//		delm(id);
//	}
//}
void group_lyh::kick(string id) {
	everyone.del(id);
}
//int group_lyh::find(string id) {
//	skipstring_lyh* p = everyone;
//	for (int i = everyone_level; i >= 0; i--) { //控制p下降
//		while (p->next[i] != NULL && p->next[i]->data < id) //控制p右移
//			p = p->next[i];
//	}
//	p = p->next[0]; //p右移一位指向结点K
//	if (p != NULL && p->data == id) {
//		return 1;
//	}
//	return 0;
//}
int group_lyh::find(string id) {
	return everyone.find(id);
}
void group_lyh::with_delone(std::string str) {
	if (way == 1) {
		if (sqq_user_lyh::find(str)->if_group(ID) == 0) {
			kick(str);
		}
	}
	else if (way == 2) {
		if (swebo_user_lyh::find(str)->if_group(ID) == 0) {
			kick(str);
		}
	}
	else if (way == 3) {
		if (swechat_user_lyh::find(str)->if_group(ID) == 0) {
			kick(str);
		}
	}
}
void group_lyh::sendnews(string str) {
	message_lyh message(1);
	message.clear();
	message.add_num(ID);
	message.add_num(name);
	message.add_num(str);
	str = message.str();
	if (way == 1) {
		for(int i :everyone.every ) {
			sqq_user_lyh::find(to_string(i))->addnews(str);
		}
	}
	else if (way == 2) {
		for (int i : everyone.every) {
			swebo_user_lyh::find(to_string(i))->addnews(str);
		}
	}
	else if (way == 3) {
		for (int i : everyone.every) {
			swechat_user_lyh::find(to_string(i))->addnews(str);
		}
	}
}
void group_lyh::addapply(string str) {
	apply.add(str);
}
void group_lyh::sendapply(message_lyh& mess) {
	apply.send(mess);
}

int qq_lyh::upload(string a) {
	if (check_key(a) == 1) {
		this->iflogin = 1;
		return 1;
	}
	swebo_user_lyh::find(ID)->with_log();
	return 0;
}
int webo_lyh::upload(string a) {
	if (check_key(a) == 1) {
		this->iflogin = 1;
		return 1;
	}
	sqq_user_lyh::find(ID)->with_log();
	return 0;
}
int webo_lyh::with_log() {
	if (sqq_user_lyh::find(ID)->_iflogin() == 1) {
		iflogin = 1;
		return 1;
	}
	else {
		return 0;
	}
}
int qq_lyh::with_log() {
	if (swebo_user_lyh::find(ID)->_iflogin() == 1) {
		iflogin = 1;
		return 1;
	}
	else {
		return 0;
	}
}
int qq_lyh::join_bind(bind_lyh* bpoint, string password) {
	if (this->check_key(password) != 1) {
		return 0;
	}
	if (bind_num != 0) {
		bind->del(1);
	}
	else {}
	bind = bpoint;
	bind->add(ID, password, 1);
	bind_num = bind->num();
	return 1;
}
int webo_lyh::join_bind(bind_lyh* bpoint, string password) {
	if (this->check_key(password) != 1) {
		return 0;
	}
	if (bind_num != 0) {
		bind->del(1);
	}
	else {}
	bind = bpoint;
	bind->add(ID, password, 1);
	bind_num = bind->num();
	return 1;
}
int wechat_lyh::join_bind(bind_lyh* bpoint, string password) {
	if (this->check_key(password) != 1) {
		return 0;
	}
	if (bind_num != 0) {
		bind->del(2);
	}
	else {}
	bind = bpoint;
	bind->add(ID, password, 2);
	bind_num = bind->num();
	return 1;
}
void qq_lyh::del_bind(int a) {
	bind->del(a);
	if (a == 1) {
		bind = NULL;
	}
	bind_num = 0;
}
void webo_lyh::del_bind(int a) {
	bind->del(a);
	if (a == 1) {
		bind = NULL;
	}
	bind_num = 0;
}
void wechat_lyh::del_bind(int a) {
	bind->del(a);
	if (a == 2) {
		bind = NULL;
	}
	bind_num = 0;
}
void qq_lyh::creat_bind(string a) {
	bind->del(1);
	bind = new bind_lyh;
	bind->add(ID, a, 1);
	bind_num = 1;
}
void webo_lyh::creat_bind(string a) {
	bind->del(1);
	bind = new bind_lyh;
	bind->add(ID, a, 1);
	bind_num = 1;
}
void wechat_lyh::creat_bind(string a) {
	bind->del(2);
	bind = new bind_lyh;
	bind->add(ID, a, 2);
	bind_num = 1;
}


qqgroup_lyh::qqgroup_lyh(string id) :group_lyh(id) {
	sqq_group_lyh::putin(this);
	way = 1;
	type = 0;
}
int qqgroup_lyh::ckind(string kind) {
	group_lyh* now;
	if (kind[0] == '1') {
		now = toqqGroup();
		free(this);
		sqq_group_lyh::putin(now);
		return 1;
	}
	else if (kind[0] == '2') {
		now = toWorkGroup();
		free(this);
		sqq_group_lyh::putin(now);
		return 1;
	}
	else if (kind[0] == '3') {
		now = toStudyGroup();
		free(this);
		sqq_group_lyh::putin(now);
		return 1;
	}
	return 0;
}
webogroup_lyh::webogroup_lyh(string id) :group_lyh(id) {
	swebo_group_lyh::putin(this);
	way = 2;
}
wechatgroup_lyh::wechatgroup_lyh(string id) :group_lyh(id) {
	swechat_group_lyh::putin(this);
	way = 3;
}
group_lyh* qqgroup_lyh::toqqGroup() { return new qqgroup_lyh(*this); }
group_lyh* qqgroup_lyh::toWorkGroup() { return new workqqgroup_lyh(ID); }
group_lyh* qqgroup_lyh::toStudyGroup() { return new studyqqgroup_lyh(ID); }

group_lyh* studyqqgroup_lyh::toqqGroup() { return new qqgroup_lyh(ID); }
group_lyh* studyqqgroup_lyh::toWorkGroup() { return new workqqgroup_lyh(ID); }
group_lyh* studyqqgroup_lyh::toStudyGroup() { return new studyqqgroup_lyh(*this); }
