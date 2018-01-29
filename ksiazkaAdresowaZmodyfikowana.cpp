#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <conio.h>
#include <sstream>

using namespace std;

string nazwaPlikuZrodlowego = "ksiazkaAdresowaZmodyfikowana.txt";
string nazwaPlikuZuzytkownikami = "uzytkownicy.txt";

struct Adresat
{
    int identyfikatoryPrzyjaciol = 0;
    int biezacyIdentyfikatorUzytkownika = 0;
    string imionaPrzyjaciol = "";
    string nazwiskaPrzyjaciol = "";
    string numeryTelefonowPrzyjaciol = "";
    string adresyPrzyjaciol = "";
    string emailePrzyjaciol = "";
};
struct Uzytkownik
{
    int idUzytkownika = 0;
    string nazwaUzytkownika = "";
    string hasloUzytkownika = "";
};
string konwersjaIntNaString(int liczba)
{
    ostringstream ss;
    ss << liczba;
    string str = ss.str();

    return str;
}
string zbieranieInformacjiOPrzyjacielu()
{
    string nowyKontakt = "",znacznikPodzialuDanychWKontakcie = "|",imie, nazwisko,  numerTelefonu, adres,email;
    cout<<"Podaj imie: "<<endl;
    cin>>imie;
    nowyKontakt += (imie+=znacznikPodzialuDanychWKontakcie);
    cout<<endl;
    cout<<"Podaj nazwisko: "<<endl;
    cin>>nazwisko;
    nowyKontakt += (nazwisko+=znacznikPodzialuDanychWKontakcie);
    cout<<endl;
    cout<<"Podaj nr telefonu: "<<endl;
    cin.sync();
    getline(cin,numerTelefonu);
    nowyKontakt += (numerTelefonu+=znacznikPodzialuDanychWKontakcie);
    cout<<endl;
    cout<<"Podaj adres: "<<endl;
    cin.sync();
    getline(cin,adres);
    nowyKontakt += (adres+=znacznikPodzialuDanychWKontakcie);
    cout<<endl;
    cout<<"Podaj adres e-mail: "<<endl;
    cin>>email;
    nowyKontakt += (email+=znacznikPodzialuDanychWKontakcie);
    cout<<endl;

    return nowyKontakt;
}
string zamienPierwszaLitereNaDuzaAPozostaleNaMale(string tekst)
{
    if (!tekst.empty())
    {
        transform(tekst.begin(), tekst.end(), tekst.begin(), ::tolower);
        tekst[0] = toupper(tekst[0]);
    }
    return tekst;
}
Adresat pobierzDaneAdresata(string daneAdresataOddzielonePionowymiKreskami)
{
    Adresat adresat;
    string pojedynczaDanaAdresata = "";
    int numerPojedynczejDanejAdresata = 1;

    for (int pozycjaZnaku = 0; pozycjaZnaku < daneAdresataOddzielonePionowymiKreskami.length(); pozycjaZnaku++)
    {
        if (daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku] != '|')
            pojedynczaDanaAdresata += daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku];
        else
        {
            switch(numerPojedynczejDanejAdresata)
            {
            case 1:
                adresat.identyfikatoryPrzyjaciol = atoi(pojedynczaDanaAdresata.c_str());
                break;
            case 2:
                adresat.biezacyIdentyfikatorUzytkownika = atoi(pojedynczaDanaAdresata.c_str());
            case 3:
                adresat.imionaPrzyjaciol = pojedynczaDanaAdresata;
                break;
            case 4:
                adresat.nazwiskaPrzyjaciol = pojedynczaDanaAdresata;
                break;
            case 5:
                adresat.numeryTelefonowPrzyjaciol = pojedynczaDanaAdresata;
                break;
            case 6:
                adresat.adresyPrzyjaciol = pojedynczaDanaAdresata;
                break;
            case 7:
                adresat.emailePrzyjaciol = pojedynczaDanaAdresata;
                break;
            }
            pojedynczaDanaAdresata = "";
            numerPojedynczejDanejAdresata++;
        }
    }
    return adresat;
}
void dodajPrzyjaciela(vector <int> &identyfikatoryAdresatow, int identyfikatorZalogowanegoUzytkownika)
{
    Adresat adresat;
    fstream plik;
    int wolnyIdentyfikator = 0, indeksLiczbDoSprawdzenia = 1;
    plik.open("ksiazkaAdresowaZmodyfikowana.txt", ios::out | ios::app);
    if (plik.good())
    {
        int ostatniElement = identyfikatoryAdresatow.size()-1;

        if(identyfikatoryAdresatow.empty()==true)
            wolnyIdentyfikator = 1;
        else
            for(int indeksWwektorzeID = 0; indeksWwektorzeID < identyfikatoryAdresatow.size(); indeksWwektorzeID++)
            {
                if(identyfikatoryAdresatow[indeksWwektorzeID] == ostatniElement+1)
                {
                    wolnyIdentyfikator += identyfikatoryAdresatow.size() +1;
                    break;
                }
                else if (identyfikatoryAdresatow[indeksWwektorzeID] == indeksLiczbDoSprawdzenia)
                    indeksLiczbDoSprawdzenia++;
                else
                {
                    wolnyIdentyfikator = indeksLiczbDoSprawdzenia;
                    break;
                }
            }

    cout<<"*######### WITAJ W FUNKCJI DODAWANIA NOWEGO KONTAKTU #########*"<<endl<<endl;
    cout<<"Kazdy nowy kontakt posiada swoj staly i niezmienny identyfikator"<<endl;
    cout<<"Nowy kontakt zostanie oznaczony pierwszym wolnym identyfikatorem, a wiec numerem: "<<wolnyIdentyfikator<<endl<<endl;
    cout<<"***###***###***###***###***##!#***###***###***###***###***###***"<<endl<<endl;
    string danePrzyjaciela = zbieranieInformacjiOPrzyjacielu();

        plik<<wolnyIdentyfikator<<"|";
        plik<<identyfikatorZalogowanegoUzytkownika<<"|";
        plik<<danePrzyjaciela;
        plik<<endl;
        plik.close();
        cout<<"Przyjaciel dodany do listy"<<endl;
        Sleep(1000);
    }
    else cout<<"Nie mozna otworzyc pliku: KsiazkaAdresowa.txt"<<endl;
}
Uzytkownik pobierzDaneUzytkownika (string daneUzytkownika)
{
   Uzytkownik uzytkownik;
    string pojedynczaDanaUzytkownika = "";
    int numerPojedynczejDanejUzytkownika = 1;

    for (int pozycjaZnaku = 0; pozycjaZnaku < daneUzytkownika.length(); pozycjaZnaku++)
    {
        if (daneUzytkownika[pozycjaZnaku] != '|')
            pojedynczaDanaUzytkownika += daneUzytkownika[pozycjaZnaku];
        else
        {
            switch(numerPojedynczejDanejUzytkownika)
            {
            case 1:
                uzytkownik.idUzytkownika = atoi(pojedynczaDanaUzytkownika.c_str());
                break;
            case 2:
                uzytkownik.nazwaUzytkownika = pojedynczaDanaUzytkownika;
                break;
            case 3:
                uzytkownik.hasloUzytkownika = pojedynczaDanaUzytkownika;
                break;
            }
            pojedynczaDanaUzytkownika = "";
            numerPojedynczejDanejUzytkownika++;
        }
    }
    return uzytkownik;
}
vector <Adresat> wczytajAdresatowZPliku(vector <Adresat> &adresaci, int identyfikatorZalogowanegoUzytkownika)
{
    Adresat adresat;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";
    vector<Adresat> adresaciNiedostepni;
    fstream plikTekstowy;
    plikTekstowy.open(nazwaPlikuZrodlowego.c_str(), ios::in);
    if (plikTekstowy.good() == true)
    {
          while (getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami))
            {
                adresat = pobierzDaneAdresata(daneJednegoAdresataOddzielonePionowymiKreskami);
                if(adresat.biezacyIdentyfikatorUzytkownika == identyfikatorZalogowanegoUzytkownika)
                adresaci.push_back(adresat);
            }
    }
    plikTekstowy.close();
    daneJednegoAdresataOddzielonePionowymiKreskami.clear();

    return adresaci;
}
vector <Adresat> wczytajPozostalychAdresatowZPliku(vector <Adresat> &adresaciNiezalogowanychUzytkownikow, int identyfikatorZalogowanegoUzytkownika)
{
    Adresat adresat;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";
    fstream plikTekstowy;
    plikTekstowy.open(nazwaPlikuZrodlowego.c_str(), ios::in);
    if (plikTekstowy.good() == true)
    {
          while (getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami))
            {
                adresat = pobierzDaneAdresata(daneJednegoAdresataOddzielonePionowymiKreskami);
                if(adresat.biezacyIdentyfikatorUzytkownika != identyfikatorZalogowanegoUzytkownika)
                {
                  adresaciNiezalogowanychUzytkownikow.push_back(adresat);
                }
            }
    }
    plikTekstowy.close();
    daneJednegoAdresataOddzielonePionowymiKreskami.clear();

    return adresaciNiezalogowanychUzytkownikow;
}
vector <int> pobierzIdentyfikatoryAdresatow(vector <Adresat> &adresaci,vector <Adresat> &adresaciNiezalogowanychUzytkownikow)
{
    vector <int> identyfikatoryAdresatow;
    identyfikatoryAdresatow.clear();
    for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
            identyfikatoryAdresatow.push_back(itr -> identyfikatoryPrzyjaciol);
    for (vector <Adresat>::iterator itr2 = adresaciNiezalogowanychUzytkownikow.begin(); itr2 != adresaciNiezalogowanychUzytkownikow.end(); itr2++)
            identyfikatoryAdresatow.push_back(itr2 -> identyfikatoryPrzyjaciol);
    sort( identyfikatoryAdresatow.begin(), identyfikatoryAdresatow.end() );
return identyfikatoryAdresatow;
}
vector <Uzytkownik> wczytajUzytkownikowZPliku(vector <Uzytkownik> &uzytkownicy)
{
    Uzytkownik uzytkownik;
    string daneJednegoUzytkownika = "";

    fstream plikTekstowy;
    plikTekstowy.open(nazwaPlikuZuzytkownikami.c_str(), ios::in);

    if(plikTekstowy.good() == true)
    {
        while(getline(plikTekstowy,daneJednegoUzytkownika))
        {
            uzytkownik = pobierzDaneUzytkownika(daneJednegoUzytkownika);
            uzytkownicy.push_back(uzytkownik);
        }
        plikTekstowy.close();
        daneJednegoUzytkownika.clear();
    }
    return uzytkownicy;
}
void dopiszUzytkownikaDoPliku(Uzytkownik uzytkownik)
{
    fstream plikTekstowy;
    plikTekstowy.open(nazwaPlikuZuzytkownikami.c_str(), ios::out | ios::app);

    if (plikTekstowy.good() == true)
    {
        plikTekstowy << uzytkownik.idUzytkownika << '|';
        plikTekstowy << uzytkownik.nazwaUzytkownika << '|';
        plikTekstowy << uzytkownik.hasloUzytkownika << '|'<<endl;
        plikTekstowy.close();

        cout << endl << "Uzytkownik zostal dodany" << endl;
        system("pause");
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
        system("pause");
    }
}
void rejestracja(vector <Uzytkownik> &uzytkownicy, int iloscUzytkownikow)
{
    Uzytkownik uzytkownik;
    string nazwa;
    if (uzytkownicy.empty() == true)
       uzytkownik.idUzytkownika = 1;
    else
       uzytkownik.idUzytkownika = uzytkownicy.back().idUzytkownika + 1;
    cout<<"Podaj nazwe uzytkownika: ";
    cin>>nazwa;

    int i = 0;
    while(i < iloscUzytkownikow)
    {
       for (vector <Uzytkownik>::iterator  itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
        if(itr -> nazwaUzytkownika == nazwa)
            {
                cout<<"Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
                cin>>nazwa;
                i=0;
            }
        else i++;
        }
    }
    uzytkownik.nazwaUzytkownika = nazwa;
    cout<<"Podaj haslo: ";
    cin>>uzytkownik.hasloUzytkownika;

    uzytkownicy.push_back(uzytkownik);
    dopiszUzytkownikaDoPliku(uzytkownik);

    cout<<"Konto zalozone" << endl;
    Sleep(1000);
}
int logowanie(vector <Uzytkownik> uzytkownicy,int iloscUzytkownikow)
{
    string nazwa, haslo;
    cout<<"Podaj login: ";
    cin>>nazwa;

        for (vector <Uzytkownik>::iterator  itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
        if(itr -> nazwaUzytkownika == nazwa)
        {
            for(int proby = 0; proby < 3; proby++)
            {
                cout<<"Podaj haslo. Pozostalo prob "<<3-proby<<": ";
                cin>>haslo;
                if(itr -> hasloUzytkownika == haslo)
                {
                    cout<< "Zalogowales sie."<<endl;
                    Sleep(1000);
                    int idZalogowanegoUzytkownika = itr->idUzytkownika;
                    return idZalogowanegoUzytkownika;
                }
            }
            cout<<"Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba"<<endl;
            Sleep(3000);
            return 0;
        }
    }
    cout<<"Nie ma uzytkownika z takim loginem"<<endl;
    Sleep(1500);
    return 0;
}
void zapiszWszystkichUzytkownikowDoPlikuTekstowego(vector <Uzytkownik> &uzytkownicy, string nazwaPlikuZuzytkownikami)
{
    fstream plikTekstowy;
    string liniaZDanymiUzytkownika = "";

    plikTekstowy.open(nazwaPlikuZuzytkownikami.c_str(), ios::out);
    if (plikTekstowy.good())
    {
        for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
            liniaZDanymiUzytkownika += konwersjaIntNaString(itr -> idUzytkownika) + '|';
            liniaZDanymiUzytkownika += itr -> nazwaUzytkownika + '|';
            liniaZDanymiUzytkownika += itr -> hasloUzytkownika + '|';

            plikTekstowy << liniaZDanymiUzytkownika << endl;
            liniaZDanymiUzytkownika = "";
        }
        plikTekstowy.close();
    }
    else
    {
        cout << "Nie mozna otworzyc pliku KsiazkaAdresowa.txt" << endl;
    }
}
struct Dane
{
    int idAdresata = 0;
    string liniaZdanymi = "";
};
void zapiszAdresatowDoPlikuTekstowego(vector <Adresat> &adresaci, vector <Adresat> &adresaciNiedostepni, vector <int> &identyfikatoryAdresatow)
{
    fstream plikTekstowy;
    Dane daneAdresata;
    string liniaZDanymiAdresata = "";
    vector <Dane>daneWszystkichAdresatow;
    plikTekstowy.open(nazwaPlikuZrodlowego.c_str(), ios::out);
    if (plikTekstowy.good())
    {
    for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
         {
                liniaZDanymiAdresata += konwersjaIntNaString(itr->identyfikatoryPrzyjaciol) + '|';
                liniaZDanymiAdresata += konwersjaIntNaString(itr->biezacyIdentyfikatorUzytkownika)+ '|';
                liniaZDanymiAdresata += itr->imionaPrzyjaciol + '|';
                liniaZDanymiAdresata += itr->nazwiskaPrzyjaciol + '|';
                liniaZDanymiAdresata += itr->numeryTelefonowPrzyjaciol + '|';
                liniaZDanymiAdresata += itr->adresyPrzyjaciol + '|';
                liniaZDanymiAdresata += itr->emailePrzyjaciol + '|';
                daneAdresata.idAdresata = (itr->identyfikatoryPrzyjaciol);
                daneAdresata.liniaZdanymi = liniaZDanymiAdresata;
                daneWszystkichAdresatow.push_back(daneAdresata);
                liniaZDanymiAdresata = "";
         }
        for(vector <Adresat>::iterator itr2 = adresaciNiedostepni.begin(); itr2 != adresaciNiedostepni.end(); itr2++)
        {
                liniaZDanymiAdresata += konwersjaIntNaString(itr2->identyfikatoryPrzyjaciol) + '|';
                liniaZDanymiAdresata += konwersjaIntNaString(itr2->biezacyIdentyfikatorUzytkownika)+ '|';
                liniaZDanymiAdresata += itr2->imionaPrzyjaciol + '|';
                liniaZDanymiAdresata += itr2->nazwiskaPrzyjaciol + '|';
                liniaZDanymiAdresata += itr2->numeryTelefonowPrzyjaciol + '|';
                liniaZDanymiAdresata += itr2->adresyPrzyjaciol + '|';
                liniaZDanymiAdresata += itr2->emailePrzyjaciol + '|';
                daneAdresata.idAdresata = (itr2->identyfikatoryPrzyjaciol);
                daneAdresata.liniaZdanymi = liniaZDanymiAdresata;
                daneWszystkichAdresatow.push_back(daneAdresata);
                liniaZDanymiAdresata = "";
        }
        for (vector <int>::iterator itrx = identyfikatoryAdresatow.begin(); itrx != identyfikatoryAdresatow.end(); itrx++)
        {
            for (vector <Dane>::iterator itr3 = daneWszystkichAdresatow.begin(); itr3 != daneWszystkichAdresatow.end(); itr3++)
            {
            if(*itrx == itr3->idAdresata)
            plikTekstowy << itr3->liniaZdanymi<< endl;
            }
        }
        plikTekstowy.close();
    }
    else
        cout << "Nie mozna otworzyc pliku KsiazkaAdresowa.txt" << endl;
}
void zmianahasla(vector <Uzytkownik> uzytkownicy, int idZalogowanegoUzytkownika)
{
    string haslo;
    system("cls");
    cout<<"<<<<<<ZMIANA HASLA DOSTEPU<<<<<<<"<<endl;
    cout<<endl;
    cout<<"Podaj nowe haslo: ";
        for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
            if(itr -> idUzytkownika == idZalogowanegoUzytkownika)
                cin>>itr -> hasloUzytkownika;
        }
        zapiszWszystkichUzytkownikowDoPlikuTekstowego(uzytkownicy, nazwaPlikuZuzytkownikami);
        cout<<"Haslo zostalo zmienione" <<endl;
        Sleep(1000);
}
void wyswietlWszystkichPrzyjaciol(vector <Adresat> &adresaci)
{
    system("cls");
    cout<<"************** AKTUALNA LISTA TWOICH KONTAKTOW  **************"<<endl<<endl;
    if (!adresaci.empty())
    {
        for (vector <Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
                cout << "Id:                 " << itr -> identyfikatoryPrzyjaciol << endl;
                cout << "Id uzytkownika:     " << itr -> biezacyIdentyfikatorUzytkownika << endl;
                cout << "Imie:               " << itr -> imionaPrzyjaciol << endl;
                cout << "Nazwisko:           " << itr -> nazwiskaPrzyjaciol << endl;
                cout << "Numer telefonu:     " << itr -> numeryTelefonowPrzyjaciol << endl;
                cout << "Adres:              " << itr -> adresyPrzyjaciol << endl;
                cout << "Email:              " << itr -> emailePrzyjaciol << endl << endl;
        }
        cout << endl;
        cout<<"************************ KONIEC LISTY ***************************"<<endl;
    }
    else
    {
        cout<<"W ksiaze adresowej nie znajduje sie zaden kontakt Z Twoim identyfikatorem uzytkownika, a wiec nadal nie dodales zadnego kontaktu!"<<endl;
        cout<<"W Menu Glownym wybierz -1- i dodaj kontakt"<<endl;
    }

    system("pause");
}
void wyswietlPrzyjaciolPoNazwisku(vector <Adresat> &adresaci)
{
    string nazwiskoPoszukiwanegoAdresata = "";
    cout<<"Podaj nazwisko: "<<endl;
    cin>>nazwiskoPoszukiwanegoAdresata;
    cout<<endl;
    nazwiskoPoszukiwanegoAdresata = zamienPierwszaLitereNaDuzaAPozostaleNaMale(nazwiskoPoszukiwanegoAdresata);
    int znalezionePozycjeNazwisko = 0;
    cout<<"OTO DANE KONTAKTOWE OSOB O NAZWISKU: "<<nazwiskoPoszukiwanegoAdresata<<endl<<endl;

     for (vector <Adresat>::iterator  itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr -> nazwiskaPrzyjaciol == nazwiskoPoszukiwanegoAdresata)
            {
                cout << endl;
                cout << "Id:                 " << itr -> identyfikatoryPrzyjaciol << endl;
                cout << "Imie:               " << itr -> imionaPrzyjaciol << endl;
                cout << "Nazwisko:           " << itr -> nazwiskaPrzyjaciol << endl;
                cout << "Numer Telefonu:     " << itr -> numeryTelefonowPrzyjaciol << endl;
                cout << "Adres:              " << itr -> adresyPrzyjaciol << endl;
                cout << "Email:              " << itr -> emailePrzyjaciol << endl;
                znalezionePozycjeNazwisko++;
        }
    }
    cout<<endl<<endl;
    cout<<"********** KONIEC LISTY **********"<<endl;
    Sleep(1500);
    if(znalezionePozycjeNazwisko == 0)
    {
        system("cls");
        cout<<"Brak wynikow dla podanego nazwiska "<<endl;
        cout<<"*******************************************************************"<<endl;
        cout<<"Wyglada na to, ze nie dodales jeszcze osoby o nazwisku "<<nazwiskoPoszukiwanegoAdresata<<endl<<endl;
        cout<<"Zrob to korzystajac z menu glownego, do ktorego zostaniesz teraz przekierowany";
    }
}
void wyswietlPrzyjaciolPoimieniu( vector <Adresat> &adresaci)
{
    string wyrazImie;
    cout<<"Podaj imie: "<<endl;
    cin>>wyrazImie;
    cout<<endl;
    int znalezionePozycjeImie = 0;
    wyrazImie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(wyrazImie);
    cout<<"OTO DANE KONTAKTOWE OSOB O IMIENIU: "<<wyrazImie<<endl<<endl;

    for(int j = 0; j < adresaci.size(); j++)
    {
        if(adresaci[j].imionaPrzyjaciol == wyrazImie)
        {
            cout<<"Numer identyfikacyjny: "<<adresaci[j].identyfikatoryPrzyjaciol<<endl;
            cout<<"Imie: "<<adresaci[j].imionaPrzyjaciol<<endl;
            cout<<"Nazwisko: "<<adresaci[j].nazwiskaPrzyjaciol<<endl;
            cout<<"Numer Telefonu: "<<adresaci[j].numeryTelefonowPrzyjaciol<<endl;
            cout<<"Adres: "<<adresaci[j].adresyPrzyjaciol<<endl;
            cout<<"Email: "<<adresaci[j].emailePrzyjaciol<<endl;
            cout<<endl;
            znalezionePozycjeImie++;
        }
    }
    cout<<endl<<endl;
    cout<<"********** KONIEC LISTY **********"<<endl;
    Sleep(1500);
    if(znalezionePozycjeImie == 0)
    {
        system("cls");
        cout<<"Brak wynikow dla podanego imienia "<<endl;
        cout<<"*******************************************************************"<<endl;
        cout<<"Wyglada na to, ze nie dodales jeszcze osoby o imieniu "<<wyrazImie<<endl<<endl;
        cout<<"Zrob to korzystajac z menu glownego, do ktorego zostaniesz teraz przekierowany";
    }
    cout<<endl;
}
int sprawdzIloscKontaktow(string nazwaPlikuZrodlowego)
{
        fstream plik;
        plik.open(nazwaPlikuZrodlowego.c_str(),ios::in);
        string liniaPobrana;
        int iloscDanych = 0;
        if( plik.good() == true)
        {
            while(getline(plik,liniaPobrana))
                iloscDanych++;
        }
        liniaPobrana.clear();
        plik.close();
    return iloscDanych;
}
void usunAdresata(vector <Adresat> &adresaci, vector <Adresat> &adresaciNiezalogowanychUzytkownikow, vector <int> &identyfikatoryAdresatow)
{
    int idUsuwanegoAdresata = 0;
    char znak;
    bool czyIstniejeAdresat = false;

    if (!adresaci.empty())
    {
        cout<<"*************** WITAJ W FUNKCJI USUWANIA ZBEDNEGO KONTAKTU ***************"<<endl<<endl;
        cout<<"Wpisz pozycje do usuniecia podajac dany numer identyfikacyjny znajdujacy sie po lewej stronie kazdego kontaktu: "<<endl<<endl;
        cin >> idUsuwanegoAdresata;

        if (cin.fail())
        {
            cout << endl << "Wprowadzono niepoprawne dane. Powrot do menu glownego" << endl;
            cin.clear();
            cin.sync();
        }
        else
        {
            for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
            {
                if (itr -> identyfikatoryPrzyjaciol == idUsuwanegoAdresata)
                {
                    czyIstniejeAdresat = true;
                    cout << endl << endl << "Potwierdz naciskajac klawisz 't': ";
                    cin >> znak;
                    if (znak == 't')
                    {
                        itr = adresaci.erase(itr);
                        cout << endl << endl << "Szukany adresat zostal USUNIETY" << endl << endl;

                        zapiszAdresatowDoPlikuTekstowego(adresaci,adresaciNiezalogowanychUzytkownikow,identyfikatoryAdresatow);
                        break;
                    }
                    else
                    {
                        cout << endl << endl << "Wybrany adresat NIE zostal usuniety" << endl << endl;
                        break;
                    }
                }
            }
            if (czyIstniejeAdresat == false)
                cout << endl << "Nie ma takiego adresata w ksiazce adresowej" << endl << endl;
        }
    }
    else
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    system("pause");
}
void edytujAdresata(vector <Adresat> &adresaci,vector <Adresat> &adresaciNiezalogowanychUzytkownikow,vector <int> &identyfikatoryAdresatow)
{
    int idWybranegoAdresata = 0;
    char wybor;
    bool czyIstniejeAdresat = false;

    system("cls");
    if (!adresaci.empty())
    {
        cout<<"*************** WITAJ W FUNKCJI EDYCJI KONTAKTU ***************"<<endl<<endl;
        cout<<"Wpisz pozycje do edycji podajac dany numer identyfikacyjny znajdujacy sie po lewej stronie kazdego kontaktu: "<<endl<<endl;
        cin >> idWybranegoAdresata;

        if (cin.fail())
        {
            cout << endl << "Wprowadzono niepoprawne dane. Powrot do menu glownego" << endl << endl;
            cin.clear();
            cin.sync();
        }
        else
        {
            for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
            {
                if (itr -> identyfikatoryPrzyjaciol == idWybranegoAdresata)
                {
                    czyIstniejeAdresat = true;

                    cout << endl << "Ktore dane zaktualizowac: " << endl;
                    cout << "1 - Imie" << endl;
                    cout << "2 - Nazwisko" << endl;
                    cout << "3 - Numer telefonu" << endl;
                    cout << "4 - Email" << endl;
                    cout << "5 - Adres" << endl;
                    cout << "6 - Powrot " << endl;
                    cout << endl << "Wybierz 1-6: ";
                    cin >> wybor;
                    switch (wybor)
                    {
                    case '1':
                        cout << "Podaj nowe imie: ";
                        cin >> itr -> imionaPrzyjaciol;
                        itr -> imionaPrzyjaciol = zamienPierwszaLitereNaDuzaAPozostaleNaMale(itr -> imionaPrzyjaciol);
                        cout << endl << "Imie zostalo zmienione" << endl << endl;
                        zapiszAdresatowDoPlikuTekstowego(adresaci,adresaciNiezalogowanychUzytkownikow,identyfikatoryAdresatow);
                        break;
                    case '2':
                        cout << "Podaj nowe nazwisko: ";
                        cin >> itr -> nazwiskaPrzyjaciol;
                        itr -> nazwiskaPrzyjaciol = zamienPierwszaLitereNaDuzaAPozostaleNaMale(itr -> nazwiskaPrzyjaciol);
                        cout << endl << "Nazwisko zostalo zmienione" << endl << endl;
                        zapiszAdresatowDoPlikuTekstowego(adresaci,adresaciNiezalogowanychUzytkownikow,identyfikatoryAdresatow);
                        break;
                    case '3':
                        cout << "Podaj nowy numer telefonu: ";
                        cin >> itr -> numeryTelefonowPrzyjaciol;
                        cout << endl << "Numer telefonu zostal zmieniony" << endl << endl;
                        zapiszAdresatowDoPlikuTekstowego(adresaci,adresaciNiezalogowanychUzytkownikow,identyfikatoryAdresatow);
                        break;
                    case '4':
                        cout << "Podaj nowy email: ";
                        cin >> itr -> emailePrzyjaciol;
                        cout << endl << "Email zostal zmieniony" << endl << endl;
                        zapiszAdresatowDoPlikuTekstowego(adresaci,adresaciNiezalogowanychUzytkownikow,identyfikatoryAdresatow);
                        break;
                    case '5':
                        cout << "Podaj nowy adres zamieszkania: ";
                        cin >> itr -> adresyPrzyjaciol;
                        itr -> adresyPrzyjaciol = zamienPierwszaLitereNaDuzaAPozostaleNaMale(itr -> adresyPrzyjaciol);
                        cout << endl << "Adres zostal zmieniony" << endl << endl;
                        zapiszAdresatowDoPlikuTekstowego(adresaci,adresaciNiezalogowanychUzytkownikow,identyfikatoryAdresatow);
                        break;
                    case '6':
                        cout << endl << "Powrot do menu glownego" << endl << endl;
                        break;
                    default:
                        cout << endl << "Nie ma takiej opcji w menu! Powrot do menu glownego." << endl << endl;
                        break;
                    }
                }
            }
            if (czyIstniejeAdresat == false)
                cout << endl << "Nie ma takiego adresata w ksiazce adresowej." << endl << endl;
        }
    }
    else
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    system("pause");
}
void wyswietlMenuGlowne( vector <Adresat> &adresaci, vector <Adresat> &adresaciNiezalogowanychUzytkownikow, vector <Uzytkownik> &uzytkownicy)
{
    int indeks, wolnyIdentyfikator = 0,idZalogowanegoUzytkownika = 0,iloscUzytkownikow = 0;
    char wybor;
    while(1)
    {
        if (idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            wczytajUzytkownikowZPliku(uzytkownicy);
            cout<<"1. Rejestracja"<<endl;
            cout<<"2. Logowanie"<<endl;
            cout<<"3. Zakoncz program"<<endl;
            wybor = getch();

         iloscUzytkownikow = sprawdzIloscKontaktow(nazwaPlikuZuzytkownikami);
         if (wybor =='1')
            {
                rejestracja(uzytkownicy,iloscUzytkownikow);
            }
            else if (wybor == '2')
            {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy,iloscUzytkownikow);

                while(idZalogowanegoUzytkownika != 0)
                {
                    system("cls");
                    int indeks = sprawdzIloscKontaktow(nazwaPlikuZrodlowego);
                    adresaci.clear();
                    vector <Adresat> adresaciZalogowanegoUzytkownika;
                    vector <Adresat> adresaciNiezalogowanychUzytkownikow;
                    adresaciZalogowanegoUzytkownika = wczytajAdresatowZPliku(adresaci,idZalogowanegoUzytkownika);
                    adresaciNiezalogowanychUzytkownikow = wczytajPozostalychAdresatowZPliku(adresaciNiezalogowanychUzytkownikow,idZalogowanegoUzytkownika);
                    vector <int> identyfikatoryAdresatow = pobierzIdentyfikatoryAdresatow(adresaciZalogowanegoUzytkownika,adresaciNiezalogowanychUzytkownikow);

                    cout<<"******************* WITAJ W KSIAZCE ADRESOWEJ *******************"<<endl<<endl;
                    cout<<"************************** MENU GLOWNE **************************"<<endl<<endl;
                    cout<<"Aktualnie w ksiazce znajduje sie "
                    <<indeks<<" zapisanych kontaktow nalezacych do roznych uzytkownikow"<<endl;
                    cout<<"Twoja baza kontaktow liczy "<<adresaciZalogowanegoUzytkownika.size()<<" pozycji(e)"<<endl<<endl;
                    cout<<"1. Dodaj przyjaciela"<<endl;
                    cout<<"2. Wyszukuj przyjaciol"<<endl;
                    cout<<"3. Usun pozycje"<<endl;
                    cout<<"4. Edytuj dany kontakt"<<endl;
                    cout<<"5. Zmien haslo"<<endl;
                    cout<<"9. Wyjscie"<<endl<<endl;
                    cout<<"Wprowadz dany numer aby skorzystac z powyzszych opcji programu"<<endl;
                    wybor = getch();
                    cout<<endl;

                    switch (wybor)
                    {
                    case '1':
                    {
                    system("cls");
                    dodajPrzyjaciela(identyfikatoryAdresatow,idZalogowanegoUzytkownika);
                    break;
                    }
                    case '2':
                    {
                      while(1)
                        {
                        system("cls");
                        char wyborwyszukiwania;

                        cout<<"******OTO FUNKCJA WYSZUKIWANIA DANYCH KONTAKTOWYCH******"<<endl<<endl;
                        cout<<"1. Wyswietl wszystkich przyjaciol"<<endl;
                        cout<<"2. Wyszukaj po imieniu"<<endl;
                        cout<<"3. Wyszukaj po nazwisku"<<endl;
                        cout<<"Wprowadz numer odpowiadajacy danej wyszukiwarce"<<endl;
                        wyborwyszukiwania = getch();

                        switch(wyborwyszukiwania)
                        {
                        case '1':
                        {
                        system ("cls");
                        wyswietlWszystkichPrzyjaciol(adresaciZalogowanegoUzytkownika);
                        cout<<endl;
                        cout<<"Nacisnij dowolny klawisz, aby kontynuowac";
                        getch();
                        break;
                        }
                        case '2':
                        {
                        system("cls");
                        wyswietlPrzyjaciolPoimieniu(adresaciZalogowanegoUzytkownika);
                        cout<<endl;
                        cout<<"Nacisnij dowolny klawisz, aby kontynuowac";
                        getch();
                        break;
                        }
                        case '3':
                        {
                        system("cls");
                        wyswietlPrzyjaciolPoNazwisku(adresaciZalogowanegoUzytkownika);
                        cout<<endl;
                        cout<<"Nacisnij dowolny klawisz, aby kontynuowac";
                        getch();
                        break;
                        }
                        default:
                        {
                        cout<<"Wprowadziles niepoprawny numer"<<endl;
                        Sleep(1000);
                        }
                        }
                        break;
                        }
                    break;
                    }
                    case '3':
                    {
                        system("cls");
                        adresaciZalogowanegoUzytkownika.clear();
                        adresaci.clear();

                        vector <Adresat> adresaciZalogowanegoUzytkownika = wczytajAdresatowZPliku(adresaci,idZalogowanegoUzytkownika);
                        wyswietlWszystkichPrzyjaciol(adresaciZalogowanegoUzytkownika);
                        cout<<endl<<endl;
                        usunAdresata(adresaciZalogowanegoUzytkownika,adresaciNiezalogowanychUzytkownikow,identyfikatoryAdresatow);
                        break;
                    }
                    case '4':
                    {
                        system("cls");
                        adresaciZalogowanegoUzytkownika.clear();
                        adresaci.clear();
                        vector <Adresat> adresaciZalogowanegoUzytkownika = wczytajAdresatowZPliku(adresaci,idZalogowanegoUzytkownika);
                        wyswietlWszystkichPrzyjaciol(adresaciZalogowanegoUzytkownika);
                        cout<<endl<<endl;
                        edytujAdresata(adresaciZalogowanegoUzytkownika,adresaciNiezalogowanychUzytkownikow, identyfikatoryAdresatow);
                    break;
                    }
                    case '5':
                    {
                    zmianahasla(uzytkownicy,idZalogowanegoUzytkownika);
                    break;
                    }
                    case '9': exit(0);
                    default:
                    {
                    cout<<"Wybierz poprawny numer!"<<endl;
                    Sleep(500);
                    }
                    }
                }
            }
            else if (wybor =='3') exit(0);
    }
}
}
int main()
{
    vector <Adresat> grupaAdresatow, adresaciNieaktywni;
    vector <Uzytkownik> uzytkownicy;

    wyswietlMenuGlowne(grupaAdresatow,adresaciNieaktywni, uzytkownicy);

    return 0;
}
