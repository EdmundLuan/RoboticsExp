#include <iostream>
#include "HLrobotconfig.h"
#include "MotionPlan.h"
#include <vector>

using namespace std;

/****
 * 实验四: 轨迹规划
 * 要 求：使用C/C++完成梯型速度规划，生成data.txt文件
 * 规划类型：关节空间、笛卡尔空间（直线）
 * 点位数量：起始点和终止点
 * 给定条件：Vel，Acc，Dec
 * 
 */

int main()
{   
	////起始点
 //   PosStruct start;
 //   start.x = 475.693; start.y = -189.407; start.z = 802.044;
 //   start.yaw = 4.221; start.pitch = 169.075; start.roll = -131.743;

 //   //终止点
	//PosStruct end;
 //   end.x = 441.78; end.y = 86.9; end.z = 877.035;
 //   end.yaw = 103.388; end.pitch = 170.195; end.roll = -90.995;

    // 起始点
    PosStruct point1, point2, point3, point4;
    point1 = { 509.892,99.918,796.366,-178.631,179.920,1.378 ,{1,1,1} };
    point2 = { 509.892,-100.082,796.366,-178.631,179.920,1.378 ,{1,1,1} };
    point3 = { 309.892,-100.082,796.366,-178.631,179.920,1.378 ,{1,1,1} };
    point4 = { 309.892,99.918,796.366,-178.631,179.920,1.378 ,{1,1,1} };

 //   //梯型速度规划
	//CHLMotionPlan trajectory1;
 //   trajectory1.SetPlanPoints(start, end);  
 //   trajectory1.SetProfile(10, 10, 10);    //vel °/s， acc °/s.s, dec °/s.s
 //   trajectory1.SetSampleTime(0.001);      //s
 //   //trajectory1.GetPlanPoints();
	//trajectory1.GetPlanPointsCartesian();

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
    //cin.get();

    trajectory1.SetPlanPoints(point2, point3);
    trajectory1.GetPlanPoints(97);
    cout << "Plan in joint space done!" << endl;
    trajectory1.GetPlanPointsCartesian(97);
    cout << "Plan in world space done!" << endl;
    cout << "Point2  ------------------>         Point3  Done!" << endl;
   // cin.get();

    trajectory1.SetPlanPoints(point3, point4);
    trajectory1.GetPlanPoints(97);
    cout << "Plan in joint space done!" << endl;
    trajectory1.GetPlanPointsCartesian(97);
    cout << "Plan in world space done!" << endl;
    cout << "Point3  ------------------>         Point4  Done!" << endl;
   // cin.get();

    trajectory1.SetPlanPoints(point4, point1);
    trajectory1.GetPlanPoints(97);
    cout << "Plan in joint space done!" << endl;
    trajectory1.GetPlanPointsCartesian(97);
    cout << "Plan in world space done!" << endl;
    cout << "Point4  ------------------>         Point1  Done!" << endl;
    cin.get();

	/*vector<vector<double>> a;
	vector<double> b,c;

	b.push_back(1);
	b.push_back(2);

	c.push_back(3);
	c.push_back(4);

	a.push_back(b);
	a.push_back(c);


	cout << a[1][1] << endl;*/

	//double Tran[16]{ 0 };
	//bool config[3] = { 1,1,1 };
	//bool Turns[6] = { 1,1,1,1,1,1 };
	//double q[6] = { 16.149*PI / 180,-14.188 * PI / 180,92.396 * PI / 180,16.699 * PI / 180,15.796 * PI / 180,157 * PI / 180 };
	//double Tool[16]{ 0 };
	//HLRobot::robotForwardHJQ(q, Tool, Tran, config, Turns);

	//for (int i = 0; i < 16; i++)
	//{
	//	cout << Tran[i] << '\t';
	//	if (i % 4 == 3)
	//	{
	//		cout << '\n';
	//	}
	//}

	//HLRobot::robotForwardHJQ(q, Tool, Tran, config, Turns);

	//for (int i = 0; i < 6; i++)
	//{
	//	cout << q[i] * 180 / PI << "\t";
	//}
	//cout << endl;

	//cin.get();

	return 0;
}