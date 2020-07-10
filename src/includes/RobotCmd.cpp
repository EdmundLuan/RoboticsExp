#include <conio.h>
#include "RobotCmd.h"

#include <fstream>
#include <iostream>
#include "Poco/Net/FTPClientSession.h"
#include "Poco/Net/DialogSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/NetException.h"

namespace Robot_Cmd
{
	/***********************
	*
	*该部分为与机器人之间的通讯，不需要更改
	*
	************************/
	int i = 0;
	//定义长度变量
	int send_len = 0;
	int recv_len = 0;
	//定义发送缓冲区和接受缓冲区
	char send_buf[100] = {};
	char recv_buf[200] = {};
	string recvstr;
	//定义服务端套接字，接受请求套接字
	 static SOCKET s_server;
	//服务端地址客户端地址
	static SOCKADDR_IN server_addr;
	//初始化
	void initialization()
	{
		//初始化套接字库
		WORD w_req = MAKEWORD(2, 2);//版本号
		WSADATA wsadata;
		int err;
		err = WSAStartup(w_req, &wsadata);
		if (err != 0) {
			cout << "初始化套接字库失败！" << endl;
		}
		else {
			cout << "初始化套接字库成功！" << endl;
		}
		//检测版本号
		if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
			cout << "套接字库版本号不符！" << endl;
			WSACleanup();
		}
		else {
			cout << "套接字库版本正确！" << endl;
		}
		//填充服务端地址信息
	}
	//连接
	void Connect()
	{
		//填充服务端信息
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.S_un.S_addr = inet_addr("192.168.10.120");
		server_addr.sin_port = htons(2090);
		//创建套接字
		s_server = socket(AF_INET, SOCK_STREAM, 0);
		if (connect(s_server, (SOCKADDR *)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
			cout << "服务器连接失败！" << endl;
			WSACleanup();
		}
		else {
			cout << "服务器连接成功！" << endl;
		}
	}
	//登录
	void Login()
	{
		sprintf_s(send_buf, 100, "[d%# System.Login 0]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(1200);
	}
	//上电
	void PowerOn()
	{
		sprintf_s(send_buf, 100, "[d%# Robot.PowerEnable 1,1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 200, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(1200);
	}
	//停止
	void Abort()
	{
		sprintf_s(send_buf, 100, "[d%# System.Abort 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(1200);
	}
	//启动
	void Start()
	{
		sprintf_s(send_buf, 100, "[d%# System.Start 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(1200);
	}
	//回零
	void Home()
	{
		sprintf_s(send_buf, 100, "[d%# Robot.Home 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(1200);
	}
	//张开爪子 IO关闭
	void ExpandClose()
	{
		sprintf_s(send_buf, 100, "[d%# IO.Set DOUT(20104),0]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
	}
	//放气，张爪
	void Expand()
	{
		//放气 IO.Set DOUT(20104), 1
		sprintf_s(send_buf, 100, "[d%# IO.Set DOUT(20104), 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(1000);
	}
	//吸气，收爪
	void Contract()
	{
		sprintf_s(send_buf, 100, "[d%# IO.Set DOUT(20103), 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(1000);
	}
	//PPB使能
	void PPB_Enable()
	{
		sprintf_s(send_buf, 100, "[d%# PPB.Enable 1,1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
	}
	//PPB加载文件
	void PPB_Read(string filename)
	{
		sprintf_s(send_buf, 100, "[d%# PPB.ReadFile 1,%s]", i++,filename);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(1200);
	}
	//运动到第一个点
	void PPB_FirstPoint()
	{
		sprintf_s(send_buf, 100, "[d%# PPB.J2StartPoint 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(1200);
	}
	//执行轨迹规划点位
	void PPB_Run()
	{
		sprintf_s(send_buf, 100, "[d%# PPB.Run 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(1200);
	}
	//下电
	void PowerOff()
	{
		sprintf_s(send_buf, 100, "[d%# Robot.PowerEnable 1,0]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(1200);
	}
	//手动模式
	void Manual() 
	{
		sprintf_s(send_buf, 100, "[d%# System.Auto 0]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 200, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(200);
	}
	//自动模式
	void Auto() 
	{
		sprintf_s(send_buf, 100, "[d%# System.Auto 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 200, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(1200);
	}
	//轴坐标模式
	void Frame() 
	{
		sprintf_s(send_buf, 100, "[d%# Robot.Frame 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(1200);
	}
	//调速
	void Speed(int speed)
	{
		//运动速度25/100
		sprintf_s(send_buf, 100, "[d%# Robot.Speed 1, %d]", i++,speed);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(1200);
		cout << "\nBe ready to hit the EMERGENCY STOP !" << endl;
		cout << "Press Enter to continue..." << endl;
		cin.get();
	}
	//
	void CloseSocket() 
	{
		//关闭套接字
		closesocket(s_server);
		//释放DLL资源
		WSACleanup();
	}
}