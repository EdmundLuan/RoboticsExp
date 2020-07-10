
#include "HLrobotconfig.h"
#include <cmath>
#include "../eigen3/Eigen/Dense"
#include <iostream>

#define PI 3.1415926

using namespace std;
using namespace Eigen;



namespace HLRobot
{


	/********************************************************************
	ABSTRACT:	机器人逆

	INPUTS:		T[16]:	位姿矩阵，其中长度距离为米
				config[3]：姿态，六轴机器人对应有8种姿态，为了安全，
				实验室中我们只计算一种即可，config在正运动学中进行了初始化，所以不需要进行更改。

				Tool:可以忽略
				Turns[6]：每个关节对应的圈数

	OUTPUTS:    theta[6] 6个关节角, 单位为弧度

	RETURN:		<none>
	***********************************************************************/
	void robotBackwardHJQ(const double* T, bool* config, double* Tool, bool* Turns, double* theta)
	{
        // -------------------------------------------------- - 六轴机器人参数c初始化--------------------------------------------------


        // 转轴方向
        Vector3d omega1(3, 1), omega2(3, 1), omega3(3, 1), omega4(3, 1), omega5(3, 1), omega6(3, 1);
        omega1 << 0, 0, 1;
        omega2 << 0, 1, 0;
        omega3 << 0, 1, 0;
        omega4 << 0, 0, 1;
        omega5 << 0, 1, 0;
        omega6 << 0, 0, 1;

        // 长度参数
        double L1 = 0.491, L2 = 0.450, L3 = 0.450, L4 = 0.084;

        // 初始位姿矩阵（g_st0)声明
        Matrix4d g_st0(4, 4);
        g_st0 << -1, 0, 0, 0,
            0, -1, 0, 0,
            0, 0, 1, L1 + L2 + L3 + L4,
            0, 0, 0, 1;

        // 正运动学初始点选择
        Vector3d q0(3, 1), q1(3, 1), q2(3, 1), q3(3, 1);
        q0 << 0, 0, 0;
        q1 << 0, 0, L1;
        q2 << 0, 0, L1 + L2;
        q3 << 0, 0, L1 + L2 + L3;

        // 逆运动学初始点选择
        Vector4d q0_4(4, 1), q1_4(4, 1), q2_4(4, 1), q3_4(4, 1), q4_4(4, 1);
        q0_4 << 0, 0, 0, 1;
        q3_4 << 0, 0, L1 + L2 + L3, 1;
        q1_4 << 0, 0, L1, 1;
        q2_4 << 0, 0, L1 + L2, 1;
        q4_4 << 0, 0, L1 + L2 + L3 + L4, 1;

        // 速度（运动螺旋xi的前三个分量-omega X q，后三个分量为omega）
        Vector3d v1(3, 1), v2(3, 1), v3(3, 1), v4(3, 1), v5(3, 1), v6(3, 1);
        v1 << -omega1.cross(q0);
        v2 << -omega2.cross(q1);
        v3 << -omega3.cross(q2);
        v4 << -omega4.cross(q0);
        v5 << -omega5.cross(q3);
        v6 << -omega6.cross(q0);

        // 运动螺旋声明(xi)
        VectorXd xi1(6, 1), xi2(6, 1), xi3(6, 1), xi4(6, 1), xi5(6, 1), xi6(6, 1);

        // 运动螺旋xi赋值
        xi1.block(0, 0, 3, 1) << v1;
        xi1.block(3, 0, 3, 1) << omega1;
        xi2.block(0, 0, 3, 1) << v2;
        xi2.block(3, 0, 3, 1) << omega2;
        xi3.block(0, 0, 3, 1) << v3;
        xi3.block(3, 0, 3, 1) << omega3;
        xi4.block(0, 0, 3, 1) << v4;
        xi4.block(3, 0, 3, 1) << omega4;
        xi5.block(0, 0, 3, 1) << v5;
        xi5.block(3, 0, 3, 1) << omega5;
        xi6.block(0, 0, 3, 1) << v6;
        xi6.block(3, 0, 3, 1) << omega6;

        // 平移向量定义及计算（变换矩阵g的右上角1X3向量p）
        Vector3d p1, p2, p3, p4, p5, p6;

        // 3X3 单位阵定义
        Matrix3d I = Matrix3d::Identity();


        // 变换矩阵初始化
        Matrix4d g_st(4, 4);
        int k = 0;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                g_st(i, j) = T[k];
                k++;
            }
        }

		// -------------------------------------------------------计算过程---------------------------------------------------------
		Matrix4d G1(4, 4), G2(4,4), G3(4,4);
		G1 << g_st * g_st0.inverse();
		double delta;
		Vector4d p, q, r;

		// ---------------------------Subproblem3 --> theta3-------------------------------
		delta = (G1*q3_4 - q1_4).norm();
		p << q3_4;
		q << q1_4;
		r << q2_4;
		Subproblem3(theta, 2, xi3, p, q, r, delta);

		// ---------------------------Subproblem2 --> theta1,2-------------------------------
		Isometry3d g3 = Eigen::Isometry3d::Identity();
		AngleAxisd Omega3(theta[2], omega3);
		g3.rotate(Omega3);
		p3 << (I - Omega3.matrix()) * (omega3.cross(v3)) + omega3 * omega3.transpose()*v3*theta[2];
		g3.pretranslate(p3);

        //cout << "g3 = " << endl << g3.matrix() << endl;

		p << g3 * q3_4;
		q << G1 * q3_4;
		r << q1_4;
		Subproblem2(theta, 0, 1, xi1, xi2, p, q, r);
        //theta[0] = 0.2818;

		// ---------------------------Subproblem3 --> theta5-------------------------------
		Isometry3d g1 = Eigen::Isometry3d::Identity();
		Isometry3d g2 = Eigen::Isometry3d::Identity();
		AngleAxisd Omega1(theta[0], omega1);
		AngleAxisd Omega2(theta[1], omega2);
		g1.rotate(Omega1);
		g2.rotate(Omega2);
		p1 << (I - Omega1.matrix()) * (omega1.cross(v1)) + omega1 * omega1.transpose()*v1*theta[0];
		p2 << (I - Omega2.matrix()) * (omega2.cross(v2)) + omega2 * omega2.transpose()*v2*theta[1];
		g1.pretranslate(p1);
		g2.pretranslate(p2);

		G2 << g3.inverse()*g2.inverse()*g1.inverse()*G1;

        delta = (G2*q0_4 - q4_4).norm();
        p << q0_4;
        q << q4_4;
        r << q3_4;
        Subproblem3(theta, 4, xi5, p, q, r, delta);

		// ---------------------------Subproblem1 --> theta4-------------------------------
		Isometry3d g5 = Eigen::Isometry3d::Identity();
		AngleAxisd Omega5(theta[4], omega5);		
		g5.rotate(Omega5);
		p5 << (I - Omega5.matrix()) * (omega5.cross(v5)) + omega5 * omega5.transpose()*v5*theta[4];
		g5.pretranslate(p5);

        p << g5 * q1_4;
		q << G2 * q1_4;
		r << q0_4;
		Subproblem1(theta, 3, xi4, p, q, r);

        // ---------------------------Subproblem1 --> theta6-------------------------------
        Isometry3d g4 = Eigen::Isometry3d::Identity();
        AngleAxisd Omega4(theta[3], omega4);
        g4.rotate(Omega4);
        p4 << (I - Omega4.matrix()) * (omega4.cross(v4)) + omega4 * omega4.transpose()*v4*theta[3];
        g4.pretranslate(p4);

        G3 << g5.inverse()*g4.inverse()*G2;

        p << 100, 0, 0, 1;
        q << G3 * p;
        r << q2_4;
        Subproblem1(theta, 5, xi6, p, q, r);
	}


	/********************************************************************
	ABSTRACT:	输入机器人的末端位置
	
	INPUTS:		q[6]: 6个关节角, 单位为弧度
				Tool:可以忽略
	
	OUTPUTS:	config[3]：姿态，六轴机器人对应有8种姿态，为了安全，
				实验室中我们只计算一种即可，config在正运动学中进行了初始化，所以不需要进行更改。
				Turns[6]：每个关节对应的圈数
				TransVector[16] : 刚体变换矩阵，也就是末端的位姿描述，其中长度距离为米
	
	RETURN:		<none>
	***********************************************************************/
	void robotForwardHJQ(const double* q, const double* Tool, double* TransVector, bool* config, bool* turns)
	{
		config[0] = 1; config[1] = 1; config[2] = 1;
		turns[0] = 1; turns[1] = 1; turns[2] = 1; turns[3] = 1; turns[4] = 1; turns[5] = 1;

        // -------------------------------------------------- - 六轴机器人参数c初始化--------------------------------------------------

        // 转轴方向
        Vector3d omega1(3, 1), omega2(3, 1), omega3(3, 1), omega4(3, 1), omega5(3, 1), omega6(3, 1);
        omega1 << 0, 0, 1;
        omega2 << 0, 1, 0;
        omega3 << 0, 1, 0;
        omega4 << 0, 0, 1;
        omega5 << 0, 1, 0;
        omega6 << 0, 0, 1;

        // 长度参数
        double L1 = 491, L2 = 450, L3 = 450, L4 = 84;

        // 初始位姿矩阵（g_st0)声明
        Matrix4d g_st0(4, 4);
        g_st0 << -1, 0, 0, 0,
            0, -1, 0, 0,
            0, 0, 1, L1 + L2 + L3 + L4,
            0, 0, 0, 1;

        // 正运动学初始点选择
        Vector3d q0(3, 1), q1(3, 1), q2(3, 1), q3(3, 1);
        q0 << 0, 0, 0;
        q1 << 0, 0, L1;
        q2 << 0, 0, L1 + L2;
        q3 << 0, 0, L1 + L2 + L3;

        // 速度（运动螺旋xi的前三个分量-omega X q，后三个分量为omega）
        Vector3d v1(3, 1), v2(3, 1), v3(3, 1), v4(3, 1), v5(3, 1), v6(3, 1);
        v1 << -omega1.cross(q0);
        v2 << -omega2.cross(q1);
        v3 << -omega3.cross(q2);
        v4 << -omega4.cross(q0);
        v5 << -omega5.cross(q3);
        v6 << -omega6.cross(q0);

        // 运动螺旋声明(xi)
        VectorXd xi1(6, 1), xi2(6, 1), xi3(6, 1), xi4(6, 1), xi5(6, 1), xi6(6, 1);

        // 运动螺旋xi赋值
        xi1.block(0, 0, 3, 1) << v1;
        xi1.block(3, 0, 3, 1) << omega1;
        xi2.block(0, 0, 3, 1) << v2;
        xi2.block(3, 0, 3, 1) << omega2;
        xi3.block(0, 0, 3, 1) << v3;
        xi3.block(3, 0, 3, 1) << omega3;
        xi4.block(0, 0, 3, 1) << v4;
        xi4.block(3, 0, 3, 1) << omega4;
        xi5.block(0, 0, 3, 1) << v5;
        xi5.block(3, 0, 3, 1) << omega5;
        xi6.block(0, 0, 3, 1) << v6;
        xi6.block(3, 0, 3, 1) << omega6;

        // 平移向量定义及计算（变换矩阵g的右上角1X3向量p）
        Vector3d p1, p2, p3, p4, p5, p6;

        // 3X3 单位阵定义
        Matrix3d I = Matrix3d::Identity();


		// 旋转向量定义
		AngleAxisd Omega1(q[0], omega1);
		AngleAxisd Omega2(q[1], omega2);
		AngleAxisd Omega3(q[2], omega3);
		AngleAxisd Omega4(q[3], omega4);
		AngleAxisd Omega5(q[4], omega5);
		AngleAxisd Omega6(q[5], omega6);

		// 变换矩阵定义（4X4）
		Isometry3d g1 = Eigen::Isometry3d::Identity();
		Isometry3d g2 = Eigen::Isometry3d::Identity();
		Isometry3d g3 = Eigen::Isometry3d::Identity();
		Isometry3d g4 = Eigen::Isometry3d::Identity();
		Isometry3d g5 = Eigen::Isometry3d::Identity();
		Isometry3d g6 = Eigen::Isometry3d::Identity();

		// 平移向量计算（变换矩阵g的右上角1X3向量p）
		p1 << (I - Omega1.matrix()) * (omega1.cross(v1)) + omega1 * omega1.transpose()*v1*q[0];
		p2 << (I - Omega2.matrix()) * (omega2.cross(v2)) + omega2 * omega2.transpose()*v2*q[1];
		p3 << (I - Omega3.matrix()) * (omega3.cross(v3)) + omega3 * omega3.transpose()*v3*q[2];
		p4 << (I - Omega4.matrix()) * (omega4.cross(v4)) + omega4 * omega4.transpose()*v4*q[3];
		p5 << (I - Omega5.matrix()) * (omega5.cross(v5)) + omega5 * omega5.transpose()*v5*q[4];
		p6 << (I - Omega6.matrix()) * (omega6.cross(v6)) + omega6 * omega6.transpose()*v6*q[5];

		// 变换矩阵计算（4X4）
		g1.rotate(Omega1);               // g1
		g1.pretranslate(p1);
		g2.rotate(Omega2);               // g2
		g2.pretranslate(p2);
		g3.rotate(Omega3);               // g3
		g3.pretranslate(p3);
		g4.rotate(Omega4);               // g4
		g4.pretranslate(p4);
		g5.rotate(Omega5);               // g5
		g5.pretranslate(p5);
		g6.rotate(Omega6);               // g6
		g6.pretranslate(p6);

		// 正向运动变换矩阵（g_st)
		Matrix4d g_st(4, 4);
		g_st << g1 * g2 * g3 * g4 * g5 * g6 * g_st0;

		// 最终结果赋值给TransVector
		int k = 0;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				TransVector[k] = g_st(i, j);
				k++;
			}
		}
	}

	//---------------------------------------------------逆运动学子问题函数定义--------------------------------------------------
	
	bool Subproblem1(double* theta, const int index, const VectorXd& xi, const Vector4d& p_4, const Vector4d& q_4, const Vector4d& r_4)
	{
		// omega,及p,q,r三点的初始化
		Vector3d omega(3, 1), p(3, 1), q(3, 1), r(3, 1);
		omega << xi.block(3, 0, 3, 1);
		p << p_4.block(0, 0, 3, 1);
		q << q_4.block(0, 0, 3, 1);
		r << r_4.block(0, 0, 3, 1);

		// u,v,t,u_prime,v_prime 五个向量的初始化
		Vector3d u(3, 1), v(3, 1), t(3, 1), u_prime(3, 1), v_prime(3, 1);
		u << p - r;
		v << q - r;
		t << u.transpose()*omega*omega;
		u_prime << u - t;
		v_prime << v - t;

		// 计算过程
		if (1)
		{
			if (u_prime.norm() == 0)
			{
				theta[index] = 0;
				cout << "There are Infinite numbers of solutions for Subproblem1 !!!\t\t\t The angle is theta" << index+1 << " !" << endl;
			}
			else
			{
				theta[index] = atan2(omega.transpose()*(u_prime.cross(v_prime)), u_prime.transpose()*v_prime);
			}
			return true;
		}
		else
		{
			cout << "There is no solution for Subproblem1 !!!\t\t\t The angle is theta" << index + 1 << " !" << endl;
			theta[index] = 0;
			return false;
		}


	}

	bool Subproblem2(double* theta, const int index1, const int index2, const VectorXd& xi1, const VectorXd& xi2, const Vector4d& p_4, const Vector4d& q_4, const Vector4d& r_4)
	{
		// omega1, omega2 及p,q,r三点的初始化
		Vector3d omega1(3, 1), omega2(3,1), p(3, 1), q(3, 1), r(3, 1);
		omega1 << xi1.block(3, 0, 3, 1);
		omega2 << xi2.block(3, 0, 3, 1);
		p << p_4.block(0, 0, 3, 1);
		q << q_4.block(0, 0, 3, 1);
		r << r_4.block(0, 0, 3, 1);

		// u,v 两个向量以及alpha,beta的初始化
		Vector3d u(3, 1), v(3, 1);
		double alpha, beta, temp, temp1, temp4, temp3;             // temp,temp1,temp2,temp3为中间运算变量
		u << p - r;
		v << q - r;
		temp = omega1.transpose()*omega2;
		temp4 = omega2.transpose()*u;
		temp3 = omega1.transpose()*v;
		alpha = (temp*temp4 - temp3) / (temp*temp - 1);
		beta = (temp*temp3 - temp4) / (temp*temp - 1);
		temp1 = u.squaredNorm() - alpha * alpha - beta * beta - 2 * alpha*beta*temp;

		// 计算过程
		if (temp1 < 0)
		{
			cout << "There is no solution for Subproblem2 !!!\t\t\t The angles are theta" << index1 + 1 << " and theta" << index2 + 1 << " !" << endl;
			theta[index1] = 0;
			theta[index2] = 0;
			return false;
		}
		else if (temp1 == 0)
		{
			Vector4d z, c;
			z.block(0,0,3,1) << alpha * omega1 + beta * omega2;
			c.block(0, 0, 3, 1) << z.block(0, 0, 3, 1) + r;
			Subproblem1(theta,index2,xi2, p_4, c, r_4);
			Subproblem1(theta, index1, xi1, c, q_4, r_4);
			return true;
		}
		else
		{
            //cout << "LLLLLLLLLLLLLLLLLLL" << endl;
			Vector4d temp2, z1, c1;
			double gamma1;
			temp2.block(0, 0, 3, 1) << omega1.cross(omega2);
			gamma1 = -sqrt((temp1 / (temp2.block(0, 0, 3, 1)).squaredNorm()));
			z1.block(0, 0, 3, 1) << alpha * omega1 + beta * omega2 + gamma1 * temp2.block(0, 0, 3, 1);
			c1.block(0, 0, 3, 1) << z1.block(0, 0, 3, 1) + r;
			Subproblem1(theta, index2, xi2, p_4, c1, r_4);
			Subproblem1(theta, index1, xi1, c1, q_4, r_4);
			return true;
		}
	}

	bool Subproblem3(double* theta, const int index, const VectorXd& xi, const Vector4d& p_4, const Vector4d& q_4, const Vector4d& r_4, const double delta)
	{
		// omega,及p,q,r三点的初始化
		Vector3d omega(3, 1), p(3, 1), q(3, 1), r(3, 1);
		omega << xi.block(3, 0, 3, 1);
		p << p_4.block(0, 0, 3, 1);
		q << q_4.block(0, 0, 3, 1);
		r << r_4.block(0, 0, 3, 1);

		// u,v,u_prime,v_prime 四个向量的初始化
		Vector3d u(3, 1), v(3, 1), t(3, 1), u_prime(3, 1), v_prime(3, 1);
		u << p - r;
		v << q - r;
		u_prime << u - u.transpose()*omega*omega;
		v_prime << v - v.transpose()*omega*omega;

		// theta0,delta_prime_squ参数的初始化
		double theta0, delta_prime_squ;
		theta0 = atan2(omega.transpose()*(u_prime.cross(v_prime)), u_prime.transpose()*v_prime);
		delta_prime_squ = delta * delta - (omega.transpose()*(p - q)).squaredNorm();

		// 中间变量temp
		double temp = u_prime.squaredNorm() + v_prime.squaredNorm() - delta_prime_squ;
		temp = temp / (2 * u_prime.norm()*v_prime.norm());

		// 计算过程
		if (abs(temp) > 1)
		{
			cout << "There is no solution for Subproblem3 !!!\t\t\t The angle is theta" << index + 1 << " !" << endl;
			theta[index] = 0;
			return false;
		}
		else
		{
			double alpha = acos(temp);
			theta[index] = theta0 - alpha;
			return true;
		}

	}


	//---------------------------------------------------------------------------【SetRobotEndPos 函数】---------------------------------------------------------
	//函数说明：暂时无用
	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	void SetRobotEndPos(const double x, const double y, const double z, const double yaw, const double pitch, const double roll, bool* config)
	{

	}

	//---------------------------------------------------------------------------【GetJointAngles 函数】---------------------------------------------------------
	//函数说明：根据当前的姿态g，得到六个关节角
	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	void GetJointAngles(double& angle1, double& angle2, double& angle3, double& angle4, double& angle5, double& angle6, const double* g)
	{
		/*Matrix4d g_st(4, 4);

		int k = 0;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				g_st(i, j) = g[k];
			}
		}*/

		double theta[6];

		bool config[3] = { 1,1,1 };
		bool Turns[6] = { 1,1,1,1,1,1 };
		double Tool[16]{ 0 };

		robotBackwardHJQ(g, config, Tool, Turns, theta);

		angle1 = theta[0] * 180 / PI;
		angle2 = theta[1] * 180 / PI;
		angle3 = theta[2] * 180 / PI;
		angle4 = theta[3] * 180 / PI;
		angle5 = theta[4] * 180 / PI;
		angle6 = theta[5] * 180 / PI;


	}

	//---------------------------------------------------------------------------【LFPB 函数】---------------------------------------------------------
	//函数说明：进行两点间LFPB轨迹规划，输入distance,acc,vel,dec，求解t_acc,t_vel,t_dec
	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	void LFPB(const double distance, const double acc, const double vel, const double dec, double& t_acc, double& t_vel, double& t_dec)
	{
		double abs_distance = abs(distance);
		double t_b0 = vel / acc;   //加速时间=减速时间
		double d_b0 = 0.5*acc*t_b0*t_b0; //匀速段起始点位置
		if (2*d_b0 >= abs_distance)      // 此时完整加速减速过程行走的距离就足够完成整个运动，不需要匀速阶段
		{
			t_vel = 0;                        //匀速时间
			t_acc = sqrt(abs_distance / acc); //加速时间
			t_dec = t_acc;                    //减速时间
		}
		else                                    // 完整加减速过程无法完成整个运动，需要匀速阶段
		{
			double d_v = abs_distance - 2 * d_b0; //匀速距离
			t_vel = d_v / vel; //匀速段时间
			t_acc = t_b0;
			t_dec = t_b0;
		}
	}

	//---------------------------------------------------------------------------【LFPB 函数】---------------------------------------------------------
	//函数说明：（重载版本）进行两点间LFPB轨迹规划，输入MoveMessage，根据distance,调整acc,vel,dec的符号,并求解t_acc,t_vel,t_dec
	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	void LFPB(const double distance, MM& mm)
	{
		double acc = mm.acc;
		double vel = mm.vel;
		double dec = mm.dec;

		double abs_distance = abs(distance);

		double t_b0 = vel / acc;
		double d_b0 = 0.5*acc*t_b0*t_b0;
		if (2 * d_b0 >= abs_distance)                 // 此时完整加速减速过程行走的距离就足够完成整个运动，不需要匀速阶段
		{
			mm.t_vel = 0;
			mm.t_acc = sqrt(abs_distance / acc);
			mm.t_dec = mm.t_acc;
		}
		else                                    // 完整加减速过程无法完成整个运动，需要匀速阶段
		{
			double d_v = abs_distance - 2 * d_b0;
			mm.t_vel = d_v / vel;
			mm.t_acc = t_b0;
			mm.t_dec = t_b0;
		}

		/*if (distance < 0)
		{
			mm.acc = -acc;
			mm.vel = -vel;
			mm.dec = -dec;
		}*/
	}

	//---------------------------------------------------------------------------【VelocityPlan 函数】---------------------------------------------------------
	//函数说明：根据运动时间，距离以及加速度，减速度规划匀速运动速度vel,以及三个阶段的运动时间,并根据距离调整加速度，速度，减速度的符号
	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	void VelocityPlan(const double t, const double distance, MM& mm)
	{
		double t1=0, t1_prime, t2=0, t2_prime, temp;

		double acc = mm.acc;
		double vel = mm.vel;
		double dec = mm.dec;

		double abs_distance = abs(distance);

		temp = sqrt(acc*acc*t*t - 4 * acc*abs_distance);
		//cout << "temp = " << temp << endl;
		if (temp > 0)                               // 存在匀速运动段
		{
			//t1 = (acc*t + temp) / (2 * acc);
			t1_prime = (acc*t - temp) / (2 * acc);
			//t2 = t - 2 * t1;
			t2_prime = t - 2 * t1_prime;

			if (t1_prime < 0.0001)
			{
				t1_prime = 0;
			}
			if (t2_prime < 0.0001)
			{
				t2_prime = 0;
			}

            mm.vel = acc * t1_prime;

			mm.t_acc = t1_prime;
			mm.t_vel = t2_prime;
			mm.t_dec = t1_prime;
		}
		else
		{
			t1_prime = sqrt(abs_distance / acc);
			t2_prime = t1_prime;
		}

		


		cout << "t_acc = " << mm.t_acc << '\t' << "t_vel = " << mm.t_vel << "t_dec = " << mm.t_dec << endl;
		/*cout << "t1_prime = " << t1_prime << '\t' << "t2_prime = " << t2_prime << endl;
		

		if (t1_prime < 0.0001)
		{
			t1_prime = 0;
		}
		if (t2_prime < 0.0001)
		{
			t2_prime = 0;
		}
		cout << "t1_prime = " << t1_prime << '\t' << "t2_prime = " << t2_prime << endl;
		cout << endl;*/

		if (distance < 0)
		{
			mm.acc = -acc;
			mm.vel = -vel;
			mm.dec = -dec;
		}
	}

	//---------------------------------------------------------------------------【LFPB_plan 函数】---------------------------------------------------------
	//函数说明：根据当前点，时间，速度，加速度等规划下一个点
	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	void LFPB_plan(double& p_now, double& v_now,double& t, const MM& mm, const double T)
	{
		double acc = mm.acc;
		double vel = mm.vel;
		double dec = mm.dec;
		double t_acc = mm.t_acc;
		double t_vel = mm.t_vel;
		double t_dec = mm.t_dec;

		if (t < t_acc)                                      // 加速阶段
		{
			p_now = p_now + v_now * T + 0.5*acc*T*T;
			v_now = v_now + acc * T;
		}
		else if (t < t_acc + t_vel)                       // 匀速阶段
		{
			p_now = p_now + vel * T;
			v_now = v_now;
		}
		else                                                // 减速阶段
		{
			p_now = p_now + v_now * T - 0.5*acc*T*T;
			v_now = v_now - acc * T;
		}
		t += T;
	}

	
}
