#include"../头文件/main.h"
// 链接 ws2_32.lib

std::mutex console_mutex; // 用于多线程安全控制台输出
SOCKET server_socket = INVALID_SOCKET; // 服务端套接字

// 初始化服务器：启动 Winsock、创建套接字、绑定地址并监听端口
bool initialize_server(const char* ip, int port) {
    WSADATA wsa_data;
    sockaddr_in server_addr;

    // 初始化 Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        std::cerr << "WSAStartup 初始化失败。错误码: " << WSAGetLastError() << std::endl;
        return false;
    }

    // 创建服务端套接字
    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket == INVALID_SOCKET) {
        std::cerr << "套接字创建失败。错误码: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return false;
    }

    // 配置服务端地址
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    // 绑定套接字到指定地址和端口
    if (bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "套接字绑定失败。错误码: " << WSAGetLastError() << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return false;
    }

    // 开始监听连接
    if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "监听失败。错误码: " << WSAGetLastError() << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return false;
    }

    std::cout << "服务器正在监听端口 " << port << "..." << std::endl;
    return true;
}

// 监听客户端连接并为每个客户端创建独立线程
void handle_connections() {
    std::vector<std::thread> threads;

    while (true) {
        sockaddr_in client_addr;
        int client_addr_size = sizeof(client_addr);

        // 接受客户端连接
        SOCKET client_socket = accept(server_socket, (sockaddr*)&client_addr, &client_addr_size);
        if (client_socket == INVALID_SOCKET) {
            std::cerr << "接受连接失败。错误码: " << WSAGetLastError() << std::endl;
            continue;
        }

        // 打印客户端连接信息
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
        {
            std::lock_guard<std::mutex> lock(console_mutex);
            std::cout << "新连接来自 " << client_ip << ":" << ntohs(client_addr.sin_port) << std::endl;
        }

        // 创建新线程处理客户端
        //下为实际使用
        threads.emplace_back(std::thread(recving_lyh::main, client_socket));
       // recving_lyh::main(client_socket);
        // 分离线程，允许其独立运行
        //下为实际使用
        threads.back().detach();
    }
}

// 清理服务器资源
void cleanup_server() {
    if (server_socket != INVALID_SOCKET) {
        closesocket(server_socket); // 关闭服务端套接字
    }
    WSACleanup(); // 清理 Winsock 资源
    {
        std::lock_guard<std::mutex> lock(console_mutex);
        std::cout << "服务器已清理资源并关闭。" << std::endl;
    }
}

void simpleface() {
    string a, b, password;
    while (1) {
        cout << "1新建qq用户 0退出" << endl;
        cin >> a;
        if (a[0] == '1') {
            cout << "输入密码";
            cin >> b;
            password=bcrypt::generateHash(b);
            cout << endl;
            cout << "输入账号";
            cin >> b;
            user_lyh* use = new qq_lyh(b, "新用户", to_string(time(0)), "0", "未知", password);
            sqq_user_lyh::putin(use);
        }
        else if (a[0] == '0') {
            return;
        }
    }
}

// 主函数
int maain() {
    string key;
    cin >> key; 
    cout<< endl;
    cout << key << endl;
    cout << bcrypt::generateHash(key) << endl;
    cout << bcrypt::generateHash(key) << endl;
    cout << bcrypt::validatePassword(key,bcrypt::generateHash(key)) << endl;
    return 1;
}
int main() {
    const char* IP = "0.0.0.0"; // 监听所有网络接口
    const int PORT = 8080;      // 监听端口

    // 初始化服务器
    if (!initialize_server(IP, PORT)) {
        return 1;
    }

    data_lyh data;
    data.start();
    
    // 监听连接并处理客户端

    std::thread handle(handle_connections);  
    handle.detach();
    //handle_connections();
    simpleface();
    cout << "按任意键离开" << endl;
    _getch();

    // 清理服务器资源
    cleanup_server();
    data.write();
    return 0;
}






























//#include <iostream>
//#include<WinSock2.h>
//#include <WS2tcpip.h> 
//#pragma comment(lib,"WS2_32")
//using namespace std;
//int start() {
//	WSADATA wsadata;
//	WSAStartup(MAKEWORD(2, 2), &wsadata);
//	SOCKET listen_socket = socket(AF_INET, SOCK_STREAM, 0);
//	if (listen_socket == -1) {
//		cout << "创建socket失败  " << GetLastError() << endl;
//		return -1;
//	}
//	sockaddr_in local ;
//	local.sin_family = AF_INET;
//	local.sin_port = htons(8080);
//	local.sin_addr.s_addr =htonl(INADDR_ANY);// INADDR_LOOPBACK
//	if (-1 == bind(listen_socket, (sockaddr*)&local, sizeof(local))) {
//		cout << "bind错误  " << GetLastError << endl;
//		return -1;
//	};
//	if (-1 == listen(listen_socket,10)){
//		cout << "listen启动失败  " << GetLastError << endl;
//		return -1;
//	};
//	while (1) {
//		SOCKET client_socket = accept(listen_socket, NULL, NULL);
//		if (client_socket == INVALID_SOCKET) {
//			continue;
//		}
//		char get[128];
//		recv(client_socket, get, 128, 0);
//		closesocket(client_socket );
//	}
//}

/*

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <thread>
#pragma comment(lib, "WS2_32")
#include"../头文件/user.h"
#include"../头文件/internet.h"
using namespace std;

// 客户端处理函数
class handle_lyh {
public:
    handle_lyh(SOCKET soc){
        socket = soc;
    };
    int recving() {
        string str;
        char c1, c2, c3;
        str.resize(4);
        int bytesReceived = recv(socket, &str[0], 3, 0);
        c1 = str[0];
        c2 = str[1];
        c3 = str[3];
        if (bytesReceived > 0) {
            if (c1 == 0) {

            }




        }
        else {
            cout << "Receive error or client disconnected." << endl;
        }
    }
protected:
    int login000() {

    }
    int checkfriend001() {

    }
    SOCKET socket;
    message_lyh message;
    user_lyh* use;
    toget_lyh toget;
};
void handleClient(SOCKET client_socket) {
    
}

int start() {
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);

    SOCKET listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_socket == INVALID_SOCKET) {
        cout << "创建 socket 失败，错误代码：" << WSAGetLastError() << endl;
        return -1;
    }

    sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(8080);
    local.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listen_socket, (sockaddr*)&local, sizeof(local)) == SOCKET_ERROR) {
        cout << "绑定失败，错误代码：" << WSAGetLastError() << endl;
        closesocket(listen_socket);
        WSACleanup();
        return -1;
    }

    if (listen(listen_socket, 10) == SOCKET_ERROR) {
        cout << "监听失败，错误代码：" << WSAGetLastError() << endl;
        closesocket(listen_socket);
        WSACleanup();
        return -1;
    }

    cout << "服务器正在监听端口 8080" << endl;

    while (true) {
        SOCKET client_socket = accept(listen_socket, nullptr, nullptr);
        if (client_socket == INVALID_SOCKET) {
            cout << "接受客户端连接失败，错误代码：" << WSAGetLastError() << endl;
            continue;
        }

        // 启动新线程处理客户端连接
        thread clientThread(handleClient, client_socket);
        clientThread.detach(); // 分离线程，以便独立运行
    }

    closesocket(listen_socket);
    WSACleanup();
    return 0;
}

int main() {
    return start();
}
*/


//int main()
//{
//    std::cout << "this is Server windows" << std::endl;
//    WSADATA wsaData;
//    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
//    {
//        std::cerr << "Failed to initialize Windsock" << std::endl;
//        return 1;
//    }
//    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);
//    if (listenSocket == INVALID_SOCKET)
//    {
//        std::cerr << "Failed to create socket" << std::endl;
//        WSACleanup();
//        return 1;
//    }
//    sockaddr_in serverAddr;
//    serverAddr.sin_family = AF_INET;
//    serverAddr.sin_port = htons(6000);
//    cout << "输入IP地址：";
//    string my_IP;
//    cin >> my_IP;
//    if (inet_pton(AF_INET, "my_IP", &(serverAddr.sin_addr)) <= 0)
//    {
//        std::cerr << "无效的服务器地址" << std::endl;
//        closesocket(listenSocket);
//        WSACleanup();
//        return 1;
//    }
//    if (bind(listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
//    {
//        std::cerr << "Failed to bind socket." << std::endl;
//        closesocket(listenSocket);
//        WSACleanup();
//        return 1;
//    }
//    if (listen(listenSocket, 5) == SOCKET_ERROR)
//    {
//        std::cerr << "Failed to listen onf socket." << std::endl;
//        closesocket(listenSocket);
//        WSACleanup();
//        return 1;
//    }
//    SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
//    while (true)
//    {
//        if (clientSocket == INVALID_SOCKET)
//        {
//            std::cerr << "Failed to accept client connection" << std::endl;
//            closesocket(listenSocket);
//            WSACleanup();
//            return 1;
//        }
//
//        char revBuffer[1024] = "";
//            if (recv(clientSocket, revBuffer, sizeof(revBuffer), 0) == SOCKET_ERROR)
//            {
//                std::cerr << "Failed to receive data" << std::endl;
//                closesocket(clientSocket);
//                continue;
//            }
//        std::cout << "recive client:" << revBuffer << std::endl;
//        std::string message = "server:hello client";
//        if (send(clientSocket, message.c_str(), message.size(), 0) == SOCKET_ERROR)
//        {
//            std::cerr << "Failed to send data" << std::endl;
//        }
//    }
//    closesocket(clientSocket);
//    closesocket(listenSocket);
//    WSACleanup();
//    return 0;
