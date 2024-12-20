#include"../头文件/recving.h"
using namespace std;
//user_lyh* recving_lyh::finduser(string& str) {
//	if (use->_way() == 1) {
//		return sqq_user_lyh::find(str);
//	}
//	else if (use->_way() == 2) {
//		return swebo_user_lyh::find(str);
//	}
//	else if (use->_way() == 3) {
//		return swechat_user_lyh::find(str);
//	}
//}
//group_lyh* recving_lyh::findgroup(string& str) {
//	if (use->_way() == 1) {
//		return sqq_group_lyh::find(str);
//	}
//	else if (use->_way() == 2) {
//		return swebo_group_lyh::find(str);
//	}
//	else if (use->_way() == 3) {
//		return swechat_group_lyh::find(str);
//	}
//}
int recving_lyh::main(SOCKET socket) {
	recving_lyh recving(socket);
	cout << "启动main" << endl;
	if (recving.login() == -1) {
		return 0;
	}
	recving.start();
}
int recving_lyh::login() {
	int timecontrol = 120000;
	setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timecontrol, sizeof(timecontrol));
	string way, account, password;
	int iff;
	cout << "进入login函数" << endl;
	while (1) {
		int signal;
		signal = message.recvsign();
		cout << "接受signal" << endl;
		if (signal == SOCKET_ERROR) {
			cout << "超时" << endl;
			return -1;
		}
		else {
			cout << "有新的登陆尝试：" << endl;
			if (message.nowsignal()[0] == '\0'|| message.nowsignal()[1] == '\0'||message.nowsignal()[2] == '\0') {
				message.recv();
				way = message.word();
				account = message.word();
				password = message.word();
				if (way[0] == '1') {
					if (sqq_user_lyh::find(account) == NULL) {
						cout << "无账号错误 " << way << " " << account << " " << password << endl;
						message.clear();
						message.add("\0");
						message.send();
						continue;
					}
					iff=sqq_user_lyh::find(account)->check_key(password);
					if (iff == 1) {
						cout << "qq用户登录" << account << endl;
						use = sqq_user_lyh::find(account);
						message.add("\1");
						message.send();
						message.reload(use->_ID());
						message.send();
						message.reload(use->_name());
						message.send();
						message.reload(use->_birth());
						message.send();
						message.reload(use->_place());
						message.send();
						use->upload(password);
						return 1;
					}
					else {
						cout << "密码错误 " << way << " " << account << " " << password << endl;
						message.clear();
						message.add("\0");
						message.send();
						continue;
					}
				}
				else if(way[0]=='2') {
					if (swebo_user_lyh::find(account) == NULL) {
						message.add("\0");
						message.send();
						continue;
					}
					iff = swebo_user_lyh::find(account)->check_key(password);
					if (iff == 1) {
						use = swebo_user_lyh::find(account);
						message.add("\1");
						message.send();
						message.reload(use->_ID());
						message.send();
						message.reload(use->_name());
						message.send();
						message.reload(use->_birth());
						message.send();
						message.reload(use->_place());
						message.send();
						use->upload(password);
						return 1;
					}
					else {
						message.add("\0");
						message.send();
						continue;
					}
				}
				else if (way[0] == '3') {
					if (swechat_user_lyh::find(account) == NULL) {
						message.add("\0");
						message.send();
						continue;
					}
					iff = swechat_user_lyh::find(account)->check_key(password);
					if (iff == 1) {
						use = swechat_user_lyh::find(account);
						message.add("\1");
						message.send();
						message.reload(use->_ID());
						message.send();
						message.reload(use->_name());
						message.send();
						message.reload(use->_birth());
						message.send();
						message.reload(use->_place());
						message.send();
						use->upload(password);
						return 1;
					}
					else {
						message.add("\0");
						message.send();
						continue;
					}
				}
			}
			else {
				continue;
			}
		}
	}
}
int recving_lyh::start() {
	//thread doit([this](){doit;});
	// 
	thread doit([this]() {doit(); });
	thread send([this]() {send(); });
	doit.detach();
	send.detach();
	//doit();
	return 1;
}
int recving_lyh::send() {
	cout << "进入send" << endl;
	while (1) {
		if (use == NULL) {
			cout << "use为NULL！" << endl;
		}
		if (use->iff_news() == 1) {
			message.waitsending();
			message.send1();
			message.sign("\0\0\1");
			use->sendnews(message);
		}
		else {
			this_thread::sleep_for(chrono::seconds(4));
		}
	}
}








int recving_lyh::doit() {
	//int timecontrol = 240000;
	//setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timecontrol, sizeof(timecontrol));
	cout << "进入doit" << endl;
	string str;
	while (1) {
		message.recvsign();
		cout << "sign" << message.nowsignal() << endl;
		str = message.nowsignal();
		if (str[0]=='\0') {
			if (str[1] == '\0') {
				if (str[2] == '\1') {
					checkfriend();
				}
				else if(str[2]=='\2') {
					addfriend();
				}
				else if (str[2] == '\3') {
					delfriend();
				}
				else if (str[2] == '\4') {
					chatfriend();
				}
				else if (str[2] == '\6') {
					applyfriend();
				}
			}
		}
		else if (str[1] == '\1') {
				if (str[2] == '\1') {
					checkgroup();
				}
				else if (str[2] == '\2') {
					addgroup();
				}
				else if (str[2] == '\3') {
					deletegroup();
				}
				else if (str[2] == '\4') {
					chatgroup();
				}
				else if (str[2] == '\6') {
					managegroup();
				}
				else if (str[2] == '\11') {
					creatgroup();
				}
				else if (str[2] == '\17') {
					pullgroup();
				}
				else if (str[2] == '\13') {
					songroup();
				}
		}
		else if (str[1] == '\2') {
			if (str[2] == '\1') {
				dataset();
			}
			else if (str[2] == '\2') {
				bindset();
			}
			else if (str[2] == '\3') {
				delset();
			}
		}
	}
}
int recving_lyh::checkfriend() {
	message.clear();
	use->show_friend(message);
	message.send();
	return 1;
}
int recving_lyh::addfriend() {
	message.recv();
	string str = message.str();
	if (use->_way() == 1) { 
		if (sqq_user_lyh::find(str) == NULL) {
			message.reload("\0");
			message.send();
			return 0;
		}
		message.recv();
		sqq_user_lyh::find(str)->addapply(message.str());
	}
	else if (use->_way() == 2) {
		if (swebo_user_lyh::find(str) == NULL) {
			message.reload("\0");
			message.send();
			return 0;
		}
		message.recv();
		swebo_user_lyh::find(str)->addapply(message.str());
	}
	else if (use->_way() == 3) {
		if (swechat_user_lyh::find(str) == NULL) {
			message.reload("\0");
			message.send();
			return 0;
		}
		message.recv();
		swechat_user_lyh::find(str)->addapply(message.str());
	}
	return 1;
}
int recving_lyh::delfriend() {
	message.recv();
	string str = message.str();
	use->del_friend(str);
	use->find(str)->del_friend(use->_ID());
	return 1;
}
int recving_lyh::chatfriend() {
	message.recv();
	string str = message.str();
	int iff=use->if_friend(str);
	if (iff == 1) {
		message.reload("\1");
		message.send();
	}
	else {
		message.reload("\0");
		message.send();
		return 1;
	}
	while (1) {
		if (message.recvsign() == SOCKET_ERROR) {
			return 0;
		};
		if (message.nowsignal() == "\0\0\0") {
			return 1;
		}
		else if (message.nowsignal() == "\0\0\5") {
			message.recv();
			use->addnews(message.str());
		}
	}
}
int recving_lyh::applyfriend() {
	use->sendapply(message);
	string id = message.word();
	message.recv();
	if (message.str()[0] == '1') {
		if (use->_way() == 1) {
			if (sqq_user_lyh::find(id) == NULL) {
				return 0;
			}
			sqq_user_lyh::find(id)->add_friend(use->_ID());
		}
		else if (use->_way() == 2) {
			if (swebo_user_lyh::find(id) == NULL) {
				return 0;
			}
			swebo_user_lyh::find(id)->add_friend(use->_ID());
		}
		else if (use->_way() == 3) {
			if (swechat_user_lyh::find(id) == NULL) {
				return 0;
			}
			message.recv();
			swechat_user_lyh::find(id)->add_friend(use->_ID());
		}
		use->add_friend(id);
	}

}

int recving_lyh::checkgroup() {
	message.clear();
	use->show_group(message);
	message.send();
	return 1;
}
int recving_lyh::addgroup() {
	message.recv();
	string str = message.str();
	if (use->_way() == 1) {
		if (sqq_group_lyh::find(str) == NULL) {
			message.reload("\0");
			message.send();
			return 0;
		}
		message.recv();
		sqq_group_lyh::find(str)->addapply(message.str());
	}
	else if (use->_way() == 2) {
		if (swebo_group_lyh::find(str) == NULL) {
			message.reload("\0");
			message.send();
			return 0;
		}
		message.recv();
		swebo_group_lyh::find(str)->addapply(message.str());
	}
	else if (use->_way() == 3) {
		if (swechat_group_lyh::find(str) == NULL) {
			message.reload("\0");
			message.send();
			return 0;
		}
		message.recv();
		swechat_group_lyh::find(str)->addapply(message.str());
	}
	return 1;
}
int recving_lyh::deletegroup() {
	message.recv();
	string str = message.str();
	use->del_group(str);
	use->findgroup(str)->with_delone(use->_ID());
	return 1;
}
int recving_lyh::chatgroup() {
	message.recv();
	string str = message.str();
	int iff = use->if_group(str);
	if (iff == 1) {
		message.reload("\1");
		message.send();
	}
	else {
		message.reload("\0");
		message.send();
		return 1;
	}
	while (1) {
		if (message.recvsign() == SOCKET_ERROR) {
			return 0;
		};
		if (message.nowsignal() == "\0\0\0") {
			return 1;
		}
		else if (message.nowsignal() == "\0\1\5") {
			message.recv();
			use->findgroup(str)->sendnews(message.str());
		}
	}
}
int recving_lyh::managegroup() {
	message.clear();
	use->show_group(message);
	message.send();
	message.recv();
	string str = message.str();
	if (use->findgroup(str)->iff_leader(use->_ID()) == 1) {
		message.reload("\1");
		message.send();
		while (1) {
			message.recvsign();
			string str = message.nowsignal();
			if (str == "\0\1\7") {
				newmanagergroup_qq(str);
			}
			else if(str == "\0\1\010"){
				delmanagergroup_qq(str);
			}
			else if (str == "\000\001\011") {
				kickgroup_leader(str);
			}
			else if (str == "\0\1\012") {
				checkgroup_leader(str);
			}
			else if (str == "\0\1\014") {
				cnamegroup_leader(str);
			}
			else if (str == "\0\1\016") {
				ckindqqgroup_leader(str);
			}
			if (str == "\0\1\6") {
				return 1;
			}
		}
		
	}
	else if (use->findgroup(str)->iff_leader(use->_ID()) == 0) {
		message.reload("\0");
		message.send();
		return 0;
	}
	else {
		message.reload("\2");
		message.send();
		while (1) {
			
			if (str == "\000\001\011") {
				kickgroup_manager(str);
			}
			else if (str == "\0\1\012") {
				checkgroup_manager(str);
			}
			else if (str == "\0\1\014") {
				cnamegroup_manager(str);
			}
			if (str == "\0\1\6") {
				return 1;
			}
		}
	}
}
int recving_lyh::newmanagergroup_qq(string &gid) {
	message.recv();
	string key, newid;
	message.replace();
	key = message.word();
	//id = message.word();
	newid = message.word();
	if (use->findgroup(gid)->find(newid) == 0) {
		message.reload("\0");
		message.send();
		return 0;
	}
	use->findgroup(gid)->leader_do(use->_ID(),key,4,newid);
	message.reload("\1");
	message.send();
	return 1;
}
int recving_lyh::delmanagergroup_qq(string &gid) {
	message.recv();
	string key, id;
	message.replace();
	key = message.word();
	id = message.word();
	if (use->findgroup(gid)->find(id) == 0) {
		message.reload("\0");
		message.send();
		return 0;
	}
	use->findgroup(gid)->leader_do(use->_ID(),key,5,id);
	message.reload("\1");
	message.send();
	return 1;
}
int recving_lyh::kickgroup_leader(string& gid) {
	message.recv();
	message.replace();
	string key, id;
	key = message.word();
	id = message.word();
	if (use->findgroup(gid)->find(id) == 0) {
		message.reload("\0");
		message.send();
		return 0;
	}
	use->findgroup(gid)->leader_do(use->_ID(), key, 3, id);
	use->find(id)->del_group(gid);
	message.reload("\1");
	message.send();
	return 1;
}
int recving_lyh::checkgroup_leader(string& gid) {
	message.recv();
	string key = message.str();
	string iff;
	string id;
	use->findgroup(gid)->sendapply(message);
	message.replace();
	id = message.word();
	message.recv();
	iff = message.str();
	if (iff[0] == '\1') {
		use->findgroup(gid)->leader_do(use->_ID(), key, 2, id);
		use->find(id)->add_group(gid);
		return 1;
	}
	else {
		return 0;
	}
}
int recving_lyh::cnamegroup_leader(string& gid) {
	string key, name;
	message.recv();
	message.replace();
	key=message.word();
	name = message.word();
	use->findgroup(gid)->leader_do(use->_ID(), key, 1, name);
	message.reload("\1");
	message.send();
	return 1;
}
int recving_lyh::ckindqqgroup_leader(string& gid) {
	message.recv();
	message.replace();
	string key, type;
	type[0] = use->findgroup(gid)->leader_do(use->_ID(), key, 7, type);
	message.reload(type);
	message.send();
	return 1;
}
int recving_lyh::kickgroup_manager(string& gid) {
	message.recv();
	message.replace();
	string key, id;
	key = message.word();
	id = message.word();
	if (use->findgroup(gid)->find(id) == 0) {
		message.reload("\0");
		message.send();
		return 0;
	}
	use->findgroup(gid)->manager_do(use->_ID(), key, 3, id);
	use->find(id)->del_group(gid);
	message.reload("\1");
	message.send();
	return 1;
}
int recving_lyh::checkgroup_manager(string& gid) {
	message.recv();
	string key = message.str();
	string iff;
	string id;
	use->findgroup(gid)->sendapply(message);
	message.replace();
	id = message.word();
	message.recv();
	iff = message.str();
	if (iff[0] == '\1') {
		use->findgroup(gid)->manager_do(use->_ID(), key, 2, id);
		use->find(id)->add_group(gid);
		return 1;
	}
	else {
		return 0;
	}
}
int recving_lyh::cnamegroup_manager(string& gid) {
	string key, name;
	message.recv();
	message.replace();
	key = message.word();
	name = message.word();
	use->findgroup(gid)->manager_do(use->_ID(), key, 1, name);
	message.reload("\1");
	message.send();
	return 1;
}

int recving_lyh::creatgroup() {
	message.recv();
	string name = message.word();
	string key = message.word();
	int id = randomnum(7);
	string ID = to_string(id);
	while (use->findgroup(ID) == NULL) {
		int id = randomnum(7);
		string ID = to_string(id);
	}
	if (use->_way() == 1) {
		group_lyh* now = new qqgroup_lyh(ID);
		now->set_leader(use->_ID());
		now->leader_do(use->_ID(), key, 1, name);
		use->add_group(ID);
		sqq_group_lyh::putin(now);
	}
	else if (use->_way() == 2) {
		group_lyh* now = new webogroup_lyh(ID);
		now->set_leader(use->_ID());
		now->leader_do(use->_ID(), key, 1, name);
		use->add_group(ID);
		swebo_group_lyh::putin(now);
	}
	else if (use->_way() == 3) {
		group_lyh* now = new wechatgroup_lyh(ID);
		now->set_leader(use->_ID());
		now->leader_do(use->_ID(), key, 1, name);
		use->add_group(ID);
		swechat_group_lyh::putin(now);
	}
	message.reload(ID);
	message.send();
	return 1;
}
int recving_lyh::pullgroup() {
	message.recv();
	string key, gid, fid;
	message.clear();
	message.add_num(fid);
	message.add_num(use->find(fid)->_ID());
	message.add_num("来自好友推荐");
	message.add_num(use->_ID());
	message.add_num(use->_name());
	use->findgroup(gid)->addapply(message.str());
	message.reload("\1");
	message.send();
	return 1;
}
int recving_lyh::songroup() {
	message.recv();
	string fid;
	string key, uid;
	key = message.word();
	fid = message.word();
	if (use->findgroup(fid) == NULL || use->findgroup(fid)->find(use->_ID()) == 0) {
		message.reload("\0");
		message.send();
		return 0;
	}
	else {
		message.reload("\1");
		message.send();
	}
	message.recv();
	int id = randomnum(7);
	string ID = to_string(id);
	while (use->findgroup(ID) == NULL) {
		int id = randomnum(7);
		string ID = to_string(id);
	}
	group_lyh* now;
	if (use->_way() == 1) {
		 now = new qqgroup_lyh(ID);
		now->set_leader(use->_ID());
		now->leader_do(use->_ID(), key, 1, "子群");
		use->add_group(ID);
		sqq_group_lyh::putin(now);
	}
	else if (use->_way() == 2) {
		 now = new webogroup_lyh(ID);
		now->set_leader(use->_ID());
		now->leader_do(use->_ID(), key, 1, "子群");
		use->add_group(ID);
		swebo_group_lyh::putin(now);
	}
	else if (use->_way() == 3) {
		 now = new wechatgroup_lyh(ID);
		now->set_leader(use->_ID());
		now->leader_do(use->_ID(), key, 1, "子群");
		use->add_group(ID);
		swechat_group_lyh::putin(now);
	}

	while (1) {
		uid = message.word();
		if (uid == "") {
			break;
		}
		if (use->findgroup(fid)->find(uid) == 1) {
			now->leader_do(use->_ID(), key, 2, uid);
			use->find(uid)->add_group(ID);
		}
	}
	message.reload(ID);
	message.send();
	return 1;
}

int recving_lyh::dataset() {
	
	string str;
	while (1) {
		message.recvsign();
		str = message.nowsignal();
		if (str == "\0\0\1") {
			setname();
		}
		else if (str == "\0\0\2") {
			setbirth();
		}
		else if (str == "\0\0\3") {
			setplace();
		}
		else if (str == "\0\2\1") {
			return 1;
		}
	}
}
int recving_lyh::setname() {
	message.recv();
	string key = message.word();
	string name = message.word();
	use->set_name(key, name);
	return 1;
}
int recving_lyh::setbirth() {
	message.recv();
	string key = message.word();
	string name = message.word();
	use->set_birth(key, name);
	return 1;
}
int recving_lyh::setplace() {
	message.recv();
	string key = message.word();
	string name = message.word();
	use->set_place(key, name);
	return 1;
}
int recving_lyh::bindset() {
	string bind;
	use->show_bind(message);
	message.send();
	message.recvsign();
	string id, key;
	if (message.nowsignal() == "\0\0\0") {
		return 1;
	}
	else if (message.nowsignal() == "\0\0\1") {
		message.recv();
		id = message.word();
		key = message.word();
		if (use->_way() == 1 || use->_way() == 2) {
			message.recv();
			message.reload("\0");
			message.send();
			return 0;
		}
		if (use->my_bind() == NULL) {
			use->creat_bind(use->_ID());
		}
		if (finduser(id, 1)->join_bind(use->my_bind(), key) == 1) {

		}
	}
	else if (message.nowsignal() == "\0\0\2") {
		id = message.word();
		key = message.word();
		if (use->_way() == 1 || use->_way() == 2) {
			message.recv();
			message.reload("\0");
			message.send();
			return 0;
		}
		if (use->my_bind() == NULL) {
			use->creat_bind(use->_ID());
		}
		finduser(id, 2)->join_bind(use->my_bind(), key);
	}
	else if (message.nowsignal() == "\0\0\3") {
		id = message.word();
		key = message.word();
		if (use->_way() == 3 ) {
			message.recv();
			message.reload("\0");
			message.send();
			return 0;
		}
		if (use->my_bind() == NULL) {
			use->creat_bind(use->_ID());
		}
		finduser(id, 3)->join_bind(use->my_bind(), key);
	}
	else if (message.nowsignal() == "\0\0\11") {
		use->creat_bind(use->_ID());
	}
	use->with_bind();
	message.reload("\1");
	message.send();
	return 1;
}
int recving_lyh::delset() {
	if (use->_way() == 1) {
		sqq_user_lyh::del(use->_ID());
	}
	else if (use->_way() == 2) {
		swebo_user_lyh::del(use->_ID());
	}
	else if (use->_way() == 3) {
		swechat_user_lyh::del(use->_ID());
	}
	return 1;
}
int recving_lyh::SHOW = 0;



