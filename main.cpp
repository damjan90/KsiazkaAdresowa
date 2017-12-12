#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

struct BazaPrzyjaciol
{
    vector <string> imiePrzyjaciela;
    vector <string> nazwiskoPrzyjaciela;
    vector <string> numerTelefonuPrzyjaciela;
    vector <string> adresPrzyjaciela;
    vector <string> emailPrzyjaciela;
    vector <int> idPrzyjaciela;
};

BazaPrzyjaciol nowyPrzyjaciel;

void dodajPrzyjaciela(int indeks)
{
    system ("cls");
    string imie, nazwisko,  numerTelefonu, adres,email;
    cout<<"Podaj imie: "<<endl;
    cin>>imie;
    cout<<endl;
    cout<<"Podaj nazwisko: "<<endl;
    cin>>nazwisko;
    cout<<endl;
    cout<<"Podaj nr telefonu: "<<endl;
    cin.sync();
    getline(cin,numerTelefonu);
    cout<<endl;
    cout<<"Podaj adres: "<<endl;
    cin.sync();
    getline(cin,adres);
    cout<<endl;
    cout<<"Podaj adres e-mail: "<<endl;
    cin>>email;


    int osobaId = indeks + 1;

    fstream plik;
    plik.open("ksiazkaAdresowaZmodyfikowana.txt", ios::out | ios::app);
    if (plik.good())
    {

        plik << osobaId <<"|";
        plik << imie << "|";
        plik << nazwisko << "|";
        plik << numerTelefonu << "|";
        plik << adres << "|";
        plik << email << "|";
        plik<<endl;


        imie.clear();
        nazwisko.clear();
        numerTelefonu.clear();
        adres.clear();
        email.clear();

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

int sprawdzIloscPrzyjaciol()
{
    fstream plik;
    plik.open("ksiazkaAdresowaZmodyfikowana.txt",ios::in);
    int obecnaIloscPrzyjaciolWksiazce = 0;
    string linia;
    if( plik.good()==false)
        exit(0);
    else
    {
        while ((getline(plik,linia))&&(linia.length()!=1 ))
        {
            obecnaIloscPrzyjaciolWksiazce++;
        }
    }
    plik.close();
    return obecnaIloscPrzyjaciolWksiazce;

}


int WczytajZPliku()
{
    fstream plik;

    plik.open("ksiazkaAdresowaZmodyfikowana.txt",ios::in);

    if( plik.good()==false)
    {
        cout<<"Plik nie istnieje!";
        exit(0);
    }

    string tymczasowy, linia;

    int nr_linii=1;
    int indeks = 0;
    int indeksliterWLinice = 0;
    while(getline(plik,linia))
    {
        do
        {
            if(linia[indeksliterWLinice]== '|')
            {
                switch(nr_linii)
                {
                case 1:
                    nowyPrzyjaciel.idPrzyjaciela.push_back(atoi(tymczasowy.c_str())) ;
                    break;
                case 2:
                    nowyPrzyjaciel.imiePrzyjaciela.push_back(tymczasowy);
                    break;
                case 3:
                    nowyPrzyjaciel.nazwiskoPrzyjaciela.push_back(tymczasowy);
                    break;
                case 4:
                    nowyPrzyjaciel.numerTelefonuPrzyjaciela.push_back(tymczasowy);
                    break;
                case 5:
                    nowyPrzyjaciel.adresPrzyjaciela.push_back(tymczasowy);
                    break;
                case 6:
                    nowyPrzyjaciel.emailPrzyjaciela.push_back(tymczasowy);
                    break;
                }
                tymczasowy.clear();
                nr_linii++;
            }
            else
                tymczasowy += linia[indeksliterWLinice];
            indeksliterWLinice++;
        }
        while(indeksliterWLinice<linia.length());

        if(nr_linii == 7)
        {
            nr_linii= 1;
            indeksliterWLinice = 0;

            indeks++;
        }
    }
    plik.close();
    linia.clear();

    return indeks;
}

void wyswietlWszystkichPrzyjaciol(int iloscPrzyjaciol)
{
    if(iloscPrzyjaciol == 0)
    {
        cout<<"W ksiaze adresowej nie znajduje sie zaden kontakt! W Menu Glownym wybierz -1- i dodaj kontakt"<<endl;
        Sleep(1500);
    }
    else
    {
        cout<<"*****AKTUALNA LISTA ZAPISANYCH KONTAKTOW*****"<<endl;
        cout<<endl;
        fstream plik;

        plik.open("ksiazkaAdresowaZmodyfikowana.txt",ios::in);

        string linia,tymczasowy;
        int indeks = 0;
        int nr_linii=1;
        int indeksliterWLinice = 0;
        while(getline(plik,linia))
        {
            do
            {
                if(linia[indeksliterWLinice]== '|')
                {
                    switch(nr_linii)
                    {
                    case 1:
                        nowyPrzyjaciel.idPrzyjaciela.push_back(atoi(tymczasowy.c_str())) ;
                        cout<<tymczasowy<<"|";
                        break;
                    case 2:
                        nowyPrzyjaciel.imiePrzyjaciela.push_back(tymczasowy);
                        cout<<tymczasowy<<"|";
                        break;
                    case 3:
                        nowyPrzyjaciel.nazwiskoPrzyjaciela.push_back(tymczasowy);
                        cout<<tymczasowy<<"|";
                        break;
                    case 4:
                        nowyPrzyjaciel.numerTelefonuPrzyjaciela.push_back(tymczasowy);
                        cout<<tymczasowy<<"|";
                        break;
                    case 5:
                        nowyPrzyjaciel.adresPrzyjaciela.push_back(tymczasowy);
                        cout<<tymczasowy<<"|";
                        break;
                    case 6:
                        nowyPrzyjaciel.emailPrzyjaciela.push_back(tymczasowy);
                        cout<<tymczasowy<<"|";
                        break;
                    }

                    tymczasowy.clear();
                    nr_linii++;
                }
                else
                    tymczasowy += linia[indeksliterWLinice];
                indeksliterWLinice++;
            }
            while(indeksliterWLinice<linia.length());

            if(nr_linii == 7)
            {
                nr_linii = 1;
                indeksliterWLinice = 0;
                cout<<endl;

                indeks++;
            }
        }
        cout<<endl;
        cout<<"***************KONIEC LISTY******************"<<endl;
        cout<<endl;
        plik.close();
        linia.clear();
    }
}

void wyswietlPrzyjaciolPoNazwisku(int indeks)
{
    string wyraz;
    cout<<"Podaj nazwisko: "<<endl;
    cin>>wyraz;
    cout<<endl;
    int znalezioneOsoby = 0;

    for(int i = 0; i<indeks; i++)
    {
        while(nowyPrzyjaciel.nazwiskoPrzyjaciela[i] == wyraz)
        {
            znalezioneOsoby++;
            i++;
        }
    }
    if(znalezioneOsoby == 0)
    {
        cout<<"Brak przyjaciol o nazwisku "<<wyraz<<endl;
    }
    else
    {
        cout<<"Znaleziono "<<znalezioneOsoby<<" przyjaciol o nazwisku "<<wyraz<<endl;
        for(int i = 0; i<indeks; i++)
        {
            if(nowyPrzyjaciel.nazwiskoPrzyjaciela[i] == wyraz)
            {
                cout<<nowyPrzyjaciel.idPrzyjaciela[i]<<"|";
                cout<<nowyPrzyjaciel.imiePrzyjaciela[i]<<"|";
                cout<<nowyPrzyjaciel.nazwiskoPrzyjaciela[i]<<"|";
                cout<<nowyPrzyjaciel.numerTelefonuPrzyjaciela[i]<<"|";
                cout<<nowyPrzyjaciel.adresPrzyjaciela[i]<<"|";
                cout<<nowyPrzyjaciel.emailPrzyjaciela[i]<<"|";
                cout<<endl;
            }
        }
    }
    cout<<endl;
}

void wyswietlPrzyjaciolPoimieniu(int indeks)
{
    string wyraz;
    cout<<"Podaj imie: "<<endl;
    cin>>wyraz;
    cout<<endl;
    int znalezioneOsoby = 0;

    for(int i = 0; i<indeks; i++)
    {
        while(nowyPrzyjaciel.imiePrzyjaciela[i] == wyraz)
        {
            znalezioneOsoby++;
            i++;
        }
    }
    if(znalezioneOsoby == 0)
    {
        cout<<"Brak przyjaciol o imieniu "<<wyraz<<endl;
    }
    else
    {
        cout<<"Znaleziono "<<znalezioneOsoby<<" przyjaciol o imieniu "<<wyraz<<endl;

        for(int i = 0; i<indeks; i++)
        {
            if(nowyPrzyjaciel.imiePrzyjaciela[i] == wyraz)
            {
                cout<<nowyPrzyjaciel.idPrzyjaciela[i]<<"|";
                cout<<nowyPrzyjaciel.imiePrzyjaciela[i]<<"|";
                cout<<nowyPrzyjaciel.nazwiskoPrzyjaciela[i]<<"|";
                cout<<nowyPrzyjaciel.numerTelefonuPrzyjaciela[i]<<"|";
                cout<<nowyPrzyjaciel.adresPrzyjaciela[i]<<"|";
                cout<<nowyPrzyjaciel.emailPrzyjaciela[i]<<"|";
                cout<<endl;
            }
        }
    }
    cout<<endl;
}
void usunPrzyjaciela(int pozycjaDoUsuniecia, int indeks)
{
    int osobaId;
    int biezacyIndeks;

    fstream pliczek;
    pliczek.open("ksiazkaAdresowaZmodyfikowana.txt", ios::out);
    if (pliczek.good())
    {
        if(pozycjaDoUsuniecia == indeks)
        {
            indeks--;
        }
        for(int biezacaPozycja = 0; biezacaPozycja<indeks; biezacaPozycja++)
        {
            if(pozycjaDoUsuniecia >= biezacaPozycja+1)
            {
                osobaId = biezacaPozycja + 1;
            }
            else
            {
                osobaId = biezacaPozycja;
            }

            if(pozycjaDoUsuniecia == biezacaPozycja + 1)
            {
                biezacaPozycja++;
            }

            pliczek << osobaId <<"|";
            pliczek << nowyPrzyjaciel.imiePrzyjaciela[biezacaPozycja]<< "|";
            pliczek << nowyPrzyjaciel.nazwiskoPrzyjaciela[biezacaPozycja]<< "|";
            pliczek << nowyPrzyjaciel.numerTelefonuPrzyjaciela[biezacaPozycja]<< "|";
            pliczek << nowyPrzyjaciel.adresPrzyjaciela[biezacaPozycja]<< "|";
            pliczek << nowyPrzyjaciel.emailPrzyjaciela[biezacaPozycja]<< "|";
            pliczek<<endl;

        }
        pliczek.close();
        if(pozycjaDoUsuniecia != 0)
        {
            cout<<"Kontakt usuniety do listy" << endl;
        }
        Sleep(500);
    }

    else
    {
        cout << "Nie mozna otworzyc pliku: ksiazkaAdresowaZmodyfikowana.txt" << endl;
    }
}


int main()
{
    int indeks;
    char wybor;
    fstream plik;
    int iloscPrzyjaciolWKsiazce;
    int pozycjaDoUsuniecia;
    while(1)
    {
        system("cls");
        int indeks = WczytajZPliku();
        cout<<"MENU GLOWNE"<<endl<<endl;
        iloscPrzyjaciolWKsiazce = sprawdzIloscPrzyjaciol();
        cout<<"Aktualnie w ksiazce adresowej znajduje sie: "
            <<iloscPrzyjaciolWKsiazce<<" przyjaciol"<<endl<<endl;
        cout<<"1. Dodaj przyjaciela"<<endl;
        cout<<"2. Wyszukuj przyjaciol"<<endl;
        cout<<"3. Usun pozycje"<<endl;
        cout<<"9. Wyjscie"<<endl;
        cin>>wybor;

        if (wybor =='1')
        {
            dodajPrzyjaciela(indeks);
        }
        else if (wybor == '2')
        {
            while(1)
            {
                system("cls");
                char wyborwyszukiwania;
                cout<<"1. Wyszukaj po nazwisku"<<endl;
                cout<<"2. Wyszukaj po imieniu"<<endl;
                cout<<"3. Wyswietl wszystkich przyjaciol"<<endl;
                cin>>wyborwyszukiwania;
                cout<<endl;

                if(wyborwyszukiwania =='1')
                {
                    wyswietlPrzyjaciolPoNazwisku(indeks);
                    system("pause");
                }
                else if (wyborwyszukiwania =='2')
                {
                    wyswietlPrzyjaciolPoimieniu(indeks);
                    system("pause");
                }
                else if (wyborwyszukiwania =='3')
                {
                    wyswietlWszystkichPrzyjaciol(iloscPrzyjaciolWKsiazce);
                    system("pause");
                }
                break;
            }
        }
        else if (wybor == '3')
        {
            wyswietlWszystkichPrzyjaciol(indeks);
            cout<<"Wpisz pozycje do usuniecia podajac dany numer porzadkowy znajdujacy sie po lewej stronie kazdego kontaktu: "<<endl<<endl;
            cout<<"Wpisz -0-, aby wyjsc bez usuwania zadnego kontaktu"<<endl;
            cin>>pozycjaDoUsuniecia;
            usunPrzyjaciela(pozycjaDoUsuniecia,indeks);
        }

        else if (wybor =='9')
        {
            exit(0);
        }

    }
    return 0;
}
