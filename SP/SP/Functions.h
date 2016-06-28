#pragma once
#include "stdafx.h"
using namespace std;
string getParameter(string line, int &i) {
	char data[20];
	int j = 0;
	while ((line[i] == ' ' || line[i] == ',') &&  i<line.size())
		i++;
	while (line[i] != ' ' && line[i] != ',' && i < line.size()) {
		data[j] = line[i];
		j++; i++;
	}
	data[j] = '\0';
	return data;
}