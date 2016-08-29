#ifndef _POSTAVI_USLOVE_
#define _POSTAVI_USLOVE_
#include "Functions.h"

void postaviUslove(int &rezultat, string &word, int& i, string line) {
	bool cond = true;
	if (word == "eq") {
		rezultat = rezultat | 0x00000000;
	}
	else if (word == "ne") {
		rezultat = rezultat | 0x20000000;
	}
	else if (word == "gt") {
		rezultat = rezultat | 0x4000000;
	}
	else if (word == "ge") {
		rezultat = rezultat | 0x60000000;
	}
	else if (word == "lt") {
		rezultat = rezultat | 0x80000000;
	}
	else if (word == "le") {
		rezultat = rezultat | 0xa0000000;
	}
	else {
		rezultat = rezultat | 0xe0000000;
		cond = false;
	}
	
	if (cond) {
		word = getParameter(line, i);
	}
}
#endif