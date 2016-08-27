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
	string testFile;
	if (argc > 0) testFile = argv[1];
	ifstream myfile;
	Elem *tabelaSimbola;
	TabelaSekcija *tabelaSekcija;
	myfile.open(testFile);
	tabelaSimbola = prviProlazAsm(myfile);
	myfile.close();

	//print table of sections after first pass 
	ofstream out;
	out.open("output.txt");
	ispisiTabeluSimbola(tabelaSimbola, out);

	myfile.open(testFile);
	tabelaSekcija = drugiProlazAsm(myfile, tabelaSimbola);
	myfile.close();

	//printing
	ispisiTabeluSekcija(tabelaSekcija, out);
	ispisiTabeluRelokacija(tabelaSekcija, out);
	freeTable(tabelaSimbola);
	freeTableOfSections(tabelaSekcija);
	out.close();
    return 0;
}

