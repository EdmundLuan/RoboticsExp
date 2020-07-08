

// This header includes several custom types.
#ifndef CUSTTYPE_HPP
#define CUSTTYPE_HPP

enum _gender {Dgend = 0, M, F}; 							// Male, Female, Default
enum _title {Dtitl = 0, FProf, AProf, Lect, ALect, None}; /* Title: Full Professor,
														   *		Associate Professor, Lecturer,
														   *    	Assistant Lecturer, or Default
														   */
enum _curr_prop {Dprop=0, Degree, NonDegree}; 		// Degree, Non-degree, Default
enum _efct_grd	{Defct=0, Excl, Good, Fair, Lmtd}; 	// Excellent, Good, Fair, Limited, Default
enum _month {Jan = 0, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec};
enum _marriage {Dmarr = 0, Married, Single};

#endif
