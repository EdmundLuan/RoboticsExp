
#include "stdafx.h"
#include "Robot.h"
#include "QKMLink\qkmlinklib_i.c"
#include

using namespace std;

#define ROBOT_RECV_TIME_OUT     (500)

#pragma region 构造/析构接口

Robot::Robot()
{
	//启动QKMLink
	// 4.在GUI启动时，创建对象:
	// (1)CoInitialize是必须调用的API，作用是初始化整个程序的COM环境
	// (2)CoUninitialize()是必须调用的API，与CoInitialize配对使用，作用是卸
	// 载整个程序的COM环境，在关闭GUI的时候调用，注意：若在其他地方调用，将
	// 导致COM组件不能使用，因此QKMLink库将失效！！！
	// 
	HRESULT hr = E_FAIL;
	hr = CoInitialize(NULL);
	if (SUCCEEDED(hr))
	{
		m_IsInit = true;

		// CoCreateInstance用于创建QKMLink接口，在条目2中声明的接口都需要使用
		// 此API创建才能使用。
		hr = CoCreateInstance(CLSID_QKMLink, NULL, CLSCTX_INPROC_SERVER, IID_IQKMLink, (void**)&g_IQKMLink);
		if (FAILED(hr))
		{
		
			m_IsInit = false;
		}
		hr = CoCreateInstance(CLSID_QKMLinkConfig, NULL, CLSCTX_INPROC_SERVER, IID_IQKMLinkConfig, (void**)&g_IQKMLinkConfig);
		if (FAILED(hr))
		{
		
			m_IsInit = false;
		}
		hr = CoCreateInstance(CLSID_QKMLinkClient, NULL, CLSCTX_INPROC_SERVER, IID_IQKMLinkClient, (void**)&g_IQKMLinkClient);
		if (FAILED(hr))
		{
			
			m_IsInit = false;
		}
	}

}

Robot::~Robot()
{
	g_IQKMLinkClient->Close();
}

#pragma endregion

#pragma region 其他


void Robot::AnalysisCmd(CString src, CString & dst) const
{
	src.Remove('[');
	src.Remove(']');
	dst = src;
}

vector<CString> Robot::SplitCString(CString strSource, CString ch) const
{
	vector <CString> vecString;

	int iPos = 0;

	CString strTmp;

	strTmp = strSource.Tokenize(ch, iPos);

	while (strTmp.Trim() != _T(""))

	{
		vecString.push_back(strTmp);

		strTmp = strSource.Tokenize(ch, iPos);

	}

	return vecString;
}

#pragma endregion




#pragma region 通信控制

bool Robot::Connect(CString ip, unsigned short port, CString id)
{
	if (m_IsInit)
	{

		//获取连接状态
		long linkStatus = -1;
		g_IQKMLinkClient->CurrentState(&linkStatus);

		if (linkStatus == -1)
		{
			//启动服务器连接

			// 1.配置客户端
			DWORD dwThreadID;
			HANDLE hClientRecieve;
			long lResult;
			BSTR bsServerAddr = ::SysAllocString(ip);
			BSTR bsSourceID = ::SysAllocString(id);

			// （1）设置需要连接的服务器IP地址
			g_IQKMLinkClient->put_ServerAddress(bsServerAddr);
			// （2）设置需要连接的服务器IP端口
			g_IQKMLinkClient->put_ServerPort(port);
			// （3）设置本客户端的ID号
			g_IQKMLinkClient->put_SourceID(bsSourceID);
			// （4）设置接收模式：0，使用线程接收；1，使用事件回调接收
			g_IQKMLinkClient->put_NoticeMode(0);
			// （5）是否使用debug模式
			g_IQKMLinkClient->put_DebugMode(VARIANT_FALSE);
			// （6）连接服务器
			g_IQKMLinkClient->Connect(&lResult);
			if (lResult < 0)
			{
				IsConnected = false;
				return false;
			}

			// 2.创建客户端接收线程，并释放线程句柄
			hClientRecieve = CreateThread(NULL, 0, ClientRecieveData, PVOID(this), 0, &dwThreadID);
			CloseHandle(hClientRecieve);

			// 3.释放BSTR资源
			::SysFreeString(bsServerAddr);
			::SysFreeString(bsSourceID);
			IsConnected = true;

			return true;
		}
	}

	return false;
}

void Robot::Disconnect()
{
	IsConnected = false;
	g_IQKMLinkClient->Close();
}

bool Robot::Send(CString sendData)
{
	std::unique_lock<std::mutex> lock(ComLock);

	try
	{

		if (IsConnected)
		{
			bool result = false;

			BSTR bsSend = NULL, bsCommand = NULL, bsState = NULL, bsSourceID = NULL, bsDestinationID = NULL;
			long lPacketID, lSequenceNum, lTimeOut, lCode;

			//指令封装
			CString cmd = L"[" + sendData + L"]";
			bsSend = cmd.AllocSysString();	// 指令内容

			SendMessageProcess(cmd);

			//发送数据
			IQKMLinkResult* pIResultClientSend = nullptr;
			g_IQKMLinkClient->Send(bsSend, L"ACKOFF", 10, &pIResultClientSend);

			if (pIResultClientSend != nullptr)
			{
				pIResultClientSend->get_Command(&bsCommand);
				pIResultClientSend->get_SourceID(&bsSourceID);
				pIResultClientSend->get_DestinationID(&bsDestinationID);
				pIResultClientSend->get_PacketID(&lPacketID);
				pIResultClientSend->get_SequenceNum(&lSequenceNum);
				pIResultClientSend->get_Timeout(&lTimeOut);
				pIResultClientSend->get_State(&bsState);
				pIResultClientSend->get_Code(&lCode);
				//sResult.Format(_T("Client feedback result %s %s %s %d %d %d %s %d"), bsCommand, bsSourceID, bsDestinationID, lPacketID, lSequenceNum, lTimeOut, bsState, lCode);
				result = true;
			}

			// 4.释放BSTR资源
			::SysFreeString(bsSend);
			::SysFreeString(bsCommand);
			::SysFreeString(bsSourceID);
			::SysFreeString(bsDestinationID);
			::SysFreeString(bsState);

			// 5.释放QKMLinkResult
			if (pIResultClientSend != nullptr)
			{
				pIResultClientSend->Release();
			}

			return result;
		}
	}
	catch (const std::exception&)
	{

	}

	return false;
}

//客户端接收线程。
static DWORD WINAPI ClientRecieveData(PVOID lParam)
{
	Robot *dlgLinkTest = (Robot*)lParam;

	//std::unique_lock<std::mutex> lock(dlgLinkTest->ComLock);

	// 1.配置COM环境，在线程中使用QKMLink需要使用CoInitialize，线程退出时调用
	// CoUninitialize()释放COM环境
	HRESULT hr = E_FAIL;
	hr = CoInitialize(NULL);	//工作线程使用COM，必须调用此函数初始化COM库
	if (SUCCEEDED(hr))
	{
		while (true)
		{
			// 2.接收从机器人端发送过来的信息，包括反馈的信息和主动的信息
			BSTR bsMessage = NULL, bsCommand = NULL;
			CString sMessage, sTemp;
			long lErrorCode;
			IQKMLinkResult* pIResultClientRcv = NULL;
			HRESULT hr = NULL;
			hr = dlgLinkTest->g_IQKMLinkClient->Receive(&bsMessage, &pIResultClientRcv, &lErrorCode);
			sMessage = bsMessage;

			// 处理error code = 0的情况，其他情况不需要处理
			if (lErrorCode == 0)
			{
				if (hr == S_OK && pIResultClientRcv != NULL)
				{
					// 3.获取Result接口的属性，并显示
					CString sShowResult;
					long lPacketID, lSequenceNum, lResultCode;
					pIResultClientRcv->get_Code(&lResultCode);
					pIResultClientRcv->get_Command(&bsCommand);
					pIResultClientRcv->get_PacketID(&lPacketID);
					pIResultClientRcv->get_SequenceNum(&lSequenceNum);
					sShowResult.Format(_T("thread: %s,%s,%d,%d\r\n"), sMessage, bsCommand, lPacketID, lSequenceNum);

					//数据解析
					if (lResultCode == 0)
					{
						dlgLinkTest->RecvMessageProcess(sMessage);

						dlgLinkTest->RecvLock.lock();
						dlgLinkTest->Message = sMessage;
						dlgLinkTest->RecvStatus = 1;
						dlgLinkTest->RecvLock.unlock();
					}
					else
					{
						dlgLinkTest->RecvLock.lock();
						dlgLinkTest->Message = sMessage;
						dlgLinkTest->RecvStatus = 2;
						dlgLinkTest->RecvLock.unlock();
					}

					// 4.释放信息包
					hr = dlgLinkTest->g_IQKMLinkClient->Stop(pIResultClientRcv, &lErrorCode);
					if (hr != S_OK && lErrorCode != 0)
					{
						MessageBox(NULL, _T("Client stop result fail!"), _T("Warn"), MB_OK);
					}
				}
			}

			// 5.释放BSTR资源
			::SysFreeString(bsMessage);
			::SysFreeString(bsCommand);

			// 6.释放QKMLinkResult
			pIResultClientRcv->Release();
		}

		// 7.线程退出时，释放线程的COM环境
		CoUninitialize();
	}
	return 0;
}

#pragma endregion

#pragma region 系统控制

bool Robot::Login()
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		CString sendData;
		sendData.Format(_T("System.Login 0"));

		//发送数据
		bool result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				RecvLock.unlock();
				return true;
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}
	return false;
}

bool Robot::Logout()
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		CString sendData;
		sendData.Format(_T("System.Logout"));

		//发送数据
		bool result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				RecvLock.unlock();
				return true;
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}
	return false;
}

bool Robot::Auto(bool isAuto)
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		CString sendData;
		sendData.Format(_T("System.Auto %d"), isAuto);

		//发送数据
		bool result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				RecvLock.unlock();
				return true;
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}
	return false;
}

bool Robot::Start()
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		CString sendData;
		sendData.Format(_T("System.Start"));

		//发送数据
		bool result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				RecvLock.unlock();
				return true;
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}
	return false;
}

bool Robot::Retry()
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		CString sendData;
		sendData.Format(_T("System.Retry %d"), RobotIndex);

		//发送数据
		bool result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				RecvLock.unlock();
				return true;
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}
	return false;
}

#pragma endregion

#pragma region 机器人控制

bool Robot::PowerOn()
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		CString sendData = L"Robot.PowerEnable 1,1";

		//发送数据
		bool result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				CString cmd;
				AnalysisCmd(Message, cmd);
				vector<CString> cmdString = SplitCString(cmd, L" ");
				RecvLock.unlock();
				return cmdString[0] == L"0";
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}
	return false;
}

bool Robot::PowerOff()
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		CString sendData = L"Robot.PowerEnable 1,0";

		//发送数据
		bool result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				CString cmd;
				AnalysisCmd(Message, cmd);
				vector<CString> cmdString = SplitCString(cmd, L" ");
				RecvLock.unlock();
				return cmdString[0] == L"0";
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}
	return false;
}

bool Robot::Home()
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		CString sendData;
		sendData.Format(_T("Robot.Home %d"), RobotIndex);

		//发送数据
		bool result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				CString cmd;
				AnalysisCmd(Message, cmd);
				vector<CString> cmdString = SplitCString(cmd, L" ");
				RecvLock.unlock();
				return cmdString[0] == L"0";
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}
	return false;
}

bool Robot::Here(double & x, double & y, double & z, double & roll)
{
	double yaw, pitch;

	return Here(x, y, z, yaw, pitch, roll);
}

bool Robot::Here(double & x, double & y, double & z, double & yaw, double & pitch, double & roll)
{
	int config;
	return Here(x, y, z, yaw, pitch, roll, config);
}

bool Robot::Here(double & x, double & y, double & z, double & yaw, double & pitch, double & roll, int & config)
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		bool result = false;
		CString sendData;
		sendData.Format(_T("Robot.Where %d"), RobotIndex);

		//发送数据
		result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				CString cmd;
				AnalysisCmd(Message, cmd);

				//cmd: 0 xxx,xxx,xxx,xxx...
				vector<CString> cmdString = SplitCString(cmd, L" ");
				if (cmdString.size() >= 2)
				{
					if (cmdString[0] == L"0")
					{
						vector<CString> pointString = SplitCString(cmdString[1], L",");

						if (pointString.size() >= 6)
						{
							x = _ttof(pointString[0]);
							y = _ttof(pointString[1]);
							z = _ttof(pointString[2]);
							yaw = _ttof(pointString[3]);
							pitch = _ttof(pointString[4]);
							roll = _ttof(pointString[5]);
							config = _ttoi(pointString[6]);

							RecvLock.unlock();
							return true;
						}
					}
				}
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}

	return false;
}

bool Robot::Joint(double & j1, double & j2, double & j3, double & j4)
{
	double j5, j6;

	return Joint(j1, j2, j3, j4, j5, j6);
}

bool Robot::Joint(double & j1, double & j2, double & j3, double & j4, double & j5, double & j6)
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		bool result = false;
		CString sendData;
		sendData.Format(_T("Robot.WhereAngle %d"), RobotIndex);

		//发送数据
		result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				CString cmd;
				AnalysisCmd(Message, cmd);

				//cmd: 0 xxx,xxx,xxx,xxx...
				vector<CString> cmdString = SplitCString(cmd, L" ");
				if (cmdString.size() >= 2)
				{
					if (cmdString[0] == L"0")
					{
						vector<CString> pointString = SplitCString(cmdString[1], L",");

						if (pointString.size() >= 6)
						{
							j1 = _ttof(pointString[0]);
							j2 = _ttof(pointString[1]);
							j3 = _ttof(pointString[2]);
							j4 = _ttof(pointString[3]);
							j5 = _ttof(pointString[4]);
							j6 = _ttof(pointString[5]);

							RecvLock.unlock();
							return true;
						}
						else if (pointString.size() >= 4)
						{
							j1 = _ttof(pointString[0]);
							j2 = _ttof(pointString[1]);
							j3 = _ttof(pointString[2]);
							j4 = _ttof(pointString[3]);
							j5 = -1;
							j6 = -1;

							RecvLock.unlock();
							return true;
						}
					}
				}

			}
			RecvLock.unlock();

			Sleep(1);
		}
	}

	return false;
}

bool Robot::Brake()
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		CString sendData;
		sendData.Format(_T("Robot.Brake %d,ALL,0"), RobotIndex);

		//发送数据
		bool result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				CString cmd;
				AnalysisCmd(Message, cmd);
				vector<CString> cmdString = SplitCString(cmd, L" ");
				RecvLock.unlock();
				return cmdString[0] == L"0";
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}
	return false;
}

bool Robot::LooseBrake()
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		CString sendData;
		sendData.Format(_T("Robot.Brake %d,ALL,1"), RobotIndex);

		//发送数据
		bool result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				CString cmd;
				AnalysisCmd(Message, cmd);
				vector<CString> cmdString = SplitCString(cmd, L" ");
				RecvLock.unlock();
				return cmdString[0] == L"0";
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}
	return false;
}

bool Robot::GetState(int &powerState, int &homeState, int &runState)
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		CString sendData;
		sendData.Format(_T("Robot.State %d"), RobotIndex);

		//发送数据
		bool result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				CString cmd;
				AnalysisCmd(Message, cmd);
				vector<CString> cmdString = SplitCString(cmd, L" ");

				if ((cmdString.size() == 2) && (cmdString[0] == L"0"))
				{
					vector<CString> status = SplitCString(cmdString[1], L",");
					if (status.size() == 3)
					{
						powerState = _ttoi(status[0]);
						homeState = _ttoi(status[1]);
						runState = _ttoi(status[2]);

						RecvLock.unlock();
						return true;
					}
				}


				RecvLock.unlock();
				return false;
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}
	return false;
}

bool Robot::SetJogMode(bool jogMode, bool jogSwitch)
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		CString sendData;
		sendData.Format(_T("Robot.JogMode %d,%d,%d"), RobotIndex, jogMode, jogSwitch);

		//发送数据
		bool result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				CString cmd;
				AnalysisCmd(Message, cmd);
				vector<CString> cmdString = SplitCString(cmd, L" ");
				RecvLock.unlock();
				return cmdString[0] == L"0";
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}
	return false;
}

bool Robot::SetJogDistance(double distance)
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		CString sendData;
		sendData.Format(_T("Robot.JogDistance %d,%f"), RobotIndex, distance);

		//发送数据
		bool result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				CString cmd;
				AnalysisCmd(Message, cmd);
				vector<CString> cmdString = SplitCString(cmd, L" ");
				RecvLock.unlock();
				return cmdString[0] == L"0";
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}
	return false;
}

bool Robot::Jog(CString axisName, double jogSpeed)
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		CString sendData;
		sendData.Format(_T("Move.Jog %s,%f"), axisName, jogSpeed);

		//发送数据
		bool result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				CString cmd;
				AnalysisCmd(Message, cmd);
				vector<CString> cmdString = SplitCString(cmd, L" ");
				RecvLock.unlock();
				return cmdString[0] == L"0";
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}
	return false;
}

bool Robot::StopJog()
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		CString sendData;
		sendData.Format(_T("Move.StopJog %d"), RobotIndex);

		//发送数据
		bool result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				CString cmd;
				AnalysisCmd(Message, cmd);
				vector<CString> cmdString = SplitCString(cmd, L" ");
				RecvLock.unlock();
				return cmdString[0] == L"0";
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}
	return false;
}

//设置坐标系
//1: 关节坐标
//2: 世界坐标
//3: 工具坐标
//4: 工件坐标
bool Robot::SetFrmae(int mode)
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		CString sendData;
		sendData.Format(_T("Robot.Frame %d,%d"), RobotIndex, mode);

		//发送数据
		bool result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				CString cmd;
				AnalysisCmd(Message, cmd);
				vector<CString> cmdString = SplitCString(cmd, L" ");
				RecvLock.unlock();
				return cmdString[0] == L"0";
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}
	return false;
}

#pragma endregion

#pragma region PPB控制

bool Robot::EnablePPB(bool isEnable)
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		CString sendData;
		sendData.Format(_T("PPB.Enable %d,%d"), RobotIndex, isEnable);

		//发送数据
		bool result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				CString cmd;
				AnalysisCmd(Message, cmd);
				vector<CString> cmdString = SplitCString(cmd, L" ");
				RecvLock.unlock();
				return cmdString[0] == L"0";
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}
	return false;
}

bool Robot::ReadFilePPB(CString file)
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		CString sendData;
		sendData.Format(_T("PPB.ReadFile %d,%s"), RobotIndex, file);

		//发送数据
		bool result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				CString cmd;
				AnalysisCmd(Message, cmd);
				vector<CString> cmdString = SplitCString(cmd, L" ");
				RecvLock.unlock();
				return cmdString[0] == L"0";
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}
	return false;
}

bool Robot::StartPositionPPB()
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		CString sendData;
		sendData.Format(_T("PPB.J2StartPoint %d,0,%d"), RobotIndex, 1);

		//发送数据
		bool result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				CString cmd;
				AnalysisCmd(Message, cmd);
				vector<CString> cmdString = SplitCString(cmd, L" ");
				RecvLock.unlock();
				return cmdString[0] == L"0";
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}
	return false;
}

bool Robot::RunPPB()
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		CString sendData;
		sendData.Format(_T("PPB.Run %d"), RobotIndex);

		//发送数据
		bool result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				CString cmd;
				AnalysisCmd(Message, cmd);
				vector<CString> cmdString = SplitCString(cmd, L" ");
				RecvLock.unlock();
				return cmdString[0] == L"0";
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}
	return false;
}

bool Robot::StopPPB()
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		CString sendData;
		sendData.Format(_T("PPB.Run %d"), RobotIndex);

		//发送数据
		bool result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				CString cmd;
				AnalysisCmd(Message, cmd);
				vector<CString> cmdString = SplitCString(cmd, L" ");
				RecvLock.unlock();
				return cmdString[0] == L"0";
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}
	return false;
}

#pragma endregion

#pragma region IO控制

bool Robot::SetDOUT(int index, bool isEnable)
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		CString sendData;
		sendData.Format(_T("IO.Set DOUT(%d),%d"), index, isEnable);

		//发送数据
		bool result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				RecvLock.unlock();
				return true;
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}
	return false;
}

bool Robot::SetAOUT(int index, bool isEnable)
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		CString sendData;
		sendData.Format(_T("IO.Set AOUT(%d),%d"), index, isEnable);

		//发送数据
		bool result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				RecvLock.unlock();
				return true;
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}
	return false;
}

bool Robot::GetDOUT(int index, bool &isEnable)
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		CString sendData;
		sendData.Format(_T("IO.Get DOUT(%d)"), index);

		//发送数据
		bool result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				CString cmd;
				AnalysisCmd(Message, cmd);
				isEnable = _ttoi(cmd);
				RecvLock.unlock();
				return true;
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}
	return false;
}

bool Robot::GetAOUT(int index, bool &isEnable)
{
	if (IsConnected)
	{
		//复位接收标志
		RecvLock.lock();
		RecvStatus = 0;
		Message = L"";
		RecvLock.unlock();

		CString sendData;
		sendData.Format(_T("IO.Get AOUT(%d)"), index);

		//发送数据
		bool result = Send(sendData);
		if (!result)
		{
			return false;
		}

		//等待数据返回
		for (size_t i = 0; i < ROBOT_RECV_TIME_OUT; i++)
		{
			RecvLock.lock();
			if (RecvStatus != 0)
			{
				CString cmd;
				AnalysisCmd(Message, cmd);
				isEnable = _ttoi(cmd);
				RecvLock.unlock();
				return true;
			}
			RecvLock.unlock();

			Sleep(1);
		}
	}
	return false;
}

#pragma endregion
