
#include"../头文件/data.h"
using namespace std;
using namespace std::filesystem;
/*
* qq，webo，wechat各自分文件存储
* user 有6位id  group7位
一个文件储存所有用户和群的的基础信息  命名 qqallbasedata（wechatallbasedata）
一个文件储存用户的好友与群聊信息

群聊 # 群ID 类型（qq才有）  $ 群主 & 管理员 @ 用户ID @ 用户ID ...... ！（结尾）
一个文件储存群聊的用户信息

bind文件 1y qqid 3y 微信id
 1n 000000 3n 000000 表示无bind信息

 to_getin信息
收信人id 发送内容 时间（time_t格式）

 apply信息
 申请人 接收者 发送内容 时间

*/
/*
const string ID;//6位
	string name;//最多20位
	string birth;//8位
	const string useage;//8位
	string place;//最多40位
	char key[32];//
	skipstring_lyh* friends;//记录id
	int friend_level=1;
	int friend_num;
	skipstring_lyh* groups;
	int group_level = 1;
	int group_num;
	bind_lyh* bind=NULL;
	int bind_num;
	leader_lyh* leader;
	functions_lyh function;
	
	*/
//class allfile_lyh {
//public:
//	const std::string id() {
//		return ID;
//	}
//	allfile_lyh(path entry) {
//		file.open(entry);
//		string tmp;
//		while (file.eof() != true) {
//			getline(file, tmp);
//			row++;
//		}
//		ID = entry.stem().string();
//	}
//	void in(string str, time_t tm) {
//		file.seekg(0, ios::end);
//		file << str << ' ' << tm << '\n';
//		row++;
//	}
//	void out(string& str, int num) {
//		string tmp = {};
//		file.seekp(ios::beg);
//		if (num == -1) {
//			while (1) {
//				file >> tmp;
//				if (file.eof() == true) { return; }
//				str += tmp;
//				str += "\n";
//				file >> tmp;
//				str += tmp;
//				str += "\n";
//			}
//		}
//		else {
//			int tmpi = row - num;
//			while (tmpi > 0) {
//				getline(file, tmp);
//				tmpi--;
//			}
//			while (file.eof() != true) {
//				file >> tmp;
//				str += tmp;
//				str += "\n";
//			}
//		}
//	}
//	void flash() {
//		file.flush();
//	}
//	void close() {
//		file.close();
//	}
//protected:
//	int row = 0;
//	string ID;
//	fstream file;
//};
//class data_lyh {
//public:
//	data_lyh(string id, char w) {
//		ID = id;
//		way = w;
//		path directory = id + w;
//		creatfile(id, w);
//		for (const auto& entry : directory_iterator(directory)) {
//			if (entry.is_regular_file() && entry.path().extension() == ".txt") {
//				file.push_back(entry.path());
//			}
//		}
//	}
//	data_lyh() {};
//	void start(string id, char w) {
//		ID = id;
//		way = w;
//		path directory = id + w;
//		creatfile(id, w);
//		for (const auto& entry : directory_iterator(directory)) {
//			if (entry.is_regular_file() && entry.path().extension() == ".txt") {
//				file.push_back(entry.path());
//			}
//		}
//	}
//	void flash() {
//		for (auto& i : file) {
//			i.flash();
//		}
//	}
//	int in(string str, time_t tm, string id) {
//		allfile_lyh* pi = find(id);
//		if (pi == NULL)return 0;
//		pi->in(str, tm);
//	}
//	int out(string& str, int num = -1, string id = '\0') {
//		allfile_lyh* pi = find(id);
//		if (pi == NULL)return 0;
//		pi->out(str, num);
//	}
//	int remove(string id) {
//		int num = 0;
//		while (num < file.size()) {
//			if (file[num].id() == id) {
//				file[num].close();
//				file.erase(file.begin() + num);
//			}
//		}
//		remove(ID + '/' + id + ".txt");
//		return 0;
//	}
//	int newone(string id) {
//		string str;
//		str = ID + '/' + id + ".txt";
//		if (find(id) != NULL) {
//			return 0;
//		}
//		fopen(str.c_str(), "w");
//		return 1;
//	}
//	int creatfile(string ID, char w) {
//		if (create_directory(ID + w) == true)return 1;
//		else return 0;
//	}
//protected:
//	string ID;
//	char way;
//	vector<allfile_lyh> file;
//	allfile_lyh* find(string id) {
//		for (auto& i : file) {
//			if (i.id() == id) {
//				return &i;
//			}
//		}
//		return NULL;
//	}
//};


	data_lyh::data_lyh(){}
	int data_lyh::start() {
		alluse("D:/project/qq/qqallbasedata.txt",1);
		alluse("D:/project/webo/weboallbasedata.txt", 2);
		alluse("D:/project/wechat/wechatallbasedata.txt", 3);
		allfriend("D:/project/qq/qqallfriend.txt", 1);
		allfriend("D:/project/webo/weboallfriend.txt", 2);
		allfriend("D:/project/wechat/wechatallfriend.txt", 3);
		//allgroup("../qq/qqeveryonegroup.txt", 1);
		//allgroup("../webo/weboeveryonegroup.txt", 2);
		//allgroup("../wechat/wechateveryonegroup.txt", 3);
		allbind("D:/project/together/bind.txt");
		allgroupnumber("D:/project/qq/qqallgroupnumber.txt", 1);
		allgroupnumber("D:/project/webo/weboallgroupnumber.txt", 2);
		allgroupnumber("D:/project/wechat/wechatallgroupnumber.txt", 3);
		allnews("D:/project/qq/qqnews.txt", 1);
		allnews("D:/project/webo/webonews.txt", 1);
		allnews("D:/project/wechat/wecahtnews.txt", 1);
		return 1;
	}
	int data_lyh::write() {
		saveqqBaseData("D:/project/qq/qqallbasedata.txt");
		saveweboBaseData("D:/project/webo/weboallbasedata.txt");
		savewechatBaseData("D:/project/wechat/wechatallbasedata.txt");
		saveqqfriend("D:/project/qq/qqallfriend.txt");
		savewebofriend("D:/project/webo/weboallfriend.txt");
		savewechatfriend("D:/project/wechat/wechatallfriend.txt");
		saveqqGroup("D:/project/qq/qqallgroupnumber.txt");
		saveweboGroup("D:/project/webo/weboallgroupnumber.txt");
		savewechatGroup("D:/project/wechat/wechatallgroupnumber.txt");
		saveBind("D:/project/together/bind.txt");
		savenewsqq("D:/project/qq/qqnews.txt");
		savenewswebo("D:/project/webo/webonews.txt");
		savenewswechat("D:/project/wechat/wecahtnews.txt");
		return 1;
	}


	int data_lyh::alluse(const char name[],int way) {
		file.open(name, std::ios::in | std::ios::out );
		file.seekg(ios::beg);
		while (file.eof() != true) {
			oneuse(way);
		}
		file.close();
		return 1;
	}
	int data_lyh::oneuse(int way) {
		string ID;
		string name;//最多20位
		string birth;//8位
		string useage;//8位
		string place;//最多40位
		string key;//
		if (!(file >> ID)) {
			return 0;
		}; 
		if (file.eof() == 1) {
			return 1;
		}
		file >> name >> birth >> useage >> place >> key;
		if (way == 1) {
			user_lyh* use = new qq_lyh(ID, name, birth, useage, place, key);
			sqq_user_lyh::putin(use);
		}
		else if (way == 2) {
			user_lyh* use = new webo_lyh(ID, name, birth, useage, place, key);
			swebo_user_lyh::putin(use);
		}
		else if (way == 3) {
			user_lyh* use = new wechat_lyh(ID, name, birth, useage, place, key);
			swechat_user_lyh::putin(use);
		}
		return 1;
	}
	int data_lyh::allfriend(const char name[], int way) {
		file.open(name,std::ios::in | std::ios::out);
		file.seekg(ios::beg);
		if (way == 1) {
			while (file.eof() != true) {
				onefriendqq();
			}
		}
		else if (way == 2) {
			while (file.eof() != true) {
				onefriendwebo();
			}
		}
		else if (way == 3) {
			while (file.eof() != true) {
				onefriendwechat();
			}
		}
		file.close();
		return 1;
	}
	int data_lyh::onefriendqq() {
		string a, b;
		if (!(file >> a)) {
			return 0;
		};
		file >> b;
		sqq_user_lyh::find(a)->add_friend(b);
	}
	int data_lyh::onefriendwebo() {
		string a, b;
		if (!(file >> a)) {
			return 0;
		};
		file >> b;
		swebo_user_lyh::find(a)->add_friend(b);
	}
	int data_lyh::onefriendwechat() {
		string a, b;
		if (!(file >> a)) {
			return 0;
		};
		file >> b;
		swechat_user_lyh::find(a)->add_friend(b);
	}
	int data_lyh::allgroup(const char name[], int way) {
		file.open(name);
		file.seekg(ios::beg);
		if (way == 1) {
			while (file.eof() != true) {
				onegroupqq();
			}
		}
		else if (way == 2) {
			while (file.eof() != true) {
				onegroupwebo();
			}
		}
		else if (way == 3) {
			while (file.eof() != true) {
				onegroupwechat();
			}
		}
		file.close();
		return 1;
	}
	int data_lyh::onegroupqq() {
		string a, b;
		if (!(file >> a)) {
			return 0;
		};
		file >> b;
		sqq_user_lyh::find(a)->add_group(b);
	}
	int data_lyh::onegroupwebo() {
		string a, b;
		if (!(file >> a)) {
			return 0;
		};
		file >> b;
		swebo_user_lyh::find(a)->add_group(b);
	}
	int data_lyh::onegroupwechat() {
		string a, b;
		if (!(file >> a)) {
			return 0;
		};
		file >> b;
		swechat_user_lyh::find(a)->add_group(b);
	}
	int data_lyh::allbind(const char name[]) {
		file.open(name);
		while (file.eof() != true) {
			onebind();
		}
		file.close();
		return 1;
	}
	int data_lyh::onebind() {
		string a="", b="", temp;
		if (!(file >> temp)) {
			return 0;
		};
		if (temp == "1y") {
			file >> a;
		}
		file >> temp;
		if (temp == "3y") {
			file >> b;
		}
		bind_lyh* bind = bind_lyh::set_bind(a, b);
		user_lyh::set_bind(bind,a, b);
	}
	int data_lyh::allgroupnumber(const char name[], int way) {
		file.open(name);
		file.seekg(ios::beg);
		if (way == 1) {
			while (file.eof() != true) {
				onegroupnumberqq();
			}
		}
		else if (way == 2) {
			while (file.eof() != true) {
				onegroupnumberwebo();
			}
		}
		else if (way == 3) {
			while (file.eof() != true) {
				onegroupnumberwechat();
			}
		}
		file.close();
		return 1;
	}
	int data_lyh::onegroupnumberqq() {
		string a = "", b = "", temp;
		if (!(file >> temp)) {
			return 0;
		}
		if (temp == "#") {
			file >> a;
			new qqgroup_lyh(a);
			while (1) {
				file >> b;
				if (b == "!") {
					break;
				}
				else if(b=="$") {
					cin >> b;
					sqq_group_lyh::find(a)->leader = b;
					sqq_group_lyh::find(a)->add(b);
					sqq_user_lyh::find(b)->add_group(a);
				}
				else if (b == "@") {
					sqq_group_lyh::find(a)->add(b);
					sqq_user_lyh::find(b)->add_group(a);
				}
				else if (b == "&") {
					sqq_group_lyh::find(a)->addm(b);
					sqq_group_lyh::find(a)->add(b);
					sqq_user_lyh::find(b)->add_group(a);
				}
			}
		}
	}
	int data_lyh::onegroupnumberwebo() {
		string a = "", b = "", temp;
		if (!(file >> temp)) {
			return 0;
		}
		if (temp == "#") {
			file >> a;
			new webogroup_lyh(a);
			while (1) {
				file >> b;
				if (b == "!") {
					break;
				}
				else if (b == "$") {
					cin >> b;
					swebo_group_lyh::find(a)->leader = b;
					swebo_group_lyh::find(a)->add(b);
					swebo_user_lyh::find(b)->add_group(a);
				}
				else if (b == "@") {
					swebo_group_lyh::find(a)->add(b);
					swebo_user_lyh::find(b)->add_group(a);
				}
			}
		}

	}
	int data_lyh::onegroupnumberwechat() {
		string a = "", b = "", temp;
		if (!(file >> temp)) {
			return 0;
		}
		if (temp == "#") {
			file >> a;
			new wechatgroup_lyh(a);
			while (1) {
				file >> b;
				if (b == "!") {
					break;
				}
				else if (b == "$") {
					cin >> b;
					swechat_group_lyh::find(a)->leader = b;
					swechat_group_lyh::find(a)->add(b);
					swechat_user_lyh::find(b)->add_group(a);
				}
				else if (b == "@") {
					swechat_group_lyh::find(a)->add(b);
					swechat_user_lyh::find(b)->add_group(a);
				}
			}
		}

	}
	int data_lyh::allnews(const char name[], int way){
		file.open(name);
		file.seekg(ios::beg);
		message_lyh mess(1);
		if (way == 1) {
			while (file.eof() != true) {
				onenewsqq(mess);
			}
		}
		else if (way == 2) {
			while (file.eof() != true) {
				onenewswebo(mess);
			}
		}
		else if (way == 3) {
			while (file.eof() != true) {
				onenewswechat(mess);
			}
		}
		file.close();
		return 1;
	}
	int data_lyh::onenewsqq(message_lyh& mess) {
		string a, b;
		time_t c;
		if (!(file >> a)) {
			return 0;
		}
		file >> b;
		file >> c;
		if (sqq_user_lyh::find(a) != NULL)sqq_user_lyh::find(a)->addnews(b, c);
	}
	int data_lyh::onenewswebo(message_lyh& mess) {
		string a, b;
		time_t c;
		if (!(file >> a)) {
			return 0;
		}
		file >> b;
		file >> c;
		swebo_user_lyh::find(a)->addnews(b, c);
	}
	int data_lyh::onenewswechat(message_lyh& mess) {
		string a, b;
		time_t c;
		if (!(file >> a)) {
			return 0;
		}
		file >> b;
		file >> c;
		if(swechat_user_lyh::find(a)!=NULL)swechat_user_lyh::find(a)->addnews(b, c);
	}



	void data_lyh::saveqqBaseData( const string& filename) {
		//ofstream file(filename, ios::out | ios::trunc);
		file.open(filename, std::ios::in | std::ios::out | std::ios::trunc);
		file.seekp(ios::beg);
		for (const auto& user : sqq_user_lyh::every) {
			if (user == NULL)continue;
			file << user->_ID() << ' '
				<< user->_name() << ' '
				<< user->_birth() << ' '
				<< user->_useage() << ' '
				<< user->_place() << '\n'
				<< user->key << '\n';
		}
		file.close();
	}
	void data_lyh::saveweboBaseData(const string& filename) {
		//ofstream file(filename, ios::out | ios::trunc);
		file.open(filename, std::ios::in | std::ios::out | std::ios::trunc);
		for (const auto& user : swebo_user_lyh::every) {
			if (user == NULL)continue;
			file << user->_ID() << ' '
				<< user->_name() << ' '
				<< user->_birth() << ' '
				<< user->_useage() << ' '
				<< user->_place() << '\n'
				<< user->key << '\n';
		}
		file.close();
	}
	void data_lyh::savewechatBaseData(const string& filename) {
		//ofstream file(filename, ios::out | ios::trunc);
		file.open(filename, std::ios::in | std::ios::out | std::ios::trunc);
		for (const auto& user : swechat_user_lyh::every) {
			if (user == NULL)continue;
			file << user->_ID() << ' '
				<< user->_name() << ' '
				<< user->_birth() << ' '
				<< user->_useage() << ' '
				<< user->_place() << '\n'
				<< user->key << '\n';
		}
		file.close();
	}

	//群聊 # 群ID 类型（qq才有）  $ 群主& 管理员 @ 用户ID @ 用户ID ...... ！（结尾）
	//	一个文件储存群聊的用户信息

	void data_lyh::saveqqGroup( const string& filename) {
		file.open(filename, std::ios::in | std::ios::out | std::ios::trunc);
		hash_lyh* ha;
		for (const auto& gro : sqq_group_lyh::every) {
			if (gro == NULL)continue;
			file << "#" << " ";
			file << " $ " << gro->leader << " ";
			ha = &gro->everyone;
			for (const auto& man : gro->manager) {
				file << " & " << man << " ";
			}
			for(int i:ha->every) {
				file << " @ " << to_string(i) << " ";
			}
			file << "\n";
		}

		file.close();
	}
	void data_lyh::saveweboGroup(const string& filename) {
		file.open(filename, std::ios::in | std::ios::out | std::ios::trunc);
		hash_lyh* ha;
		for (const auto& gro : swebo_group_lyh::every) {
			if (gro == NULL)continue;
			file << "#" << " ";
			file << " $ " << gro->leader << " ";
			ha = &gro->everyone;
			for (int i : ha->every) {
				file << " @ " << to_string(i) << " ";
			}
			file << "\n";
		}

		file.close();
	}
	void data_lyh::savewechatGroup( const string& filename) {
		file.open(filename, std::ios::in | std::ios::out | std::ios::trunc);
		hash_lyh* ha;
		for (const auto& gro : swechat_group_lyh::every) {
			if (gro == NULL)continue;
			file << "#" << " ";
			file << " $ " << gro->leader << " ";
			ha = &gro->everyone;
			for (int i : ha->every) {
				file << " @ " << to_string(i) << " ";
			}
			file << "\n";
		}
		file.close();
	}


	void data_lyh::saveqqfriend(const string& filename) {
		file.open(filename, std::ios::in | std::ios::out | std::ios::trunc);
		hash_lyh* ha;
		for (const auto& gro : sqq_user_lyh::every) {
			if (gro == NULL)continue;
			for(int i : (gro->friends).every) {
				cout << "0";
				cout << i ;
				file << " " << gro->ID << " " << to_string(i)<<" \n";
			}
		}
		file.close();
	}
	void data_lyh::savewebofriend(const string& filename) {
		file.open(filename, std::ios::in | std::ios::out | std::ios::trunc);
		hash_lyh* ha;
		for (const auto& gro : swebo_user_lyh::every) {
			if (gro == NULL)continue;
			ha = &gro->friends;
			for(int i:ha->every) {
				file << " " << gro->ID << " " << to_string(i) << " \n";
			}
		}
		file.close();
	}
	void data_lyh::savewechatfriend(const string& filename) {
		file.open(filename, std::ios::in | std::ios::out | std::ios::trunc);
		hash_lyh* ha;
		for (const auto& gro : swechat_user_lyh::every) {
			if (gro == NULL)continue;
			ha = &gro->friends;
			for (int i : ha->every) {
				file << " " << gro->ID << " " << to_string(i) << " \n";
			}
		}
		file.close();
	}

	// 写入 `bind` 信息
	void data_lyh::saveBind( const string& filename) {
		file.open(filename, std::ios::in | std::ios::out | std::ios::trunc);
		for (const auto& use : swechat_user_lyh::every) {
			if (use == NULL)continue;
			if (use->bind_num == 2) {
				file << " 1y " << use->bind->qq << " 3y " << use->bind->wechat << " \n";
			}
		}
		file.close();
	}

	// 写入消息信息
	void data_lyh::savenewsqq(const string& filename) {
		file.open(filename, std::ios::in | std::ios::out | std::ios::trunc);
		if (!file.is_open()) {
			cerr << "无法打开文件：" << filename << endl;
			return;
		}
		string str;
		getin_lyh *get;
		for (const auto& use : sqq_user_lyh::every) {
			if (use == NULL)continue;
			if (use->iff_news() == 0)continue;
			get = use->news.head;
			while (get != NULL) {
				file << " " << use->ID << " " << get->data << " " << get->TIME << " \n";
			}
		}

		file.close();
	}
	void data_lyh::savenewswebo(const string& filename) {
		file.open(filename, std::ios::in | std::ios::out | std::ios::trunc);
		if (!file.is_open()) {
			cerr << "无法打开文件：" << filename << endl;
			return;
		}
		string str;
		getin_lyh* get;
		for (const auto& use : swebo_user_lyh::every) {
			if (use == NULL)continue;
			if (use->iff_news() == 0)continue;
			get = use->news.head;
			while (get != NULL) {
				file << " " << use->ID << " " << get->data << " " << get->TIME << " \n";
			}
		}

		file.close();
	}
	void data_lyh::savenewswechat(const string& filename) {
		file.open(filename, std::ios::in | std::ios::out | std::ios::trunc);
		if (!file.is_open()) {
			cerr << "无法打开文件：" << filename << endl;
			return;
		}
		string str;
		getin_lyh* get;
		for (const auto& use : swechat_user_lyh::every) {
			if (use == NULL)continue;
			if (use->iff_news() == 0)continue;
			get = use->news.head;
			while (get != NULL) {
				file << " " << use->ID << " " << get->data << " " << get->TIME << " \n";
			}
		}

		file.close();
	}
	//// 写入申请信息
	//void saveApplies(const vector<apply>& applies, const string& filename) {
	//	ofstream file(filename, ios::out | ios::trunc);
	//	if (!file.is_open()) {
	//		cerr << "无法打开文件：" << filename << endl;
	//		return;
	//	}

	//	for (const auto& app : applies) {
	//		file << app.applicantID << ' ' << app.receiverID << ' ' << app.content << ' ' << app.time << '\n';
	//	}

	//	file.close();
	//}
	int flashin(data_lyh* data) {
		while (1) {
			std::this_thread::sleep_for(std::chrono::seconds(360));
			data->write();
		}
		return 1;
	}
	int flashdata(data_lyh* data) {
		std::thread flash(flashin, data);
		flash.detach();
		return 1;
	}