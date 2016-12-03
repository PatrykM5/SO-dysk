#pragma once

#include<iostream>
#include<string>

using namespace std;

#define ILE_S 64 // ile sektorow
#define WIELKOSC_S 16 // wielkosc pojedynczego sektora
#define DYSK 1024 // wielkosc dysku w bajtach
#define MAX_P 32 //max ilosc plikow

struct n_plik
{
	string nazwa_pliku;
	int nr_wezla;
};

struct i_wezel {
	string mode;
	int size=0;
	int blok_bezposredni1=0;
	int blok_bezposredni2=0;
	int blok_posredni=0; //nr bloku indeskowego, ktory znajduje sie na dysku
};

class Katalog {
	int temp;
public:
	int plikow;
	n_plik pliki[MAX_P];
	Katalog();
	~Katalog();
	int usun_plik(string nazwa);
	int znajdz_plik(string nazwa);
	void zmien_nazwe_p(string s_nazwa, string n_nazwa);
};

class Dysk {
private:
	unsigned char dysk[DYSK];
	int wolne_miejsce;
public:
	Katalog katalog1;
	i_wezel wezly[MAX_P];
	Dysk();
	void wyswietl_dysk_l();
	void wyswietl_dysk_z();
	void zapisz_plik(string dane,string nazwa_p);
	void wyswietl_plik(string nazwa);
	string sektor_tekst(int nr_s,char tekst[]);
	void wyswietl_katalog();
	int znajdz_wolne();
	int ile_sektorow();
	bool zapisz_blok(int, int);
	void blok_indeksowy(int, int, int);
	void skasuj_plik(string nazwa);
	void wyczysc_sektor(int);
	void usun_blok_i(int);
	void utworz_plik(string nazwa);
	int znajdz_w();
};