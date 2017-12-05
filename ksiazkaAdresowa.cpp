#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>

using namespace std;

struct przyjaciel
{
    int id;
    string imie, nazwisko,adres, email, nrTel;
};

void dodajPrzyjaciela(przyjaciel bazaPrzyjaciol[],int indeks)
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

    bazaPrzyjaciol[indeks].id = osobaId;
    bazaPrzyjaciol[indeks].imie = imie;
    bazaPrzyjaciol[indeks].nazwisko = nazwisko;
    bazaPrzyjaciol[indeks].nrTel = numerTelefonu;
    bazaPrzyjaciol[indeks].adres = adres;
    bazaPrzyjaciol[indeks].email = email;

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);
    if (plik.good())
    {
        plik << osobaId << endl;
        plik << imie << endl;
        plik << nazwisko << endl;
        plik << numerTelefonu << endl;
        plik << adres << endl;
        plik << email << endl;

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

int WczytajZPliku(przyjaciel bazaPrzyjaciol[])
{
    fstream plik;

    plik.open("KsiazkaAdresowa.txt",ios::in);

    if( plik.good()==false)
    {
        cout<<"Plik nie istnieje!";
        exit(0);
    }

    string imie[1000], nazwisko[1000], numerTelefonu[1000], adres[1000], email[1000];
    int id[1000];
    string linia;

    int nr_linii=1;
    int indeks = 0;
    while(getline(plik,linia))
    {
        switch(nr_linii)
        {
        case 1:
            id[indeks] = atoi(linia.c_str());
            break;
        case 2:
            imie[indeks] = linia;
            break;
        case 3:
            nazwisko[indeks] = linia;
            break;
        case 4:
            numerTelefonu[indeks] = linia;
            break;
        case 5:
            adres[indeks] = linia;
            break;
        case 6:
            email[indeks] = linia;
            break;
        }
        int aktualneID = indeks+1;
        bazaPrzyjaciol[indeks].id = aktualneID;
        bazaPrzyjaciol[indeks].imie = imie[indeks];
        bazaPrzyjaciol[indeks].nazwisko = nazwisko[indeks];
        bazaPrzyjaciol[indeks].nrTel = numerTelefonu[indeks];
        bazaPrzyjaciol[indeks].adres = adres[indeks];
        bazaPrzyjaciol[indeks].email = email[indeks];

        nr_linii++;
        if(nr_linii == 7)
        {
            nr_linii= 1;
            indeks++;
        }
    }
    plik.close();

    return indeks;
}

void wyswietlWszystkichPrzyjaciol(przyjaciel baza[], int indeks)
{
    for(int i = 0; i<indeks; i++)
    {
        cout<<baza[i].id<<endl;
        cout<<baza[i].imie<<endl;
        cout<<baza[i].nazwisko<<endl;
        cout<<baza[i].nrTel<<endl;
        cout<<baza[i].adres<<endl;
        cout<<baza[i].email<<endl;
        cout<<endl;
    }
}

void wyswietlPrzyjaciolPoNazwisku(przyjaciel baza[], int indeks)
{
    string wyraz;
    cout<<"Podaj nazwisko: "<<endl;
    cin>>wyraz;
    cout<<endl;
    int znalezioneOsoby = 0;

    for(int i = 0; i<indeks; i++)
    {
        while(baza[i].nazwisko == wyraz)
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
            if(baza[i].nazwisko == wyraz)
            {
                cout<<baza[i].id<<endl;
                cout<<baza[i].imie<<endl;
                cout<<baza[i].nazwisko<<endl;
                cout<<baza[i].nrTel<<endl;
                cout<<baza[i].adres<<endl;
                cout<<baza[i].email<<endl;
                cout<<endl;
            }
        }
    }
    cout<<endl;
}

void wyswietlPrzyjaciolPoimieniu(przyjaciel baza[], int indeks)
{
    string wyraz;
    cout<<"Podaj imie: "<<endl;
    cin>>wyraz;
    cout<<endl;
    int znalezioneOsoby = 0;

    for(int i = 0; i<indeks; i++)
    {
        while(baza[i].imie == wyraz)
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
            if(baza[i].imie == wyraz)
            {
                cout<<baza[i].id<<endl;
                cout<<baza[i].imie<<endl;
                cout<<baza[i].nazwisko<<endl;
                cout<<baza[i].nrTel<<endl;
                cout<<baza[i].adres<<endl;
                cout<<baza[i].email<<endl;
                cout<<endl;
            }
        }
    }
    cout<<endl;
}

int main()
{
    przyjaciel baza[1000];
    int indeks = 0;
    char wybor;
    while(1)
    {
        system("cls");
        cout<<"1. Dodaj przyjaciela"<<endl;
        cout<<"2. Wyszukuj przyjaciol"<<endl;
        cout<<"9. Wyjscie"<<endl;
        cin>>wybor;
        if (wybor =='1')
        {
            dodajPrzyjaciela(baza,indeks);
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

                int indeks = WczytajZPliku(baza);

                if(wyborwyszukiwania =='1')
                {
                    wyswietlPrzyjaciolPoNazwisku(baza,indeks);
                    system("pause");
                }
                else if (wyborwyszukiwania =='2')
                {
                    wyswietlPrzyjaciolPoimieniu(baza,indeks);
                    system("pause");
                }
                else if (wyborwyszukiwania =='3')
                {
                    wyswietlWszystkichPrzyjaciol(baza,indeks);
                    system("pause");
                }
                break;
            }
        }
        else if (wybor =='9')
        {
            exit(0);
        }
    }
    return 0;
}
