#pragma once
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib, "WS2_32.lib")
#define Low 10
#define Middle 25
#define High 40
using namespace std;
namespace Robot_Cmd
{
	void initialization();
	void Connect();
	void Login();
	void PowerOn();
	void Abort();
	void Start();
	void Home();
	void ExpandClose();
	void Expand();
	void Contract();
	void PPB_Enable();
	void PPB_Read(string filename);
	void PPB_Run();
	void PPB_FirstPoint();
	void PowerOff();
	void Manual();
	void Auto();
	void Frame();
	void Speed(int speed);
	void CloseSocket();
}