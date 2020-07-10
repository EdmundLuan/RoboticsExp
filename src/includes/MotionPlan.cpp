#include <iostream>
#include <fstream>
#include "MotionPlan.h"
#include "HLrobotconfig.h"
#include <algorithm>
#include <Windows.h>
#include "../eigen3/Eigen/Dense"
#include <vector>

using namespace std;
using namespace HLRobot;
using namespace Eigen;

/********************************************************************
ABSTRACT:	构造函数

INPUTS:		<none>

OUTPUTS:	<none>

RETURN:		<none>
***********************************************************************/

CHLMotionPlan::CHLMotionPlan()
{
	for (int i = 0; i < 6; i++)
	{
		mJointAngleBegin[i] = 0;
		mJointAngleEnd[i] = 0;
	}

	for (int i = 0; i < 16; i++)
	{
		mStartMatrixData[i] = 0;
		mEndMatrixData[i] = 0;
	}
	for (int i = 0; i < 3; i++)
	{
		mConfig[i] = 0;
	}

	mSampleTime = 0.001;
	mVel = 0;
	mAcc = 0;
	mDec = 0;

	mStart = PosStruct(0,0,0,0,0,0);
	mEnd = PosStruct(0,0,0,0,0,0);
}

/********************************************************************
ABSTRACT:	析构函数

INPUTS:		<none>

OUTPUTS:	<none>

RETURN:		<none>
***********************************************************************/
CHLMotionPlan::~CHLMotionPlan()
{

}

/********************************************************************
ABSTRACT:	设置采样时间

INPUTS:		sampleTime			采样时间，单位S

OUTPUTS:	<none>

RETURN:		<none>
***********************************************************************/
void CHLMotionPlan::SetSampleTime(double sampleTime)
{
	if (sampleTime < 0.001)
	{
		mSampleTime = 0.001;
	}
	else
	{
		mSampleTime = sampleTime;
	}
}

/********************************************************************
ABSTRACT:	设置运动参数

INPUTS:		vel			速度，单位m/s
			acc			加速度，单位m/s/s
			dec			减速度，单位m / s / s

OUTPUTS:	<none>

RETURN:		<none>
***********************************************************************/
void CHLMotionPlan::SetProfile(double vel, double acc, double dec)
{
	mVel = vel;
	mAcc = acc;
	mDec = dec;
}

/********************************************************************
ABSTRACT:	设置规划的起始单位和技术点位

INPUTS:		startPos			起始点位笛卡尔坐标
			endPos				结束点位笛卡尔坐标

OUTPUTS:	<none>

RETURN:		<none>
***********************************************************************/
void CHLMotionPlan::SetPlanPoints(PosStruct startPos, PosStruct endPos)
{
	
	mStart = startPos;
	mEnd = endPos;

	double startAngle[3], endAngle[3];

	startAngle[0] = startPos.yaw * PI / 180;
	startAngle[1] = startPos.pitch * PI / 180;
	startAngle[2] = startPos.roll * PI / 180;

	endAngle[0] = endPos.yaw * PI / 180;
	endAngle[1] = endPos.pitch * PI / 180;
	endAngle[2] = endPos.roll * PI / 180;

	mStartMatrixData[0] = cos(startAngle[0])*cos(startAngle[1])*cos(startAngle[2]) - sin(startAngle[0])*sin(startAngle[2]);
	mStartMatrixData[1] = -cos(startAngle[0])*cos(startAngle[1])*sin(startAngle[2]) - sin(startAngle[0])*cos(startAngle[2]);
	mStartMatrixData[2] = cos(startAngle[0])*sin(startAngle[1]);
	mStartMatrixData[3] = startPos.x / 1000;

	mStartMatrixData[4] = sin(startAngle[0])*cos(startAngle[1])*cos(startAngle[2]) + cos(startAngle[0])*sin(startAngle[2]);
	mStartMatrixData[5] = -sin(startAngle[0])*cos(startAngle[1])*sin(startAngle[2]) + cos(startAngle[0])*cos(startAngle[2]);
	mStartMatrixData[6] = sin(startAngle[0])*sin(startAngle[1]);
	mStartMatrixData[7] = startPos.y / 1000;

	mStartMatrixData[8] = -sin(startAngle[1])*cos(startAngle[2]);
	mStartMatrixData[9] = sin(startAngle[1])*sin(startAngle[2]);
	mStartMatrixData[10] = cos(startAngle[1]);
	mStartMatrixData[11] = startPos.z / 1000;

	mStartMatrixData[12] = 0;
	mStartMatrixData[13] = 0;
	mStartMatrixData[14] = 0;
	mStartMatrixData[15] = 1;

	mEndMatrixData[0] = cos(endAngle[0])*cos(endAngle[1])*cos(endAngle[2]) - sin(endAngle[0])*sin(endAngle[2]);
	mEndMatrixData[1] = -cos(endAngle[0])*cos(endAngle[1])*sin(endAngle[2]) - sin(endAngle[0])*cos(endAngle[2]);
	mEndMatrixData[2] = cos(endAngle[0])*sin(endAngle[1]);
	mEndMatrixData[3] = endPos.x / 1000;

	mEndMatrixData[4] = sin(endAngle[0])*cos(endAngle[1])*cos(endAngle[2]) + cos(endAngle[0])*sin(endAngle[2]);
	mEndMatrixData[5] = -sin(endAngle[0])*cos(endAngle[1])*sin(endAngle[2]) + cos(endAngle[0])*cos(endAngle[2]);
	mEndMatrixData[6] = sin(endAngle[0])*sin(endAngle[1]);
	mEndMatrixData[7] = endPos.y / 1000;

	mEndMatrixData[8] = -sin(endAngle[1])*cos(endAngle[2]);
	mEndMatrixData[9] = sin(endAngle[1])*sin(endAngle[2]);
	mEndMatrixData[10] = cos(endAngle[1]);
	mEndMatrixData[11] = endPos.z / 1000;

	mEndMatrixData[12] = 0;
	mEndMatrixData[13] = 0;
	mEndMatrixData[14] = 0;
	mEndMatrixData[15] = 1;

	double start_matrix[16];
	double end_matrix[16];

	for (int i = 0; i < 16; i++)
	{
		start_matrix[i] = mStartMatrixData[i];
		end_matrix[i] = mEndMatrixData[i];
	}

	double angle1 = 0, angle2 = 0, angle3 = 0, angle4 = 0, angle5 = 0, angle6 = 0;
	//HLRobot::SetRobotEndPos(startPos.x, startPos.y, startPos.z, startPos.yaw, startPos.pitch, startPos.roll, startPos.config);
	HLRobot::GetJointAngles(angle1, angle2, angle3, angle4, angle5, angle6, start_matrix);
	//根据当前的初末姿态g，得到初末状态的六个关节角
	mJointAngleBegin[0] = angle1;
	mJointAngleBegin[1] = angle2;
	mJointAngleBegin[2] = angle3; 
	mJointAngleBegin[3] = angle4;
	mJointAngleBegin[4] = angle5;
	mJointAngleBegin[5] = angle6;

	//HLRobot::SetRobotEndPos(endPos.x, endPos.y, endPos.z, endPos.yaw, endPos.pitch, endPos.roll, endPos.config);
	HLRobot::GetJointAngles(angle1, angle2, angle3, angle4, angle5, angle6, end_matrix);
	mJointAngleEnd[0] = angle1;
	mJointAngleEnd[1] = angle2;
	mJointAngleEnd[2] = angle3;
	mJointAngleEnd[3] = angle4;
	mJointAngleEnd[4] = angle5;
	mJointAngleEnd[5] = angle6;

}

/********************************************************************
ABSTRACT:	运动轨迹规划部分

INPUTS:		pos						二维位置向量

OUTPUTS:	pos						二维位置向量（第一维：位置个数，第二维：每个轴的关节角度，单位弧度）

RETURN:		<none>
***********************************************************************/

/******
 * 参考步骤
 * 步骤1：创建文件并写入初始角度
 * 步骤2：计算每个轴旋转的角度
 * 步骤3：计算每个轴移动到终止点所需要时间
 * 步骤4：根据采样时间计算离散点位数
 * 步骤5：根据离散点位数得到每刻的关节角数值
 * 步骤6：将每时刻的关节角数值写入到文件
 */
void CHLMotionPlan::GetPlanPoints(char opt)
{
	ofstream outfile;               			//创建文件
    if(opt=='a')
        outfile.open("dataPlanInJointSpace.txt", ios::app);
    else
	    outfile.open("dataPlanInJointSpace.txt");
	outfile << mJointAngleBegin[0] << "  "
			<< mJointAngleBegin[1] << "  "
			<< mJointAngleBegin[2] << "  "
			<< mJointAngleBegin[3] << "  "
			<< mJointAngleBegin[4] << "  "
			<< mJointAngleBegin[5] << "  ";
	outfile << endl;//保存初始的时间、六个关节角度

	//cout << mJointAngleBegin[0] << "  "
	//	<< mJointAngleBegin[1] << "  "
	//	<< mJointAngleBegin[2] << "  "
	//	<< mJointAngleBegin[3] << "  "
	//	<< mJointAngleBegin[4] << "  "
	//	<< mJointAngleBegin[5] << "  ";
	//cout << endl;//保存初始的时间、六个关节角度


	// 计算六个轴的转角
	double angle[6];
	for (int i = 0; i < 6; i++)
	{
		angle[i] = mJointAngleEnd[i] - mJointAngleBegin[i];
	}

	// 计算六个转轴运动时间，并找到最大所需时间
	double t_acc[6], t_vel[6], t_dec[6], t_all[6], t_max = 0;
	for (int i = 0; i < 6; i++)
	{
		LFPB(angle[i], mAcc, mVel, mDec, t_acc[i], t_vel[i], t_dec[i]);
		t_all[i] = t_acc[i] + t_vel[i] + t_dec[i]; //加速+匀速+减速=总时长
		//cout << "t_all[i] = " << t_all[i] << '\t';
		if (t_max < t_all[i])
		{
			t_max = t_all[i];            // 最大运动时间
		}
	}
	cout << endl;

	// --------------------------------------------------------轨迹计算--------------------------------------------------------

	vector<vector<double>> all_points;        // 所有轨迹点

	int max_num = int(t_max / mSampleTime);   // 离散点数量

	for (int i = 0; i < 6; i++)
	{
		// 当前关节关节所有位置点
		vector<double> points;

		// 当前关节运动信息
		MM mm;
		if (angle[i] >= 0)                   // 角度增加的运动
		{
			mm = { mAcc, mVel, mDec, t_acc[i], t_vel[i], t_dec[i] };
		}
		else                                 // 角度减小的运动
		{
			mm = { -mAcc, -mVel, -mDec, t_acc[i], t_vel[i], t_dec[i] };
		}
		
		int num = t_all[i] / mSampleTime;

		//当前关节运动数据（位置，速度，时间）
		double v = 0, p = mJointAngleBegin[i], t = 0;

		// 下一时刻关节运动数据（位置，速度）
		double v_next = 0, p_next = 0;

		// 计算过程
		for (int j = 0; j < max_num; j++)
		{
			if (j < num)                  // 该关节还未运动值至目标点
			{
				LFPB_plan(p, v, t, mm, mSampleTime);
				points.push_back(p);
			}
			else                         // 该关节已经运动至目标点
			{
				points.push_back(p);
			}
		}

		all_points.push_back(points);
	}

	// 写入数据
	for (int i = 0; i < max_num; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			outfile << all_points[j][i] << "  ";
		}
		outfile << endl;
	}

	outfile.close();
	

}

//---------------------------------------------------------------------------【GetPlanPointsCartesian 函数】---------------------------------------------------------
//函数说明：笛卡尔坐标系进行轨迹规划，获取离散点位
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void CHLMotionPlan::GetPlanPointsCartesian(char opt)
{
	ofstream outfile;
    if (opt == 'a')
        outfile.open("dataPlanInCartesian.txt", ios::app);
    else
        outfile.open("dataPlanInCartesian.txt");
	outfile << mJointAngleBegin[0] << "  "
		<< mJointAngleBegin[1] << "  "
		<< mJointAngleBegin[2] << "  "
		<< mJointAngleBegin[3] << "  "
		<< mJointAngleBegin[4] << "  "
		<< mJointAngleBegin[5] << "  ";
	outfile << endl;//保存初始的时间、六个关节角度

    ofstream fout;
    if (opt == 'a')
        fout.open("dataPos.txt",ios::app);
    else
        fout.open("dataPos.txt");

    fout << mStart.x << "  "
        << mStart.y << "  "
        << mStart.z << "  ";
    fout << endl;


    


	// 计算x,y,z 三个方向移动的距离以及起始点到终止点的向量direction
	double distance[3];
    double direction[3];
    double distance_p, temp1, temp2, temp3;
	distance[0] = (mEnd.x - mStart.x) / 1000.0;
	distance[1] = (mEnd.y - mStart.y) / 1000.0;
	distance[2] = (mEnd.z - mStart.z) / 1000.0;
    double sum = distance[0] * distance[0] + distance[1] * distance[1] + distance[2] * distance[2];
    direction[0] = distance[0]/sum;
    direction[1] = distance[1]/sum;
    direction[2] = distance[2]/sum;
    temp1 = distance[0] / direction[0];
    temp2 = distance[1] / direction[1];
    temp3 = distance[2] / direction[2];
    if (distance[0] != 0)
    {
        distance_p = temp1;
    }
    else if (distance[1] != 0)
    {
        distance_p = temp2;
    }
    else
    {
        distance_p = temp3;
    }
    cout << direction[0] << "\t" << direction[1] << "\t" << direction[2] << "\t" << endl;
    cout << temp1 << "\t" << temp2 << "\t" << temp3 << "\t" << endl;

    // 初始坐标
	double start[3] = { mStart.x/1000, mStart.y/1000, mStart.z/1000};

	//// 定义x,y,z三个方向的运动信息
	//MM mm[3];
	//for (int i = 0; i < 3; i++)
	//{
	//	mm[i] = { mAcc / 100,mVel / 100,mDec / 100,0,0,0 };
	//}

	//
	//// 求解x,y,z三个方向的运动时间
	//double t_acc[6], t_vel[6], t_dec[6], t_all[6], t_max = 0;
	//int index = 0;
	//for (int i = 0; i < 3; i++)
	//{
	//	LFPB(distance[i], mm[i]);
	//	t_all[i] = mm[i].t_acc + mm[i].t_vel + mm[i].t_dec;
	//	cout << "t_all[i] = " << t_all[i] << '\t';
	//	if (t_max < t_all[i])
	//	{
	//		t_max = t_all[i];            // 最大运动时间
	//		index = i;
	//	}
	//}
 //   cout << "Index = " << index << endl;

    //  求解运动时间
    MM mm = { mAcc / 100,mVel / 100,mDec / 100,0,0,0 };
    LFPB(distance_p, mm);

	//// 根据最大运动时间来重新规划六个自由度的匀速运动速度vel
	//for (int i = 0; i < 3; i++)
	//{
	//	if (i != index)
	//	{
	//		VelocityPlan(t_max, distance[i], mm[i]);
	//	}
	//	
	//}

	// --------------------------------------------------------轨迹计算--------------------------------------------------------

	vector<vector<double>> all_points;        // 所有轨迹点

    int num = int((mm.t_acc + mm.t_vel + mm.t_dec) / mSampleTime) - 1;   // 离散点数量

    int real_num = 0;

		

		//// 当前关节运动信息
		//MM mm;
		//if (angle[i] >= 0)                   // 角度增加的运动
		//{
		//	mm = { mAcc, mVel, mDec, t_acc[i], t_vel[i], t_dec[i] };
		//}
		//else                                 // 角度减小的运动
		//{
		//	mm = { -mAcc, -mVel, -mDec, t_acc[i], t_vel[i], t_dec[i] };
		//}

		//int num = t_max / mSampleTime;

		//当前关节运动数据（位置，速度，时间）
		double v = 0, p = 0, t = 0;

		//// 下一时刻关节运动数据（位置，速度）
		//double v_next = 0, p_next = 0;

		// 计算过程
		for (int j = 0; j < num; j++)
		{
            // 当前关节关节所有位置点
            vector<double> points;

			LFPB_plan(p, v, t, mm, mSampleTime);

            if (p < distance_p)
            {
                for (int i = 0; i < 3; i++)
                {
                    points.push_back((start[i] + direction[i] * p) * 1000);
                    fout << points[i] << "  ";
                }
                fout << endl;
                all_points.push_back(points);
                real_num++;

            }
            
		}
        vector<double> points;
        points.push_back(mEnd.x);
        points.push_back(mEnd.y);
        points.push_back(mEnd.z);

        all_points.push_back(points);
        real_num++;
        //cout << "t = " << t << endl << endl;

		

	// -------------------------------------------将笛卡尔坐标转换为关节角-------------------------------------------
	vector<vector<float>> joint_points;

	double Tran[16]{ 0 };
	bool config[3] = { 1,1,1 };
	bool Turns[6] = { 1,1,1,1,1,1 };
	double Tool[16]{ 0 };
	double q[6];

	for (int i = 0; i < real_num; i++)
	{
		vector<float> points;                     // 当前时刻六个关节角

		double Angle[3] = { mStart.yaw/180*PI, mStart.pitch / 180 * PI, mStart.roll / 180 * PI };
		PosStruct Pos = { all_points[i][0], all_points[i][1], all_points[i][2], 0, 0, 0};

		Tran[0] = cos(Angle[0])*cos(Angle[1])*cos(Angle[2]) - sin(Angle[0])*sin(Angle[2]);
		Tran[1] = -cos(Angle[0])*cos(Angle[1])*sin(Angle[2]) - sin(Angle[0])*cos(Angle[2]);
		Tran[2] = cos(Angle[0])*sin(Angle[1]);
		Tran[3] = Pos.x / 1000;

		Tran[4] = sin(Angle[0])*cos(Angle[1])*cos(Angle[2]) + cos(Angle[0])*sin(Angle[2]);
		Tran[5] = -sin(Angle[0])*cos(Angle[1])*sin(Angle[2]) + cos(Angle[0])*cos(Angle[2]);
		Tran[6] = sin(Angle[0])*sin(Angle[1]);
		Tran[7] = Pos.y / 1000;

		Tran[8] = -sin(Angle[1])*cos(Angle[2]);
		Tran[9] = sin(Angle[1])*sin(Angle[2]);
		Tran[10] = cos(Angle[1]);
		Tran[11] = Pos.z / 1000;

		Tran[12] = 0;
		Tran[13] = 0;
		Tran[14] = 0;
		Tran[15] = 1;
        HLRobot::robotBackwardHJQ(Tran, config, Tool, Turns, q);

		for (int i = 0; i < 6; i++)
		{
			points.push_back(q[i] * 180 / PI);
		}

		joint_points.push_back(points);
	}


	// 写入数据
	for (int i = 0; i < real_num; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			outfile << joint_points[i][j] << "  ";
		}
		outfile << endl;
	}

	outfile.close();
    fout.close();


}