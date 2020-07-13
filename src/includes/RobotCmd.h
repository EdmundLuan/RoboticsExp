#pragma once
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib, "WS2_32.lib")
#include <string>
#include "MotionPlan.h"
#include "HLrobotconfig.h"
using namespace std;
namespace Robot_Cmd
{
	void initialization();
	void Connect();
	void Login();
    void Logout();
	void PowerOn();
	void Abort();
    void Retry();
	void Start();
	void Home();
	void ExpandClose();
	void Expand();
	void Contract();
	void PPB_Enable();
	void PPB_ReadData1();
    void PPB_ReadData2();
    void PPB_ReadData3();
    void PPB_ReadData4();
    void PPB_ReadData0();
	void PPB_ReadData(char* file);
	void PPB_Run();
	void PPB_FirstPoint();
	void PowerOff();
	void Manual();
	void Auto();
	void Frame();
	void Speed(int speed);
	void CloseSocket();
    void Plan(PosStruct P1, PosStruct P2);
    void Plan_NotOverwrite(PosStruct P1, PosStruct P2);
	void Calculation1(PosStruct p1, PosStruct p2);
    void Palletize1(PosStruct p1, PosStruct p2);
    void Calculation(PosStruct p1, PosStruct p2, vector<string> &nameList);
    string getFileName(int id);
    void Palletize(PosStruct p1, PosStruct p2, vector<string> &nameList);
}