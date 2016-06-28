// SP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Functions.h"
using namespace std;
struct DeoTabeleSekcija {
	char **sadrzaj;
	string imeSekcije;
	int rbSekcije;
	int trElem;
	DeoTabeleSekcija(string ime, int rb) {
		imeSekcije = ime;
		rbSekcije = rb;
		sadrzaj = (char**)calloc(20, sizeof(char*));
		trElem = 0;
	}
};

struct ElemSekcija {
	DeoTabeleSekcija *deo;
	ElemSekcija *next;
	ElemSekcija(DeoTabeleSekcija *_deo, ElemSekcija* _next = NULL) {
		deo = _deo;
		next = _next;
	}
};
struct DeoTabele {
	string ime;
	int rb;
	int sekcija;
	int vrednost;
	char vidljivost;
	int velicina;
	DeoTabele(string _ime, int _rb, int _sekcija, int _vrednost = 0, char _vidljivost = 'l', int _velicina = 0) {
	ime = _ime;
	rb = _rb;
	sekcija = _sekcija;
	vrednost = _vrednost;
	vidljivost = _vidljivost;
	velicina = _velicina;
	}
};
struct Elem {
	DeoTabele *deo;
	Elem *next;
	Elem(DeoTabele *_deo, Elem *sled = NULL) {
		deo = _deo;
		next = sled;
	}
};

void dodajDeo(Elem *sekc, Elem *kraj, string ime, int sekcija, char vidljivost) {
	DeoTabele *deo = new DeoTabele(ime, 0, sekcija, 0, vidljivost, 0);
	Elem *novi = new Elem(deo);
	if (kraj == sekc) {
		kraj = novi;
		sekc->next = kraj;
	}
	else {
		kraj->next = novi;
		kraj = novi;
	}
}
void dodajSekciju(Elem *sekc, string ime, int rb, int sekcija, char vidljivost, ElemSekcija *trSekcija) {
	DeoTabele *deo = new DeoTabele(ime, rb, sekcija, 0, vidljivost, 0);
	Elem *novi = new Elem(deo, sekc->next);
	sekc->next = novi;
	DeoTabeleSekcija *deoSekc = new DeoTabeleSekcija(ime, rb);
	trSekcija ->next = new ElemSekcija(deoSekc);

}
Elem* imaSimbola(Elem *sekc, string simbol) {
	int i = 0;
	Elem *tek = sekc ->next;
	while (tek!= NULL) {
		if (strcmp(simbol.c_str(), tek->deo->ime.c_str()) == 0)
			return tek;
		tek = tek->next;
	}
	return NULL;
}
void ispisiTabelu(Elem *head, Elem *sekc) {
	Elem *tek = head;
	while(tek != NULL) {
			cout << tek -> deo->rb << "            " << tek->deo->ime << "                 " << tek->deo->sekcija << "       " << tek->deo->vrednost << "     " << tek->deo->vidljivost << "     " << tek->deo->velicina<<'\n';
			tek = tek->next;
	}
}
void postaviRb(Elem *head) {
	int id = 0;
	while (head != NULL) {
		head->deo->rb = id++;
		head = head->next;
	}
}
void freeTable(Elem *head) {
	Elem *pom = head;
	while (head) {
		head = head->next;
		free(pom);
		pom = head;
	}
}
Elem* dohvatiSekciju(Elem *head, int rb) {
	int i = 0;
	Elem *tek = head;
	while (i++ < rb) tek = tek->next;
	return tek;
}
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
	ElemSekcija *tabelaSekcija, *trSekcija;
	DeoTabele *deo = new DeoTabele("UND", 0, 0);

	head = sekcije = kraj = new Elem(deo);
	DeoTabeleSekcija *deoSekc = new DeoTabeleSekcija("UND", 0);
	tabelaSekcija = trSekcija = new ElemSekcija(deoSekc);

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
				cout << '\n' << "JELENA:: " << simbol << '\n'; //ispis parametra
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
			dodajSekciju(sekcije, word, id, id, 'l', trSekcija);
			sekcije = sekcije->next;
			trSekcija = trSekcija->next;
			id++;
		}
		else if (word.size() >= 5 && word.substr(0, 5) == ".data") {
			dodajSekciju(sekcije, word, id, id, 'l', trSekcija);
			sekcije = sekcije->next;
			trSekcija = trSekcija->next;
			id++;
		}
		else if (word.size() >= 5 && word.substr(0, 5) == ".text") {
			dodajSekciju(sekcije, word, id, id, 'l', trSekcija);
			sekcije = sekcije->next;
			trSekcija = trSekcija->next;
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
			trSekcija->deo->sadrzaj[trSekcija->deo->trElem] = (char*)calloc(10, sizeof(char));
			while (i < line.size()) {
				while (line[i] == ' ' || line[i] == ',') i++;
				c = line[i]; i++;
				trSekcija->deo->sadrzaj[trSekcija->deo->trElem][j++] = c;
				sekcije->deo->velicina++;
			}
		}
		else if (word == ".skip") {
			int numSkip, j = 0;
			//dohvati prvi argument
			string data = getParameter(line, i);
			numSkip = atoi(data.c_str());
			sekcije->deo->velicina += numSkip;
			trSekcija->deo->sadrzaj[trSekcija->deo->trElem] = (char*)calloc(numSkip, sizeof(char));
			if (i < line.size()) {
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

		}
		else if (word == ".align") {
			char data[20];
			int j = 0;
			int maxBr = 0;
			while (line[i] == ' ' || line[i] == ',') i++;
			while (line[i] != ' ' && line[i] != ',' && i<line.size()) data[j++] = line[i++];
			int broj = stoi(data);
			
			if (i++ < line.size()) {
				while (line[i] == ',' || line[i] == ' ') i++;
				char c = line[i++];
				if (i++ < line.size()) { //imamo treci parametar
					while (line[i] != ' ' && line[i] != ',' && i<line.size()) data[j++] = line[i++];
					maxBr = stoi(data);
					if (broj - sekcije->deo->velicina > maxBr) continue; //nece se izvrsiti
				}
				trSekcija->deo->sadrzaj[trSekcija->deo->trElem] = (char*)calloc(broj, sizeof(char));
				for (i = 0; i < broj; i++)
					trSekcija->deo->sadrzaj[trSekcija->deo->trElem][i] = c;
			}
			else { //nemamo drugi parametar
				trSekcija->deo->sadrzaj[trSekcija->deo->trElem] = (char*)calloc(broj, sizeof(char));
				for (i = 0; i < broj; i++)
					trSekcija->deo->sadrzaj[trSekcija->deo->trElem][i] = 0;
			}
			sekcije->deo->velicina += broj;
			trSekcija->deo->trElem++;


		}
		else if (word == ".word") { //case for label
			char data[20];
			int j = 0, cnt =0;
			int maxBr = 0;
			while (line[i] == ' ' || line[i] == ',') i++;
			while (line[i] != ' ' && line[i] != ',' && i<line.size()) data[j++] = line[i++];
			unsigned int broj = stoi(data);
			trSekcija->deo->sadrzaj[trSekcija->deo->trElem][cnt++] = (char)broj;
			trSekcija->deo->sadrzaj[trSekcija->deo->trElem][cnt++] = (char)(broj>>4);
			sekcije->deo->velicina += 2;
			trSekcija->deo->trElem++;
		}
		else if (word == ".long") {
			char data[20];
			int j = 0, cnt = 0;
			int maxBr = 0;
			while (line[i] == ' ' || line[i] == ',') i++;
			while (line[i] != ' ' && line[i] != ',' && i<line.size()) data[j++] = line[i++];
			unsigned int broj = stoi(data);
			trSekcija->deo->sadrzaj[trSekcija->deo->trElem][cnt++] = (char)broj;
			trSekcija->deo->sadrzaj[trSekcija->deo->trElem][cnt++] = (char)(broj >> 4);
			trSekcija->deo->sadrzaj[trSekcija->deo->trElem][cnt++] = (char)(broj >> 4);
			trSekcija->deo->sadrzaj[trSekcija->deo->trElem][cnt++] = (char)(broj >> 4);
			sekcije->deo->velicina += 4;
			trSekcija->deo->trElem++;
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

