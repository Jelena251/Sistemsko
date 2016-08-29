#ifndef DRUGI_PROLAZ_H_
#define DRUGI_PROLAZ_H_
#include "Functions.h"
#include "Instrukcija.h"
using namespace std;

TabelaSekcija* drugiProlazAsm(ifstream &myfile,Elem *tabelaSimbola) {
	string word, line;

//ovde napravi tabelu sekcija

	TabelaSekcija *head, *tr;
	int id;
	Elem* sekcija = imaSimbola(tabelaSimbola, "UND");
	head = new TabelaSekcija(sekcija, NULL);
	tr = head;
	while (!myfile.eof()) {

		getline(myfile, line);
		int i = 0;
		word = getParameter(line, i);
		if (word == ".public") {
		}
		else if (word == ".extern") {

		}
		else if (word.size() >= 4 && word.substr(0, 4) == ".bss") {
			tr -> next = new TabelaSekcija(imaSimbola(tabelaSimbola, word), NULL);
			if (tr->next) tr = tr->next;
		}
		else if (word.size() >= 5 && word.substr(0, 5) == ".data") {
			tr->next = new TabelaSekcija(imaSimbola(tabelaSimbola, word), NULL);
			if (tr->next) tr = tr->next;
		}
		else if (word.size() >= 5 && word.substr(0, 5) == ".text") {
			tr->next = new TabelaSekcija(imaSimbola(tabelaSimbola, word), NULL);
			if (tr->next) tr = tr->next;
		}
		else if (word[i - 1] == ':') {
			//sta radimo sa labelom u drugom prolazu
		}
		else if (word == ".char") {
			char c;
			while (i < line.size()) {
				c = getChar(line, i);
				if (c != ' ') {
					tr->sadrzaj[tr->trVel] = c;
					tr->trVel++;
				}
			}
		}
		else if (word == ".skip") {
			int numSkip = stoi(getParameter(line, i));
			if (i < line.size()) {
				char c = getChar(line, i);
				for (int j = 0; j < numSkip; j++) {
					tr->sadrzaj[tr->trVel] = c;
					tr->trVel++;
				}
			}else{
				for (int j = 0; j < numSkip; j++) {
					tr->sadrzaj[tr->trVel] = 0x00;
					tr->trVel++;
				}
			}
		}
		else if (word == ".align") {
			int mutual = stoi(getParameter(line, i));
			int sizeToAdd = 0;
			while ((tr->trVel + sizeToAdd) % mutual != 0) sizeToAdd++;
			if (i < line.size()) {
				char sadr = getChar(line, i);
				if (i < line.size()) {
					int maxSizeToAdd = stoi(getParameter(line, i));
					if (sizeToAdd <= maxSizeToAdd) {
						for (int j = 0; j < sizeToAdd; j++) {
							tr->sadrzaj[tr->trVel] = sadr;
							tr->trVel++;
						}
					}
				}
				else {
					for (int j = 0; j < sizeToAdd; j++) {
						tr->sadrzaj[tr->trVel] = sadr;
						tr->trVel++;
					}
				}
			}else {
				for (int j = 0; j < sizeToAdd; j++) {
					tr->sadrzaj[tr->trVel] = 0x00;
					tr->trVel++;
				}
			}
		}
		else if (word == ".word") {
			unsigned int n;
			string par = getParameter(line, i);
			Elem *sim = imaSimbola(tabelaSimbola, par);
			if(sim){
				int type = (sim->deo->vidljivost == 'l') ? sim->deo->sekcija : sim->deo->rb;
				tr->dodajRelokaciju(new Relocation(tr->trVel, 0, "APS_32", type));
				if (sim->deo->vidljivost == 'l') {
					n = sim->deo->vrednost;
				}
				else {
					n = 0;
				}
				tr->sadrzaj[tr->trVel] = (char)(n & 0x00ff);
				n <<= 8;
				tr->trVel++;
				tr->sadrzaj[tr->trVel] = char(n & 0x00ff);
				n <<= 8;
				tr->trVel++;
				tr->sadrzaj[tr->trVel] = char(n & 0x00ff);
				n <<= 8;
				tr->trVel++;
				tr->sadrzaj[tr->trVel] = char(n & 0x00ff);
				tr->trVel++;
			}
			else {
				n = stoi(par);
				tr->sadrzaj[tr->trVel] = (char)(n & 0x00ff);
				n <<= 8;
				tr->trVel++;
				tr->sadrzaj[tr->trVel] = char(n & 0x00ff);
				tr->trVel++;
			}
		}
		else if (word == ".long") {
			unsigned int n;
			string tipRel;
				//par je aritmmeticki izraz
				//obrada izraza
				int j = 0;
				string par1 ="", par2 = "";
				char op1=' ', op2=' ';
				if (line[i] == '-') {
						i++; op1 = '-'; 
					}
					else {
						op1 = '+';
					}

				par1 = getParameter(line, i); //ovo je prvi parametar
				if (i < line.size()) {
					i++;
					op2 = line[i];
					i++;
					par2 = getParameter(line, i); //ovo je drugi parametar
				}
				Elem *sim1 = imaSimbola(tabelaSimbola, par1);
				Elem *sim2 = NULL;
				if (par2 != "") {
					sim2 = imaSimbola(tabelaSimbola, par2);
				}
				if (sim1 && sim2) {
					if ((sim1->deo->sekcija == sim2->deo->sekcija) && sim1->deo->vidljivost == 'l' && sim2->deo->vidljivost == 'l' && ((op1 == '+' && op2 == '-') || (op1 == '-' && op2 == '+'))) {
						if (op1 == '+' && op2 == '+')
							n = sim1->deo->vrednost + sim2->deo->vrednost;
						else if (op1 == '+' && op2 == '-')
							n = sim1->deo->vrednost - sim2->deo->vrednost;
						else if (op1 == '-' && op2 == '+')
							n = 0-sim1->deo->vrednost + sim2->deo->vrednost;
						else 
							n = 0-sim1->deo->vrednost - sim2->deo->vrednost;
					}
					else {
						//relokacija za labelu 1
						if (op1 == '-') tipRel = "APS_32N";
						else tipRel = "APS_32";
						int	type = (sim1->deo->vidljivost == 'l') ? sim1->deo->sekcija : sim1->deo->rb;
						tr->dodajRelokaciju(new Relocation(tr->trVel, 0, tipRel, type));

						if (op2 == '-') tipRel = "APS_32N";
						else tipRel = "APS_32";
						type = (sim2->deo->vidljivost == 'l') ? sim2->deo->sekcija : sim2->deo->rb;
						tr->dodajRelokaciju(new Relocation(tr->trVel, 0, tipRel, type));

						//sta upisuje u n ?????????
						if (sim1->deo->vidljivost == 'l' && sim2->deo->vidljivost == 'l') {
							if (op1 == '+' && op2 == '+')
								n = sim1->deo->vrednost + sim2->deo->vrednost;
							else if (op1 == '+' && op2 == '-')
								n = sim1->deo->vrednost - sim2->deo->vrednost;
							else if (op1 == '-' && op2 == '+')
								n = 0 - sim1->deo->vrednost + sim2->deo->vrednost;
							else
								n = 0 - sim1->deo->vrednost - sim2->deo->vrednost;
						}
						else if (sim1->deo->vidljivost == 'l') {
							if (op1 = '-') n = 0 - sim1->deo->vrednost;
							else n = sim1->deo->vrednost;
						}
						else if (sim2->deo->vidljivost == 'l') {
							if (op2 = '-') n = 0 - sim2->deo->vrednost;
							else n = sim2->deo->vrednost;
						}
						else
							n = 0;
					}
				}else if (sim1) {
					//relokacija za labelu1
					if (op1 == '-') tipRel = "APS_32N";
					else tipRel = "APS_32";
					int	type = (sim1->deo->vidljivost == 'l') ? sim1->deo->sekcija : sim1->deo->rb;
					tr->dodajRelokaciju(new Relocation(tr->trVel, 0, tipRel, type));
					int vr = (sim1->deo->vidljivost == 'l') ? sim1->deo->vrednost : sim1->deo->rb;
					//ako ima drugi operand sta radi i sta upisuje u n??? - obicno upisuje onu vrednost od 
					if (par2 != "") {
						if (op1 == '+' && op2 == '+') {
							n = vr + stoi(par2);
						}else if (op1 == '+' && op2 == '-') {
							n = vr - stoi(par2);
						}else if (op1 == '-' && op2 == '+') {
							n = 0 - vr + stoi(par2);
						}
						else {
							n = 0- vr - stoi(par2);
						}
					}
					else {
						n = vr;
					}
				}
				else if (sim2) {

					if (op2 == '-') tipRel = "APS_32N";
					else tipRel = "APS_32";
					int	type = (sim2->deo->vidljivost == 'l') ? sim2->deo->sekcija : sim2->deo->rb;
					tr->dodajRelokaciju(new Relocation(tr->trVel, 0, tipRel, type));
					int vr = (sim2->deo->vidljivost == 'l') ? sim2->deo->sekcija : sim2->deo->rb;
					if (op1 == '+' && op2 == '+') {
						n = vr + stoi(par1);
					}
					else if (op1 == '+' && op2 == '-') {
						n = stoi(par1) - vr;
					}
					else if (op1 == '-' && op2 == '+') {
						n = vr + stoi(par1);
					}
					else {
						n = 0 - vr - stoi(par1);
					}
				}
				else {
					n = stoi(par1);
					if (par2 != "") {
						int n2 = stoi(par2);
						if (op1 == '+' && op2 == '+') {
							n = n + n2;
						}
						else if (op1 == '+' && op2 == '-') {
							n = n - n2;
						}
						else if (op1 == '-' && op2 == '+') {
							n = n2 - n;
						}
						else n = 0 - n - n2;
					}
				}
			
			tr->sadrzaj[tr->trVel] = (char)(n & 0x00ff);
			tr->trVel++;
			n <<= 8;
			tr->sadrzaj[tr->trVel] = (char)(n & 0x00ff);
			tr->trVel++;
			n <<= 8;
			tr->sadrzaj[tr->trVel] = (char)(n & 0x00ff);
			tr->trVel++;
			n <<= 8;
			tr->sadrzaj[tr->trVel] = (char)(n & 0x00ff);
			tr->trVel++;
		}
		else if (word == ".end") {
			return head;
		}
		else {

			
			int n = obradiInstrukciju(word, i, line, tabelaSimbola, tr);
			tr->sadrzaj[tr->trVel] = (char)((n & 0xff000000)>>24);
			tr->trVel++;
			n <<= 8;
			tr->sadrzaj[tr->trVel] = (char)((n & 0xff000000) >> 24);
			tr->trVel++;
			n <<= 8;
			tr->sadrzaj[tr->trVel] = (char)((n & 0xff000000) >> 24);
			tr->trVel++;
			n <<= 8;
			tr->sadrzaj[tr->trVel] = (char)((n & 0xff000000) >> 24);
			tr->trVel++;

		}
	}
	return head;
}
#endif