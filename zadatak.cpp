#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
//#include "red_polje.h"
#include "red_pokazivac.h"
using namespace std;

klijent polje[1000];

void unos(char *znakovni_niz) {
	cin.getline(znakovni_niz, 150);
	if(cin.gcount() == 1) cin.getline(znakovni_niz, 150);
}

int gen_ai() {
	return (rand() % 491 + 10);
}

int gen_bi() {
	return (rand() % 721 + 80);
}

int gen_cdi() {
	return (rand() % 5 + 1);
}

void gen_i_pr(char *i_pr) {
	int a = rand() % 8 + 3;
	int b = rand() % 8 + 3;
	i_pr[0] = char(rand() % 26 + 65);
	for(int i = 1; i < a; i++) i_pr[i] = char(rand() % 26 + 97);
	i_pr[a] = char(32);
	i_pr[a + 1] = char(rand() % 26 + 65);
	for(int i = a + 2; i <= a + b; i++) i_pr[i] = char(rand() % 26 + 97);
	i_pr[a + b + 1] = '\0';
}

void gen_dat(char *dat) {
	int d = rand() % 31 + 1;
	int m = rand() % 12 + 1;
	int g = rand() % 71 + 1925;
	if(m <= 7 && !(m % 2) && d > 30) d = 30;
	if(m > 7 && m % 2 && d > 30) d = 30;
	if(m == 2 && d > 28) d = 28;
	char dan[3], mj[3], god[5];
	itoa(d, dan, 10); itoa(m, mj, 10); itoa(g, god, 10);
	if(d < 10) { strcpy(dat, "0"); strcat(dat, dan); }
	else strcpy(dat, dan);
	strcat(dat, ".");
	if(m < 10) strcat(dat, "0");
	strcat(dat, mj); strcat(dat, "."); strcat(dat, god); strcat(dat, ".");
}

void gen_spol(char &spol) {
	int a = rand() % 10;
	if(a < 5) spol = 'm';
	else spol = 'z';
}

void prioritet(int ci) {
	cout << "Prioritet klijenta: ";
	switch(ci) {
		case 1: cout << "VIP klijent" << endl; break;
		case 2: cout << "Invalid" << endl; break;
		case 3: cout << "Trudnica" << endl; break;
		case 4: cout << "Umirovljenik" << endl; break;
		case 5: cout << "Ostali klijenti" << endl; break;
	}
}

void usluga(int di, bool h) {
	if(h) cout << "Vrsta usluge: ";
	switch(di) {
		case 1: cout << "Predaja/preuzimanje posiljke" << endl; break;
		case 2: cout << "Placanje racuna" << endl; break;
		case 3: cout << "Uplata lutrije" << endl; break;
		case 4: cout << "Western Union" << endl; break;
		case 5: cout << "Evotv" << endl; break;
	}
}

void dodaj(int n, bool &f) {
	klijent x;
	int g;
	char god[5];
	cout << endl << "Velicina niza: " << n << endl;
	cout << "=============================================" << endl << endl;
	for(int i = 0; i < n; i++) {
		cout << "Zapis br. " << (i + 1) << ":" << endl << endl;
		gen_i_pr(x.i_pr); gen_dat(x.dat); gen_spol(x.spol);
		x.ai = gen_ai(); x.bi = gen_bi();
		for(int j = 6; j < 10; j++) god[j - 6] = x.dat[j];
		god[4] = '\0'; g = atoi(god);
		do {
			x.ci = gen_cdi();
		} while((x.ci == 3 && x.spol == 'm') || (x.ci == 3 && g < 1965) || (x.ci == 4 && g > 1954));
		x.di = gen_cdi();
		cout << "Ime i prezime: " << x.i_pr << endl;
		cout << "Datum rodjenja: " << x.dat << endl;
		cout << "Spol: " << x.spol << endl;
		prioritet(x.ci);
		usluga(x.di, 1);
		cout << "------------------------------------------" << endl << endl;
		polje[i] = x;
	}
	f = 1;
	cout << endl << "Zapisi su uspjesno dodani u niz" << endl;
}

void testna(int &n, bool &f) {
	klijent x;
	fstream dat;
	dat.open("testni_podaci.dat", ios::in | ios::binary);
	if(dat) {
		dat.seekg(0, ios::end);
		n = (dat.tellg() / sizeof(klijent));
		dat.seekg(0);
		cout << endl << "Modificiram velicinu niza... ";
		cout << "Nova velicina niza je " << n << " zapisa" << endl << endl;
		for(int i = 0; i < n; i++) {
			dat.read((char *) &x, sizeof(x));
			polje[i] = x;
		}
		dat.close(); dat.clear();
		f = 1;
		cout << "Testni podaci su uspjesno ucitani iz datoteke" << endl;
	}
	else cout << endl << "Datoteka s testnim podacima ne postoji na disku!" << endl;
}

void ispis(int n, bool f) {
	if(f) {
		cout << endl << "Velicina niza: " << n << endl;
		cout << "=============================================" << endl << endl;
		for(int i = 0; i < n; i++) {
			cout << "Zapis br. " << (i + 1) << ":" << endl << endl;
			cout << "Ime i prezime: " << polje[i].i_pr << endl;
			cout << "Datum rodjenja: " << polje[i].dat << endl;
			cout << "Spol: " << polje[i].spol << endl;
			prioritet(polje[i].ci);
			usluga(polje[i].di, 1);
			cout << "------------------------------------------" << endl << endl;
		}
	}
	else cout << endl << "Niz je prazan!" << endl;
}

void jarac() {
	bool h = 0;
	int d, m, g;
	char dan[3], mj[3], god[5];
	while(!IsEmptyQ(Q)) {
		if(FrontQ(Q).di == 3) {
			for(int j = 0; j < 2; j++) dan[j] = FrontQ(Q).dat[j];
			dan[2] = '\0';
			for(int j = 3; j < 5; j++) mj[j - 3] = FrontQ(Q).dat[j];
			mj[2] = '\0';
			for(int j = 6; j < 10; j++) god[j - 6] = FrontQ(Q).dat[j];
			god[4] = '\0';
			d = atoi(dan); m = atoi(mj); g = atoi(god);
			if(((d >= 22 && m == 12) || (d <= 20 && m == 1)) && g > 1974) {
				cout << "Ime i prezime: " << FrontQ(Q).i_pr << endl;
				cout << "Datum rodjenja: " << FrontQ(Q).dat << endl;
				cout << "Spol: " << FrontQ(Q).spol << endl;
				prioritet(FrontQ(Q).ci);
				usluga(FrontQ(Q).di, 1);
				cout << "------------------------------------------" << endl << endl;
				h = 1;
			}
		}
		EnQueueQ(FrontQ(Q), Pom); DeQueueQ(Q);
	}
	while(!IsEmptyQ(Pom)) {
		EnQueueQ(FrontQ(Pom), Q); DeQueueQ(Pom);
	}
	if(!h) cout << endl << "Ne postoje takvi klijenti!" << endl << endl;
}

void odlazak_trudnice() {
	bool z = 0;
	while(!IsEmptyQ(Q)) {
		if(FrontQ(Q).ci == 3 && FrontQ(Q).di == 5 && !z){
			DeQueueQ(Q); z = 1;
		}
		else {
			EnQueueQ(FrontQ(Q), Pom);
			DeQueueQ(Q);
		}
	}
	while(!IsEmptyQ(Pom)) {
		EnQueueQ(FrontQ(Pom), Q);
		DeQueueQ(Pom);
	}
}

void ispis_reda() {
	while(!IsEmptyQ(Q)) {
		cout << "Ime i prezime: " << FrontQ(Q).i_pr << endl;
		cout << "Datum rodjenja: " << FrontQ(Q).dat << endl;
		cout << "Spol: " << FrontQ(Q).spol << endl;
		prioritet(FrontQ(Q).ci);
		usluga(FrontQ(Q).di, 1);
		cout << "------------------------------------------" << endl << endl;
		EnQueueQ(FrontQ(Q), Pom); DeQueueQ(Q);
	}
	while(!IsEmptyQ(Pom)) {
		EnQueueQ(FrontQ(Pom), Q); DeQueueQ(Pom);
	}
}

void simulacija(int n, bool f) {
	if(f) {
		klijent salter[5]; bool salt[5];
		int trudnica[1000]; int tr1 = 0, tr2 = -1;
		klijent trud[1000];
		for(int i = 0; i < 5; i++) salt[i] = 0;
		for(int i = 0; i < 1000; i++) trudnica[i] = 0;
		cout << endl << "Pritisnite ENTER za pokretanje simulacije... ";
		cin.ignore(); getchar();
		system("cls");
		for(int i = 0; i < n; i++) {
			for(int j = tr1; j <= tr2; j++) {
				trudnica[j] += salter[FrontQ(Q).di - 1].bi;
			}
			for(int j = tr1; j <= tr2; j++) {
				if(trudnica[j] >= 1060) {
					tr1++;
					cout << endl << "Trudnica " << trud[j].i_pr << " je zbog predugog cekanja izasla iz reda" << endl;
					cout << endl << "Pritisnite ENTER za ispis glavnog reda prije odlaska trudnice... "; getchar();
					cout << endl;
					ispis_reda();
					odlazak_trudnice();
					cout << "Pritisnite ENTER za ispis glavnog reda nakon odlaska trudnice... "; getchar();
					cout << endl;
					ispis_reda();
					cout << "Pritisnite ENTER za nastavak simulacije... "; getchar();
					cout << endl;
				}
			}
			for(int j = 0; j < 5; j++) {
				if(salt[j]) {
					salter[j].bi -= polje[i].ai;
					if(salter[j].bi <= 0) {
						salt[j] = 0;
						if(salter[j].spol == 'm') { cout << "Klijent " << salter[j].i_pr << " je napustio salter: "; usluga(j + 1, 0); }
						else { cout << "Klijentica " << salter[j].i_pr << " je napustila salter: "; usluga(j + 1, 0); }
					}
				}
			}
			if(IsEmptyQ(Q)) {
				if(salt[polje[i].di - 1] == 0) {
					salter[polje[i].di - 1] = polje[i];
					salt[polje[i].di - 1] = 1;
					if(polje[i].spol == 'm') { cout << "Klijent " << polje[i].i_pr << " je dosao na salter: "; usluga(polje[i].di, 0); }
					else { cout << "Klijentica " << polje[i].i_pr << " je dosla na salter: "; usluga(polje[i].di, 0); }
				}
				else {
					EnQueueQ(polje[i], Q);
					if(polje[i].spol == 'm') cout << "Klijent " << polje[i].i_pr << " je dosao na celo reda" << endl;
					else cout << "Klijentica " << polje[i].i_pr << " je dosla na celo reda" << endl;
					if(polje[i].ci == 3 && polje[i].di == 5) trud[++tr2] = polje[i];
				}
			}
			else {
				EnQueueQ(polje[i], Q);
				if(polje[i].spol == 'm') cout << "Klijent " << polje[i].i_pr << " je dosao na zacelje reda" << endl;
				else cout << "Klijentica " << polje[i].i_pr << " je dosla na zacelje reda" << endl;
				if(polje[i].ci == 3 && polje[i].di == 5) trud[++tr2] = polje[i];
				if(salt[FrontQ(Q).di - 1] == 0) {
					salter[FrontQ(Q).di - 1] = FrontQ(Q);
					salt[FrontQ(Q).di - 1] = 1;
					if(FrontQ(Q).spol == 'm') { cout << "Klijent " << FrontQ(Q).i_pr << " je dosao s cela reda na salter: "; usluga(FrontQ(Q).di, 0); }
					else { cout << "Klijentica " << FrontQ(Q).i_pr << " je dosla s cela reda na salter: "; usluga(FrontQ(Q).di, 0); }
					if(FrontQ(Q).ci == 3 && FrontQ(Q).di == 5) tr1++;
					DeQueueQ(Q);
					if(polje[i].ci < FrontQ(Q).ci) {
						EnQueueQ(polje[i], Pom);
						while(!IsEmptyQ(Q)) {
							EnQueueQ(FrontQ(Q), Pom);
							DeQueueQ(Q);
						}
						while(!IsEmptyQ(Pom)) {
							EnQueueQ(FrontQ(Pom), Q);
							DeQueueQ(Pom);
						}
						if(FrontQ(Q).spol == 'm') cout << endl << "Klijent " << FrontQ(Q).i_pr << " ima veci prioritet i dolazi na celo reda" << endl;
						else cout << endl << "Klijentica " << FrontQ(Q).i_pr << " ima veci prioritet i dolazi na celo reda" << endl;
					}
				}
			}
		}
		cout << endl << "Simulacija gotova. Pritisnite ENTER za ispis klijenata horoskopskog znaka Jarac, mladjih od 40 god. koji cekaju na uplatu lutrije... ";
		getchar();
		cout << endl;
		jarac();
	}
	else cout << endl << "Niz je prazan!" << endl;
}

int main() {
	InitQ(Q);
	InitQ(Pom);
	srand(time(NULL)); rand();
	int izbor, n;
	bool f = 0;
	cout << endl << "Dobrodosli u program koji simulira red u poslovnici Hrvatske poste." << endl << endl;
	cout << "Za pocetak unesite broj N koji predstavlja velicinu niza: ";
	do {
		cin >> n;
	} while(n <= 0 || n > 1000);
	do {
		system("cls");
		cout << "IZBORNIK:" << endl << endl;
		cout << "\t1) Dodavanje zapisa o klijentima poste" << endl;
		cout << "\t2) Ucitavanje datoteke s testnim podacima" << endl;
		cout << "\t3) Ispis zapisa o klijentima poste" << endl;
		cout << "\t4) Simulacija reda u poslovnici Hrvatske poste" << endl;
		cout << "\t9) Izlaz iz programa" << endl << endl;
		cout << "Izaberite jednu od ponudjenih opcija: "; cin >> izbor;
		switch(izbor) {
			case 1:
				dodaj(n, f);
				cin.ignore();
				getchar();
				break;
			case 2:
				testna(n, f);
				cin.ignore();
				getchar();
				break;
			case 3:
				ispis(n, f);
				cin.ignore();
				getchar();
				break;
			case 4:
				simulacija(n, f);
				getchar();
				break;
			case 9: break;
			default:
				cout << endl << "Pogresan unos!" << endl;
				cin.ignore();
				getchar();
				break;
		}
	} while(izbor != 9);
	return 0;
}
