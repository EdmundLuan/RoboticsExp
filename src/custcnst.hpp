


// This header defines several custom constants
#ifndef CUSTCNST_HPP
#define CUSTCNST_HPP

#include <string>

#include "custcls.hpp"
#include "custtype.hpp"

const std::string DefaultStr = "N/A";
const int WholeWidth = 80;
const int CmdWidth = 20;
const int OSWidth = 15;

// Strings & enumeration type for gender
const std::map<std::string, _gender> StrToGend = _map_gen<std::string, _gender>::createMap({
	{"F", F},
	{"M", M},
	{"Defult", Dgend}
});
const std::map<_gender, std::string> GendToStr = _map_gen<_gender, std::string>::createMap({
	{F, "F"},
	{M, "M"},
	{Dgend, "Default"}
});
// Strings & enumeration type for curriculum property
const std::map<std::string, _curr_prop> StrToCurProp = _map_gen<std::string, _curr_prop>::createMap({
	{"DEGREE", Degree},
	{"NONDEGREE", NonDegree},
	{"Default", Dprop}
});
const std::map<_curr_prop, std::string> CurPropToStr = _map_gen<_curr_prop, std::string>::createMap({
	{Degree, "DEGREE"},
	{NonDegree, "NONDEGREE"},
	{Dprop, "Default"}
});
// Strings & enumeration type for effect grade
const std::map<std::string, _efct_grd> StrToEfct = _map_gen<std::string, _efct_grd>::createMap({
	{"EXCELLENT", Excl},
	{"GOOD", Good},
	{"FAIR", Fair},
	{"LIMITED",Lmtd},
	{"Default",Defct}
});
const std::map<_efct_grd, std::string> EfctToStr = _map_gen<_efct_grd, std::string>::createMap({
	{Excl , "EXCELLENT"},
	{Good, "GOOD"},
	{Fair, "FAIR"},
	{Lmtd, "LIMITED"},
	{Defct, "Default"}
});
// Strings & enumeration type for month
const std::map<std::string, _month> StrToMon = _map_gen<std::string, _month>::createMap({
	{"Jan.", Jan},
	{"Feb.", Feb},
	{"Mar.", Mar},
	{"Apr.", Apr},
	{"May.", May},
	{"Jun.", Jun},
	{"Jul.", Jul},
	{"Aug.", Aug},
	{"Sep.", Sep},
	{"Oct.", Oct},
	{"Nov.", Nov},
	{"Dec.", Dec}
});
const std::map<_month, std::string> MonToStr = _map_gen<_month, std::string>::createMap({
	{ Jan, "Jan."},
	{ Feb, "Feb."},
	{ Mar, "Mar."},
	{ Apr, "Apr."},
	{ May, "May."},
	{ Jun, "Jun."},
	{ Jul, "Jul."},
	{ Aug, "Aug."},
	{ Sep, "Sep."},
	{ Oct, "Oct."},
	{ Nov, "Nov."},
	{ Dec, "Dec."}
});
// Strings & enumeration type for title
const std::map<std::string, _title> StrToTitl = _map_gen<std::string, _title>::createMap({
	{ "FULL PROF.", FProf },
	{ "ASSOCIATE PROF.", AProf },
	{ "LECTURER", Lect },
	{ "ASSISTANT LECTURER", ALect },
	{ "NONE", None},
	{ "Default", Dtitl}
});
const std::map<_title, std::string> TitlToStr = _map_gen<_title, std::string>::createMap({
	{ FProf, "FULL PROF."},
	{ AProf, "ASSOCIATE PROF."},
	{ Lect, "LECTURER"},
	{ ALect, "ASSISTANT LECTURER" },
	{ None, "NONE" },
	{ Dtitl, "Default"}
});
// Strings & enumeration type for marriage status
const std::map<std::string, _marriage> StrToMrg = _map_gen<std::string, _marriage>::createMap({
	{"MARRIED", Married},
	{"SINGLE", Single},
	{"Defualt", Dmarr}
});
const std::map<_marriage, std::string> MrgToStr = _map_gen<_marriage, std::string>::createMap({
	{Married, "MARRIED" },
	{Single, "SINGLE" },
	{Dmarr, "Defualt" }
});

#endif
