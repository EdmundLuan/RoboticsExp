/*
	Copyright (C) 2020  Edmund Luan

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


/*=================================== MACRO ==============================================*/
#define ENVM_WINDOWS 		// Macro defined when file compiled on WINDOWS platforms

/*======================= STANDARD HEADER ====================================*/
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>

/*=============================== CUSTOM HEADER ======================================*/
#include "interact.hpp"
#include "custcnst.hpp"
#include "custcls.hpp"
#include "glbvar.hpp"

#include "stfinfo.hpp"
#include "stfprof.hpp"
#include "stfslry.hpp"
#include "stfcont.hpp"

//#include "HLrobotconfig.h"
/*================================= CONSTANT ==============================================*/

// Commands and description for main
// Please Please Please remember to add a comma',' after each pair
const std::map<std::string, std::string> MainCmd = _map_gen<std::string, std::string>::createMap({
	// { "info", "Enter Staff Information Manage Subsystem"},
	{ "prof", "Enter Staff Profile Manage Subsystem"},
	// { "slry", "Enter Staff Salary Manage Subsystem"},
	// { "cont", "Enter Staff Contact Manage Subsystem"},
	{ "lice", "Print License"},
	{ "exit", "Exit"},
	{ "help", "Display this command list again" }
});

/*============================ FUNCTION DECLARATION ================================ */
inline void prntLcs();
inline void prntLcsShrt();
/*================================= MAIN =======================================*/

int main() {
	prntPrtL();
	std::cout << "Welcome to PalletizerX V0.1.0 !\n" << std::endl;
	//Copyright information
	std::cout << "Created by Edmund Luan 2020\n" << std::endl;
	// License & Copyright information
	prntLcsShrt();

	prntCmds(MainCmd);
	while (1) {
		std::cout << std::setfill(' ') << std::setw(OSWidth) << std::left << "-main:   ";
		std::string str;
		str = cptrOne(std::cin);
		// !Please check the MainCmd constant before modifying this switch statement!
		switch (hash(str.c_str())) {
		case "cd"_hash: rec.cd();
			break;
		case "sd"_hash: rec.sd();
			break;
		// case "info"_hash: infoSub();
		// 	break;
		case "prof"_hash: profSub();
			break;
		// case "slry"_hash: slrySys.slrySub();
		// 	break;
		// case "cont"_hash: contSys.contSub();
		// 	break;
		case "lice"_hash: prntLcs();
			break;
		case "exit"_hash:
			return 0;
		case "help"_hash: prntCmds(MainCmd);
			break;
		default: std::cout << "-main: " << str << ": command not found" << std::endl;
		}
	}
	return 0;
}

inline void prntLcsShrt() {
	std::cout << "\tCopyright (C) 2020  Edmund Luan\n\
\tThis program comes with ABSOLUTELY NO WARRANTY.\n\
\tThis is free software, and you are welcome to redistribute it\n\
\tunder certain conditions; type 'lice' for details." << std::endl;
}

inline void prntLcs() {
	std::cout << "\
	Copyright (C) 2020  Edmund Luan\n\n\
\tThis program is free software: you can redistribute it and/or modify\n\
\tit under the terms of the GNU General Public License as published by\n\
\tthe Free Software Foundation, either version 3 of the License, or\n\
\t(at your option) any later version.\n\
\n\
\tThis program is distributed in the hope that it will be useful,\n\
\tbut WITHOUT ANY WARRANTY; without even the implied warranty of\n\
\tMERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
\tGNU General Public License for more details.\n\
\n\
\tYou should have received a copy of the GNU General Public License\n\
\talong with this program.  If not, see <http://www.gnu.org/licenses/>. " << std::endl;
}
