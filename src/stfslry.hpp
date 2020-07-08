
#ifndef STFSLRY_HPP
#define STFSLRY_HPP


#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
#include <string>
#include <vector>
#include <functional>
#include <cstdlib>

#include "custcnst.hpp"
#include "custcls.hpp"
#include "custtype.hpp"
#include "interact.hpp"
#include "glbvar.hpp"
#include "hash.hpp"
#include "acctmngsys.hpp"
/*=============================== CLASS DEFINITION =====================================*/
// Staff
struct _stff {
	// Members
	std::string nm; 	// Name
	std::string adrs; 	// Address
	std::string payRnk;
	_gender gndr; 	// Gender
	_date brthDt; 	// Birth date
	_marriage mrg;  // Marriage status
	_title titl; 	// Title
	unsigned int slry; 		// Salary
	short empBit;
	// Constructor
	_stff() {
		nm = adrs = payRnk = DefaultStr;
		gndr = Dgend;
		mrg = Dmarr;
		titl = Dtitl;
		slry = 0;
		empBit = 1;
	}
	// Compare function
	bool operator < (const _stff rhs) const { return slry < rhs.slry; }
	bool operator > (const _stff rhs) const { return slry > rhs.slry; }

};

// Whole Salary System
struct _salary_system {
	/*=============================== CONSTANT =====================================*/
	// Commands and description for slrySub
	const std::map<std::string, std::string> SlryDscrp;

	/*==================================== MEMBER =====================================*/
	std::vector<_stff> slrySet;
	_accounts slryAccts;
	unsigned long long slrySum;
	long double slryAvr;

	// Constructor
	_salary_system():
		SlryDscrp(_map_gen<std::string, std::string>::createMap( {
		{"input", "Input record(s)"},
		{"disp", "Display all records"},
		{"find", "Search records by pay rank"},
		{"sort", "Sort records by salary"},
		{"rm", "Remove ONE record by name"},
		{"mdfy", "Modify ONE record by name"},
		{"stat", "Display statistical data" },
		{"w", "Save records in files"},
		{"wq", "Quit to main interface after saving records in files"},
		{"q!", "Quit to main interface without saving"},
		{"help", "Display this command list again"}
	})),
	slrySum(0ull),
	slryAvr(0.0l) {}

	/*=============================== MEMBER FUNCTION DECLARATION =====================================*/
	void slrySub(); 	// Salary subsystem commandline interface
	inline void _maintain(); 	// Maintain statistical data
	inline void prntStats();	// Display statistical data
	void printSlry();	// Display the whole slrySet on screen
	void slryIpRl();	// Display input format stipulation and instance
	inline int _insrtSlry(std::istream & );  	// Basic insert operation
	int inputSlry();	// Input salary records
	void _slrySrtRl(); 	// Display sorting manual & instance
	int sortSlry();	// Sort by salary
	inline int _fndSlry(std::ostream& , const std::string& );	// Basic search operation
	inline std::vector<std::vector<_stff>::iterator> _srchNm(const std::string& );  // Search by a name
	int findSlry();	 // Search by pay rank
	int rmSlry(); 		// Remove one salary record
	void _slryMdfyRl(); // Display modification manual & instance
	int mdfySlry(); 	// Modify one salary
	int readSlry(); 	// Read salary records from files
	int writeSlry(); 	// Write salary records into files
	inline void clear(); 		// Clear slrySet
};

/*=============================== VARIABLE =====================================*/

_salary_system slrySys;

/*=============================== FUNCTION DECLARATION =====================================*/
std::istream& operator >> (std::istream&, _stff&);
std::ostream& operator << (std::ostream&, const _stff&);


/*=============================== MEMBER FUNCTION DEFINITION =====================================*/
void _salary_system::slrySub() {
	prntPrtL();
	std::cout << "Staff Salary Manage Subsystem\n" << std::endl;
	// Login
	if (!slryAccts.loggedBit) {
		std::cout << "LOGIN:" << std::endl;
		if (!slryAccts.login()) {
			std::cout << "-slrySub:  Failed to login..." << '\n';
			return;
		}
	}
	// Load from files
	std::cout << "Loading records from files..." << std::endl;
	if (readSlry())
		std::cout << "Records loaded.\n" << std::endl;
	else
		std::cout << "Fail to load records from files.\n" << std::endl;

	prntCmds(SlryDscrp);
	while (1) {
		std::cout << std::setfill(' ') << std::setw(OSWidth) << std::left <<  "-SlrySub:   ";
		std::string str = cptrOne(std::cin);
		if (SlryDscrp.count(str)) { 	// Legitimate command
			// !Please check the SlryDscrp constant before modifying this switch statement!
			switch (hash(str.c_str())) {
			case "input"_hash: inputSlry();
				break;
			case "disp"_hash: printSlry();
				break;
			case "find"_hash: findSlry();
				break;
			case "sort"_hash: sortSlry();
				break;
			case "rm"_hash: rmSlry();
				break;
			case "mdfy"_hash: mdfySlry();
				break;
			case "stat"_hash: prntStats();
				break;
			case "w"_hash: writeSlry();
				break;
			case "wq"_hash:
				if (!writeSlry()) {
					std::cout << "Insist to quit anyway ?\t y/n\n" << std::endl;
					std::string s = cptrOne(std::cin);
					if (s != "y" && s != "Y")
						break;
				}
				clear();
				slryAccts.logout(std::string(rec.dir + "/slryAccts.txt"));
				return;
			case "q!"_hash:
				clear();
				slryAccts.logout(std::string(rec.dir + "/slryAccts.txt"));
				return;
			case "help"_hash: prntCmds(SlryDscrp);
				break;
			default:
				std::cerr << "Sorry, programmer the idiot forgot to put command \"" << str << "\" in list..." << std::endl;
			}
		}
		else { 	// Illegal command input
			std::cout << "-slrySub: " << str << ": command not found" << std::endl;
		}
	}

	std::cerr << "Error occurred in slrySub: unexpected exit" << std::endl;
	slryAccts.logout(rec.dir + "slryAccts.txt");
	return;
}

inline void _salary_system::_maintain() {
	slrySum = 0ull;
	slryAvr = 0.0l;
	if (!slrySet.size())
		return;
	for (auto i : slrySet) {
		slrySum += i.slry;
	}
	slryAvr = (long double)slrySum / slrySet.size();
}

inline void _salary_system:: prntStats() {	// Display statistical data
	prntPrtL();
	int w = 30;
	std::cout << "Statistical Data of Salary Records\n\n";
	std::cout << std::setfill(' ') << std::setw(w) << std::left
	          << "ITEM" << "Figure" << std::endl;
	std::cout << std::setw(w) << std::left
	          << "TOTAL of records" << slrySet.size() << std::endl;
	std::cout << std::setw(w) << std::left
	          << "SUM of salary" << slrySum << std::endl;
	std::cout << std::setw(w) << std::left << std::fixed << std::setprecision(2)
	          << "AVERAGE of salary" << slryAvr << std::endl;
	std::cout << '\n';
}

void _salary_system:: slryIpRl() {
	int w = 50;
	std::cout << "Inputing records.\nHere's input manual and instance:" << std::endl;
	std::cout << std::setfill(' ') << std::setw(w) << std::left
	          << "Entity" << "Description\n"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "Billy King" << "Name"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "M/F/DEFAULT" << "Gender"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "Jun. 1969" << "Date of birth"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "SINGLE/MARRIED/Default" << "Marriage Status"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "JIU RI MU LI" << "Contact Address"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "FULL PROF./ASSOCIATE PROF./LECTURER/" << std::endl
	          << std::setw(w) << std::left
	          << "ASSISTANT LECTURER/ NONE/ Default" << "Title"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "E6" << "Pay Rank"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << 66666 << "Monthly Salary, an unsigned interger"
	          << std::endl;
}

int _salary_system:: inputSlry() {
	prntPrtL();
	slryIpRl();
	std::cout << "\n**REMINDER** Enter \"eoi\" when finish inputing.\n" << std::endl;
	int cnt = 0;
	while (cnt < 1000000) {
		if (_insrtSlry(std::cin)) {
			++cnt;
			std::cout << "\n1 record added.\n" << std::endl;
		}
		else
			break;
	}
	std::cout << "\nTotal " << cnt << " record(s) added.\n" << std::endl;
	_maintain();
	return 1;
}

void _salary_system::printSlry() {
	prntPrtL();
	std::vector<_stff>::iterator i = slrySet.begin();
	if (slrySet.begin() == slrySet.end()) {
		std::cout << "Record Set Empty." << std::endl;
		return;
	}
	std::cout << "\nAll record(s): \n\n";
	for (; i != slrySet.end(); i++) {
		std::cout << (*i);
		std::cout << std::endl;
	}
	if (slrySet.begin() == slrySet.end())
		std::cout << "Record Set Empty." << std::endl;
}

void _salary_system:: _slrySrtRl() {
	std::cout << "Sort Manual" << std::endl;
	std::cout << "sort\t[-g greater]\t[-l less]" << std::endl;
	std::cout << "Specify at most 1 argument, indicating sorting rule. Latter arguments shall be ignored.\
 \nDefult sorting order is \"less\"(i.e. records shall be sorted by salary in an increasing order). "
	          << std::endl;
	std::cout << "Here's an instance:" << std::endl;
	std::cout << "sort\t-g\n" << std::endl;
}

int _salary_system:: sortSlry() {
	prntPrtL();
	_slrySrtRl();
	std::cout << "sort\t-";
	std::vector<std::string> line = cptr(std::cin);
	int flg = 0;
	for (auto s : line) {
		if (s.find('g') != std::string::npos) {
			flg = 1;
			break;
		}
	}
	if (flg)
		sort(slrySet.begin(), slrySet.end(), std::greater<_stff>());
	else
		sort(slrySet.begin(), slrySet.end());
	std::cout << "\nRecords sorted.\n" << std::endl;
	return 1;
}

inline int _salary_system:: _fndSlry(std::ostream &os, const std::string &pR) {
	int cnt = 0;
	for (auto itSlry : slrySet) {
		if (itSlry.payRnk == pR) {
			os << itSlry << std::endl;
			++cnt;
		}
	}
	return cnt;
}

int _salary_system:: findSlry() { 	// If searching operation is not activated, return 0; otherwise a positive integer.
	prntPrtL();
	std::cout << "Search:" << std::endl;
	std::cout << "Search for specific records by Pay Rank." << std::endl;
	std::cout << "Please enter Pay Rank for search in ONE SINGLE LINE.\n" << std::endl;
	std::cout << "Search for:\t";
	std::string str = cptrOne(std::cin);
	if (str.empty()) {
		std::cout << "Nothing to search.\n" << std::endl;
		return 0;
	}
	std::cout << "\nSearching result of Pay Rank \"" << str << "\" :" << std::endl;
	int cnt = _fndSlry(std::cout, str);

	std::cout << "\nTotal " << cnt << " record(s) been found.\n" << std::endl;
	return cnt + 1;
}

inline int _salary_system::_insrtSlry(std::istream &is) {
	_stff tmp;
	is >> tmp;
	if (!tmp.empBit) {
		slrySet.push_back(tmp);
		return 1;
	}
	// Insert Failed!
	return 0;
}

inline std::vector<std::vector<_stff>::iterator> _salary_system::_srchNm(const std::string &kw) {
	std::vector<std::vector<_stff>::iterator> res;
	std::vector<_stff>::iterator itSlry = slrySet.begin();
	for (; itSlry != slrySet.end(); itSlry++ ) {
		if ((*itSlry).nm.find(kw) != std::string::npos || kw.find((*itSlry).nm) != std::string::npos)
			res.push_back(itSlry);
	}
	return res;
}

int _salary_system:: rmSlry() {
	prntPrtL();
	std::cout << "Please input a staff Name.\n" << std::endl;
	std::cout << "rm   -";
	std::string aName = gtLn(std::cin);
	// Find salary record
	std::vector<std::vector<_stff>::iterator> rsltIterators = _srchNm(aName);
	if (!rsltIterators.size()) {
		std::cout << "\nSalary record after name of \"" << aName << "\" not found.\n" << std::endl;
		return 0;
	}
	else {
		std::cout << "\nSearching result:\n" << std::endl;
		std::vector<std::vector<_stff>::iterator>::iterator itRsltIterators = rsltIterators.begin();
		for (; itRsltIterators != rsltIterators.end(); itRsltIterators++)
			std::cout << "*" << itRsltIterators - rsltIterators.begin() << std::endl
			          << *(*itRsltIterators) << std::endl;
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
	// Remove
	int cnt = 0;
	for (auto s : line) {
		unsigned int srlNmb = strtoul(s.c_str(), nullptr, 10);
		if (srlNmb >= 0 && srlNmb < rsltIterators.size()) {
			slrySet.erase(rsltIterators.at(srlNmb));
			++cnt;
		}
	}
	std::cout << "\nTotal " << cnt << " salary record(s) removed.\n" << std::endl;
	_maintain();
	return 1;
}

void _salary_system:: _slryMdfyRl() {
	std::cout << "Modification manual:\n" << std::endl;
	std::cout << "[-*SN serial number]   [-n name]  [-g gender]  [-b birth date]  [-m marriage status]\
   [-a address]   [-t title]   [-r pay rank]   [-s salary]\n";
	std::cout << "\n*Select and modify record(s) one by one. Please follow steps below:\n";
	std::cout << "*<1> Input the SERIAL NUMBER ahead of each record (starting with a '*') in ONE SINGLE LINE to select\
 a record to be modified.\n";
	std::cout << "*<2> Input the above optional ARGUMENTS to specify item(s) to be modified of the selected record\n";
	std::cout << "*<3> Start modifying.\n";
	std::cout << "*Input NOTHING in step<1> to finish modifying.\n";
	std::cout << "\nHere's an instance to modify title, and pay rank\n\nmdfy\t-0\nmdfy\t-0  -tr\n" << std::endl;
}

int _salary_system::mdfySlry() {
	prntPrtL();
	std::cout << "Please input a staff Name.\n" << std::endl;
	std::cout << "mdfy   -";
	std::string aName = gtLn(std::cin);
	// Find salary record
	std::vector<std::vector<_stff>::iterator> rsltIterators = _srchNm(aName);
	if (!rsltIterators.size()) {
		std::cout << "\nSalary record after name of \"" << aName << "\" not found.\n" << std::endl;
		return 0;
	}
	else {
		std::cout << "\nSearching result:\n" << std::endl;
		std::vector<std::vector<_stff>::iterator>::iterator itRsltIterators = rsltIterators.begin();
		for (; itRsltIterators != rsltIterators.end(); itRsltIterators++)
			std::cout << "*" << itRsltIterators - rsltIterators.begin() << std::endl
			          << *(*itRsltIterators) << std::endl;
	}
	// Manual
	_slryMdfyRl();
	// Modify
	while (1) {
		std::cout << "-mdfy\t-";
		std::string strSN = cptrOne(std::cin);
		unsigned int srlNmb = strtoul(strSN.c_str(), nullptr, 10);
		// Input Check
		while (1) {
			if (strSN.empty()) {
				std::cout << "\nModification finished.\n" << std::endl;
				_maintain();
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
		std::cout << "-mdfy\t-" << srlNmb << "  -";
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
			// Marriage status
			if (ss.find('m') != std::string::npos) {
				std::cout << "Current Marriage Status:\n\t" << MrgToStr.at(rsltIterators.at(srlNmb)->mrg) << std::endl;
				std::cout << "New Marriage Status:\n\t";
				rsltIterators.at(srlNmb)->mrg = rcgnz(gtLn(std::cin), StrToMrg);
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
			// Modify Address
			if (ss.find('a') != std::string::npos) {
				std::cout << "Current Address:\n\t" << rsltIterators.at(srlNmb)->adrs << std::endl;
				std::cout << "New Address:\n\t";
				rsltIterators.at(srlNmb)->adrs = gtLn(std::cin);
				if (rsltIterators.at(srlNmb)->adrs.empty())
					rsltIterators.at(srlNmb)->adrs = DefaultStr;
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
			// Modify Salary
			if (ss.find('s') != std::string::npos) {
				std::cout << "Current Salary:\n\t" << rsltIterators.at(srlNmb)->slry << std::endl;
				std::cout << "New Salary:\n\t";
				std::string strSlry = gtLn(std::cin);
				bool flg = true;
				for (auto c : strSlry) {
					if (!isdigit(c)) {
						flg = false;
						break;
					}
				}
				while (!flg) {
					std::cout << "Invalid input! Salary should be a natural number!\n";
					strSlry = gtLn(std::cin);
					flg = true;
					for (auto c : strSlry) {
						if (!isdigit(c)) {
							flg = false;
							break;
						}
					}
				}
				rsltIterators.at(srlNmb)->slry = (unsigned int) strtoul(strSlry.c_str(), nullptr, 10);
			}
		}
		std::cout << "\nNEW version of this salary record:\n" << *(rsltIterators.at(srlNmb)) << std::endl;
	}
	std::cerr << "Error occurred in -mdfy: unexpected exit" << std::endl;
	_maintain();
	return 0;
}

int _salary_system::readSlry() {
	std::ifstream input(rec.dir + "/slry.txt");
	if (input.fail())
		return 0;
	while (!input.eof()) {
		_insrtSlry(input);
	}
	input.close();
	_maintain();
	return 1;
}

int _salary_system:: writeSlry() {
	std::ofstream output(rec.dir + "/slry.txt");
	if (output.fail()) {
		std::cerr << "Writing Error occurred: cannot open output file.\n" << std::endl;
		return 0;
	}
	std::vector<_stff>::iterator i = slrySet.begin();
	for (; i != slrySet.end(); i++) {
		output << (*i);
		output << std::endl;
	}
	output.close();
	std::cout << "Records written into files." << std::endl;
	return 1;
}

inline void _salary_system:: clear() {
	slrySet.clear();
	_maintain();
}

/*=============================== FUNCTION DEFINITION =====================================*/
std::istream& operator >> (std::istream &is, _stff &stfRec) {
	// Name & some checks
	std::vector<std::string> line = cptr(is);
	stfRec.nm = "";
	std::vector<std::string>::iterator i = line.begin();
	for (; i != line.end() && (*i) != ""; i++) {
		if (i != line.begin())
			stfRec.nm += ' ';
		stfRec.nm += (*i);
	}
	if (!stfRec.nm.empty() && stfRec.nm != "eoi") {
		stfRec.empBit = 0;
	}
	else {
		stfRec.nm = DefaultStr;
		return is;
	}
	// Gender
	std::string str = cptrOne(is);
	stfRec.gndr = rcgnz(str, StrToGend);
	// Birth Date
	line = cptr(is, 2);
	stfRec.brthDt.mon = rcgnz(line[0], StrToMon);
	stfRec.brthDt.yr = line[1];
	// Marriage status
	str = cptrOne(is);
	stfRec.mrg = rcgnz(str, StrToMrg);
	// Address
	stfRec.adrs = "";
	line = cptr(is);
	i = line.begin();
	for (; i != line.end() && (*i) != ""; i++) {
		if (i != line.begin())
			stfRec.adrs += ' ';
		stfRec.adrs += (*i);
	}
	if (stfRec.adrs.empty())
		stfRec.adrs = DefaultStr;
	// Title
	line = cptr(is, 2);
	str = line[0] + (!line[1].empty() ? " " + line[1] : "");
	stfRec.titl = rcgnz(str, StrToTitl);
	// Pay Rank
	stfRec.payRnk = cptrOne(is);
	// Salary
	str = cptrOne(is);
	// <cerrno>:: errno == ERANGE --> Out of Range
	stfRec.slry = (unsigned int)strtoul(str.c_str(), nullptr, 10);
	return is;
}
std::ostream& operator << (std::ostream &os, const _stff &stfRec) {
	// Name
	os << stfRec.nm << std::endl;
	// Gender
	os << GendToStr.at(stfRec.gndr) << std::endl;
	// Birth Date
	os << MonToStr.at(stfRec.brthDt.mon) << ' ' << stfRec.brthDt.yr << std::endl;
	// Marriage Status
	os << MrgToStr.at(stfRec.mrg) << std::endl;
	// Address
	os << stfRec.adrs << std::endl;
	// Title
	os << TitlToStr.at(stfRec.titl) << std::endl;
	// Pay Rank
	os << stfRec.payRnk << std::endl;
	// Salary
	os << stfRec.slry << std::endl;
	return os;
}


#endif
