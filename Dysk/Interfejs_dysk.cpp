#include"Dysk.h"

void test1(Dysk &d1) {
	d1.utworz_plik("plik1");
	d1.utworz_plik("plik2");
	d1.wyswietl_katalog();
	d1.katalog1.zmien_nazwe_p("plik1", "jakis_p");
	cout << "Zmiana nazwy pliku (plik1 na jakis_p)\n";
	d1.wyswietl_katalog();
	system("pause");
}

void test2(Dysk &d1) {
	string dane = "tutaj jakis przykladowy tekst do zapisania tutaj jakis przykladowy tekst do zapisania tutaj jakis przykladowy tekst do zapisania tutaj jakis przykladowy tekst do zapisania tutaj jakis przykladowy tekst do zapisania tutaj jakis przykladowy tekst do zapisania";
	d1.zapisz_plik(dane, "jakis_p");
	cout << "Zapisywanie danych do pliku (jakis_p)\n";
	string dane1 = "nowe dane do zapisania nowe dane do zapisania";
	d1.zapisz_plik(dane1, "plik2");
	cout << "Zapisywanie danych do pliku (plik2)\n";
	cout << "Wyswietlanie zawartosci dysku\n";
	d1.wyswietl_dysk_z();
	system("pause");
	d1.wyswietl_dysk_l();
	system("pause");
	cout << "Wyswietlenie zawartosci pliku (plik2)\n";
	d1.wyswietl_plik("plik2");
	system("pause");
}

void test3(Dysk &d1) {
	d1.utworz_plik("plik3");
	cout << "Tworzenie pliku (plik3) i zapisanie do niego danych\n";
	string dane2 = "A teraz cos z zupelnie innej beczki. A teraz cos z zupelnie innej beczki. A teraz cos z zupelnie innej beczki. A teraz cos z zupelnie innej beczki. A teraz cos z zupelnie innej beczki. A teraz cos z zupelnie innej beczki.";
	d1.zapisz_plik(dane2, "plik3");
	d1.wyswietl_dysk_z();
	system("pause");
	d1.wyswietl_dysk_l();
	system("pause");
	d1.skasuj_plik("plik2");
	cout << "Usuwanie pliku (plik2)\n";
	d1.wyswietl_katalog();
	system("pause");
	d1.wyswietl_dysk_z();
	system("pause");
	d1.wyswietl_dysk_l();
	system("pause");
	d1.utworz_plik("plik4");
	cout << "Utworzenie pliku (plik4)\n";
	d1.wyswietl_katalog();
	system("pause");
	string dane3 = "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh";
	d1.zapisz_plik(dane3, "plik4");
	cout << "Zapisanie danych do pliku (plik4)\n";
	d1.wyswietl_dysk_z();
	system("pause");
	d1.wyswietl_dysk_l();
	system("pause");
}

void menu() {
	Dysk d1;
	int wybor=0;
	string nazwa,dane;
	int temp=0;
	while (wybor != 12) {
		cout << "1.Przeprowadz test1\n2.Przeprowadz test2\n3.Przeprowadz test3\n4.Utworz plik\n5.Usun plik\n6.Zapisz dane do pliku\n7.Wyswietl katalog\n"
			<< "8.Wyswietl plik\n9.Wyswietl dysk znakowo\n10.Wyswietl dysk liczbowo\n11.Wyswietl wezel\n12.Zakoncz menu dysku\n";
		cin >> wybor;
		switch (wybor) {
		case 1: test1(d1); break;
		case 2: test2(d1); break;
		case 3: test3(d1); break;
		case 4: cout << "Podaj nazwe pliku: ";
			cin >> nazwa;
			d1.utworz_plik(nazwa); break;
		case 5: cout << "Podaj nazwe pliku: ";
			cin >> nazwa;
			d1.skasuj_plik(nazwa); break;
		case 6: cout << "Podaj nazwe pliku: ";
			cin >> nazwa;
			cout << "Podaj dane do zapisania: ";
			cin.ignore();
			getline(cin, dane);
			d1.zapisz_plik(dane, nazwa); break;
		case 7: d1.wyswietl_katalog(); break;
		case 8: cout << "Podaj nazwe pliku: ";
			cin >> nazwa;
			d1.wyswietl_plik(nazwa); break;
		case 9: d1.wyswietl_dysk_z(); break;
		case 10: d1.wyswietl_dysk_l(); break;
		case 11: cout << "Podaj numer wezla do wyswietlenia: ";
			cin >> temp;
			d1.wyswietl_wezel(temp); break;
		case 12: cout << "Koncze menu dysku\n"; break;
		default: cout << "Bledny wybor!\n"; break;
		}
	}
}


//funkcja main do testowania implementacji
void main() {
	menu();
	//d1.wyswietl_dysk_z();
	//d1.wyswietl_dysk_l();
	/*int bity[8];
	for (int i = 0; i < 8; i++) {
	bity[i] = 0;
	cout << bity[i];
	}
	cout << endl;
	dectobin(10,bity);
	for (int i = 0; i < 8; i++) {
	cout << bity[i];
	}
	cout << endl;
	int wynik=0;
	wynik = bintodec(bity);
	cout << wynik << endl;*/
	/*string dane = "tutaj jakis przykladowy tekst do zapisania tutaj jakis przykladowy tekst do zapisania tutaj jakis przykladowy tekst do zapisania tutaj jakis przykladowy tekst do zapisania tutaj jakis przykladowy tekst do zapisania tutaj jakis przykladowy tekst do zapisania";
	d1.utworz_plik("plik1");
	d1.utworz_plik("plik2");
	d1.wyswietl_katalog();
	d1.zapisz_plik(dane, "plik1");
	string dane1 = "nowe dane do zapisania nowe dane do zapisania";
	d1.zapisz_plik(dane1, "plik2");
	d1.katalog1.zmien_nazwe_p("plik1", "jakis_p");
	d1.wyswietl_katalog();
	d1.wyswietl_plik("plik2");*/
	

	/*d1.zapisz_plik(dane1, "plik2");

	d1.zapisz_plik(dane1, "plik2");
	d1.zapisz_plik(dane1, "plik2");
	d1.zapisz_plik(dane1, "plik2");
	d1.zapisz_plik(dane1 + "!", "plik2");
	d1.zapisz_plik(dane1, "plik2");
	d1.wyswietl_plik("plik2");
	cout << endl;

	d1.wyswietl_dysk_z();
	d1.wyswietl_dysk_l();*/
	//d1.katalog1.usun_plik("plik1");
	//d1.katalog1.usun_plik("plik2");
	/*d1.utworz_plik("plik3");
	string dane2 = "A teraz cos z zupelnie innej beczki. A teraz cos z zupelnie innej beczki. A teraz cos z zupelnie innej beczki. A teraz cos z zupelnie innej beczki. A teraz cos z zupelnie innej beczki. A teraz cos z zupelnie innej beczki.";
	d1.zapisz_plik(dane2, "plik3");
	d1.wyswietl_katalog();
	d1.wyswietl_dysk_l();
	d1.wyswietl_dysk_z();*/
	//d1.wyczysc_sektor(2);
	//d1.usun_blok_i(3);
	/*d1.skasuj_plik("plik2");
	d1.utworz_plik("plik4");
	d1.wyswietl_katalog();
	string dane3 = "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh";
	d1.zapisz_plik(dane3, "plik4");
	string nazwa="plik",temp;
	for (int i = 0; i < 31; i++) {
	temp = (char)i;
	nazwa.insert(0,temp);
	d1.utworz_plik(nazwa);
	}
	d1.wyswietl_katalog();
	d1.wyswietl_dysk_l();
	d1.wyswietl_dysk_z();*/
	system("pause");
}