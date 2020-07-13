// This header includes operations defining basic behaviors of interfaces
#ifndef INTERACT_HPP
#define INTERACT_HPP

#include <iostream>
#include <iomanip>
#include <cctype>
#include <limits>
#include <string>
#include <vector>
#include <map>
#include <utility>

#include "custcnst.hpp"

/*==================================== CONSTANT ======================================*/
const int DefaultPerLine = 20;

/*=============================== FUNCTION DELARATION ================================*/
void prntPrtL(); 		// Print parting line
void prntCmds(const std::map<std::string, std::string>& );	// Print commands on screen
std::vector<std::string> cptr (std::istream& , int); 	// Capture strings in ONE line from specific stream
std::string cptrOne (std::istream&); 					// Capture the first string in ONE line
// Recognize
template <typename T>
T rcgnz (const std::string& , const std::map<std::string, T>& );

/*=============================== FUNCTION DEFINITION ================================*/
void prntPrtL() {
	std::cout << std::setfill('-') << std::setw(WholeWidth) << '-' << std::endl;
}

void prntCmds(const std::map<std::string, std::string> &argCmds) {
	prntPrtL();
	std::cout << std::setfill(' ') << std::setw(CmdWidth) << std::left
	          << "Commands" << "Description\n"
	          << std::endl;

	for (auto i : argCmds) {
		std::cout << std::setw(CmdWidth) << std::left
		          << i.first << i.second
		          << std::endl;
	}
	std::cout << std::endl;
}

// Capture a specific number of strings in ONE single line while ignoring space characters.
// Characters except line feed character shall be considered as a whole string between
// a pair of quotation marks.
std::vector<std::string> cptr (std::istream &is, int n = DefaultPerLine) {
	std::vector<std::string> v;
	bool flagQ = 0; 	// flagQ = 1 when quotation mark "\"" is detected.
	char c = 0;
	int cnt = 0;
	std::string str;
	is.get(c);
	while (c != '\n' && cnt < n && !is.eof() ) {
		if ((!isspace(c) || flagQ) && c != '"') {
			str += c;
		}
		else if (c == '"') {
			flagQ = !flagQ;
		}
		else if (!str.empty()) {
			v.push_back(str);
			++cnt;
			str = "";
		}
		else if (!isspace(c)) {
			std::cerr << "Error occurred: unexpected capture scenario!\n" << std::endl;
			break;
		}
		is.get(c);
	}
	if (!str.empty()) {
		v.push_back(str);
		++cnt;
		str = "";
	}
	// Clear Buffer in current line.
	if (c != '\n') {
		is.ignore(1000, '\n');
	}
	// Make sure vector v has n element(s)
	for (int i = cnt; i < n; ++i) v.push_back("");
	return v;
}
// Capture the first string in one line
std::string cptrOne (std::istream &is) {
	std::vector<std::string> v = cptr(is, 1);
	if (v.size())
		return v.at(0);
	// std::cout << "Capture Error: nothing captured!\n" << std::endl;
	return "";
}
// Merge the whole line into 1 string, ignore extra space characters
inline std::string _mergeLn(std::vector<std::string> line) {
	std::string ss = "";
	std::vector<std::string>::iterator itS = line.begin();
	for (; itS != line.end() && (*itS) != "" ; itS++) {
		if (itS != line.begin())
			ss += ' ';
		ss += *itS;
	}
	return ss;
}
// My getline, capture first n strings and merge them into one
std::string gtLn(std::istream &is, int n = DefaultPerLine) {
	return _mergeLn(cptr(is, n));
}

// Recognize
template <typename T>
T rcgnz (const std::string& str, const std::map<std::string, T>& tMap) {
	T res = (T)0;
	if (tMap.count(str)) {
		res = tMap.at(str);
	}
	return res;
}

#endif
