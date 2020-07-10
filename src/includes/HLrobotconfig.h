
#ifndef ROBOTCONFIG_H_
#define ROBOTCONFIG_H_

#include "MotionPlan.h"
#include <Eigen/Dense>

using namespace Eigen;

const double PI = 3.1415926;
namespace HLRobot
{ 
	//double qlimP[6] = { 170 * PI / 180,120 * PI / 180,48 * PI / 180, 180 * PI / 180, 120 * PI / 180,360 * PI / 180 };
	//double qlimN[6] = { -170 * PI / 180,-120 * PI / 180,-228 * PI / 180, -180 * PI / 180, -120 * PI / 180,-360 * PI / 180 };

	typedef struct MoveMessage
	{
		double acc;
		double vel;
		double dec;
		double t_acc;
		double t_vel;
		double t_dec;
	}MM;

	//---------------------------------------------------机器人前向运动学，逆运动学函数声明--------------------------------------------------
	void robotBackwardHJQ(const double* TransVector, bool* config, double* Tool, bool* Turns, double* theta);
	void robotForwardHJQ(const double* q, const double* Tool, double* TransVector, bool* config, bool* turns);

	//---------------------------------------------------逆运动学子问题函数声明--------------------------------------------------
	bool Subproblem1(double* theta, const int index, const VectorXd& xi, const Vector4d& p_4, const Vector4d& q_4, const Vector4d& r_4);
	bool Subproblem2(double* theta, const int index1, const int index2, const VectorXd& xi1, const VectorXd& xi2, const Vector4d& p_4, const Vector4d& q_4, const Vector4d& r_4);
	bool Subproblem3(double* theta, const int index, const VectorXd& xi, const Vector4d& p_4, const Vector4d& q_4, const Vector4d& r_4, const double delta);

	//---------------------------------------------------------------------------【LFPB 函数】---------------------------------------------------------
	//函数说明：进行两点间LFPB轨迹规划，输入distance ,acc, vel, dec
	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	void LFPB(const double distance, const double acc, const double vel, const double dec, double& t_acc, double& t_vel, double& t_dec);
	void LFPB(const double distance, MM& mm);

	//---------------------------------------------------------------------------【VelocityPlan 函数】---------------------------------------------------------
	//函数说明：根据运动时间和加速度，减速度规划匀速运动速度
	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	void VelocityPlan(const double t, const double distance, MM& mm);

	//---------------------------------------------------------------------------【LFPB_plan 函数】---------------------------------------------------------
	//函数说明：根据当前点，时间，速度，加速度等规划下一个点
	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	void LFPB_plan(double& p_now, double& v_now, double& t, const MM& mm, const double T);

	//---------------------------------------------------------------------------【SetRobotEndPos 函数】---------------------------------------------------------
	//函数说明：暂时无用
	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	void SetRobotEndPos(const double x, const double y, const double z, const double yaw, const double pitch, const double roll, bool* config);

	//---------------------------------------------------------------------------【GetJointAngles 函数】---------------------------------------------------------
	//函数说明：根据当前的姿态g，得到六个关节角
	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	void GetJointAngles(double& angle1, double& angle2, double& angle3, double& angle4, double& angle5, double& angle6, const double* g);
}

#endif
