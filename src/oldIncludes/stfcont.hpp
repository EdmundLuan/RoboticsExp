

#ifndef STFCONT_HPP
#define STFCONT_HPP

#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
#include <string>
#include <vector>
#include <functional>

#include "custcnst.hpp"
#include "custcls.hpp"
#include "custtype.hpp"
#include "interact.hpp"
#include "glbvar.hpp"
#include "hash.hpp"
#include "acctmngsys.hpp"
/*=============================== CLASS DEFINITION =====================================*/
// Contact
struct _contact {
	// Members
	std::string nm; 	// Name
	std::string phnmb;  // Phone number
	std::string adrs; 	// Address
	std::string rmk; 	// Remarks
	short empBit;
	// Constructor
	_contact(): nm(DefaultStr), phnmb(DefaultStr), adrs(DefaultStr), rmk(DefaultStr), empBit(1) {}
	// Compare function (by name)
	bool operator < (const _contact rhs) const { return nm < rhs.nm; }
	bool operator > (const _contact rhs) const { return nm > rhs.nm; }
};

// Whole Contacts System
struct _contacts_system {
	/*=============================== CONSTANT =====================================*/
	// Commands and description for contSub
	const std::map<std::string, std::string> contDscrp;
	/*============================= MEMBER ===============================*/
	std::vector<_contact> contSet;
	// Constructor
	_contacts_system():
		contDscrp(_map_gen<std::string, std::string>::createMap( {
		{"input", "Input record(s)"},
		{"disp", "Display all records"},
		{"find", "Search records by Name or Phone Number"},
		{"sort", "Sort records by Name or Phone Number"},
		{"rm", "Remove records by Name or Phone Number"},
		{"mdfy", "Modify records by Name or Phone Number"},
		{"w", "Save records in files"},
		{"wq", "Quit to main interface after saving records in files"},
		{"q!", "Quit to main interface without saving"},
		{"help", "Display this command list again"}
	})) {};

	/*=================== MEMBER FUNCTION DECLARATION ===================*/
	void contSub(); 	// Contacts subsystem commandline interface
	static bool cmpPNG(const _contact lhs, const _contact rhs) {return lhs.phnmb > rhs.phnmb;}
	static bool cmpPNL(const _contact lhs, const _contact rhs) {return lhs.phnmb < rhs.phnmb;}
	void printCont();	// Display the whole contSet on screen
	void contIpRl();	// Display input format stipulation and instance
	inline int _insrtCont(std::istream & );  	// Basic insert operation
	int inputCont();	// Input contact records
	void _contSrtRl(); 	// Display sorting manual & instance
	int sortCont();	// Sort by name or phone number
	inline int _mtch(const std::string& , const std::string& ); 		// Substring matching
	inline std::vector<_contact> _fndCont (const std::vector<std::string>& );// Basic search operation
	inline std::vector<_contact> _fndCont (const std::vector<std::string>&, std::vector<std::vector<_contact>::iterator>& );
	int findCont();	 // Search by name or phone number
	int rmCont(); 		// Remove contact records
	void _contMdfyRl(); // Display modification manual & instance
	int mdfyCont(); 	// Modify contacts
	int readCont(); 	// Read contact records from files
	int writeCont(); 	// Write contact records into files
	inline void clear(); // Clear contSet
};

/*==================================== VARIABLE =======================================*/

_contacts_system contSys;

/*================================= FUNCTION DECLARATION =====================================*/
std::istream& operator >> (std::istream&, _contact&);
std::ostream& operator << (std::ostream&, const _contact&);


/*================================ MEMBER FUNCTION DEFINITION =====================================*/
void _contacts_system::contSub() {
	prntPrtL();
	std::cout << "Staff Contacts Manage Subsystem\n" << std::endl;
	// Load from files
	std::cout << "Loading records from files..." << std::endl;
	if (readCont())
		std::cout << "Records loaded.\n" << std::endl;
	else
		std::cout << "Fail to load records from files.\n" << std::endl;

	prntCmds(contDscrp);
	while (1) {
		std::cout << std::setfill(' ') << std::setw(OSWidth) << std::left <<  "-contSub:   ";
		std::string str = cptrOne(std::cin);
		if (contDscrp.count(str)) { 	// Legitimate command
			// !Please check the contDscrp constant before modifying this switch statement!
			switch (hash(str.c_str())) {
			case "input"_hash: inputCont();
				break;
			case "disp"_hash: printCont();
				break;
			case "find"_hash: findCont();
				break;
			case "sort"_hash: sortCont();
				break;
			case "rm"_hash: rmCont();
				break;
			case "mdfy"_hash: mdfyCont();
				break;
			case "w"_hash: writeCont();
				break;
			case "wq"_hash:
				if (!writeCont()) {
					std::cout << "Insist to quit anyway ?\t y/n\n" << std::endl;
					std::string s = cptrOne(std::cin);
					if (s != "y" && s != "Y")
						break;
				}
				clear();
				return;
			case "q!"_hash:
				clear();
				return;
			case "help"_hash: prntCmds(contDscrp);
				break;
			default:
				std::cerr << "Sorry, programmer the idiot forgot to put command \"" << str << "\" in list..." << std::endl;
			}
		}
		else { 	// Illegal command input
			std::cout << "-contSub: " << str << ": command not found" << std::endl;
		}
	}

	std::cerr << "Error occurred in contSub: unexpected exit" << std::endl;
	return;
}

void _contacts_system::printCont() {
	prntPrtL();
	std::vector<_contact>::iterator i = contSet.begin();
	if (contSet.begin() == contSet.end()) {
		std::cout << "Record Set Empty." << std::endl;
		return;
	}
	std::cout << "\nAll record(s): \n\n";
	for (; i != contSet.end(); i++) {
		std::cout << (*i);
		std::cout << std::endl;
	}
	if (contSet.begin() == contSet.end())
		std::cout << "Record Set Empty." << std::endl;
}

void _contacts_system:: contIpRl() {
	int w = 50;
	std::cout << "Inputing records.\nHere's input manual and instance:" << std::endl;
	std::cout << std::setfill(' ') << std::setw(w) << std::left
	          << "Entity" << "Description\n"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "Billy Wong" << "Name"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "18812345678" << "Phone Number"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "XIN RI MU LI" << "Contact Address"
	          << std::endl;
	std::cout << std::setw(w) << std::left
	          << "Changed the boss of the gym." << "Remarks, less than 140 words"
	          << std::endl;
}

int _contacts_system:: inputCont() {
	prntPrtL();
	contIpRl();
	std::cout << "\n**REMINDER** Enter \"eoi\" when finish inputing.\n" << std::endl;
	int cnt = 0;
	while (cnt < 1000000) {
		if (_insrtCont(std::cin)) {
			++cnt;
			std::cout << "\n1 record added.\n" << std::endl;
		}
		else
			break;
	}
	std::cout << "\nTotal " << cnt << " record(s) added.\n" << std::endl;
	return 1;
}

inline int _contacts_system::_insrtCont(std::istream &is) {
	_contact tmp;
	is >> tmp;
	if (!tmp.empBit) {
		contSet.push_back(tmp);
		return 1;
	}
	// Insert Failed!
	return 0;
}

void _contacts_system:: _contSrtRl() {
	std::cout << "Sort Manual" << std::endl;
	std::cout << "\nsort\t[-g greater]\t[-l less]\t[-n name]\t[-p phone number]\n" << std::endl;
	std::cout << "*Specify at most 2 arguments, indicating sorting rule and order.\n*Extra or latter ambiguous arguments\
 shall be ignored. \n*Defult sorting order is \"less\" and that of rule is \"name\" (i.e. records shall be sorted in an\
 increasing order by name). "
	          << std::endl;
	std::cout << "\nHere's an instance:" << std::endl;
	std::cout << "sort\t-pg\n" << std::endl;
}

int _contacts_system:: sortCont() {
	prntPrtL();
	_contSrtRl();
	std::cout << "sort\t-";
	std::string line = gtLn(std::cin, 2);
	int fRl = 0, fOd = 0, flag = 0;
	for (auto c : line) {
		if (c == 'g' && !fOd) {
			flag += 1;
			fOd = 1;
		}
		else if (c == 'l' && !fOd) fOd = 1;
		else if (c == 'n' && !fRl) fRl = 1;
		else if (c == 'p' && !fRl) {
			fRl = 1;
			flag += 2;
		}
	}
	switch (flag) {
	case 0: sort(contSet.begin(), contSet.end()); break;
	case 1: sort(contSet.begin(), contSet.end(), std::greater<_contact>()); break;
	case 2: sort(contSet.begin(), contSet.end(), cmpPNL); break;
	case 3: sort(contSet.begin(), contSet.end(), cmpPNG); break;
	default: std::cerr << "Sorting Error occurred: unexpected rule!" << std::endl;
		return 0;
	}
	std::cout << "\nRecords sorted.\n" << std::endl;
	return 1;
}

inline int _contacts_system::_mtch(const std::string &s1, const std::string &s2) {
	return s2.find(s1) != std::string::npos || s1.find(s2) != std::string::npos;
}

inline std::vector<_contact>  _contacts_system:: _fndCont(const std::vector<std::string> &kws) {
	std::vector<_contact> res;
	for (auto cont : contSet) {
		for (auto kwrd : kws)
			if (_mtch(kwrd, cont.nm) || _mtch(kwrd, cont.phnmb)) {
				res.push_back(cont);
				break;
			}
	}
	return res;
}

inline std::vector<_contact>  _contacts_system:: _fndCont(const std::vector<std::string> &kws, std::vector<std::vector<_contact>::iterator> &itRslts) {
	std::vector<_contact> res;
	std::vector<_contact>::iterator itCont = contSet.begin();
	for (; itCont != contSet.end(); itCont++) {
		for (auto kwrd : kws)
			if (_mtch(kwrd, itCont->nm) || _mtch(kwrd, itCont->phnmb)) {
				res.push_back(*itCont);
				itRslts.push_back(itCont);
				break;
			}
	}
	return res;
}

int _contacts_system:: findCont() { 	// If searching operation is not activated, return 0; otherwise a positive integer.
	prntPrtL();
	std::cout << "Search:" << std::endl;
	std::cout << "*Search for specific record(s) by NAME or PHONE NUMBER." << std::endl;
	std::cout << "*Please enter keyword(s) in ONE SINGLE LINE, seperated by space character(s).\n" << std::endl;
	std::cout << "Search for:\t";
	std::vector<std::string> line = cptr(std::cin);
	std::vector<std::string>::reverse_iterator itLn = line.rbegin();
	for (; itLn != line.rend(); itLn++) {
		if ((*itLn).empty())
			line.pop_back();
	}
	if (!line.size()) {
		std::cout << "Nothing to search.\n" << std::endl;
		return 0;
	}
	// Searching operation activated
	std::vector<_contact> rslt = _fndCont(line);
	if (rslt.size()) {
		std::cout << "\nSearching result:\n" << std::endl;
		for (auto cont : rslt)
			std::cout << cont << std::endl;
	}
	std::cout << "\nTotal " << rslt.size() << " record(s) been found.\n" << std::endl;
	return rslt.size() + 1;
}

int _contacts_system:: rmCont() {
	prntPrtL();
	std::cout << "Please input keywords within a NAME or a PHONE NUMBER.\n" << std::endl;
	std::cout << "rm   -find\t";
	std::vector<std::string> line = cptr(std::cin);
	std::vector<std::string>::reverse_iterator i = line.rbegin();
	for (; i != line.rend(); i++) {
		if ((*i).empty())
			line.pop_back();
	}
	if (!line.size()) {
		std::cout << "Nothing to search.\n" << std::endl;
		return 0;
	}
	// Find contact record
	std::vector<std::vector<_contact>::iterator> rsltIterators;
	std::vector<_contact> rslt = _fndCont(line, rsltIterators);
	if (!rslt.size()) {
		std::cout << "\nContact not found.\n" << std::endl;
		return 0;
	}
	else {
		std::cout << "\nSearching result:\n" << std::endl;
		std::vector<_contact>::iterator itRslt = rslt.begin();
		for (; itRslt != rslt.end(); itRslt++)
			std::cout << "*" << itRslt - rslt.begin() << std::endl << *itRslt << std::endl;
	}
	// Confirm
	std::cout << "\n*Input the above SERIAL NUMBER ahead of each record, seperated by space character(s) to select\
 record(s) to be removed.\n";
	std::cout << "*Input NOTHING to cancel removal.\n" << std::endl;
	line = cptr(std::cin);
	i = line.rbegin();
	for (; i != line.rend(); i++) {
		if ((*i).empty())
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
		if (srlNmb >= 0 && srlNmb < rslt.size()) {
			contSet.erase(rsltIterators.at(srlNmb));
			++cnt;
		}
	}
	std::cout << "\nTotal " << cnt << " contact record(s) removed.\n" << std::endl;
	return 1;
}

void _contacts_system:: _contMdfyRl() {
	std::cout << "Modification manual:\n" << std::endl;
	std::cout << "[-*s serial number]   [-n name]   [-p phone number]   [-a address]   [-r remarks]\n";
	std::cout << "\n*Select and modify record(s) one by one. Please follow steps below:\n";
	std::cout << "*<1> Input the SERIAL NUMBER ahead of each record (starting with a '*') in ONE SINGLE LINE to select\
 a record to be modified.\n";
	std::cout << "*<2> Input the above optional ARGUMENTS to specify item(s) to be modified of the selected record\n";
	std::cout << "*<3> Start modifying.\n";
	std::cout << "*Input NOTHING in step<1> to finish modifying.\n";
	std::cout << "\nHere's an instance to modify phone number and remarks\n\nmdfy\t-0\nmdfy\t-0  -nr\n" << std::endl;
}

int _contacts_system::mdfyCont() {
	prntPrtL();
	std::cout << "Please input keyword(s) within a NAME or a PHONE NUMBER.\n" << std::endl;
	std::cout << "mdfy   -find\t";
	std::vector<std::string> line = cptr(std::cin);
	std::vector<std::string>::reverse_iterator i = line.rbegin();
	for (; i != line.rend(); i++) {
		if ((*i).empty())
			line.pop_back();
	}
	if (!line.size()) {
		std::cout << "Nothing to search.\n" << std::endl;
		return 0;
	}
	// Find contact record
	std::vector<std::vector<_contact>::iterator> rsltIterators;
	std::vector<_contact> rslt = _fndCont(line, rsltIterators);
	if (!rslt.size()) {
		std::cout << "\nContact not found.\n" << std::endl;
		return 0;
	}
	else {
		std::cout << "\nSearching result:\n" << std::endl;
		std::vector<_contact>::iterator itRslt = rslt.begin();
		for (; itRslt != rslt.end(); itRslt++)
			std::cout << "*" << itRslt - rslt.begin() << std::endl << *itRslt << std::endl;
	}
	// Manual
	_contMdfyRl();
	// Modify
	while (1) {
		std::cout << "-mdfy\t-";
		std::string str = cptrOne(std::cin);
		unsigned int srlNmb = strtoul(str.c_str(), nullptr, 10);
		// Input Check
		while (1) {
			if (str.empty()) {
				std::cout << "\nModification finished.\n" << std::endl;
				return 1;
			}
			else if (isdigit(str[0]) && srlNmb >= 0  && srlNmb < rsltIterators.size())
				break;
			std::cout << "Invalid serial number!\n" << std::endl;
			std::cout << "-mdfy\t-";
			str = cptrOne(std::cin);
			srlNmb = strtoul(str.c_str(), nullptr, 10);
		}
		std::cout << "-mdfy\t-" << srlNmb << "  -";
		line = cptr(std::cin);
		for (auto ss : line) {
			// Modify Name
			if (ss.find('n') != std::string::npos) {
				std::cout << "Current Name:\n\t" << rsltIterators.at(srlNmb)->nm << std::endl;
				std::cout << "New Name:\n\t";
				rsltIterators.at(srlNmb)->nm = gtLn(std::cin);
				if (rsltIterators.at(srlNmb)->nm.empty())
					rsltIterators.at(srlNmb)->nm = DefaultStr;
			}
			// Modify Phone Number
			if (ss.find('p') != std::string::npos) {
				std::cout << "Current Phone Number:\n\t" << rsltIterators.at(srlNmb)->phnmb << std::endl;
				std::cout << "New Phone Number:\n\t";
				rsltIterators.at(srlNmb)->phnmb = gtLn(std::cin);
				if (rsltIterators.at(srlNmb)->phnmb.empty())
					rsltIterators.at(srlNmb)->phnmb = DefaultStr;
			}
			// Modify Address
			if (ss.find('a') != std::string::npos) {
				std::cout << "Current Address:\n\t" << rsltIterators.at(srlNmb)->adrs << std::endl;
				std::cout << "New Address:\n\t";
				rsltIterators.at(srlNmb)->adrs = gtLn(std::cin);
				if (rsltIterators.at(srlNmb)->adrs.empty())
					rsltIterators.at(srlNmb)->adrs = DefaultStr;
			}
			// Modify Remarks
			if (ss.find('r') != std::string::npos) {
				std::cout << "Current Remarks:\n\t" << rsltIterators.at(srlNmb)->rmk << std::endl;
				std::cout << "New Remarks:\n\t";
				rsltIterators.at(srlNmb)->rmk = gtLn(std::cin);
				if (rsltIterators.at(srlNmb)->rmk.empty())
					rsltIterators.at(srlNmb)->rmk = DefaultStr;
			}
		}
		std::cout << "\nNEW version of this contact record:\n\n" << *(rsltIterators.at(srlNmb)) << std::endl;
	}
	std::cerr << "Error occurred in -mdfy: unexpected exit" << std::endl;
	return 0;
}

int _contacts_system::readCont() {
	std::ifstream input(rec.dir + "/cont.txt");
	if (input.fail())
		return 0;
	while (!input.eof()) {
		_insrtCont(input);
	}
	input.close();
	return 1;
}

int _contacts_system:: writeCont() {
	std::ofstream output(rec.dir + "/cont.txt");
	if (output.fail()) {
		std::cerr << "Writing Error occurred: cannot open output file.\n" << std::endl;
		return 0;
	}
	std::vector<_contact>::iterator i = contSet.begin();
	for (; i != contSet.end(); i++) {
		output << (*i) << std::endl;
	}
	output.close();
	std::cout << "Records written into files." << std::endl;
	return 1;
}

inline void _contacts_system:: clear() {
	contSet.clear();
}

/*=============================== FUNCTION DEFINITION =====================================*/
std::istream& operator >> (std::istream &is, _contact &cont) {
	// Name & some checks
	cont.nm = gtLn(is) ;
	if (!cont.nm.empty() && cont.nm != "eoi") {
		cont.empBit = 0;
	}
	else {
		cont.nm = DefaultStr;
		return is;
	}
	// Phone Number
	cont.phnmb = gtLn(is);
	if (cont.phnmb.empty())
		cont.phnmb = DefaultStr;
	// Address
	cont.adrs = gtLn(is);
	if (cont.adrs.empty())
		cont.adrs = DefaultStr;
	// Remarks
	cont.rmk = gtLn(is, 140);
	if (cont.rmk.empty())
		cont.rmk = DefaultStr;
	return is;
}
std::ostream& operator << (std::ostream &os, const _contact &cont) {
	// Name
	os << cont.nm << std::endl;
	// Phone number
	os << cont.phnmb << std::endl;
	// Address
	os << cont.adrs << std::endl;
	// Remarks
	os << cont.rmk << std::endl;
	return os;
}

#endif
