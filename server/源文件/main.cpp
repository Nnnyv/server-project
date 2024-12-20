#include"../ͷ�ļ�/main.h"
// ���� ws2_32.lib

std::mutex console_mutex; // ���ڶ��̰߳�ȫ����̨���
SOCKET server_socket = INVALID_SOCKET; // ������׽���

// ��ʼ�������������� Winsock�������׽��֡��󶨵�ַ�������˿�
bool initialize_server(const char* ip, int port) {
    WSADATA wsa_data;
    sockaddr_in server_addr;

    // ��ʼ�� Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        std::cerr << "WSAStartup ��ʼ��ʧ�ܡ�������: " << WSAGetLastError() << std::endl;
        return false;
    }

    // ����������׽���
    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket == INVALID_SOCKET) {
        std::cerr << "�׽��ִ���ʧ�ܡ�������: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return false;
    }

    // ���÷���˵�ַ
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    // ���׽��ֵ�ָ����ַ�Ͷ˿�
    if (bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "�׽��ְ�ʧ�ܡ�������: " << WSAGetLastError() << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return false;
    }

    // ��ʼ��������
    if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "����ʧ�ܡ�������: " << WSAGetLastError() << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return false;
    }

    std::cout << "���������ڼ����˿� " << port << "..." << std::endl;
    return true;
}

// �����ͻ������Ӳ�Ϊÿ���ͻ��˴��������߳�
void handle_connections() {
    std::vector<std::thread> threads;

    while (true) {
        sockaddr_in client_addr;
        int client_addr_size = sizeof(client_addr);

        // ���ܿͻ�������
        SOCKET client_socket = accept(server_socket, (sockaddr*)&client_addr, &client_addr_size);
        if (client_socket == INVALID_SOCKET) {
            std::cerr << "��������ʧ�ܡ�������: " << WSAGetLastError() << std::endl;
            continue;
        }

        // ��ӡ�ͻ���������Ϣ
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
        {
            std::lock_guard<std::mutex> lock(console_mutex);
            std::cout << "���������� " << client_ip << ":" << ntohs(client_addr.sin_port) << std::endl;
        }

        // �������̴߳���ͻ���
        //��Ϊʵ��ʹ��
        threads.emplace_back(std::thread(recving_lyh::main, client_socket));
       // recving_lyh::main(client_socket);
        // �����̣߳��������������
        //��Ϊʵ��ʹ��
        threads.back().detach();
    }
}

// �����������Դ
void cleanup_server() {
    if (server_socket != INVALID_SOCKET) {
        closesocket(server_socket); // �رշ�����׽���
    }
    WSACleanup(); // ���� Winsock ��Դ
    {
        std::lock_guard<std::mutex> lock(console_mutex);
        std::cout << "��������������Դ���رա�" << std::endl;
    }
}

void simpleface() {
    string a, b, password;
    while (1) {
        cout << "1�½�qq�û� 0�˳�" << endl;
        cin >> a;
        if (a[0] == '1') {
            cout << "��������";
            cin >> b;
            password=bcrypt::generateHash(b);
            cout << endl;
            cout << "�����˺�";
            cin >> b;
            user_lyh* use = new qq_lyh(b, "���û�", to_string(time(0)), "0", "δ֪", password);
            sqq_user_lyh::putin(use);
        }
        else if (a[0] == '0') {
            return;
        }
    }
}

// ������
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
    const char* IP = "0.0.0.0"; // ������������ӿ�
    const int PORT = 8080;      // �����˿�

    // ��ʼ��������
    if (!initialize_server(IP, PORT)) {
        return 1;
    }

    data_lyh data;
    data.start();
    
    // �������Ӳ�����ͻ���

    std::thread handle(handle_connections);  
    handle.detach();
    //handle_connections();
    simpleface();
    cout << "��������뿪" << endl;
    _getch();

    // �����������Դ
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
//		cout << "����socketʧ��  " << GetLastError() << endl;
//		return -1;
//	}
//	sockaddr_in local ;
//	local.sin_family = AF_INET;
//	local.sin_port = htons(8080);
//	local.sin_addr.s_addr =htonl(INADDR_ANY);// INADDR_LOOPBACK
//	if (-1 == bind(listen_socket, (sockaddr*)&local, sizeof(local))) {
//		cout << "bind����  " << GetLastError << endl;
//		return -1;
//	};
//	if (-1 == listen(listen_socket,10)){
//		cout << "listen����ʧ��  " << GetLastError << endl;
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
#include"../ͷ�ļ�/user.h"
#include"../ͷ�ļ�/internet.h"
using namespace std;

// �ͻ��˴�����
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
        cout << "���� socket ʧ�ܣ�������룺" << WSAGetLastError() << endl;
        return -1;
    }

    sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(8080);
    local.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listen_socket, (sockaddr*)&local, sizeof(local)) == SOCKET_ERROR) {
        cout << "��ʧ�ܣ�������룺" << WSAGetLastError() << endl;
        closesocket(listen_socket);
        WSACleanup();
        return -1;
    }

    if (listen(listen_socket, 10) == SOCKET_ERROR) {
        cout << "����ʧ�ܣ�������룺" << WSAGetLastError() << endl;
        closesocket(listen_socket);
        WSACleanup();
        return -1;
    }

    cout << "���������ڼ����˿� 8080" << endl;

    while (true) {
        SOCKET client_socket = accept(listen_socket, nullptr, nullptr);
        if (client_socket == INVALID_SOCKET) {
            cout << "���ܿͻ�������ʧ�ܣ�������룺" << WSAGetLastError() << endl;
            continue;
        }

        // �������̴߳���ͻ�������
        thread clientThread(handleClient, client_socket);
        clientThread.detach(); // �����̣߳��Ա��������
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
//    cout << "����IP��ַ��";
//    string my_IP;
//    cin >> my_IP;
//    if (inet_pton(AF_INET, "my_IP", &(serverAddr.sin_addr)) <= 0)
//    {
//        std::cerr << "��Ч�ķ�������ַ" << std::endl;
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
