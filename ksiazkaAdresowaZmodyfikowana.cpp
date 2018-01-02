#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <conio.h>

using namespace std;

vector <string> imionaPrzyjaciol;
vector <string> nazwiskaPrzyjaciol;
vector <string> numeryTelefonowPrzyjaciol;
vector <string> adresyPrzyjaciol;
vector <string> emailePrzyjaciol;
vector <int> identyfikatoryPrzyjaciol;

string zbieranieInformacjiOPrzyjacielu()
{
    string nowyKontakt = "";
    string znacznikPodzialuDanychWKontakcie = "|";
    string imie, nazwisko,  numerTelefonu, adres,email;
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
void dodajPrzyjaciela(int indeks, int wolnyIdentyfikator)
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
        plik << wolnyIdentyfikator<<"|";
        plik << danePrzyjaciela;
        plik<<endl;
        plik.close();
        cout<<"Przyjaciel dodany do listy" << endl;
        Sleep(1000);
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;
    }
    indeks++;
}
int wczytajZPlikuDanePrzyjaciol()
{
    int indeksDanych = 0;
    fstream plik;
    plik.open("ksiazkaAdresowaZmodyfikowana.txt",ios::in);
    if( plik.good()==false)
    {
        cout<<"Blad!!Plik z danymi nie istnieje!"<<endl;
        return indeksDanych;
    }

    string tymczasowy, odczytywanaLinia;
    int nrLinii=1;

    int indeksliterWLinice = 0;
    while(getline(plik,odczytywanaLinia))
    {
        do
        {
            if(odczytywanaLinia[indeksliterWLinice]== '|')
            {
                switch(nrLinii)
                {
                case 1:
                    identyfikatoryPrzyjaciol.push_back(atoi(tymczasowy.c_str())) ;
                    break;
                case 2:
                    imionaPrzyjaciol.push_back(tymczasowy);
                    break;
                case 3:
                    nazwiskaPrzyjaciol.push_back(tymczasowy);
                    break;
                case 4:
                    numeryTelefonowPrzyjaciol.push_back(tymczasowy);
                    break;
                case 5:
                    adresyPrzyjaciol.push_back(tymczasowy);
                    break;
                case 6:
                    emailePrzyjaciol.push_back(tymczasowy);
                    break;
                }
                tymczasowy.clear();
                nrLinii++;
            }
            else tymczasowy += odczytywanaLinia[indeksliterWLinice];
            indeksliterWLinice++;
        }
        while(indeksliterWLinice<odczytywanaLinia.length());
        if(nrLinii == 7)
        {
            nrLinii= 1;
            indeksliterWLinice = 0;
            indeksDanych++;
        }
    }
    plik.close();
    odczytywanaLinia.clear();
    return indeksDanych;
}
void wyswietlWszystkichPrzyjaciol(int iloscDanych)
{
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
        int numerPorzadkowy = 0;
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
}
void wyswietlPrzyjaciolPoNazwisku(int iloscKontaktow)
{
    string wyrazNazwisko;
    cout<<"Podaj nazwisko: "<<endl;
    cin>>wyrazNazwisko;
    cout<<endl;
    int znalezionePozycjeNazwisko = 0;
    cout<<"OTO DANE KONTAKTOWE OSOB O NAZWISKU: "<<wyrazNazwisko<<endl<<endl;

    for(int i = 0; i<iloscKontaktow; i++)
    {
        if(wyrazNazwisko == nazwiskaPrzyjaciol[i])
        {
            cout<<"Numer identyfikacyjny: "<<identyfikatoryPrzyjaciol[i]<<endl;
            cout<<"Imie: "<<imionaPrzyjaciol[i]<<endl;
            cout<<"Nazwisko: "<<nazwiskaPrzyjaciol[i]<<endl;
            cout<<"Numer Telefonu: "<<numeryTelefonowPrzyjaciol[i]<<endl;
            cout<<"Adres: "<<adresyPrzyjaciol[i]<<endl;
            cout<<"Email: "<<emailePrzyjaciol[i]<<endl;
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
void wyswietlPrzyjaciolPoimieniu(int iloscKontaktow)
{
    string wyrazImie;
    cout<<"Podaj imie: "<<endl;
    cin>>wyrazImie;
    cout<<endl;
    int znalezionePozycjeImie = 0;
    cout<<"OTO DANE KONTAKTOWE OSOB O IMIENIU: "<<wyrazImie<<endl<<endl;

    for(int j = 0; j<iloscKontaktow; j++)
    {
        if(wyrazImie == imionaPrzyjaciol[j])
        {
            cout<<"Numer identyfikacyjny: "<<identyfikatoryPrzyjaciol[j]<<endl;
            cout<<"Imie: "<<imionaPrzyjaciol[j]<<endl;
            cout<<"Nazwisko: "<<nazwiskaPrzyjaciol[j]<<endl;
            cout<<"Numer Telefonu: "<<numeryTelefonowPrzyjaciol[j]<<endl;
            cout<<"Adres: "<<adresyPrzyjaciol[j]<<endl;
            cout<<"Email: "<<emailePrzyjaciol[j]<<endl;
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

    if( plik.good()==false)
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
void zapiszZmianyDoPliku(vector <string> &wektorDanych)
{
    fstream plik;
    plik.open("ksiazkaAdresowaZmodyfikowana.txt", ios::out);

    if (plik.good())
    {
        for(int x = 0; x<wektorDanych.size(); x++)
        {
            plik << wektorDanych[x]<<endl;
        }
        plik.close();
        wektorDanych.clear();
    }
}
int znajdzWolnyIdentyfikator (int indeks, vector <int> &iDprzyjaciol)
{
    sort(iDprzyjaciol.begin(), iDprzyjaciol.end());

    int ostatniElement = iDprzyjaciol.size()-1;
    int wolneID = 0;

    if(iDprzyjaciol.empty()== true)
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
void usunPrzyjaciela(int pozycjaDoUsuniecia, int sumaKontaktow)
{
    if((pozycjaDoUsuniecia>0)&&(pozycjaDoUsuniecia<=sumaKontaktow))
    {
        vector <string> zbiorPobranychLinii = utworzBazeKontaktowZpliku();

        zbiorPobranychLinii.erase(zbiorPobranychLinii.begin() + (pozycjaDoUsuniecia-1));

        zapiszZmianyDoPliku(zbiorPobranychLinii);

        system("cls");
        cout<<"Kontakt usuniety z listy" << endl;
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
    int k = 0;
    while(biezacaLinia[k] != '|')
    {
        identyfikatorEdytowanegoKontaktu +=biezacaLinia[k];
        k++;
    }
    identyfikatorEdytowanegoKontaktu += "|";

    return identyfikatorEdytowanegoKontaktu;
    identyfikatorEdytowanegoKontaktu.clear();
}
void edytujKontakt(int pozycjaDoEdycji, int indeks)
{
    if((pozycjaDoEdycji>0)&&(pozycjaDoEdycji<=indeks))
    {
        vector <string> wszystkieLinie = utworzBazeKontaktowZpliku();

        system("cls");
        cout<<"Wchodzisz w edycje kontaktu pod numerem: "<<pozycjaDoEdycji<<endl;
        string liniaDoEdycji = wszystkieLinie[pozycjaDoEdycji-1];
        cout<<liniaDoEdycji<<endl<<endl;
        cout<<"Potwierdz dowolnym klawiszem"<<endl;
        getch();
        cout<<endl;
        cout<<"Identyfikator edytowanego kontaktu: "<<identyfikatoryPrzyjaciol[pozycjaDoEdycji-1]<<endl;
        cout<<"Obecne Imie: "<<imionaPrzyjaciol[pozycjaDoEdycji-1]<<endl;
        cout<<"Obecne Nazwisko: "<<nazwiskaPrzyjaciol[pozycjaDoEdycji-1]<<endl;
        cout<<"Aktualny Numer Telefonu: "<<numeryTelefonowPrzyjaciol[pozycjaDoEdycji-1]<<endl;
        cout<<"Adres: "<<adresyPrzyjaciol[pozycjaDoEdycji-1]<<endl;
        cout<<"Zapisany Email: "<<emailePrzyjaciol[pozycjaDoEdycji-1]<<endl;
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
void wyczyscBuforDanych()
{
    identyfikatoryPrzyjaciol.clear();
    imionaPrzyjaciol.clear();
    nazwiskaPrzyjaciol.clear();
    numeryTelefonowPrzyjaciol.clear();
    adresyPrzyjaciol.clear();
    emailePrzyjaciol.clear();
}
void wyszukiwanieKontaktowWKiazceAdresowej(int indeks)
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
            wyswietlWszystkichPrzyjaciol(indeks);
            cout<<endl;
            cout<<"Nacisnij dowolny klawisz, aby kontynuowac";
            getch();
            break;
        }
        case '2':
        {
            system("cls");
            wyswietlPrzyjaciolPoimieniu(indeks);
            cout<<endl;
            cout<<"Nacisnij dowolny klawisz, aby kontynuowac";
            getch();
            break;
        }
        case '3':
        {
            system("cls");
            wyswietlPrzyjaciolPoNazwisku(indeks);
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
        usunPrzyjaciela(pozycjaDoUsuniecia,indeks);
    }
}
void wyswietlanieMenuEdycjiKontaktu(int indeks)
{
    system("cls");
    wyswietlWszystkichPrzyjaciol(indeks);
    cout<<endl<<endl;
    if(indeks != 0)
    {
        cout<<"*************** WITAJ W FUNKCJI EDYCJI KONTAKTU ***************"<<endl<<endl;
        cout<<"Wpisz pozycje do edycji podajac dany numer porzadkowy znajdujacy sie po lewej stronie kazdego kontaktu: "<<endl<<endl;
        cout<<"Wpisz -0-, aby wyjsc bez dokonywania jakichkolwiek zmian w ksiazce adresowej"<<endl;
        int pozycjaDoEdycji;
        cin>>pozycjaDoEdycji;
        edytujKontakt(pozycjaDoEdycji,indeks);
    }
}
void wyswietlMenuGlowne()
{
    int indeks, wolnyIdentyfikator = 0;
    char wybor;
    while(1)
    {
        system("cls");
        wyczyscBuforDanych();
        int indeks = wczytajZPlikuDanePrzyjaciol();
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

        switch (wybor)
        {
        case '1':
        {
            system("cls");
            int wolnyIdentyfikator = znajdzWolnyIdentyfikator(indeks, identyfikatoryPrzyjaciol);
            dodajPrzyjaciela(indeks,wolnyIdentyfikator);
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
    wyswietlMenuGlowne();

    return 0;
}

