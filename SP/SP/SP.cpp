// SP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Functions.h"
#include "Strukture.h"
#include "PrviProlaz.h"
#include "DrugiProlaz.h"
using namespace std;

int main(int argc, char *argv[])
{
	cout << "Unesite ime test fajla";
	string testFile;
	cin >> testFile;
	ifstream myfile;
	Elem *tabelaSimbola;
	TabelaSekcija *tabelaSekcija;
	myfile.open(testFile);
	tabelaSimbola = prviProlazAsm(myfile);
	myfile.close();
	myfile.open(testFile);
	tabelaSekcija = drugiProlazAsm(myfile, tabelaSimbola);
	myfile.close();
	ofstream out;
	out.open("output.txt");
	ispisiTabeluSimbola(tabelaSimbola, out);
	ispisiTabeluSekcija(tabelaSekcija, out);
	freeTable(tabelaSimbola);
	freeTableOfSections(tabelaSekcija);
	myfile.close();
    return 0;
}

