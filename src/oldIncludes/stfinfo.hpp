

#ifndef STFINFO_HPP
#define STFINFO_HPP

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

#include "hash.hpp"
#include "interact.hpp"
#include "custcls.hpp"
#include "custtype.hpp"
#include "glbvar.hpp"

/*============================ TYPE/CLASS DEFINITION ================================*/

struct _curriculum {
	std::string curName;					// Curriculm Name
	std::string sem; 					// Semester
	_curr_prop curProp; 	// Curriculum Property
	_efct_grd eff;	 		// Effect Grade

	_curriculum(): curName(DefaultStr), sem(DefaultStr), curProp(Dprop) {}
};

struct _info {
	std::string stfID; 			// Staff ID number
	std::string stfName; 		// Staff name
	_gender gend; 			// Staff gender
	_title titl; 			// Staff title
	_curriculum course[3]; 	// Mainly teaching courses
	unsigned short tScr; 			// Teaching Score
	short empBit; 				// Empty bit

	_info(): stfID(DefaultStr), stfName(DefaultStr), gend(Dgend), titl(Dtitl), tScr(0), empBit(1) {}
};

/*================================== CONSTANT =====================================*/
const std::map<std::string, std::string> InfoCmd = _map_gen<std::string, std::string>::createMap({
	{"input", "Input record(s)"},
	{"disp", "Display all records"},
	{"find", "Search records by NAME or CURRICULUM"},
	{"sort", "Sort records by STAFF ID or TEACHING SCORES"},
	{"ins", "Insert a single record"},
	{"w", "Save records in files"},
	{"wq", "Quit to main interface after saving records in files"},
	{"q!", "Quit to main interface without saving"},
	{"help", "Display this command list again"}
});

/*=================================== VARIABLE ======================================*/
std::vector<_info> infoSet;

/*=========================== FUNCTION DECLARATION =============================*/
std::istream& operator >> (std::istream&, _info&);
std::ostream& operator << (std::ostream&, const _info&);
bool operator < (const _info, const _info);
bool operator > (const _info, const _info);
bool cmpScrG(const _info, const _info); 	// Teaching scores compare function: Greater
bool cmpScrL(const _info, const _info);	 	// Teaching scores compare function: Less
void infoSub(); 	// Info subsystem commandline interface
void printInfo();	// Display the whole infoSet on screen
void inputRule();	// Display input format stipulation and instance
int inputInfo();	// Input several pieces of info
void sortRule(); 	// Display sorting manual & instance
int sortInfo();	// Sort infoSet by staff ID or teaching scores
inline std::vector<_info> _fndInfo(const std::vector<std::string>& );	// Search operation
int findInfo();	// Search info by name or currirulum
inline int _isrtInfo(std::istream&); 	// Insert operation
int insertInfo();	// Insert one single piece of info
int readInfo(); 	// Read info from files
int writeInfo(); 	// Write info into files

/*=========================== FUNCTION DEFINITION =============================*/
void infoSub() {
	std::cout << "----------------- Staff Information Manage Subsystem --------------- \n" << std::endl;
	std::cout << "Loading records from files..." << std::endl;
	if (readInfo())
		std::cout << "Records loaded.\n" << std::endl;
	else
		std::cout << "Fail to load records from files.\n" << std::endl;
	prntCmds(InfoCmd);
	while (1) {
		std::cout << std::setfill(' ') << std::setw(OSWidth) << std::left <<  "-infoSub:   ";
		std::string str;
		str = cptrOne(std::cin);
		// !Please check the InfoCmd constant before modifying this switch statement!
		switch (hash(str.c_str())) {
		case "input"_hash: inputInfo();
			break;
		case "disp"_hash: printInfo();
			break;
		case "find"_hash: findInfo();
			break;
		case "sort"_hash: sortInfo();
			break;
		case "ins"_hash: insertInfo();
			break;
		case "w"_hash: writeInfo();
			break;
		case "wq"_hash: writeInfo(); infoSet.clear();
			return;
		case "q!"_hash: infoSet.clear();
			return;
		case "help"_hash: prntCmds(InfoCmd);
			break;
		default: std::cout << "-infosub: " << str << ": command not found" << std::endl;
		}
	}

	std::cerr << "Error occurred in infoSub: unexpected exit" << std::endl;
	return;
}

bool operator < (const _info x, const _info y) { return x.stfID < y.stfID; }
bool operator > (const _info x, const _info y) { return x.stfID > y.stfID; }
bool cmpScrG(const _info x, const _info y) {
	return x.tScr > y.tScr;
}
bool cmpScrL(const _info x, const _info y) {
	return x.tScr < y.tScr;
}

std::istream& operator >> (std::istream &is, _info &info) {
	info.stfID = cptrOne(is);
	if (info.stfID == "eoi" || info.stfID.empty())
		return is;
	else
		info.empBit = 0;
	info.stfName = gtLn(is);
	if (info.stfName.empty())
		info.stfName = DefaultStr;
	std::string str;
	// Read title
	str = gtLn(is);
	info.titl = rcgnz(str, StrToTitl);
	// Read gender
	str = cptrOne(is);
	info.gend = rcgnz(str, StrToGend);
	//Read Courses
	for (int i = 0; i < 3; ++i) {
		// Name and sem
		info.course[i].curName = gtLn(is);
		info.course[i].sem = gtLn(is);
		// Property
		str = cptrOne(is);
		info.course[i].curProp = rcgnz(str, StrToCurProp);
		// Effect
		str = cptrOne(is);
		info.course[i].eff = rcgnz(str, StrToEfct);
	}
	// Score
	str = cptrOne(is);
	info.tScr = (unsigned short) strtoul(str.c_str(), nullptr, 10);

	return is;
}

std::ostream& operator << (std::ostream & os, const _info & info) {
	// ID and Name
	os << info.stfID << std::endl << info.stfName << std::endl;
	// Gender
	os << GendToStr.at(info.gend) << std::endl;
	std::string str;
	// Title
	os << TitlToStr.at(info.titl) << std::endl;
	// Courses
	for (int i = 0; i < 3; ++i) {
		// Name
		os << info.course[i].curName << std::endl;
		// Semester
		os << '\t' << info.course[i].sem << std::endl;
		// Property
		os << '\t' << CurPropToStr.at(info.course[i].curProp) << std::endl;
		// Effect
		os << '\t' << EfctToStr.at(info.course[i].eff) << std::endl;
	}
	// Score
	os << info.tScr << std::endl;
	return os;
}

void printInfo() {
	std::vector<_info>::iterator i = infoSet.begin();
	if (infoSet.begin() == infoSet.end()) {
		std::cout << "Record Set Empty." << std::endl;
		return;
	}
	std::cout << "\nAll record(s):\n\n";
	for (; i != infoSet.end(); i++) {
		std::cout << (*i);
		std::cout << std::endl;
	}
	std::cout << '\n';
}

void inputRule() {
	int w = 50;
	std::cout << "Inputing records.\nHere's input manual and instance:" << std::endl;
	std::cout << std::setfill(' ') << std::setw(w) << std::left
	          << "Entity" << "Description\n"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "SZ12345678" << "STAFF ID"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "DYING PROGRAMMER" << "NAME"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "FULL PROF./ASSOCIATE PROF./LECTURER/" << std::endl
	          << std::setw(w) << std::left
	          << "ASSISTANT LECTURER/ NONE/ DEFAULT" << "TITLE"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "M/F/DEFAULT" << "GENDER"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "COURSE 1" << "MAINLY TEACHING COURSE 1"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "2019 SPRING" << "SEMESTER OF COURSE 1"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "DEGREE COURSE/NON-DEGREE COURSE/DEFAULT" << "PROPERTY OF COURSE 1"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "EXCELLENT/GOOD/FAIR/LIMITED" << "TEACHING ASSESSMENT OF COURSE 1"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "COURSE 2" << "MAINLY TEACHING COURSE 2"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "2019 SUMMER" << "SEMESTER OF COURSE 2"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "DEGREE COURSE/NON-DEGREE COURSE/DEFAULT" << "PROPERTY OF COURSE 2"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "EXCELLENT/GOOD/FAIR/LIMITED" << "TEACHING ASSESSMENT OF COURSE 1"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "COURSE 3" << "MAINLY TEACHING COURSE 3"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "2019 FALL" << "SEMESTER OF COURSE 3"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "DEGREE COURSE/NON-DEGREE COURSE/DEFAULT" << "PROPERTY OF COURSE 3"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "EXCELLENT/GOOD/FAIR/LIMITED" << "TEACHING ASSESSMENT OF COURSE 3"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "85" << "OVERALL TEACHING SCORE, AN INTEGER BETWEEN 0 AND 100 (BOTH INCLUDED)"
	          << std::endl;
}

int inputInfo() {
	prntPrtL();
	inputRule();
	std::cout << "\nEnter \"eoi\" when finish inputing.\n" << std::endl;
	int cnt = 0;
	while (cnt < 1000000) {
		if (_isrtInfo(std::cin)) {
			std::cout << "\n1 record added.\n" << std::endl;
			++cnt;
		}
		else
			break;
	}
	std::cout << "\nTotal " << cnt << " record(s) added.\n" << std::endl;
	return 1;
}

void sortRule() {
	std::cout << "Sort Manual" << std::endl;
	std::cout << "\n[-i ID]   [-s score]   [-g greater]   [-l less]\n" << std::endl;
	std::cout << "Specify at most 2 arguments, indicating sorting criterion and rule respectively,\
seperated by space characters(tab, space etc.) in ONE single line. Defult sorting argument of criterion is \
\"ID\", and that of rule is \"less\"(sort in an increasing order). Accept the first argument of criterion \
or rule. Latter ambiguous arguments shall be ignored." << std::endl;
	std::cout << "Here's an instance:" << std::endl;
	std::cout << "\nsort  -sg\n" << std::endl;
}

int sortInfo() {
	prntPrtL();
	sortRule();
	std::cout << "sort  -";
	short flag = 0;
	std::string str = gtLn(std::cin, 2);
	for (auto i : str) {
		flag += i == 's' ? 2 : i == 'g' ?  1 : 0;
	}
	switch (flag) {
	case 0: sort(infoSet.begin(), infoSet.end()); break;
	case 1: sort(infoSet.begin(), infoSet.end(), std::greater<_info>()); break;
	case 2: sort(infoSet.begin(), infoSet.end(), cmpScrL); break;
	case 3: sort(infoSet.begin(), infoSet.end(), cmpScrG); break;
	default: std::cerr << "Sorting Error occurred: unexpected rule!" << std::endl;
		return 0;
	}
	std::cout << "\nRecords sorted.\n" << std::endl;
	return 1;
}

inline int _isrtInfo(std::istream &is) {
	_info tmp;
	is >> tmp;
	if (!tmp.empBit) {
		infoSet.push_back(tmp);
		return 1;
	}
	// Insert Failed!
	return 0;
}

int insertInfo() {
	prntPrtL();
	inputRule();
	if (_isrtInfo(std::cin)) {
		sort(infoSet.begin(), infoSet.end(), cmpScrL);
		std::cout << "\n1 record added.\n" << std::endl;
		return 1;
	}
	return 0;
}

inline std::vector<_info> _fndInfo(const std::vector<std::string> &kws) {
	std::vector<_info> res;
	for (auto itInfo : infoSet) {
		for (auto kw : kws) {
			if (itInfo.stfName.find(kw) != std::string::npos || kw.find(itInfo.stfName) != std::string::npos) {
				res.push_back(itInfo);
				continue;
			}
			for (int i = 0; i < 3; ++i) {
				if (itInfo.course[i].curName.find(kw) != std::string::npos || kw.find(itInfo.course[i].curName) != std::string::npos) {
					res.push_back(itInfo);
					break;
				}
			}
		}
	}
	return res;
}

int findInfo() { 	// If searching operation is not activated, return 0; otherwise a positive integer.
	prntPrtL();
	std::cout << "Search:" << std::endl;
	std::cout << "Search for specific records by keywords in NAME of staff or CURRICULUM." << std::endl;
	std::cout << "Please enter keywords for search in ONE single line.\n" << std::endl;
	std::cout << "Search for:     ";
	std::vector<std::string> line = cptr(std::cin);
	std::vector<std::string>::reverse_iterator ritLn = line.rbegin();
	for (; ritLn != line.rend(); ritLn++) {
		if ((*ritLn).empty())
			line.pop_back();
	}
	if (!line.size()) {
		std::cout << "Nothing to search.\n" << std::endl;
		return 0;
	}
	std::cout << "\nSearching result:\n" << std::endl;
	std::vector<_info> rslt = _fndInfo(line);
	for (auto i : rslt) {
		std::cout << i << std::endl;
	}
	std::cout << "Total " << rslt.size() << " record(s) been found.\n" << std::endl;
	return rslt.size() + 1;
}

int readInfo() {
	std::ifstream input(rec.dir + "/info.txt");
	if (input.fail())
		return 0;
	while (!input.eof()) {
		_isrtInfo(input);
	}
	input.close();
	return 1;
}

int writeInfo() {
	std::ofstream output(rec.dir + "/info.txt");
	if (output.fail()) {
		std::cerr << "Writing Error occurred: cannot open output file.\n" << std::endl;
		return 0;
	}
	std::vector<_info>::iterator i = infoSet.begin();
	for (; i != infoSet.end(); i++) {
		output << (*i);
		output << std::endl;
	}
	output.close();
	std::cout << "Records written into files." << std::endl;
	return 1;
}

#endif
