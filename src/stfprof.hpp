

// Staff Profile Manage Subsystem
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
/*=============================== CLASS DEFINITION =====================================*/
struct _staff {
	std::string ID;
	std::string nm;
	_gender gndr;
	_date brthDt;
	unsigned short age; 	// This is idiot, it's absolutely redundant.
	std::string sect;
	_title titl;
	std::string payRnk;
	std::string phone;
	short empBit;

	_staff() {
		ID = nm = sect = payRnk = phone = DefaultStr;
		gndr = Dgend;
		titl = Dtitl;
		age = 0;
		empBit = 1;
	}
};

/*=============================== CONSTANT =====================================*/
// Commands and description for profSub
const std::map<std::string, std::string> ProfDscrp = _map_gen<std::string, std::string>::createMap({
	{"input", "Input record(s)"},
	{"disp", "Display all records"},
	{"find", "Search records by keywords"},
	{"sort", "Sort records by several optional critira"},
	{"rm", "Remove ONE record by staff ID"},
	{"mdfy", "Modify ONE record by staff ID"},
	{"w", "Save records in files"},
	{"wq", "Quit to main interface after saving records in files"},
	{"q!", "Quit to main interface without saving"},
	{"help", "Display this command list again"}
});



/*=============================== VARIABLE =====================================*/
std::vector<_staff> profSet;
_accounts profAccts;

/*=============================== FUNCTION DELARATION =====================================*/
std::istream& operator >> (std::istream&, _staff&);
std::ostream& operator << (std::ostream&, const _staff&);
bool operator < (const _staff, const _staff); 	// Overloaded compare function by ID, less
bool operator > (const _staff, const _staff); 	// Overloaded compare function by ID, greater
bool cmpNmG(const _staff, const _staff); 		// Compare function by name, greater
bool cmpNmL(const _staff, const _staff); 		// Compare function by name, less
void profSub(); 	// Profile subsystem commandline interface
void printProf();	// Display the whole profSet on screen
void profInputRule();	// Display input format stipulation and instance
inline int _insrtProf(std::istream & );  	// Basic insert operation
int inputProf();	// Input profiles
void _profSrtRl(); 	// Display sorting manual & instance
int sortProf();	// Sort profSet
inline int _mtch(const std::string& , const std::string& ); 	// Keywords matching
inline std::vector<_staff> _fndProf(const std::vector<std::string>& );	// Basic search operation
inline std::vector<std::vector<_staff>::iterator> _srchID(const std::string& );  	// Search for profile with an ID
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
	prntCmds(ProfDscrp);
	while (1) {
		std::cout << std::setfill(' ') << std::setw(OSWidth) << std::left <<  "-profSub:   ";
		std::string str = cptrOne(std::cin);
		if (ProfDscrp.count(str)) { 	// Legitimate command
			// !Please check the ProfDscrp constant before modifying this switch statement!
			switch (hash(str.c_str())) {
			case "input"_hash: inputProf();
				break;
			case "disp"_hash: printProf();
				break;
			case "find"_hash: findProf();
				break;
			case "sort"_hash: sortProf();
				break;
			case "rm"_hash: rmProf();
				break;
			case "mdfy"_hash: mdfyProf();
				break;
			case "w"_hash: writeProf();
				break;
			case "wq"_hash:
				writeProf();
				profSet.clear();
				profAccts.logout(std::string(rec.dir+"/profAccts.txt"));
				return;
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

bool operator < (const _staff lhs, const _staff rhs) {	return lhs.ID < rhs.ID; }
bool operator > (const _staff lhs, const _staff rhs) {	return lhs.ID > rhs.ID; }
bool cmpNmL (const _staff lhs, const _staff rhs) {	return lhs.nm < rhs.nm; }
bool cmpNmG (const _staff lhs, const _staff rhs) {	return lhs.nm > rhs.nm; }

std::istream& operator >> (std::istream &is, _staff &prof) {
	// ID & some checks
	prof.ID = cptrOne(is);
	if (!prof.ID.empty() && prof.ID != "eoi" ) {
		prof.empBit = 0;
	}
	else
		return is;
	// Name
	prof.nm = "";
	std::vector<std::string> line = cptr(is);
	std::vector<std::string>::iterator i = line.begin();
	for (; i != line.end() && (*i) != ""; i++) {
		if (i != line.begin())
			prof.nm += ' ';
		prof.nm += (*i);
	}
	if (prof.nm.empty())
		prof.nm = DefaultStr;
	// Gender
	std::string str = cptrOne(is);
	prof.gndr = rcgnz(str, StrToGend);
	// Birth Date
	line = cptr(is, 2);
	prof.brthDt.mon = rcgnz(line[0], StrToMon);
	prof.brthDt.yr = line[1];
	// Age
	str = cptrOne(is);
	prof.age = (unsigned short)strtoul(str.c_str(), nullptr, 10);
	// Section
	prof.sect = "";
	line = cptr(is);
	i = line.begin();
	for (; i != line.end() && (*i) != ""; i++) {
		if (i != line.begin())
			prof.sect += ' ';
		prof.sect += (*i);
	}
	if (prof.sect.empty())
		prof.sect = DefaultStr;
	// Title
	line = cptr(is, 2);
	str = line[0] + (!line[1].empty() ? " " + line[1] : "");
	prof.titl = rcgnz(str, StrToTitl);
	// Pay Rank
	prof.payRnk = cptrOne(is);
	// Phone number
	prof.phone = "";
	line = cptr(is);
	i = line.begin();
	for (; i != line.end() && (*i) != ""; i++) {
		if (i != line.begin())
			prof.phone += ' ';
		prof.phone += (*i);
	}
	if (prof.phone.empty())
		prof.phone = DefaultStr;

	return is;
}
std::ostream& operator << (std::ostream & os, const _staff & prof) {
	// ID and Name
	os << prof.ID << std::endl << prof.nm << std::endl;
	// Gender
	os << GendToStr.at(prof.gndr) << std::endl;
	// Birth Date
	os << MonToStr.at(prof.brthDt.mon) << ' ' << prof.brthDt.yr << std::endl;
	// Age
	os << prof.age << std::endl;
	// Section
	os << prof.sect << std::endl;
	// Title
	os << TitlToStr.at(prof.titl) << std::endl;
	// Pay Rank
	os << prof.payRnk << std::endl;
	// Phone number
	os << prof.phone << std::endl;
	return os;
}

void profInputRule() {
	int w = 60;
	std::cout << "Inputing records.\nHere's input manual and instance:" << std::endl;
	std::cout << std::setfill(' ') << std::setw(w) << std::left
	          << "Entity" << "Description\n"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "SZ12345678" << "Staff ID"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "DYING PROGRAMMER" << "Name"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "M/F/DEFAULT" << "Gender"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "Jun. 1989" << "Date of birth"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "30" << "Age"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "School of Computer Science and Technology" << "Section belong to"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "FULL PROF./ASSOCIATE PROF./LECTURER/" << std::endl
	          << std::setw(w) << std::left
	          << "ASSISTANT LECTURER/ NONE/ DEFAULT" << "Title"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "6" << "Pay Rank"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "13666666666" << "Phone number"
	          << std::endl;
}

int inputProf() {
	prntPrtL();
	profInputRule();
	std::cout << "\nEnter \"eoi\" when finish inputing.\n" << std::endl;
	int cnt = 0;
	while (cnt < 1000000) {
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
	_staff tmp;
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
	std::cout << "Search for specific records by keywords in {name, ID, section, phone number}" << std::endl;
	std::cout << "Please enter keywords for search in ONE SINGLE LINE, seperated by space character(s).\n" << std::endl;
	std::cout << "Search for:    ";
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
	//int cnt = _fndProf(std::cout, line);
	std::vector<_staff> rslt = _fndProf(line);
	for (auto i : rslt) {
		std::cout << i << std::endl;
	}
	std::cout << "\nTotal " << rslt.size() << " record(s) been found.\n" << std::endl;
	return rslt.size() + 1;
}

inline int _mtch(const std::string &s1, const std::string &s2) {
	return s2.find(s1) != std::string::npos || s1.find(s2) != std::string::npos;
}
inline std::vector<_staff> _fndProf(const std::vector<std::string> &kws) {
	std::vector<_staff> res;
	for (auto itProf : profSet) {
		for (auto itKws : kws) {
			bool match = _mtch(itProf.ID, itKws) || _mtch(itProf.nm, itKws) || _mtch(itProf.sect, itKws) || _mtch(itProf.phone, itKws);
			if (match) {
				res.push_back(itProf);
				break;
			}
		}
	}
	return res;
}

void _profSrtRl() {
	std::cout << "Sort Manual" << std::endl;
	std::cout << "[-i ID]	[-n name]	 [-g greater]	[-l less]" << std::endl;
	std::cout << "Specify at most 2 arguments, indicating sorting rule and order respectively,\
 seperated by space character(s) in ONE single LINE. Accept the first 2 arguments. Latter or latter\
 ambiguous arguments shall be ignored. Defult sorting rule is \"ID\", and that of order\
 is \"less\" (i.e. records shall be sorted by ID in an increasing order ). " << std::endl;
	std::cout << "Here's an instance:" << std::endl;
	std::cout << "-n  -g\n" << std::endl;
}

int sortProf() {
	prntPrtL();
	_profSrtRl();
	std::cout << "sort  ";
	std::vector<std::string> line = cptr(std::cin, 2);
	int flag = 0;
	for (auto i : line) {
		flag += i == "-n" ? 2 : i == "-g" ?  1 : 0;
	}
	switch (flag) {
	case 0: sort(profSet.begin(), profSet.end()); break;
	case 1: sort(profSet.begin(), profSet.end(), std::greater<_staff>()); break;
	case 2: sort(profSet.begin(), profSet.end(), cmpNmL); break;
	case 3: sort(profSet.begin(), profSet.end(), cmpNmG); break;
	default: std::cerr << "Sorting Error occurred: unexpected rule!" << std::endl;
		return 0;
	}
	std::cout << "\nRecords sorted.\n" << std::endl;
	return 1;
}

void printProf() {
	std::cout << '\n';
	std::vector<_staff>::iterator i = profSet.begin();
	for (; i != profSet.end(); i++) {
		std::cout << (*i);
		std::cout << std::endl;
	}
	if (profSet.begin() == profSet.end())
		std::cout << "Record Set Empty.\n" << std::endl;
}

inline std::vector<std::vector<_staff>::iterator> _srchID(const std::string &str) {
	std::vector<std::vector<_staff>::iterator> res;
	std::vector<_staff>::iterator itProf = profSet.begin();
	for (; itProf != profSet.end(); itProf++ ) {
		if ((*itProf).ID == str)
			res.push_back(itProf);
	}
	return res;
}

int rmProf() {
	prntPrtL();
	std::cout << "**REMINDER** Administrator authority is necessary for removal operation." << std::endl;
	std::cout << "Please input a staff ID.\n" << std::endl;
	std::cout << "rm   -";
	std::string str;
	str = cptrOne(std::cin);
	// Find profile
	std::vector<std::vector<_staff>::iterator> rsltIterators = _srchID(str);
	if (!rsltIterators.size()) {
		std::cout << "\nProfile not found.\n" << std::endl;
		return 0;
	}
	else {
		std::cout << "\nSearching result:\n" << std::endl;
		std::vector<std::vector<_staff>::iterator>::iterator itRsltIterators = rsltIterators.begin();
		for (; itRsltIterators != rsltIterators.end(); itRsltIterators++)
			std::cout << "*" << itRsltIterators - rsltIterators.begin() << std::endl
			          << **itRsltIterators << std::endl;
	}
	// Confirm
	std::cout << "\n*Input the above SERIAL NUMBER ahead of each record, seperated by space character(s) to select\
 record(s) to be removed.\n";
	std::cout << "*Input NOTHING to cancel removal.\n" << std::endl;
	std::vector<std::string> line = cptr(std::cin);
	std::vector<std::string>::reverse_iterator rItLn = line.rbegin();
	for (; rItLn != line.rend(); rItLn++) {
		if ((*rItLn).empty())
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
	return 1;
}

void _profMdfyRl() {
	std::cout << "Modification manual:\n" << std::endl;
	std::cout << "[-*s serial number]   [-n name]   [-g gender]  [-b birth date]  [-s section]  [-t title]\
 [-r pay rank]  [-p phone]\n";
	std::cout << "\n*Select and modify record(s) one by one. Please follow steps below:\n";
	std::cout << "*<1> Input the SERIAL NUMBER ahead of each record (starting with a '*') in ONE SINGLE LINE to select\
 a record to be modified.\n";
	std::cout << "*<2> Input the above optional ARGUMENTS to specify item(s) to be modified of the selected record\n";
	std::cout << "*<3> Start modifying.\n";
	std::cout << "*Input NOTHING in step<1> to finish modifying.\n";
	std::cout << "\nHere's an instance to modify section, title, and pay rank\n\nmdfy\t-0\nmdfy\t-0  -str\n" << std::endl;
}

int mdfyProf() {
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
	std::vector<std::vector<_staff>::iterator> rsltIterators = _srchID(str);
	if (!rsltIterators.size()) {
		std::cout << "\nProfile after ID of \"" << str << "\" not found.\n" << std::endl;
		return 0;
	}
	else {
		std::cout << "\nSearching result:\n" << std::endl;
		std::vector<std::vector<_staff>::iterator>::iterator itRsltIterators = rsltIterators.begin();
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
	std::cerr << "Error occurred in -mdfy: unexpected exit" << std::endl;
	return 0;
}

int readProf() {
	std::ifstream input(rec.dir + "/prof.txt");
	if (input.fail())
		return 0;
	while (!input.eof()) {
		_insrtProf(input);
	}
	input.close();
	return 1;
}

int writeProf() {
	std::ofstream output(rec.dir + "/prof.txt");
	if (output.fail()) {
		std::cerr << "Writing Error occurred: cannot open output file.\n" << std::endl;
		return 0;
	}
	std::vector<_staff>::iterator i = profSet.begin();
	for (; i != profSet.end(); i++) {
		output << (*i);
		output << std::endl;
	}
	output.close();
	std::cout << "Records written into files." << std::endl;
	return 1;
}

#endif
