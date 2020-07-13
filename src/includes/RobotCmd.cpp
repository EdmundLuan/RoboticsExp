#include <conio.h>
#include "RobotCmd.h"
#include "MotionPlan.h"
#include <fstream>
#include <iostream>
#include "Poco/Net/FTPClientSession.h"
#include "Poco/Net/DialogSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/NetException.h"
#include "PointsCoordinates.h"
#include "FtpControl.h"
#pragma comment(lib, "WS2_32.lib")

namespace Robot_Cmd
{

	/*该部分为与机器人之间的通讯，不需要更改*/
	static int i = 0;
    static int dataID = 0;
    static int readDataID = 0;
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


    /**************************** Functions **************************/
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
		sprintf_s(send_buf, 100, "[%d# System.Login 0]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(200);
	}
    //断开连接
    void Logout()
    {
        sprintf_s(send_buf, 100, "[%d# System.Logout]", i++);
        send_len = send(s_server, send_buf, 100, 0);
        recv_len = recv(s_server, recv_buf, 100, 0);
        cout << recv_buf << endl;
        memset(recv_buf, '\0', sizeof(recv_buf));
        Sleep(1000);
    }
	//上电
	void PowerOn()
	{
		sprintf_s(send_buf, 100, "[%d# Robot.PowerEnable 1,1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 200, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(500);
	}
	//停止
	void Abort()
	{
		sprintf_s(send_buf, 100, "[%d# System.Abort 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(200);
	}
	//启动
	void Start()
	{
		sprintf_s(send_buf, 100, "[%d# System.Start 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(200);
	}
    //启动
    void Retry()
    {
        sprintf_s(send_buf, 100, "[%d# System.Retry 1]", i++);
        send_len = send(s_server, send_buf, 100, 0);
        recv_len = recv(s_server, recv_buf, 100, 0);
        cout << recv_buf << endl;
        memset(recv_buf, '\0', sizeof(recv_buf));
        Sleep(200);
    }
	//回零
	void Home()
	{
		sprintf_s(send_buf, 100, "[%d# Robot.Home 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(200);
	}
	//张开爪子 IO关闭
	void ExpandClose()
	{
		sprintf_s(send_buf, 100, "[%d# IO.Set DOUT(20104),0]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
	}
	//放气，张爪
	void Expand()
	{
		//放气 IO.Set DOUT(20104), 1
		sprintf_s(send_buf, 100, "[%d# IO.Set DOUT(20104), 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(200);
	}
	//吸气，收爪
	void Contract()
	{
		sprintf_s(send_buf, 100, "[%d# IO.Set DOUT(20103), 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(300);
	}
	//PPB使能
	void PPB_Enable()
	{
		sprintf_s(send_buf, 100, "[%d# PPB.Enable 1,1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
	}
	//PPB加载文件
    void PPB_ReadData0()
    {
        sprintf_s(send_buf, 100, "[%d# PPB.ReadFile 1,data/serverdata0.txt]", i++);
        send_len = send(s_server, send_buf, 100, 0);
        recv_len = recv(s_server, recv_buf, 100, 0);
        cout << recv_buf << endl;
        memset(recv_buf, '\0', sizeof(recv_buf));
        Sleep(200);
    }
	void PPB_ReadData1()
	{
		sprintf_s(send_buf, 100, "[%d# PPB.ReadFile 1,data/serverdata1.txt]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(200);
	}
    void PPB_ReadData2()
    {
        sprintf_s(send_buf, 100, "[%d# PPB.ReadFile 1,data/serverdata2.txt]", i++);
        send_len = send(s_server, send_buf, 100, 0);
        recv_len = recv(s_server, recv_buf, 100, 0);
        cout << recv_buf << endl;
        memset(recv_buf, '\0', sizeof(recv_buf));
        Sleep(200);
    }
    void PPB_ReadData3()
    {
        sprintf_s(send_buf, 100, "[%d# PPB.ReadFile 1,data/serverdata3.txt]", i++);
        send_len = send(s_server, send_buf, 100, 0);
        recv_len = recv(s_server, recv_buf, 100, 0);
        cout << recv_buf << endl;
        memset(recv_buf, '\0', sizeof(recv_buf));
        Sleep(200);
    }
    void PPB_ReadData4()
    {
        sprintf_s(send_buf, 100, "[%d# PPB.ReadFile 1,data/serverdata4.txt]", i++);
        send_len = send(s_server, send_buf, 100, 0);
        recv_len = recv(s_server, recv_buf, 100, 0);
        cout << recv_buf << endl;
        memset(recv_buf, '\0', sizeof(recv_buf));
        Sleep(200);
    }
	void PPB_ReadData(char* file)
	{
		sprintf_s(send_buf, 100, "[%d# PPB.ReadFile 1,%s]", i++, file);
        printf("Reached PPB_ReadData.\n");
        printf("%s", file);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
        
		Sleep(200);
	}
	//运动到第一个点
	void PPB_FirstPoint()
	{
		sprintf_s(send_buf, 100, "[%d# PPB.J2StartPoint 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(200);
	}
	//执行轨迹规划点位
	void PPB_Run()
	{
		sprintf_s(send_buf, 100, "[%d# PPB.Run 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(200);
	}
	//下电
	void PowerOff()
	{
		sprintf_s(send_buf, 100, "[%d# Robot.PowerEnable 1,0]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(1000);
	}
	//手动模式
	void Manual() 
	{
		sprintf_s(send_buf, 100, "[%d# System.Auto 0]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 200, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(200);
	}
	//自动模式
	void Auto() 
	{
		sprintf_s(send_buf, 100, "[%d# System.Auto 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 200, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(200);
	}
	//轴坐标模式
	void Frame() 
	{
		sprintf_s(send_buf, 100, "[%d# Robot.Frame 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(200);
	}
	//调速
	void Speed(int speed)
	{
		//运动速度25/100
		sprintf_s(send_buf, 100, "[%d# Robot.Speed 1, %d]", i++,speed);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(200);
	}
	//
	void CloseSocket() 
	{
		//关闭套接字
		closesocket(s_server);
		//释放DLL资源
		WSACleanup();
	}

    void Plan(PosStruct P1, PosStruct P2)
    {
        //梯型速度规划
        CHLMotionPlan trajectory1;
        trajectory1.SetProfile(20, 20, 20);    //vel °/s， acc °/s.s, dec °/s.s  设置运动参数
        trajectory1.SetSampleTime(0.001);      //s 设置采样时间
        trajectory1.SetPlanPoints(P1, P2);
        trajectory1.GetPlanPoints(32);
        cout << "Plan in joint space done!" << endl;
        trajectory1.GetPlanPointsCartesian(32);
        cout << "Plan in world space done!" << endl;

    }
    void Plan_NotOverwrite(PosStruct P1, PosStruct P2)
    {
        //梯型速度规划
        CHLMotionPlan trajectory1;
        trajectory1.SetProfile(20, 20, 20);    //vel °/s， acc °/s.s, dec °/s.s  设置运动参数
        trajectory1.SetSampleTime(0.001);      //s 设置采样时间
        trajectory1.SetPlanPoints(P1, P2);
        trajectory1.GetPlanPoints(97);
        cout << "Plan in joint space done!" << endl;
        trajectory1.GetPlanPointsCartesian(97);
        cout << "Plan in world space done!" << endl;
    }

    string getFileName(int id) {
        char shit[10] = { 0 };
        string idStr(itoa(id, shit, 10));
        string filename("data/serverdata" + idStr + ".txt");
        return filename;
    }

	void Calculation(PosStruct st, PosStruct ed, vector<string>& nameList) {
        char file[100];
        string fileName;
		// Calculating Safe Points
		PosStruct stSafe = st;
		PosStruct edSafe = ed;
		stSafe.z += 260;
		edSafe.z += 260;
		//PPB使能 
		PPB_Enable();
		// 轨迹规划
		Plan(stSafe, st);
        fileName = getFileName(dataID);
        cout << fileName << endl;

        nameList.push_back(fileName);
        strcpy(file, fileName.c_str());
        printf("%s\n", file+5);
		FtpControl::Upload("192.168.10.101", "data", "dataPlanInCartesian.txt", file+5);
		cout << "File"<<dataID++<<" has been sent to server..." << endl;
        

		/*suck*/

		Plan(st, stSafe);
        fileName = getFileName(dataID);
        nameList.push_back(fileName);
        strcpy(file, fileName.c_str());
        FtpControl::Upload("192.168.10.101", "data", "dataPlanInCartesian.txt", file+5);
        cout << "File" << dataID++ << " has been sent to server..." << endl;

		Plan(edSafe, ed);
        fileName = getFileName(dataID);
        nameList.push_back(fileName);
        strcpy(file, fileName.c_str());
        FtpControl::Upload("192.168.10.101", "data", "dataPlanInCartesian.txt", file+5);
        cout << "File" << dataID++ << " has been sent to server..." << endl;

		/* expand */
		Plan(ed, edSafe);
        fileName = getFileName(dataID);
        nameList.push_back(fileName);
        strcpy(file, fileName.c_str());
        FtpControl::Upload("192.168.10.101", "data", "dataPlanInCartesian.txt", file+5);
        cout << "File" << dataID++ << " has been sent to server..." << endl;

		cout << "Planning and Upload Completed!" << endl;
		/* Planning and Upload Completed ! */
	}
	void Palletize(PosStruct st, PosStruct ed, vector<string>& nameList) {
		/*******************************************************************************/
		//第0段：大区安全点到取料点
        char file[100];
        strcpy(file, nameList.at(readDataID++).c_str());
		PPB_ReadData(file);
		Speed(50);
		cout << "\nBe ready to hit the EMERGENCY STOP !\n" << endl;
		//cout << "Press Enter to continue..." << endl;
		//cin.get();
		//到安全点 
		PPB_FirstPoint();
		Sleep(200);
		// 下去取料
		PPB_Run();
		Sleep(200);
		cout << "Moving to Picking Point..." << endl;

		/*吸气, 抓取*/
		ExpandClose();
		Contract();
		cout << "Picking..." << endl;

		//第1段：回取料安全点
        strcpy(file, nameList.at(readDataID++).c_str());
        PPB_ReadData(file);
		PPB_FirstPoint();
		Sleep(200);
		PPB_Run();
		cout << "Moving back to Pick Point and ready to move away..." << endl;
		Sleep(300);

		//第3段：放料安全点到放料点
        strcpy(file, nameList.at(readDataID++).c_str());
        PPB_ReadData(file);
		PPB_FirstPoint();
		Sleep(200);
		PPB_Run();
		cout << "Moving to Stashing Point..." << endl;
		Sleep(200);

		/*码垛*/
		ExpandClose();
		Expand();
		cout << "Unloading..." << endl;


		//第4段: 回取料安全点待命
        strcpy(file, nameList.at(readDataID++).c_str());
        PPB_ReadData(file);
		PPB_FirstPoint();
		Sleep(200);
		PPB_Run();
		cout << "Moving bakc to Safe Point..." << endl;
		Sleep(400);
		/*********************************************************************************/
	}
}
