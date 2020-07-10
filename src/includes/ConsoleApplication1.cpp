// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。

#include "HLrobotconfig.h"
#include "MotionPlan.h"
#include "RobotCmd.h"
#include <vector>
#include<iostream>
#include<fstream>
#include<winsock.h>
#include <conio.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
using namespace Robot_Cmd;
#include "FtpControl.h"
#pragma comment(lib, "WS2_32.lib")

int main()
{

	initialization();
	Connect();
	Login();
	Manual();
	Auto();
	Start();
	PowerOn();
	Frame();
	Home();
	Expand();

	/***********************
	*
	*点位规划，生成data文件
	*
	************************/

	// 起始点
	PosStruct point1, point2;
	point1 = { 448.019,-282.355,614.999,0,180,-135 };  //P1Safe
	point2 = { 483.707,150.235,615.0, -90.0,180.0,45.0 }; //PBSafe

	//梯型速度规划
	CHLMotionPlan trajectory1;
	trajectory1.SetProfile(20, 20, 20);    //vel °/s， acc °/s.s, dec °/s.s  设置运动参数
	trajectory1.SetSampleTime(0.001);      //s 设置采样时间
	trajectory1.SetPlanPoints(point1, point2);
	trajectory1.GetPlanPoints(32);
	cout << "Plan in joint space done!" << endl;
	trajectory1.GetPlanPointsCartesian(32);
	cout << "Plan in world space done!" << endl;
	cout << "Point1  ------------------>    Point2    Done." << endl;
	cout << "Press Enter to continue...\n" << endl;
	cin.get();

	/********************************************************/


	PPB_Enable();

	FtpControl::Upload("192.168.10.101", "data", "dataPlanInJointSpace.txt", "serverdata.txt");
	cout << "File1 has been sent to server..." << endl;
	char file1[100] = "serverdata.txt";
	PPB_Read(file1);
	Speed(25);
	PPB_FirstPoint();
	ExpandClose();
	Contract();
	PPB_Run();
	ExpandClose();
	Expand();

	//第二段点位文件
	FtpControl::Upload("192.168.10.101", "data", "data2.txt", "serverdata2.txt");
	cout << "File2 has been sent to server..." << endl;

	char file2[100] = "serverdata2.txt";
	PPB_Read(file2);
	PPB_FirstPoint();
	PPB_Run();
	PowerOff();
	//关闭套接字
	CloseSocket();
	return 0;
}


