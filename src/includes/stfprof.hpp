
// Point Profile Manage Subsystem
#ifndef STFPROF_HPP
#define STFPROF_HPP

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <functional>
#include <cstdlib>

#include "custcnst.hpp"
#include "custtype.hpp"
#include "interact.hpp"
#include "glbvar.hpp"
#include "hash.hpp"
#include "acctmngsys.hpp"
#include "PointsCoordinates.h"
#include "HLrobotconfig.h"
#include "MotionPlan.h"
/*=============================== CLASS DEFINITION =====================================*/
struct point {
	std::string name;
    PosStruct coordnt;
	short empBit;

	point() {
		name = DefaultStr;
        coordnt = PosStruct(0, 0, 0, 0, 0, 0);
		empBit = 1;
	}

    point(string ss, PosStruct pos) {
        name = ss;
        coordnt = pos;
        empBit = 0;
    }
};

/*=============================== CONSTANT =====================================*/
// Commands and description for profSub
const std::map<std::string, std::string> ProfDscrp = _map_gen<std::string, std::string>::createMap({
	{"input", "Input point(s)"},
	{"disp", "Display all point(s)"},
	{"find", "Search records by keywords"},
	// {"sort", "Sort records by several optional critira"},
	{"rm", "Remove ONE record by point's name"},
	{"mdfy", "Modify ONE record by point's name"},
	// {"w", "Save records in files"},
	// {"wq", "Quit to main interface after saving records in files"},
	{"q!", "Quit to main interface without saving"},
	{"help", "Display this command list again"}
});



/*=============================== VARIABLE =====================================*/
std::vector<point> profSet;
_accounts profAccts;

/*=============================== FUNCTION DELARATION =====================================*/
std::istream& operator >> (std::istream&, PosStruct&);
std::ostream& operator << (std::ostream&, const PosStruct&);

bool cmpNmG(const point, const point); 		// Compare function by name, greater
bool cmpNmL(const point, const point); 		// Compare function by name, less
void profSub(); 	// Profile subsystem commandline interface
void printProf();	// Display the whole profSet on screen
void profInputRule();	// Display input format stipulation and instance
inline int _insrtProf(std::istream & );  	// Basic insert operation
int inputProf();	// Input profiles
void _profSrtRl(); 	// Display sorting manual & instance
inline int _mtch(const std::string& , const std::string& ); 	// Keywords matching
inline std::vector<point> _fndProf(const std::vector<std::string>& );	// Basic search operation
inline std::vector<std::vector<point>::iterator> _srchID(const std::string& );  	// Search for profile with an ID
int findProf();	 // Search for profile
int rmProf(); 		// Remove one profile
void _profMdfyRl(); // Display modification manual & instance
int mdfyProf(); 	// Modify one profile
int readProf(); 	// Read profiles from files
int writeProf(); 	// Write profiles into files

/*=============================== FUNCTION DEFINITION =====================================*/
void profSub() {
	prntPrtL();
	std::cout << "Staff Profile Manage Subsystem\n" << std::endl;
	std::cout << "Loading records from files..." << std::endl;
	if (readProf())
		std::cout << "Records loaded.\n" << std::endl;
	else
		std::cout << "Fail to load records from files.\n" << std::endl;
    
    // Temporary initialize
    profSet.push_back(point("PA", PA));
    profSet.push_back(point("PB", PB));
    profSet.push_back(point("PC", PC));
    profSet.push_back(point("PD", PD));
    profSet.push_back(point("A1P1", A1P1));
    profSet.push_back(point("A1P2", A1P2));
    profSet.push_back(point("A1P1", A2P1));
    profSet.push_back(point("A2P1", A2P2));


	prntCmds(ProfDscrp);
	while (1) {
		std::cout << std::setfill(' ') << std::setw(OSWidth) << std::left <<  "-profSub:   ";
		std::string str = cptrOne(std::cin);
		if (ProfDscrp.count(str)) { 	// Legitimate command
			// !Please check the ProfDscrp constant before modifying this switch statement!
			switch (myhash(str.c_str())) {
			case "input"_hash: inputProf();
				break;
			case "disp"_hash: printProf();
				break;
			case "rm"_hash: rmProf();
				break;
			case "mdfy"_hash: mdfyProf();
				break;
            case "find"_hash: findProf();
                break;
			/*case "w"_hash: writeProf();
				break;
			case "wq"_hash:
				writeProf();
				profSet.clear();
				profAccts.logout(std::string(rec.dir+"/profAccts.txt"));
				return;*/
			case "q!"_hash:
				profSet.clear();
				profAccts.logout(std::string(rec.dir+"/profAccts.txt"));
				return;
			case "help"_hash: prntCmds(ProfDscrp);
				break;
			default:
				std::cerr << "Sorry, programmer the idiot forgot to put command \"" << str << "\" in list..." << std::endl;
			}
		}
		else { 	// Illegal command input
			std::cout << "-profSub: " << str << ": command not found" << std::endl;
		}
	}

	std::cerr << "Error occurred in profSub: unexpected exit" << std::endl;
	return;
}

/*bool operator < (const point lhs, const point rhs) {	return lhs.ID < rhs.ID; }
bool operator > (const point lhs, const point rhs) {	return lhs.ID > rhs.ID; }*/
bool cmpNmL (const point lhs, const point rhs) {	return lhs.name < rhs.name; }
bool cmpNmG (const point lhs, const point rhs) {	return lhs.name > rhs.name; }

std::istream& operator >> (std::istream &is, point &prof) {
    prof.name = cptrOne(is);
    if (prof.name == "eoi") {
        prof.empBit = 1;
        return is;
    }
    prof.coordnt.x = atof(cptrOne(is).c_str());
    prof.coordnt.y = atof(cptrOne(is).c_str());
    prof.coordnt.z = atof(cptrOne(is).c_str());
    prof.coordnt.yaw = atof(cptrOne(is).c_str());
    prof.coordnt.pitch = atof(cptrOne(is).c_str());
    prof.coordnt.roll = atof(cptrOne(is).c_str());
    prof.empBit = 0;
	return is;
}
std::ostream& operator << (std::ostream & os, const point & prof) {
    os << prof.name << std::endl;
	// x, y, z
    os << "\tX=\t" << prof.coordnt.x << std::endl;
    os << "\tY=\t" << prof.coordnt.y << std::endl;
    os << "\tZ=\t" << prof.coordnt.z << std::endl;
	// RPY  
    os << "\tYAW=\t" << prof.coordnt.yaw << std::endl;
    os << "\tPITCH=\t" << prof.coordnt.pitch << std::endl;
    os << "\tROLL=\t" << prof.coordnt.roll << std::endl;
	return os;
}

void profInputRule() {
	int w = 60;
	std::cout << "Inputing records.\nHere's input manual and instance:" << std::endl;
	std::cout << std::setfill(' ') << std::setw(w) << std::left
	          << "Entity" << "Description\n"
	          << std::endl;
    std::cout << std::setw(w) << std::left
        << "Point HaHaHa" << "Name"
        << std::endl;
	std::cout << std::setw(w) << std::left
	          << "1" << "X Coordinate"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "2.2" << "Y Coordinate"
	          << std::endl;
    std::cout << std::setw(w) << std::left
                << "2.3" << "Z Coordinate"
                << std::endl;
    std::cout << std::setw(w) << std::left
        << "180" << "yaw Angle"
        << std::endl;
    std::cout << std::setw(w) << std::left
        << "90" << "pitch Angle"
        << std::endl;
    std::cout << std::setw(w) << std::left
        << "45" << "roll Angle"
        << std::endl;

}

int inputProf() {
	prntPrtL();
	profInputRule();
	std::cout << "\nEnter \"eoi\" when finish inputing.\n" << std::endl;
	int cnt = 0;
	while (cnt < 1000) {
		if (_insrtProf(std::cin)) {
			++cnt;
			std::cout << "\n1 record added.\n" << std::endl;
		}
		else
			break;
	}
	std::cout << "Total " << cnt << " record(s) added.\n" << std::endl;
	return 1;
}

inline int _insrtProf(std::istream &is) {
	point tmp;
	is >> tmp;
	if (!tmp.empBit) {
		profSet.push_back(tmp);
		return 1;
	}
	// Insert Failed!
	return 0;
}

int findProf() { 	// If searching operation is not activated, return 0; otherwise a positive integer.
    
	prntPrtL();
	std::cout << "Search:" << std::endl;
	std::cout << "Search for specific records by keywords in {name}." << std::endl;
	std::cout << "Please enter keywords for search in ONE SINGLE LINE, seperated by space character(s).\n" << std::endl;
	std::cout << "Search for:    ";
	std::vector<std::string> line = cptr(std::cin);
    //for (auto i : line) cout << i << i.size() << endl;
	//std::vector<std::string>::reverse_iterator ritLn = line.rbegin();
    /*
	for (; ritLn != line.end(); ritLn++) {
		if ((*ritLn).empty())
			line.pop_back();
	}*/
    for (int i = line.size() - 1; i >= 0; --i) {
        if (!line.at(i).size())
            line.pop_back();
    }
	if (!line.size()) {
		std::cout << "Nothing to search.\n" << std::endl;
		return 0;
	}
	std::cout << "\nSearching result:\n" << std::endl;
	//int cnt = _fndProf(std::cout, line);
	std::vector<point> rslt = _fndProf(line);
	for (auto i : rslt) {
		std::cout << i << std::endl;
	}
	std::cout << "\nTotal " << rslt.size() << " record(s) been found.\n" << std::endl;
	return rslt.size() + 1;
    return 0;
}

inline int _mtch(const std::string &s1, const std::string &s2) {
	return s2.find(s1) != std::string::npos || s1.find(s2) != std::string::npos;
}
inline std::vector<point> _fndProf(const std::vector<std::string> &kws) {
	std::vector<point> res;
	for (auto itProf : profSet) {
		for (auto itKws : kws) {
            bool match = _mtch(itProf.name, itKws);// || _mtch(itProf.nm, itKws) || _mtch(itProf.sect, itKws) || _mtch(itProf.phone, itKws);
			if (match) {
				res.push_back(itProf);
				break;
			}
		}
	}
	return res;
}

void _profSrtRl() {

}

void printProf() {
	std::cout << '\n';
	std::vector<point>::iterator i = profSet.begin();
	for (; i != profSet.end(); i++) {
		std::cout << (*i);
		std::cout << std::endl;
	}
	if (profSet.begin() == profSet.end())
		std::cout << "Record Set Empty.\n" << std::endl;
}


int rmProf() {/*
	prntPrtL();
	std::cout << "**REMINDER** Administrator authority is necessary for removal operation." << std::endl;
	std::cout << "Please input a point's name.\n" << std::endl;
	std::cout << "rm   -";
	std::string str;
	str = cptrOne(std::cin);
	// Find profile
	std::vector<std::vector<point>::iterator> rsltIterators = _srchID(str);
	if (!rsltIterators.size()) {
		std::cout << "\nProfile not found.\n" << std::endl;
		return 0;
	}
	else {
		std::cout << "\nSearching result:\n" << std::endl;
		std::vector<std::vector<point>::iterator>::iterator itRsltIterators = rsltIterators.begin();
		for (; itRsltIterators != rsltIterators.end(); itRsltIterators++)
			std::cout << "*" << itRsltIterators - rsltIterators.begin() << std::endl
			          << **itRsltIterators << std::endl;
	}
	// Confirm
	std::cout << "\n*Input the above SERIAL NUMBER ahead of each record, seperated by space character(s) to select\
 record(s) to be removed.\n";
	std::cout << "*Input NOTHING to cancel removal.\n" << std::endl;
	std::vector<std::string> line = cptr(std::cin);
	//std::vector<std::string>::reverse_iterator rItLn = line.rbegin();
    for (int i = line.size() - 1; i >= 0; --i) {
        if (!line.at(i).size())
            line.pop_back();
    }
	if (!line.size()) {
		std::cout << "\nRemoval cancelled.\n" << std::endl;
		return 0;
	}
	// Check for authority
	bool flag = false;
	if (!profAccts.loggedBit) {
		std::cout << "Please log in." << std::endl;
		flag = profAccts.login();
	}
	else {
#ifdef ENVM_WINDOWS
		flag = profAccts.chkPswrd(profAccts.logged);
#else
		flag = profAccts.chkPswrdUnix(profAccts.logged);
#endif
	}
	if (!flag) {
		std::cout << "Removal failed.\n" << std::endl;
		return 0;
	}
	// Remove
    
	int cnt = 0;
	for (auto s : line) {
		unsigned int srlNmb = strtoul(s.c_str(), nullptr, 10);
		if (srlNmb >= 0 && srlNmb < rsltIterators.size()) {
			profSet.erase(rsltIterators.at(srlNmb));
			++cnt;
		}
	}
	std::cout << "\nTotal " << cnt << " profile record(s) removed.\n" << std::endl;
    */
	return 1;
}

void _profMdfyRl() {/*
	std::cout << "Modification manual:\n" << std::endl;
	std::cout << "[-x x coordinate]  [-y y coordinate] [-z z coordinate] [-r roll angle] [-p pitch angle] [-ya -yaw]\n";
	std::cout << "\n*Select and modify record(s) one by one. Please follow steps below:\n";
	std::cout << "*<1> Input the SERIAL NUMBER ahead of each record (starting with a '*') in ONE SINGLE LINE to select\
 a record to be modified.\n";
	std::cout << "*<2> Input the above optional ARGUMENTS to specify item(s) to be modified of the selected record\n";
	std::cout << "*<3> Start modifying.\n";
	std::cout << "*Input NOTHING in step<1> to finish modifying.\n";
	std::cout << "\nHere's an instance to modify section, title, and pay rank\n\nmdfy\t-0\nmdfy\t-0  -str\n" << std::endl;*/
}

int mdfyProf() {/*
	prntPrtL();
	std::cout << "**REMINDER** Administrator authority is necessary for modification operation." << std::endl;
	// Check for authority
	bool flag = false;
	if (!profAccts.loggedBit) {
		std::cout << "\nLOGIN:" << std::endl;
		flag = profAccts.login();
	}
	else {
#ifdef ENVM_WINDOWS
		flag = profAccts.chkPswrd(profAccts.logged);
#else
		flag = profAccts.chkPswrdUnix(profAccts.logged);
#endif
	}
	if (!flag) {
		std::cout << "Login failed.\n" << std::endl;
		return 0;
	}
	std::cout << "Please input a staff ID\n" << std::endl;
	std::cout << "mdfy   -";
	std::string str;
	str = cptrOne(std::cin);
	// Find profile
	std::vector<std::vector<point>::iterator> rsltIterators = _srchID(str);
	if (!rsltIterators.size()) {
		std::cout << "\nProfile after ID of \"" << str << "\" not found.\n" << std::endl;
		return 0;
	}
	else {
		std::cout << "\nSearching result:\n" << std::endl;
		std::vector<std::vector<point>::iterator>::iterator itRsltIterators = rsltIterators.begin();
		for (; itRsltIterators != rsltIterators.end(); itRsltIterators++)
			std::cout << "*" << itRsltIterators - rsltIterators.begin() << std::endl
			          << **itRsltIterators << std::endl;
	}
	// Manual
	_profMdfyRl();
	// Modify
	while (1) {
		std::cout << "-mdfy\t-" << str << "  -" ;
		std::string strSN = cptrOne(std::cin);
		unsigned int srlNmb = strtoul(strSN.c_str(), nullptr, 10);
		// Input Check
		while (1) {
			if (strSN.empty()) {
				std::cout << "\nModification finished.\n" << std::endl;
				return 1;
			}
			else if (isdigit(strSN[0]) && srlNmb >= 0  && srlNmb < rsltIterators.size())
				break;
			std::cout << "Invalid serial number!\n" << std::endl;
			std::cout << "-mdfy\t-";
			strSN = cptrOne(std::cin);
			srlNmb = strtoul(strSN.c_str(), nullptr, 10);
		}
		// Start to Modify
		std::cout << "-mdfy\t-" << str << "  -" << srlNmb << "  -";
		std::vector<std::string> line = cptr(std::cin);
		for (auto ss : line) {
			// Modify Name
			if (ss.find('n') != std::string::npos) {
				std::cout << "Current Name:\n\t" << rsltIterators.at(srlNmb)->nm << std::endl;
				std::cout << "New Name:\n\t";
				rsltIterators.at(srlNmb)->nm = gtLn(std::cin);
				if (rsltIterators.at(srlNmb)->nm.empty())
					rsltIterators.at(srlNmb)->nm = DefaultStr;
			}
			// Gender
			if (ss.find('g') != std::string::npos) {
				std::cout << "Current Gender:\n\t" << GendToStr.at(rsltIterators.at(srlNmb)->gndr) << std::endl;
				std::cout << "New Gender:\n\t";
				rsltIterators.at(srlNmb)->gndr = rcgnz(gtLn(std::cin), StrToGend);
			}
			// Birth date
			if (ss.find('b') != std::string::npos) {
				std::cout << "Current Birth Date:\n\t" << MonToStr.at(rsltIterators.at(srlNmb)->brthDt.mon) << ' '
				          << rsltIterators.at(srlNmb)->brthDt.yr << std::endl;
				std::cout << "Birth Date:\n\t";
				std::vector<std::string> lline = cptr(std::cin, 2);
				rsltIterators.at(srlNmb)->brthDt.mon = rcgnz(lline[0], StrToMon);
				if (lline[1] > "1899" && lline[1] < "2020")
					rsltIterators.at(srlNmb)->brthDt.yr = lline[1];
			}
			// Modify Section
			if (ss.find('s') != std::string::npos) {
				std::cout << "Current Section:\n\t" << rsltIterators.at(srlNmb)->sect << std::endl;
				std::cout << "New Section:\n\t";
				rsltIterators.at(srlNmb)->sect = gtLn(std::cin);
				if (rsltIterators.at(srlNmb)->sect.empty())
					rsltIterators.at(srlNmb)->sect = DefaultStr;
			}
			// Title
			if (ss.find('t') != std::string::npos) {
				std::cout << "Current Title:\n\t" << TitlToStr.at(rsltIterators.at(srlNmb)->titl) << std::endl;
				std::cout << "New Title:\n\t";
				rsltIterators.at(srlNmb)->titl = rcgnz(gtLn(std::cin), StrToTitl);
			}
			// Modify Pay Rank
			if (ss.find('r') != std::string::npos) {
				std::cout << "Current Pay Rank:\n\t" << rsltIterators.at(srlNmb)->payRnk << std::endl;
				std::cout << "New Pay Rank:\n\t";
				rsltIterators.at(srlNmb)->payRnk = gtLn(std::cin);
				if (rsltIterators.at(srlNmb)->payRnk.empty())
					rsltIterators.at(srlNmb)->payRnk = DefaultStr;
			}
			// Modify Phone Number
			if (ss.find('p') != std::string::npos) {
				std::cout << "Current Phone Number:\n\t" << rsltIterators.at(srlNmb)->phone << std::endl;
				std::cout << "New Phone Number:\n\t";
				rsltIterators.at(srlNmb)->phone = gtLn(std::cin);
				if (rsltIterators.at(srlNmb)->phone.empty())
					rsltIterators.at(srlNmb)->phone = DefaultStr;
			}
		}
		std::cout << "\nNEW version of this profile record:\n\n" << *(rsltIterators.at(srlNmb)) << std::endl;
	}
	std::cerr << "Error occurred in -mdfy: unexpected exit" << std::endl;*/
	return 0;
}

int readProf() {/*
	std::ifstream input(rec.dir + "/prof.txt");
	if (input.fail())
		return 0;
	while (!input.eof()) {
		_insrtProf(input);
	}
	input.close();*/
	return 1;
}

int writeProf() {/*
	std::ofstream output(rec.dir + "/prof.txt");
	if (output.fail()) {
		std::cerr << "Writing Error occurred: cannot open output file.\n" << std::endl;
		return 0;
	}
	std::vector<point>::iterator i = profSet.begin();
	for (; i != profSet.end(); i++) {
		output << (*i);
		output << std::endl;
	}
	output.close();
	std::cout << "Records written into files." << std::endl;*/
	return 1;
}

#endif
