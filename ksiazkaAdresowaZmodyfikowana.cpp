#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <conio.h>

using namespace std;

struct Adresat
{
int identyfikatoryPrzyjaciol = 0;
string imionaPrzyjaciol = "";
string nazwiskaPrzyjaciol = "";
string numeryTelefonowPrzyjaciol = "";
string adresyPrzyjaciol = "";
string emailePrzyjaciol = "";
};

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

void dodajPrzyjaciela(int wolnyIdentyfikator)
{
    cout<<"*######### WITAJ W FUNKCJI DODAWANIA NOWEGO KONTAKTU #########*"<<endl<<endl;
    cout<<"Kazdy nowy kontakt posiada swoj staly i niezmienny identyfikator"<<endl;
    cout<<"Nowy kontakt zostanie oznaczony pierwszym wolnym identyfikatorem, a wiec numerem: "<<wolnyIdentyfikator<<endl<<endl;
    cout<<"***###***###***###***###***###***###***###***###***###***###***"<<endl<<endl;
    string danePrzyjaciela = zbieranieInformacjiOPrzyjacielu();
    fstream plik;
    plik.open("ksiazkaAdresowaZmodyfikowana.txt", ios::out | ios::app);
    if (plik.good())
    {
        plik<<wolnyIdentyfikator<<"|";
        plik<<danePrzyjaciela;
        plik<<endl;
        plik.close();
        cout<<"Przyjaciel dodany do listy"<<endl;
        Sleep(1000);
    }
    else cout<<"Nie mozna otworzyc pliku: KsiazkaAdresowa.txt"<<endl;
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
                adresat.imionaPrzyjaciol = pojedynczaDanaAdresata;
                break;
            case 3:
                adresat.nazwiskaPrzyjaciol = pojedynczaDanaAdresata;
                break;
            case 4:
                adresat.numeryTelefonowPrzyjaciol = pojedynczaDanaAdresata;
                break;
            case 5:
                adresat.adresyPrzyjaciol = pojedynczaDanaAdresata;
                break;
            case 6:
                adresat.emailePrzyjaciol = pojedynczaDanaAdresata;
                break;
            }
            pojedynczaDanaAdresata = "";
            numerPojedynczejDanejAdresata++;
        }
    }
    return adresat;
}
vector <Adresat> wczytajAdresatowZPliku(vector <Adresat> &adresaci)
{
    Adresat adresat;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";

    fstream plikTekstowy;
    plikTekstowy.open("ksiazkaAdresowaZmodyfikowana.txt", ios::in);

    if (plikTekstowy.good() == true)
    {
        while (getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami))
        {
            adresat = pobierzDaneAdresata(daneJednegoAdresataOddzielonePionowymiKreskami);
            adresaci.push_back(adresat);
        }
        plikTekstowy.close();
        daneJednegoAdresataOddzielonePionowymiKreskami.clear();
    }
    return adresaci;
}
int wyswietlWszystkichPrzyjaciol(int iloscDanych)
{
    int numerPorzadkowy = 0;
    if(iloscDanych == 0)
    {
        cout<<"W ksiaze adresowej nie znajduje sie zaden kontakt! W Menu Glownym wybierz -1- i dodaj kontakt"<<endl;
        Sleep(1500);
    }
    else
    {
        fstream plik;
        plik.open("ksiazkaAdresowaZmodyfikowana.txt",ios::in);
        cout<<"************** AKTUALNA LISTA WSZYSTKICH KONTAKTOW **************"<<endl<<endl;

        string pobranaLinia;

        while(getline(plik,pobranaLinia))
        {
            numerPorzadkowy++;
            cout<<numerPorzadkowy<<".   ";
            cout<<pobranaLinia<<endl;
        }
        cout<<endl;
        cout<<"************************ KONIEC LISTY ***************************"<<endl;
        cout<<endl;
        plik.close();
        pobranaLinia.clear();
    }
    return numerPorzadkowy;
}
void wyswietlPrzyjaciolPoNazwisku(int iloscKontaktow, vector <Adresat> &adresaci)
{
    string wyrazNazwisko;
    cout<<"Podaj nazwisko: "<<endl;
    cin>>wyrazNazwisko;
    cout<<endl;
    int znalezionePozycjeNazwisko = 0;
    cout<<"OTO DANE KONTAKTOWE OSOB O NAZWISKU: "<<wyrazNazwisko<<endl<<endl;

    for(int i = 0; i < adresaci.size(); i++)
    {
        if(adresaci[i].nazwiskaPrzyjaciol == wyrazNazwisko)
        {
            cout<<"Numer identyfikacyjny: "<<adresaci[i].identyfikatoryPrzyjaciol<<endl;
            cout<<"Imie: "<<adresaci[i].imionaPrzyjaciol<<endl;
            cout<<"Nazwisko: "<<adresaci[i].nazwiskaPrzyjaciol<<endl;
            cout<<"Numer Telefonu: "<<adresaci[i].numeryTelefonowPrzyjaciol<<endl;
            cout<<"Adres: "<<adresaci[i].adresyPrzyjaciol<<endl;
            cout<<"Email: "<<adresaci[i].emailePrzyjaciol<<endl;
            cout<<endl;
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
        cout<<"Wyglada na to, ze nie dodales jeszcze osoby o nazwisku "<<wyrazNazwisko<<endl<<endl;
        cout<<"Zrob to korzystajac z menu glownego, do ktorego zostaniesz teraz przekierowany";
    }
    cout<<endl;
}
void wyswietlPrzyjaciolPoimieniu(int iloscKontaktow, vector <Adresat> &adresaci)
{
    string wyrazImie;
    cout<<"Podaj imie: "<<endl;
    cin>>wyrazImie;
    cout<<endl;
    int znalezionePozycjeImie = 0;
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
vector <string> utworzBazeKontaktowZpliku()
{
    vector <string> kontaktyZapisaneWPliku;
    fstream plik;

    plik.open("ksiazkaAdresowaZmodyfikowana.txt",ios::in);

    if( plik.good() == false)
    {
        cout<<"Plik nie istnieje!";
        exit(0);
    }
    string liniaPobrana;
    while(getline(plik,liniaPobrana))
    {
        kontaktyZapisaneWPliku.push_back(liniaPobrana);
    }
    liniaPobrana.clear();
    plik.close();

    return kontaktyZapisaneWPliku;
}
int sprawdzIloscKontaktow()
{
        fstream plik;
        plik.open("ksiazkaAdresowaZmodyfikowana.txt",ios::in);
        string liniaPobrana;
        int iloscDanych = 0;
        if( plik.good() == true)
        {
            while(getline(plik,liniaPobrana))
            {
                iloscDanych++;
            }
            liniaPobrana.clear();
            plik.close();
        }
    return iloscDanych;
}
void zapiszZmianyDoPliku(vector <string> wektorDanych)
{
    fstream plik;
    plik.open("ksiazkaAdresowaZmodyfikowana.txt", ios::out);

    if (plik.good())
    {
        for(int x = 0; x < wektorDanych.size(); x++)
        {
            plik<<wektorDanych[x]<<endl;
        }
        plik.close();
        wektorDanych.clear();
    }
}
void usunPrzyjaciela(int pozycjaDoUsuniecia, int sumaKontaktow,vector <string> &listaKontaktow)
{
    if((pozycjaDoUsuniecia > 0) && (pozycjaDoUsuniecia <= sumaKontaktow))
    {
        vector <string> zbiorPobranychLinii = utworzBazeKontaktowZpliku();

        zbiorPobranychLinii.erase(zbiorPobranychLinii.begin() + (pozycjaDoUsuniecia-1));

        zapiszZmianyDoPliku(zbiorPobranychLinii);

        system("cls");
        cout<<"Kontakt usuniety z listy"<<endl;
        Sleep(1000);
    }

    else if(pozycjaDoUsuniecia == 0)
    {
        Sleep(500);
    }
    else
    {
        system("cls");
        cout<<"Podaj poprawny numer"<<endl;
        Sleep(1000);
    }

}
string odczytajIdentyfikatorEdytowanegoKontaktu(string liniaDoSprawdzenia)
{
    string biezacaLinia = liniaDoSprawdzenia;
    string identyfikatorEdytowanegoKontaktu = "";
    int sprawdzanyZnak = 0;
    while(biezacaLinia[sprawdzanyZnak] != '|')
    {
        identyfikatorEdytowanegoKontaktu +=biezacaLinia[sprawdzanyZnak];
        sprawdzanyZnak++;
    }
    identyfikatorEdytowanegoKontaktu += "|";

    return identyfikatorEdytowanegoKontaktu;
    identyfikatorEdytowanegoKontaktu.clear();
}
vector <int> utworzVectorZidentyfikatorami()
{
    fstream plik;
    plik.open("ksiazkaAdresowaZmodyfikowana.txt",ios::in);
    string liniaPobrana, pobranaCyfra;
    int liczbaPoKonwersji, iloscDanych = 1;
    vector <int> identyfikatory;
    if( plik.good() == true)
    {
        while(getline(plik,liniaPobrana))
        {
            pobranaCyfra = odczytajIdentyfikatorEdytowanegoKontaktu(liniaPobrana);
            liczbaPoKonwersji =  atoi(pobranaCyfra.c_str());
            identyfikatory.push_back(liczbaPoKonwersji);
        }
        liniaPobrana.clear();
        plik.close();
    }
    return identyfikatory;
}
int znajdzWolnyIdentyfikator (int indeks, vector <int> &iDprzyjaciol)
{
    sort(iDprzyjaciol.begin(), iDprzyjaciol.end());

    int ostatniElement = iDprzyjaciol.size()-1,wolneID = 0;

    if(iDprzyjaciol.empty() == true)
    {
        return wolneID = 1;
    }
    else
    {
        wolneID += iDprzyjaciol[ostatniElement] + 1;
        return wolneID;
    }
    iDprzyjaciol.clear();
}
void edytujKontakt(int pozycjaDoEdycji, int indeks, vector <Adresat> &adresaci)
{
    if((pozycjaDoEdycji > 0) && (pozycjaDoEdycji <= indeks))
    {
        vector <string> wszystkieLinie = utworzBazeKontaktowZpliku();

        system("cls");
        cout<<"Wchodzisz w edycje kontaktu pod numerem: "<<pozycjaDoEdycji<<endl;
        string liniaDoEdycji = wszystkieLinie[pozycjaDoEdycji-1];
        cout<<liniaDoEdycji<<endl<<endl;
        cout<<"Potwierdz dowolnym klawiszem"<<endl;
        getch();
        cout<<endl;
        cout<<"Identyfikator edytowanego kontaktu: "<<adresaci[pozycjaDoEdycji-1].identyfikatoryPrzyjaciol<<endl;
        cout<<"Obecne Imie: "<<adresaci[pozycjaDoEdycji-1].imionaPrzyjaciol<<endl;
        cout<<"Obecne Nazwisko: "<<adresaci[pozycjaDoEdycji-1].nazwiskaPrzyjaciol<<endl;
        cout<<"Aktualny Numer Telefonu: "<<adresaci[pozycjaDoEdycji-1].numeryTelefonowPrzyjaciol<<endl;
        cout<<"Adres: "<<adresaci[pozycjaDoEdycji-1].adresyPrzyjaciol<<endl;
        cout<<"Zapisany Email: "<<adresaci[pozycjaDoEdycji-1].emailePrzyjaciol<<endl;
        cout<<endl;

        string idKontaktuEdytowanego = odczytajIdentyfikatorEdytowanegoKontaktu(liniaDoEdycji);
        string noweDaneEdytowanegoKontaktu = idKontaktuEdytowanego+zbieranieInformacjiOPrzyjacielu();
        wszystkieLinie.erase(wszystkieLinie.begin() + (pozycjaDoEdycji-1));
        wszystkieLinie.insert(wszystkieLinie.begin() + (pozycjaDoEdycji-1),noweDaneEdytowanegoKontaktu);
        noweDaneEdytowanegoKontaktu.clear();
        liniaDoEdycji.clear();
        zapiszZmianyDoPliku(wszystkieLinie);
        system("cls");
        cout<<"Kontakt zmodyfikowany"<<endl;
        Sleep(1000);
    }

    else if(pozycjaDoEdycji == 0)
    {
        Sleep(500);
    }
    else
    {
        system("cls");
        cout<<"Podaj poprawny numer"<<endl;
        Sleep(1000);
    }
}
void wyszukiwanieKontaktowWKiazceAdresowej(int indeks)
{
    while(1)
    {
        vector <Adresat> adresaci;
        adresaci.clear();
        wczytajAdresatowZPliku(adresaci);
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
            wyswietlWszystkichPrzyjaciol(indeks);
            cout<<endl;
            cout<<"Nacisnij dowolny klawisz, aby kontynuowac";
            getch();
            break;
        }
        case '2':
        {
            system("cls");
            wyswietlPrzyjaciolPoimieniu(indeks,adresaci);
            cout<<endl;
            cout<<"Nacisnij dowolny klawisz, aby kontynuowac";
            getch();
            break;
        }
        case '3':
        {
            system("cls");
            wyswietlPrzyjaciolPoNazwisku(indeks,adresaci);
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
}
void pokazMenuUsuwaniaDanegoKontaktu(int indeks)
{
    system("cls");
    wyswietlWszystkichPrzyjaciol(indeks);
    cout<<endl<<endl;
    if (indeks != 0)
    {
        cout<<"*************** WITAJ W FUNKCJI USUWANIA ZBEDNEGO KONTAKTU ***************"<<endl<<endl;
        cout<<"Wpisz pozycje do usuniecia podajac dany numer porzadkowy znajdujacy sie po lewej stronie kazdego kontaktu: "<<endl<<endl;
        cout<<"Wpisz -0-, aby wyjsc bez usuwania zadnego kontaktu"<<endl;
        int pozycjaDoUsuniecia;
        cin>>pozycjaDoUsuniecia;
        vector <string> linieZapisaneWPliku = utworzBazeKontaktowZpliku();
        usunPrzyjaciela(pozycjaDoUsuniecia,indeks, linieZapisaneWPliku);
    }
}
void wyswietlanieMenuEdycjiKontaktu(int indeks)
{
    vector <Adresat> adresaci;
    system("cls");
    wyswietlWszystkichPrzyjaciol(indeks);
    wczytajAdresatowZPliku(adresaci);
    cout<<endl<<endl;
    if(indeks != 0)
    {
        cout<<"*************** WITAJ W FUNKCJI EDYCJI KONTAKTU ***************"<<endl<<endl;
        cout<<"Wpisz pozycje do edycji podajac dany numer porzadkowy znajdujacy sie po lewej stronie kazdego kontaktu: "<<endl<<endl;
        cout<<"Wpisz -0-, aby wyjsc bez dokonywania jakichkolwiek zmian w ksiazce adresowej"<<endl;
        int pozycjaDoEdycji;
        cin>>pozycjaDoEdycji;
        wczytajAdresatowZPliku(adresaci);
        edytujKontakt(pozycjaDoEdycji,indeks, adresaci);
    }
}
void wyswietlMenuGlowne( vector <Adresat> &adresaci)
{
    int indeks, wolnyIdentyfikator = 0;
    char wybor;
    while(1)
    {
        system("cls");
        int indeks = sprawdzIloscKontaktow();
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
        wybor = getch();
        cout<<endl;

        wczytajAdresatowZPliku(adresaci);
        switch (wybor)
        {
        case '1':
        {
            system("cls");
            vector <int> identyfikatoryPrzyjaciol = utworzVectorZidentyfikatorami();
            int wolnyIdentyfikator = znajdzWolnyIdentyfikator(indeks, identyfikatoryPrzyjaciol);
            dodajPrzyjaciela(wolnyIdentyfikator);
            break;
        }
        case '2':
        {
            wyszukiwanieKontaktowWKiazceAdresowej(indeks);
            break;
        }
        case '3':
        {
            pokazMenuUsuwaniaDanegoKontaktu(indeks);
            break;
        }
        case '4':
        {
            wyswietlanieMenuEdycjiKontaktu(indeks);
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
int main()
{
    vector <Adresat> grupaAdresatow;

    wyswietlMenuGlowne(grupaAdresatow);

    return 0;
}
