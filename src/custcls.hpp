


// This header includes several resusable custom classes.
#ifndef CUSTCLS_HPP
#define CUSTCLS_HPP

#include <string>
#include <utility>
#include <map>
#include <limits>


#include "custtype.hpp"
#include "interact.hpp"

// A const map generator of any 2 types
template <typename T1, typename T2>
struct _map_gen {
	static std::map<T1, T2> createMap(const std::vector<std::pair<T1, T2> > pairs) {
		std::map<T1, T2> MyMap(pairs.begin(), pairs.end());
		return MyMap;
	}
};
// Date: year & month
struct _date {
	std::string yr;
	_month mon;

	_date(): yr("0000"), mon(Jan) {}
};

// Directory for files.
struct _directory {
	std::string dir;
#ifndef ENVM_WINDOWS
	_directory(): dir("/Users/Edmonds/Desktop/run/Staff_Info_ManagerX/Staff_Info_ManagerX/files") {}
#endif
#ifdef ENVM_WINDOWS
	_directory(): dir("./files") {}
#endif
	// Change directory
	void cd() {
		std::cout << "Current direcotry: \n\t" << dir << std::endl;
		std::cout << "New directory: \n\t";
		std::string str;
		getline(std::cin, str);
		// str = gtLn(std::cin);
		dir = str;
		std::cout << "\n...Done.\n" << std::endl;
	}
	// Show directory
	void sd() {
		std::cout << "\n" << dir << "\n" << std::endl;
	}
};

#endif
