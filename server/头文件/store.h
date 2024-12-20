#pragma once
#include "user.h"
#include"group.h"

using std::string;
class user_lyh;
class group_lyh;
	//store类，存储每个应用的用户或群组的指针。
	class sqq_user_lyh {
	public:
		friend class data_lyh;
		static user_lyh* find(string);
		static void putin(user_lyh*);
		static void del(string);
		static void allnull();
	protected:
		static user_lyh* every[1000000];
	};

	class swebo_user_lyh {
	public:
		friend class data_lyh;
		static user_lyh* find(string ID);
		static void putin(user_lyh*);
		static void del(string ID);
		static void allnull();
	protected:
		static user_lyh* every[1000000];
	};

	class swechat_user_lyh {
	public:
		friend class data_lyh;
		static user_lyh* find(string ID);
		static void putin(user_lyh*);
		static void del(string ID);
		static void allnull();
	protected:
		static user_lyh* every[1000000];
	};

	class sqq_group_lyh {
	public:
		friend class data_lyh;
		static group_lyh* find(string ID);
		static void putin(group_lyh*);
		static void del(string ID);
		static void allnull();
	protected:
		static group_lyh* every[10000000];
	};

	class swebo_group_lyh {
	public:
		friend class data_lyh;
		static group_lyh* find(string ID);
		static void putin(group_lyh*);
		static void del(string ID);
		static void allnull();
	protected:
		static group_lyh* every[10000000];
	};

	class swechat_group_lyh {
	public:
		friend class data_lyh;
		static group_lyh* find(string ID);
		static void putin(group_lyh*);
		static void del(string ID);
		static void allnull();
	protected:
		static group_lyh* every[10000000];
	};

	

user_lyh* finduser(std::string, int);
group_lyh* findgroup(std::string, int);