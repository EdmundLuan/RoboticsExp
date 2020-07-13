#ifndef PALLETIZE_HPP
#define PALLETIZE_HPP
/*
	Copyright (C) 2020  Edmund Luan, Fangcheng Zhu

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "RobotCmd.h"
#include "PointsCoordinates.h"
#include "HLrobotconfig.h"
#include "MotionPlan.h"
using namespace std;
using namespace Robot_Cmd;

int palletize()
{
    initialization();
    Connect();
    Login();
    Manual();
    Auto();
    Start();
    Retry();
    PowerOn();
    Frame();
    Home();
    Expand();
    PosStruct ST1 = A1P1;
    ST1.z += 10;
    PosStruct ST2 = ST1;
    ST2.z += 10;
    PosStruct ST3 = ST2;
    ST3.z += 10;

    
    vector<string> nameList;// data name list
    //²ð¶â
    Calculation(ST3, PA, nameList);
    Calculation(ST2, PB, nameList);
    Calculation(ST1, PC, nameList);
    Calculation(A1P1, PD, nameList);

    //Âë¶â
    Calculation(PA, A1P1, nameList);
    Calculation(PB, ST1, nameList);
    Calculation(PC, ST2, nameList);
    Calculation(PD, ST3, nameList);

    cout << "\nPress Enter to start palletizing... " << endl;
    cin.get();

    Palletize(ST3, PA, nameList);
    Palletize(ST2, PB, nameList);
    Palletize(ST1, PC, nameList);
    Palletize(A1P1, PD, nameList);

    Palletize(PA, A1P1, nameList);
    Palletize(PB, ST1, nameList);
    Palletize(PC, ST2, nameList);
    Palletize(PD, ST3, nameList);
    cout << "Palletizing Over... Mission Complete!" << endl <<endl;

    //ÏÂµç 
    PowerOff();
    cout << "Power Down... " << endl << endl;

    //¹Ø±ÕÌ×½Ó×Ö
    CloseSocket();
    return 0;
}

#endif