

#ifndef ACCTMNGSYS_HPP
#define ACCTMNGSYS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <limits>
#include <cstdlib>

#ifdef ENVM_WINDOWS
#include <conio.h>	// Windows platform only.
#endif

#include "hash.hpp"

/*==================================== TYPE ALIAS ================================*/
typedef std::map<std::string, hash_t>::iterator _it_msh;
/*==================================== CONSTANT ================================*/

/*==================================== CLASS DECLARATION ================================*/

// User account & Passcode
// Dependencies: hash.hpp, string
class _user {
public:
	std::string usrNm; 	// User name
	_user(): usrNm("admin"), pswrd("123"_hash) {}
	hash_t getPass() { return pswrd; }
private:
	hash_t pswrd; 	// Passcode
};

// Accout manage system
// Dependencies: hash.hpp, string, map
struct _accounts {
	std::vector<_user> acctSet;
	std::map<std::string, hash_t> usrToPswrd;
	std::map<std::string, hash_t>::iterator logged;
	short loggedBit;
	// Constructor
	_accounts() {
		acctSet.push_back(_user());
		usrToPswrd.insert(std::pair<std::string, hash_t>(acctSet[0].usrNm, acctSet[0].getPass()));
		logged = usrToPswrd.end();
		loggedBit = 0;
	}
	// Login
	int login();
	// Logout
	inline void logout(std::string);
	// Check password
	int chkPswrd(const std::map<std::string, hash_t>::iterator);
	int chkPswrdUnix(const std::map<std::string, hash_t>::iterator);
	// Add account
	void addAcct();
	// Erase account
	void ersAcct();
};


/*==================================== MEMBER FUNCTION DEFINITION ================================*/

int _accounts::login() {
	std::cout << "User Name:   ";
	std::string usr;
	getline(std::cin, usr);
	if (!usrToPswrd.count(usr)) {
		std::cout << "User \"" << usr << "\" not found!\n" << std::endl;
		return 0;
	}
#ifdef ENVM_WINDOWS
	return chkPswrd(usrToPswrd.find(usr));
#else
	return chkPswrdUnix(usrToPswrd.find(usr));
#endif
}

inline void _accounts::logout(std::string dir) {
	std::cout << "logout" << '\n';
	loggedBit = 0;
	logged = usrToPswrd.end();
	std::ofstream output(dir);
	for(auto acct: acctSet){
		output << acct.usrNm << std::endl;
		output << usrToPswrd.at(acct.usrNm)<<std::endl;
	}
	output.close();
	std::cout << "...completed.\n" << std::endl;
}

#ifdef ENVM_WINDOWS
// Password checking function for Windows platform
int _accounts::chkPswrd(const std::map<std::string, hash_t>::iterator itMap) {
	for (int i = 3; i > 0; i--) {
		char ch = 6;
		std::cout << "Passcode:" << ch;
		std::string pscd;
		char chr = 0;
		while ((chr = _getch()) != 13) { 	// 13 = '\r'
			pscd += chr;
		}
		std::cout << "\b ";
		std::cout << std::endl;
		hash_t k = myhash(pscd.c_str());
		if (k == itMap->second) { 	// Login Successfully.
			logged = itMap;
			loggedBit = 1;
			std::cout << '\n';
			return 1;
		}
		if (i > 1)
			std:: cout << "Sorry, try again." << std::endl;
	}
	// Fail to login
	std::cout << "3 incorrect passcode attempts\n" << std::endl;
	return 0;
}
#endif

#ifndef ENVM_WINDOWS
// Password checking function for Unix-core OS
int _accounts::chkPswrdUnix(const std::map<std::string, hash_t>::iterator itMap) {
	for (int i = 3; i > 0; i--) {
		std::cout << "Passcode:";
		// Following several system() statements are only valid on operating systems with Unix core.
		system("stty -echo");
		std::string pscd;
		getline(std::cin, pscd);
		std::cout << std::endl;
		hash_t k = hash(pscd.c_str());
		if (k == itMap->second) { 	// Login Successfully.
			logged = itMap;
			loggedBit = 1;
			std::cout << '\n';
			system("stty echo");
			return 1;
		}
		if (i > 1)
			std:: cout << "Sorry, try again." << std::endl;
	}
	// Fail to login
	std::cout << "3 incorrect passcode attempts\n" << std::endl;
	system("stty echo");
	return 0;
}
#endif

#endif


