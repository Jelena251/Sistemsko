// SP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Functions.h"
#include "Strukture.h"
using namespace std;

int main(int argc, char *argv[])
{
	cout << "Unesite ime test fajla";
	string testFile;
	cin >> testFile;
	ifstream myfile;
	myfile.open(testFile);

	//ovde treba pozvati ParseFile

	string word,line;
	
	Elem *head, *sekcije, *kraj;
	head = sekcije = kraj = NULL;
	//ElemSekcija *tabelaSekcija, *trSekcija;
	DeoTabele *deo = new DeoTabele("UND", 0, 0);

	head = sekcije = kraj = new Elem(deo);
	//DeoTabeleSekcija *deoSekc = new DeoTabeleSekcija("UND", 0);
	//tabelaSekcija = trSekcija = new ElemSekcija(deoSekc);

	int id = 1;

	while (!myfile.eof()) {
		char data[100];
		getline(myfile, line);
		//u stringu line je sada prvi red
		cout << line << '\n';
		int i = 0;
		/*while (i < line.size()) {
			if (line[i] != ' ') {
				data[i - 1] = line[i++];
			}
			else {
				break;
			}
		}
		if (data[i] != '\0') data[i] = '\0';
		word = data;
		*/
		word = getParameter(line, i);
		if (word == ".public") {
			string simbol;
			simbol = getParameter(line, i);
			while (simbol.compare("\0") != 0) {
				Elem *pom = imaSimbola(sekcije, simbol);
				if (!pom) {
					dodajDeo(sekcije, kraj, simbol, sekcije->deo->rb, 'g');
					if (kraj == sekcije)
						kraj = sekcije->next;
					else
						kraj = kraj->next;
				}
				else {
					pom->deo->vidljivost = 'g';
				}
				simbol = getParameter(line, i);
			}
		}
		else if (word == ".extern") {
			string simbol = getParameter(line, i);
			while (simbol.compare("\0") != 0) {
					if (!imaSimbola(sekcije, simbol)) {
						dodajDeo(sekcije, kraj, simbol, 0, 'g');
						if (kraj == sekcije)
							kraj = sekcije->next;
						else
							kraj = kraj->next;
					}
					simbol = getParameter(line, i);
				}
		}
		else if (word.size() >= 4 && word.substr(0, 4) == ".bss") {
			dodajSekciju(sekcije, word, id, id, 'l');
			sekcije = sekcije->next;
			//trSekcija = trSekcija->next;
			id++;
		}
		else if (word.size() >= 5 && word.substr(0, 5) == ".data") {
			dodajSekciju(sekcije, word, id, id, 'l');
			sekcije = sekcije->next;
			//trSekcija = trSekcija->next;
			id++;
		}
		else if (word.size() >= 5 && word.substr(0, 5) == ".text") {
			dodajSekciju(sekcije, word, id, id, 'l');
			sekcije = sekcije->next;
			//trSekcija = trSekcija->next;
			id++;
		}
		else if (word[i - 1] == ':') {
			word[i - 1] = '\0';
			Elem *simb = imaSimbola(sekcije, word);
			if (simb != NULL) {
				simb->deo->sekcija = sekcije->deo->rb;
				simb->deo->vrednost = sekcije->deo->velicina;
			}
			else {
				dodajDeo(sekcije, kraj, word, sekcije->deo->rb, 'l');
				if (kraj == sekcije)
					kraj = sekcije->next;
				else
					kraj = kraj->next;
			}
		}
		else if (word == ".char") {
			//ovde vdi za 'b'
			char c; 
			int j = 0;
			//trSekcija->deo->sadrzaj[trSekcija->deo->trElem] = (char*)calloc(10, sizeof(char));
			while (i < line.size()) {
				while (line[i] == ' ' || line[i] == ',') i++;
				c = line[i]; i++;
				//trSekcija->deo->sadrzaj[trSekcija->deo->trElem][j++] = c;
				sekcije->deo->velicina++;
			}
		}
		else if (word == ".skip") {
			int numSkip, j = 0;
			//dohvati prvi argument
			string data = getParameter(line, i);
			numSkip = atoi(data.c_str());
			sekcije->deo->velicina += numSkip;
			//trSekcija->deo->sadrzaj[trSekcija->deo->trElem] = (char*)calloc(numSkip, sizeof(char));
			/*if (i < line.size()) {
				i++;
				while (line[i] == ',' || line[i] == ' ') i++;
				char c = line[i];
				i++;
				//fill numSkip bytes with hexadecimal value of ascii representation of 
				stringstream izlaz;
				izlaz << std::hex << static_cast<int>(c);
				string sadrzaj = izlaz.str();
				for (i = 0; i < numSkip; i++)
					trSekcija->deo->sadrzaj[trSekcija->deo->trElem][i] = c;
			}
			else {
				for (i = 0; i < numSkip; i++)
					trSekcija->deo->sadrzaj[trSekcija->deo->trElem][i] = 0;
			}
			trSekcija->deo->trElem++;
			*/
		}
		else if (word == ".align") {
			int maxBr = 0;
			int broj = stoi(getParameter(line, i));
			int uvecanje = 0;
			while ((sekcije->deo->velicina + uvecanje) % broj != 0) uvecanje++;
			if (i < line.size()) {
				char c = *(getParameter(line, i).c_str());
				if (i < line.size()) {
					maxBr = stoi(getParameter(line, i));
					if (uvecanje <= maxBr)
						sekcije->deo->velicina += uvecanje;
				}
				else 
					sekcije->deo->velicina += uvecanje;
			}else
				sekcije->deo->velicina += uvecanje;


		}
		else if (word == ".word") { //case for label
			unsigned int broj = stoi(getParameter(line, i));
			//trSekcija->deo->sadrzaj[trSekcija->deo->trElem][cnt++] = (char)broj;
			//trSekcija->deo->sadrzaj[trSekcija->deo->trElem][cnt++] = (char)(broj>>4);
			sekcije->deo->velicina += 2;
			//trSekcija->deo->trElem++;
		}
		else if (word == ".long") {
			int cnt = 0;
			unsigned int broj = stoi(getParameter(line, i));
			/*trSekcija->deo->sadrzaj[trSekcija->deo->trElem][cnt++] = (char)broj;
			trSekcija->deo->sadrzaj[trSekcija->deo->trElem][cnt++] = (char)(broj >> 4);
			trSekcija->deo->sadrzaj[trSekcija->deo->trElem][cnt++] = (char)(broj >> 4);
			trSekcija->deo->sadrzaj[trSekcija->deo->trElem][cnt++] = (char)(broj >> 4);
			*/
			sekcije->deo->velicina += 4;
			//trSekcija->deo->trElem++;
		}
		else if (word == ".end") {
			cout << ".END\n";
			break;
		}else{
			cout << "GRESKA";
		}
	}
	postaviRb(head);
	ispisiTabelu(head, sekcije);
	freeTable(head);
	myfile.close();
    return 0;
}

