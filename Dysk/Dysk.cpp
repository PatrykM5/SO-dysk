#include"Dysk.h"

//funkcje do przetwarzania wektora bitowego
void dectobin(int liczba, int bity[]){
	int w = 7;
	while (liczba)
	{
		bity[w] = liczba % 2;
		liczba /= 2;
		w--;
	}
}

int bintodec(int bity[8]){
	int wynik = 0;
	for (int i = 7, mnoznik = 1; i >= 0; i--, mnoznik *= 2){
		wynik += bity[i] * mnoznik;
	}
	return wynik;
}

//konstruktor klasy dysk ->OK
Dysk::Dysk(){
	dysk[0] = (char)(255>>1);	//zajety 1 sektor na wektor bitowy 8 z 16B
	for (int i = 1; i < 8; i++){
		dysk[i] = (char)255;
	}
	for (int i = 8; i < DYSK; i++){
		dysk[i] = 0;
	}
	wolne_miejsce = ILE_S-1;
	for (int i = 0; i < MAX_P; i++) {
		katalog1.pliki[i].nazwa_pliku = "";
	}
}

//wyswietlanie dysku l i z ->OK
void Dysk::wyswietl_dysk_l(){
	int nr_sektora = 0;
	for (int i = 0; i < DYSK; i++){
		if (i % WIELKOSC_S == 0) {
			cout << endl << "s" << nr_sektora << "\t";
			nr_sektora++;
		}
		cout << (int)dysk[i] <<" ";
	}
	cout << endl;
}
void Dysk::wyswietl_dysk_z(){
	int nr_sektora = 0;
	for (int i = 0; i < DYSK; i++){
		if (i % WIELKOSC_S == 0) {
			cout << endl << "s" << nr_sektora << "\t";
			nr_sektora++;
		}
		cout << dysk[i] <<" ";
	}
	cout << endl;
}


//dopisywanie danych do pliku/na dysk ->OK
void Dysk::zapisz_plik(string dane,string nazwa_p)
{
	string bufor, blad;
	int wynik=0,nr_w;
	int size=0;
	bool udane=false;
	nr_w=katalog1.znajdz_plik(nazwa_p);
	if (nr_w != -1) {
		//cout << "Znaleziono plik\n";
		size = ceil((double)dane.length() / WIELKOSC_S);
		try {
			if (size <= wolne_miejsce-1 && size <=18) {
				for (int i = 0; i < size; i++) {
					udane = false;
					if (wezly[nr_w].size >= 18) throw blad = "Przekroczono maksymalna wielkosc pliku: ";
					while (udane!=true) {
						wynik = znajdz_wolne();
						udane = zapisz_blok(nr_w, wynik);
					}
					bufor = dane.substr(i * WIELKOSC_S, WIELKOSC_S);
					for (int j = 0; j < bufor.length(); j++)
						dysk[(wynik * WIELKOSC_S) + j] = bufor[j];
					wolne_miejsce -= 1;
				}
				
			}
			else blad = "Brak miejsca na dysku!\n";
		} 
		catch (string blad) {
			cout << blad <<endl;
		}
	}
	else cout << "Nie znaleziono pliku!\n";
}

//wyswietla plik znakowo, odczytuje z dysku ->OK
void Dysk::wyswietl_plik(string nazwa_p)
{
	char bufor[WIELKOSC_S];
	string dane;
	int wynik = 0, nr_w, size;
	bool udane = false;
	nr_w = katalog1.znajdz_plik(nazwa_p);
	size = wezly[nr_w].size;
	if (nr_w != -1) {
		//cout << "Znaleziono plik\n";
		sektor_tekst(wezly[nr_w].blok_bezposredni1,bufor);
		sektor_tekst(wezly[nr_w].blok_bezposredni2,bufor);
		//obsluzyc blok indeksowy
		for (int i = 0; i < size - 2; i++) {
			wynik = (int)dysk[wezly[nr_w].blok_posredni*WIELKOSC_S+i];
			sektor_tekst(wynik,bufor);
		}
		cout << endl;
	}
	else cout << "Nie znaleziono pliku!\n";
}

//zwraca sektor dysku na wyjsciu konsoli oraz jako zmienna string ->OK
string Dysk::sektor_tekst(int nr_s,char tekst[]) {
	for (int i = 0; i < WIELKOSC_S; i++) {
		tekst[i] = dysk[nr_s * WIELKOSC_S + i];
		if(tekst[i]!=(char)0) cout << tekst[i];
	}
	return tekst;
}

//wyswietla katalog w formie tabeli nazwa pliku, nr wezla ->OK
void Dysk::wyswietl_katalog()
{
	int temp = 0,i=0;
	cout << "Nazwa pliku\tNr_wezla\n";
	while(temp!=katalog1.plikow) {
		if (katalog1.pliki[i].nazwa_pliku != "") {
			cout << katalog1.pliki[i].nazwa_pliku << "\t\t" << katalog1.pliki[i].nr_wezla << endl;
			temp++;
		}
		i++;
	}
}

//znajduje wolny sektor i zmiennia jego dostepnosc ->OK
int Dysk::znajdz_wolne()
{
	string error;
	bool found = false;
	int blok, wynik=0, nr_bitu;
	int bity[8] = { 0 };
	for (int i = 0; i < 8; i++) {
		if ((int)dysk[i] > 0) {
			found = true;
			blok = i;
			break;
		}
	}
	if (found) { 
		dectobin((int)dysk[blok], bity);
		
		for (int i = 0; i < 8; i++) {
			if (bity[i] == 1) {
				bity[i] = 0;
				nr_bitu = i;
				break;
			}
		}
		dysk[blok]=(char)bintodec(bity);
	}
	else {
		throw error = "Brak miejsca/wolnych sektorow";
	}
	return blok*8+nr_bitu;
}

//zwraca ilosc wolnych sektorow ->OK
int Dysk::ile_sektorow()
{
	return wolne_miejsce;
}

//zapisuje numery blokow posrednich i bezposrednich ->OK
bool Dysk::zapisz_blok(int nr_w, int wynik)
{
	int temp = 0;
	if (wezly[nr_w].size < 18) {
		wezly[nr_w].size++;
		/*cout << wezly[nr_w].size << "\t";*/
		if (wezly[nr_w].blok_bezposredni1 == 0) wezly[nr_w].blok_bezposredni1 = wynik;
		else if (wezly[nr_w].blok_bezposredni2 == 0) wezly[nr_w].blok_bezposredni2 = wynik;
		else if (wezly[nr_w].blok_posredni == 0) {
			wezly[nr_w].blok_posredni = wynik;
			wezly[nr_w].size--;
			return false;
			/*wynik = znajdz_wolne();
			blok_indeksowy(wezly[nr_w].blok_posredni, wezly[nr_w].size, wynik);*/
		}
		else {
			//return false;
			//tutaj przeszukiwanie bloku
			blok_indeksowy(wezly[nr_w].blok_posredni, wezly[nr_w].size, wynik);
		}
	}
	else return false;
	return true;
}

//obsluga bloku indeksowego i-wezla ->OK
void Dysk::blok_indeksowy(int nr_s,int size, int wynik) {
	int temp = (nr_s * WIELKOSC_S) + size - 3;
	dysk[temp] = (char)wynik;
	//cout << (int)dysk[temp] << endl;
}

//usuwa plik z dysku
void Dysk::skasuj_plik(string nazwa)
{
	int temp1;
	int wynik = katalog1.usun_plik(nazwa);
	if (wynik != -1) {
		temp1 = wezly[wynik].blok_bezposredni1;
		if(temp1!=0) wyczysc_sektor(temp1);
		temp1 = wezly[wynik].blok_bezposredni2;
		if (temp1 != 0) wyczysc_sektor(temp1);
		//tutaj kasowanie z bloku indeksowego
		temp1 = wezly[wynik].blok_posredni;
		usun_blok_i(temp1);
		//kasowanie bloku indeksowego
		if (temp1 != 0) wyczysc_sektor(temp1);
		//usuwanie danych z i-wezla, nadawanie domyslnych wartosci
		wezly[wynik].blok_bezposredni1 = 0;
		wezly[wynik].blok_bezposredni2 = 0;
		wezly[wynik].blok_posredni = 0;
		wezly[wynik].size = 0;
		wezly[wynik].mode = "";
	}
}

//usuwa dane z sektora zastêpuj¹c zerami oraz zmienia dostepnosc sektora ->OK
void Dysk::wyczysc_sektor(int nr_s)
{
	//zmiana dostepnosci sektora
	int bity[8] = { 0 };//ok
	int w_b = 0,bit=0, wynik=0;//ok
	int temp = nr_s / 8;//temp->w ktorym bajcie dysku jest
	//cout << "bajt dysku: " << temp << " usuwany sektor: " << nr_s << endl;
	w_b = (int)dysk[temp];//w_b->pobranie bajta dysku jako int
	bit = nr_s % 8;//bit->nr bitu ktory ma byc zmieniony
	//cout << "bajt jako int: " << w_b << "bit do zmiany: " <<bit << endl;
	dectobin(w_b, bity);//bajt z dysku zamieniny na tablica bitow
	bity[bit] = 1;
	wynik=bintodec(bity);//wynik->zamiana tablicy bitow na bajt
	//cout << "Bajt do zapisania: " << wynik<<endl;
	dysk[temp] = (char)wynik;
	//usuwanie danych ze wskazanego sektora
	for (int i = 0; i < WIELKOSC_S; i++) {
		dysk[nr_s * WIELKOSC_S + i] = (char)0;
	}
	wolne_miejsce++;
}

//usuwa sektory z bloku indeksowego ->OK
void Dysk::usun_blok_i(int nr_s)
{
	int temp = 0;
	//cout << "bloki: ";
	for (int i = 0; i < WIELKOSC_S; i++) {
		temp = (int)dysk[nr_s*WIELKOSC_S+i];
		//cout << temp << "\t";
		//jesli wpis bloku indeksowego nie jest 0 wtedy kasuje sektor
		if (temp == 0) {
			break;
			//cout << "pusty\n";
		}
		else {
			wyczysc_sektor(temp);
		}
	}
	//cout << endl;
}

//tworzy plik (maksymalnie 32 pliki) o podanej nazwie ->OK
void Dysk::utworz_plik(string nazwa)
{
	string error;
	int nr_w;
	if (nazwa == "") {
		cout << "Bledna nazwa pliku!\n";
		return;
	}
	if (katalog1.znajdz_plik(nazwa) == -1) {
		if (katalog1.plikow < MAX_P) {
			//tutaj szukanie wolnego i-wezla
			nr_w = znajdz_w();
			if (nr_w == -1) cout << "Brak i-wezlow\n";
			else {
				katalog1.pliki[nr_w].nazwa_pliku = nazwa;
				katalog1.pliki[nr_w].nr_wezla = nr_w;
				wezly[nr_w].mode = "plik";
				katalog1.plikow++;
			}
		}
		else cout << "Zbyt duzo plikow!\n";
	}
	else cout << "Plik o tej nazwie istnieje!\n";
}

//znajduje wolny i-wezel
int Dysk::znajdz_w()
{
	int wezel = -1;
	for (int i = 0; i < MAX_P; i++) {
		if (wezly[i].mode == "") return i;
	}
	return wezel;
}

//wyswietla dane i-wezla o zadanym numerze
void Dysk::wyswietl_wezel(int nr_w)
{
	if (wezly[nr_w].size == 0) cout << "Brak zajetych blokow\n";
	else {
		cout << "Blok bezposredni 1: " << wezly[nr_w].blok_bezposredni1 << " sektor\n";
		if(wezly[nr_w].blok_bezposredni2 != 0) cout << "Blok bezposredni 2: " << wezly[nr_w].blok_bezposredni2 << " sektor\n";
		if(wezly[nr_w].blok_posredni != 0)cout << "Blok indeksowy: " << wezly[nr_w].blok_posredni << " sektor\n";
	}
}

//konstruktor klasy katalog ->OK
Katalog::Katalog()
{
	plikow = 0;
}

//destruktor klasy katalog
Katalog::~Katalog()
{
	plikow = 0;
}

//usuwanie pliku z katalogu ->OK
int Katalog::usun_plik(string nazwa)
{
	int wynik=0;
	wynik = znajdz_plik(nazwa);
	if (wynik != -1) {
		//tutaj usuwanie pliku
		//cout << "znaleziono plik w: " <<wynik << endl;
		plikow--;
		pliki[wynik].nazwa_pliku = "";
		pliki[wynik].nr_wezla = -1;
		return wynik;
	}
	else{
		cout << "Nie znaleziono pliku!\n";
		return -1;
	}
}

//znajduje plik i zwraca nr wezla pliku ->OK
int Katalog::znajdz_plik(string nazwa)
{
	int wynik = -1;
	bool found = false;
	for (int i = 0; i < MAX_P; i++) {
		if (pliki[i].nazwa_pliku == nazwa) {
			found = true;
			wynik = pliki[i].nr_wezla;
			break;
		}
	}
	return wynik;
}

//zmienia nazwe pliku w folderze ->OK
void Katalog::zmien_nazwe_p(string s_nazwa, string n_nazwa) {
	int nr_wezla = znajdz_plik(s_nazwa);
	if(nr_wezla!=-1)
	pliki[nr_wezla].nazwa_pliku = n_nazwa;
}