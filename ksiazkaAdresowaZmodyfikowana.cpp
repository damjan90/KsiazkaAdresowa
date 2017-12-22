#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

    vector <string> imionaPrzyjaciol; vector <string> nazwiskaPrzyjaciol; vector <string> numeryTelefonowPrzyjaciol;
    vector <string> adresyPrzyjaciol; vector <string> emailePrzyjaciol; vector <int> identyfikatoryPrzyjaciol;

string zamienIntNaString(int liczba){
   ostringstream ss;
   ss << liczba;
    string liczbaPoKonwersji = ss.str();
    return liczbaPoKonwersji;
}
string zbieranieInformacjiOPrzyjacielu(int indeks){
    string nowyKontakt = "";
    string znacznikPodzialuDanychWKontakcie = "|";
    int osobaId = indeks + 1;
    string liczbaWStringu = zamienIntNaString(osobaId);
    nowyKontakt += (liczbaWStringu+znacznikPodzialuDanychWKontakcie);
    string imie, nazwisko,  numerTelefonu, adres,email;
    cout<<"Podaj imie: "<<endl;cin>>imie;nowyKontakt += (imie+=znacznikPodzialuDanychWKontakcie);cout<<endl;
    cout<<"Podaj nazwisko: "<<endl;cin>>nazwisko;nowyKontakt += (nazwisko+=znacznikPodzialuDanychWKontakcie);cout<<endl;
    cout<<"Podaj nr telefonu: "<<endl;cin.sync();getline(cin,numerTelefonu);nowyKontakt += (numerTelefonu+=znacznikPodzialuDanychWKontakcie);cout<<endl;
    cout<<"Podaj adres: "<<endl;cin.sync();getline(cin,adres); nowyKontakt += (adres+=znacznikPodzialuDanychWKontakcie);cout<<endl;
    cout<<"Podaj adres e-mail: "<<endl;cin>>email; nowyKontakt += (email+=znacznikPodzialuDanychWKontakcie);cout<<endl;
    imie.clear();nazwisko.clear();numerTelefonu.clear();adres.clear();email.clear();
    return nowyKontakt;

}
void dodajPrzyjacielaDoPliku(int indeks){

    string danePrzyjaciela = zbieranieInformacjiOPrzyjacielu(indeks);

    fstream plik;
    plik.open("ksiazkaAdresowaZmodyfikowana.txt", ios::out | ios::app);
    if (plik.good()){

        plik << danePrzyjaciela;
        plik<<endl;

        plik.close();

        cout<<"Przyjaciel dodany do listy" << endl;
        Sleep(1000);
    }
    else{
        cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;
    }
    indeks++;
}
int WczytajZPlikuDanePrzyjaciol(){
    fstream plik;

    plik.open("ksiazkaAdresowaZmodyfikowana.txt",ios::in);

    if( plik.good()==false){
        cout<<"Plik nie istnieje!";exit(0);
    }

    string tymczasowy, linia;
    int nr_linii=1;int indeks = 0;int indeksliterWLinice = 0;
    while(getline(plik,linia)){
        do{
            if(linia[indeksliterWLinice]== '|'){
                switch(nr_linii){
                case 1:identyfikatoryPrzyjaciol.push_back(atoi(tymczasowy.c_str())) ;break;
                case 2:imionaPrzyjaciol.push_back(tymczasowy);break;
                case 3:nazwiskaPrzyjaciol.push_back(tymczasowy);break;
                case 4:numeryTelefonowPrzyjaciol.push_back(tymczasowy);break;
                case 5:adresyPrzyjaciol.push_back(tymczasowy);break;
                case 6:emailePrzyjaciol.push_back(tymczasowy);break;
                }
                tymczasowy.clear();nr_linii++;
            }
            else
            tymczasowy += linia[indeksliterWLinice];
            indeksliterWLinice++;
        }
        while(indeksliterWLinice<linia.length());

        if(nr_linii == 7){
            nr_linii= 1;indeksliterWLinice = 0;indeks++;
        }
    }
    plik.close();linia.clear();
    return indeks;
}
void wyswietlWszystkichPrzyjaciol(int indeks){
    if(indeks == 0){
        cout<<"W ksiaze adresowej nie znajduje sie zaden kontakt! W Menu Glownym wybierz -1- i dodaj kontakt"<<endl;
        Sleep(1500);
    }
    else{
        fstream plik;
        plik.open("ksiazkaAdresowaZmodyfikowana.txt",ios::in);
        cout<<"************** AKTUALNA LISTA WSZYSTKICH KONTAKTOW **************"<<endl<<endl;
        string linia;
        while(getline(plik,linia)){
         cout<<linia<<endl;
        }
        cout<<endl;
        cout<<"************************ KONIEC LISTY ***************************"<<endl;cout<<endl;
        plik.close();linia.clear();
    }
}
void wyswietlPrzyjaciolPoNazwisku(int indeks){

    string wyraz;
    cout<<"Podaj nazwisko: "<<endl;
    cin>>wyraz;cout<<endl;
    int znalezionePozycje = 0;
    cout<<"OTO DANE KONTAKTOWE OSOB O NAZWISKU: "<<wyraz<<endl<<endl;

        for(int j = 0; j<indeks; j++){
            if(wyraz == nazwiskaPrzyjaciol[j]){
                cout<<"Numer porzadkowy: "<<identyfikatoryPrzyjaciol[j]<<endl;
                cout<<"Imie: "<<imionaPrzyjaciol[j]<<endl;
                cout<<"Nazwisko: "<<nazwiskaPrzyjaciol[j]<<endl;
                cout<<"Numer Telefonu: "<<numeryTelefonowPrzyjaciol[j]<<endl;
                cout<<"Adres: "<<adresyPrzyjaciol[j]<<endl;
                cout<<"Email: "<<emailePrzyjaciol[j]<<endl;
                cout<<endl;
                znalezionePozycje++;
            }
        }
        cout<<endl<<endl;
        cout<<"********** KONIEC LISTY **********"<<endl;
        Sleep(1000);
    if(znalezionePozycje == 0){
            system("cls");
    cout<<"Brak wynikow dla podanego nazwiska "<<endl;
    cout<<"*******************************************************************"<<endl;
    cout<<"Wyglada na to, ze nie dodales jeszcze osoby o nazwisku "<<wyraz<<endl;
    cout<<"Zrob to korzystajac z menu glownego";}
    cout<<endl;
}
void wyswietlPrzyjaciolPoimieniu(int indeks){


    string wyraz;
    cout<<"Podaj imie: "<<endl;
    cin>>wyraz;cout<<endl;
    int znalezionePozycje = 0;
    cout<<"OTO DANE KONTAKTOWE OSOB O IMIENIU: "<<wyraz<<endl<<endl;

        for(int j = 0; j<indeks; j++){
            if(wyraz == imionaPrzyjaciol[j]){
                cout<<"Numer porzadkowy: "<<identyfikatoryPrzyjaciol[j]<<endl;
                cout<<"Imie: "<<imionaPrzyjaciol[j]<<endl;
                cout<<"Nazwisko: "<<nazwiskaPrzyjaciol[j]<<endl;
                cout<<"Numer Telefonu: "<<numeryTelefonowPrzyjaciol[j]<<endl;
                cout<<"Adres: "<<adresyPrzyjaciol[j]<<endl;
                cout<<"Email: "<<emailePrzyjaciol[j]<<endl;
                cout<<endl;
                znalezionePozycje++;
            }
        }
        cout<<endl<<endl;
        cout<<"********** KONIEC LISTY **********"<<endl;
        Sleep(1000);
    if(znalezionePozycje == 0){
            system("cls");
    cout<<"Brak wynikow dla podanego imienia "<<endl;
    cout<<"*******************************************************************"<<endl;
    cout<<"Wyglada na to, ze nie dodales jeszcze osoby o imieniu "<<wyraz<<endl;
    cout<<"Zrob to korzystajac z menu glownego";}
    cout<<endl;
}
int obliczIloscCyfrDoZastapienia(string liniaDoSprawdzenia){
    int liczbaCyfr = 0;
      string biezacaLinia = liniaDoSprawdzenia;
            int k = 0;
            while(biezacaLinia[k] != '|')
            {
                liczbaCyfr++;
                k++;
            }
   return liczbaCyfr;
}
void skorygujIzapiszPoprawneidentyfikatoryPrzyjaciol(vector <string> &wektorDanych){
  for(int j = 0; j<wektorDanych.size();j++)
    {
            int id = j+1;
            string liczbaPoKonwersji = zamienIntNaString(id);
            string tymczasowyWyraz = wektorDanych[j];
            int iloscCyfrDoWstawienia = obliczIloscCyfrDoZastapienia(tymczasowyWyraz);

        wektorDanych[j].replace(0,iloscCyfrDoWstawienia,liczbaPoKonwersji);
        tymczasowyWyraz.clear();
    }

    fstream plik;
    plik.open("ksiazkaAdresowaZmodyfikowana.txt", ios::out);

    if (plik.good()){
        for(int x = 0; x<wektorDanych.size();x++){
          plik << wektorDanych[x]<<endl;
        }
        plik.close();
        wektorDanych.clear();
}
}
vector <string> utworzBazeKontaktow(){
    vector <string> kontaktyZapisaneWPliku;
    fstream plik;

    plik.open("ksiazkaAdresowaZmodyfikowana.txt",ios::in);

    if( plik.good()==false){
        cout<<"Plik nie istnieje!"; exit(0);
    }
        string linia;
        while(getline(plik,linia)){
          kontaktyZapisaneWPliku.push_back(linia);
        }
    linia.clear();
    plik.close();

    return kontaktyZapisaneWPliku;
}
void usunPrzyjaciela(int pozycjaDoUsuniecia, int indeks){

  if((pozycjaDoUsuniecia>0)&&(pozycjaDoUsuniecia<=indeks))
{
    vector <string> Wszystkieliniie = utworzBazeKontaktow();

    Wszystkieliniie.erase(Wszystkieliniie.begin() + (pozycjaDoUsuniecia-1));

    skorygujIzapiszPoprawneidentyfikatoryPrzyjaciol(Wszystkieliniie);

        system("cls");
        cout<<"Kontakt usuniety z listy" << endl;
        Sleep(1000);
}

else if(pozycjaDoUsuniecia == 0){
   Sleep(500);
}
else
{
  system("cls");
  cout<<"Podaj poprawny numer"<<endl;
  Sleep(1000);
}

}
void edytujKontakt(int pozycjaDoEdycji, int indeks){

if((pozycjaDoEdycji>0)&&(pozycjaDoEdycji<=indeks))
{
    vector <string> Wszystkieliniie = utworzBazeKontaktow();

    system("cls");
    cout<<"Wchodzisz w edycje kontaktu pod numerem: "<<pozycjaDoEdycji<<endl;
    cout<<Wszystkieliniie[pozycjaDoEdycji-1]<<endl<<endl;
    cout<<"Potwierdz dowolnym klawiszem"<<endl;
    system ("pause");
    cout<<endl;
    cout<<"Obecne Imie: "<<imionaPrzyjaciol[pozycjaDoEdycji-1]<<endl;
    cout<<"Obecne Nazwisko: "<<nazwiskaPrzyjaciol[pozycjaDoEdycji-1]<<endl;
    cout<<"Aktualny Numer Telefonu: "<<numeryTelefonowPrzyjaciol[pozycjaDoEdycji-1]<<endl;
    cout<<"Adres: "<<adresyPrzyjaciol[pozycjaDoEdycji-1]<<endl;
    cout<<"Zapisany Email: "<<emailePrzyjaciol[pozycjaDoEdycji-1]<<endl;
    cout<<endl;

    string noweDaneEdytowanegoKontaktu = zbieranieInformacjiOPrzyjacielu(indeks);
    Wszystkieliniie.erase(Wszystkieliniie.begin() + (pozycjaDoEdycji-1));
    Wszystkieliniie.insert(Wszystkieliniie.begin() + (pozycjaDoEdycji-1),noweDaneEdytowanegoKontaktu);

    skorygujIzapiszPoprawneidentyfikatoryPrzyjaciol(Wszystkieliniie);
    system("cls");
    cout<<"Kontakt zmodyfikowany"<<endl;
    Sleep(1000);
}

else if(pozycjaDoEdycji == 0){
   Sleep(500);
}
else
{
  system("cls");
  cout<<"Podaj poprawny numer"<<endl;
  Sleep(1000);
}
}
void menuGlowne(){
    int indeks;
    char wybor;
    while(1){
        system("cls");
        int indeks = WczytajZPlikuDanePrzyjaciol();
        cout<<"******************* WITAJ W KSIAZCE ADRESOWEJ *******************"<<endl<<endl;
        cout<<"************************** MENU GLOWNE **************************"<<endl<<endl;
        cout<<"Aktualnie w ksiazce znajduje sie: "
            <<indeks<<" zapisanych kontaktow do Twych przyjaciol"<<endl<<endl;
        cout<<"1. Dodaj przyjaciela"<<endl;
        cout<<"2. Wyszukuj przyjaciol"<<endl;
        cout<<"3. Usun pozycje"<<endl;
        cout<<"4. Edytuj dany kontakt"<<endl;
        cout<<"9. Wyjscie"<<endl<<endl;
        cout<<"Wprowadz dany numer aby skorzystac z powyzszych opcji programu"<<endl;
        cin>>wybor;
        cout<<endl;

        if (wybor =='1'){
            system("cls");
            dodajPrzyjacielaDoPliku(indeks);
        }
        else if (wybor == '2'){
            while(1){
                system("cls");
                char wyborwyszukiwania;
                cout<<"1. Wyszukaj po nazwisku"<<endl;
                cout<<"2. Wyszukaj po imieniu"<<endl;
                cout<<"3. Wyswietl wszystkich przyjaciol"<<endl;
                cin>>wyborwyszukiwania;
                cout<<endl;
                indeks = WczytajZPlikuDanePrzyjaciol();
                if(wyborwyszukiwania =='1'){
                    wyswietlPrzyjaciolPoNazwisku(indeks);system("pause");
                }
                else if (wyborwyszukiwania =='2'){
                    wyswietlPrzyjaciolPoimieniu(indeks);system("pause");
                }
                else if (wyborwyszukiwania =='3'){
                    wyswietlWszystkichPrzyjaciol(indeks);system("pause");
                }
                break;
            }
        }
        else if (wybor == '3'){
            system("cls");
            wyswietlWszystkichPrzyjaciol(indeks); cout<<endl<<endl;
            if (indeks != 0)
            {
                cout<<"*************** WITAJ W FUNKCJI USUWANIA ZBEDNEGO KONTAKTU ***************"<<endl<<endl;
                cout<<"Wpisz pozycje do usuniecia podajac dany numer porzadkowy znajdujacy sie po lewej stronie kazdego kontaktu: "<<endl<<endl;
                cout<<"Wpisz -0-, aby wyjsc bez usuwania zadnego kontaktu"<<endl;
                int pozycjaDoUsuniecia;cin>>pozycjaDoUsuniecia;
                usunPrzyjaciela(pozycjaDoUsuniecia,indeks);
            }

        }
        else if (wybor == '4'){
            system("cls");
            wyswietlWszystkichPrzyjaciol(indeks); cout<<endl<<endl;
            if(indeks != 0)
            {
                cout<<"*************** WITAJ W FUNKCJI EDYCJI KONTAKTU ***************"<<endl<<endl;
                cout<<"Wpisz pozycje do edycji podajac dany numer porzadkowy znajdujacy sie po lewej stronie kazdego kontaktu: "<<endl<<endl;
                cout<<"Wpisz -0-, aby wyjsc bez dokonywania jakichkolwiek zmian w ksiazce adresowej"<<endl;
                int pozycjaDoEdycji;cin>>pozycjaDoEdycji;
                edytujKontakt(pozycjaDoEdycji,indeks);
            }

        }

        else if (wybor =='9'){
                exit(0);
        }
        else{
            cout<<"Wybierz poprawny numer!"<<endl;Sleep(1000);
        }

    }
}
int main()
{
   menuGlowne();

    return 0;
}
