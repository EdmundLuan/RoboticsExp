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

	/*�ò���Ϊ�������֮���ͨѶ������Ҫ����*/
	static int i = 0;
    static int dataID = 0;
    static int readDataID = 0;
	//���峤�ȱ���
	int send_len = 0;
	int recv_len = 0;
	//���巢�ͻ������ͽ��ܻ�����
	char send_buf[100] = {};
	char recv_buf[200] = {};
	string recvstr;
	//���������׽��֣����������׽���
	 static SOCKET s_server;
	//����˵�ַ�ͻ��˵�ַ
	static SOCKADDR_IN server_addr;


    /**************************** Functions **************************/
	//��ʼ��
	void initialization()
	{
		//��ʼ���׽��ֿ�
		WORD w_req = MAKEWORD(2, 2);//�汾��
		WSADATA wsadata;
		int err;
		err = WSAStartup(w_req, &wsadata);
		if (err != 0) {
			cout << "��ʼ���׽��ֿ�ʧ�ܣ�" << endl;
		}
		else {
			cout << "��ʼ���׽��ֿ�ɹ���" << endl;
		}
		//���汾��
		if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
			cout << "�׽��ֿ�汾�Ų�����" << endl;
			WSACleanup();
		}
		else {
			cout << "�׽��ֿ�汾��ȷ��" << endl;
		}
		//������˵�ַ��Ϣ
	}
	//����
	void Connect()
	{
		//���������Ϣ
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.S_un.S_addr = inet_addr("192.168.10.120");
		server_addr.sin_port = htons(2090);
		//�����׽���
		s_server = socket(AF_INET, SOCK_STREAM, 0);
		if (connect(s_server, (SOCKADDR *)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
			cout << "����������ʧ�ܣ�" << endl;
			WSACleanup();
		}
		else {
			cout << "���������ӳɹ���" << endl;
		}
	}
	//��¼
	void Login()
	{
		sprintf_s(send_buf, 100, "[%d# System.Login 0]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(200);
	}
    //�Ͽ�����
    void Logout()
    {
        sprintf_s(send_buf, 100, "[%d# System.Logout]", i++);
        send_len = send(s_server, send_buf, 100, 0);
        recv_len = recv(s_server, recv_buf, 100, 0);
        cout << recv_buf << endl;
        memset(recv_buf, '\0', sizeof(recv_buf));
        Sleep(1000);
    }
	//�ϵ�
	void PowerOn()
	{
		sprintf_s(send_buf, 100, "[%d# Robot.PowerEnable 1,1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 200, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(500);
	}
	//ֹͣ
	void Abort()
	{
		sprintf_s(send_buf, 100, "[%d# System.Abort 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(200);
	}
	//����
	void Start()
	{
		sprintf_s(send_buf, 100, "[%d# System.Start 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(200);
	}
    //����
    void Retry()
    {
        sprintf_s(send_buf, 100, "[%d# System.Retry 1]", i++);
        send_len = send(s_server, send_buf, 100, 0);
        recv_len = recv(s_server, recv_buf, 100, 0);
        cout << recv_buf << endl;
        memset(recv_buf, '\0', sizeof(recv_buf));
        Sleep(200);
    }
	//����
	void Home()
	{
		sprintf_s(send_buf, 100, "[%d# Robot.Home 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(200);
	}
	//�ſ�צ�� IO�ر�
	void ExpandClose()
	{
		sprintf_s(send_buf, 100, "[%d# IO.Set DOUT(20104),0]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
	}
	//��������צ
	void Expand()
	{
		//���� IO.Set DOUT(20104), 1
		sprintf_s(send_buf, 100, "[%d# IO.Set DOUT(20104), 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(200);
	}
	//��������צ
	void Contract()
	{
		sprintf_s(send_buf, 100, "[%d# IO.Set DOUT(20103), 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(300);
	}
	//PPBʹ��
	void PPB_Enable()
	{
		sprintf_s(send_buf, 100, "[%d# PPB.Enable 1,1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
	}
	//PPB�����ļ�
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
	//�˶�����һ����
	void PPB_FirstPoint()
	{
		sprintf_s(send_buf, 100, "[%d# PPB.J2StartPoint 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(200);
	}
	//ִ�й켣�滮��λ
	void PPB_Run()
	{
		sprintf_s(send_buf, 100, "[%d# PPB.Run 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(200);
	}
	//�µ�
	void PowerOff()
	{
		sprintf_s(send_buf, 100, "[%d# Robot.PowerEnable 1,0]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(1000);
	}
	//�ֶ�ģʽ
	void Manual() 
	{
		sprintf_s(send_buf, 100, "[%d# System.Auto 0]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 200, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(200);
	}
	//�Զ�ģʽ
	void Auto() 
	{
		sprintf_s(send_buf, 100, "[%d# System.Auto 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 200, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(200);
	}
	//������ģʽ
	void Frame() 
	{
		sprintf_s(send_buf, 100, "[%d# Robot.Frame 1]", i++);
		send_len = send(s_server, send_buf, 100, 0);
		recv_len = recv(s_server, recv_buf, 100, 0);
		cout << recv_buf << endl;
		memset(recv_buf, '\0', sizeof(recv_buf));
		Sleep(200);
	}
	//����
	void Speed(int speed)
	{
		//�˶��ٶ�25/100
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
		//�ر��׽���
		closesocket(s_server);
		//�ͷ�DLL��Դ
		WSACleanup();
	}

    void Plan(PosStruct P1, PosStruct P2)
    {
        //�����ٶȹ滮
        CHLMotionPlan trajectory1;
        trajectory1.SetProfile(20, 20, 20);    //vel ��/s�� acc ��/s.s, dec ��/s.s  �����˶�����
        trajectory1.SetSampleTime(0.001);      //s ���ò���ʱ��
        trajectory1.SetPlanPoints(P1, P2);
        trajectory1.GetPlanPoints(32);
        cout << "Plan in joint space done!" << endl;
        trajectory1.GetPlanPointsCartesian(32);
        cout << "Plan in world space done!" << endl;

    }
    void Plan_NotOverwrite(PosStruct P1, PosStruct P2)
    {
        //�����ٶȹ滮
        CHLMotionPlan trajectory1;
        trajectory1.SetProfile(20, 20, 20);    //vel ��/s�� acc ��/s.s, dec ��/s.s  �����˶�����
        trajectory1.SetSampleTime(0.001);      //s ���ò���ʱ��
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
		//PPBʹ�� 
		PPB_Enable();
		// �켣�滮
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
		//��0�Σ�������ȫ�㵽ȡ�ϵ�
        char file[100];
        strcpy(file, nameList.at(readDataID++).c_str());
		PPB_ReadData(file);
		Speed(50);
		cout << "\nBe ready to hit the EMERGENCY STOP !\n" << endl;
		//cout << "Press Enter to continue..." << endl;
		//cin.get();
		//����ȫ�� 
		PPB_FirstPoint();
		Sleep(200);
		// ��ȥȡ��
		PPB_Run();
		Sleep(200);
		cout << "Moving to Picking Point..." << endl;

		/*����, ץȡ*/
		ExpandClose();
		Contract();
		cout << "Picking..." << endl;

		//��1�Σ���ȡ�ϰ�ȫ��
        strcpy(file, nameList.at(readDataID++).c_str());
        PPB_ReadData(file);
		PPB_FirstPoint();
		Sleep(200);
		PPB_Run();
		cout << "Moving back to Pick Point and ready to move away..." << endl;
		Sleep(300);

		//��3�Σ����ϰ�ȫ�㵽���ϵ�
        strcpy(file, nameList.at(readDataID++).c_str());
        PPB_ReadData(file);
		PPB_FirstPoint();
		Sleep(200);
		PPB_Run();
		cout << "Moving to Stashing Point..." << endl;
		Sleep(200);

		/*���*/
		ExpandClose();
		Expand();
		cout << "Unloading..." << endl;


		//��4��: ��ȡ�ϰ�ȫ�����
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
