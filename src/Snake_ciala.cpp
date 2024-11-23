//DEFINICJE METOD
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <MMSystem.h>
#include <stdio.h>
#include "Snake_klasy.h"
#include <fstream>


using namespace std;

//INTRO
//KONSTRUKTOR INTRO
Intro::Intro()
{
    hanInt = GetStdHandle(STD_OUTPUT_HANDLE);
}
//DESTRUKTOR INTRO
Intro::~Intro()
{
}
//THX INTRO
void Intro::wysTHX()
{
        system("color 8f");
        cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t     THX\n\t\t\t\t\tsound system";
        PlaySound(TEXT("C:\\Program Files\\Snake\\Sounds\\THX.wav"),NULL,SND_SYNC);
        system("cls");
        system("color 0a");
}
//SNAKE INTRO
void Intro::wysTyt()
{
    SetConsoleTextAttribute(hanInt, 10);
    PlaySound(TEXT("C:\\Program Files\\Snake\\Sounds\\Snejk.wav"),NULL,SND_ASYNC);
    cout << endl;
    Sleep(500);
    cout << "   o o O";
    SetConsoleTextAttribute(hanInt, 12);
    cout << "~";
    SetConsoleTextAttribute(hanInt, 10);
    cout << "                    o" << endl;
    cout << "   o                         o" << endl;
    cout << "   o o o   o o o   o o o     o   o   o o o" << endl;
    cout << "       o   o   o   o   o     o o     o o " << endl;
    cout << "   o o o   o   o   o o o o   o   o   o o o" << endl;
    Sleep(3000);
    PlaySound(TEXT("C:\\Program Files\\Snake\\Sounds\\keyboard_sound.wav"),NULL,SND_ASYNC);
    cout << "\n\n";
    SetConsoleTextAttribute(hanInt, 2);
    cout << "                W";
    Sleep(100);
    cout << "K";
    Sleep(100);
    cout << "-";
    Sleep(100);
    cout << "K";
    Sleep(100);
    cout << " S";
    Sleep(100);
    cout << "T";
    Sleep(100);
    cout << "U";
    Sleep(100);
    cout << "D";
    Sleep(100);
    cout << "I";
    Sleep(100);
    cout << "O";
    Sleep(100);
    cout << "S";
    PlaySound(TEXT("C:\\Program Files\\Snake\\Sounds\\WK-K_Studios.wav"),NULL,SND_SYNC);
    SetConsoleTextAttribute(hanInt, 120);
    HideCursor(false);
    cout << "\n\n\n\n\n\n\nPRESS ANY BUTTON TO CONTINUE\r";
    Sleep(500);

    //OCEKIWANIE NA GRACZA
    while (true)
    {
        SetConsoleTextAttribute(hanInt, 15);
        cout << "PRESS ANY BUTTON TO CONTINUE\r";
        Sleep(500);
        SetConsoleTextAttribute(hanInt, 120);
        cout << "PRESS ANY BUTTON TO CONTINUE\r";
        Sleep(500);
        if(kbhit()) break;
    }
    getch();
    system("cls");
}

//MENU
//KONSTRUKTOR MENU
Menu::Menu(HANDLE h, bool s, int p, int a)
{
    hanMen = h;
    selection = s;
    position = p;
    arrow = a;
}
//DESTRUKTOR MENU
Menu::~Menu()
{
}
//WYSWIETLANIE MENU
void Menu::wysMen()
{
    //LOGO
    HideCursor(false);
    system("color 0a");
    SetConsoleTextAttribute(hanMen, 10);
    cout << endl;
    cout << "   o o O";
    SetConsoleTextAttribute(hanMen, 12);
    cout << "~";
    SetConsoleTextAttribute(hanMen, 10);
    cout << "                    o" << endl;
    cout << "   o                         o" << endl;
    cout << "   o o o   o o o   o o o     o   o   o o o" << endl;
    cout << "       o   o   o   o   o     o o     o o " << endl;
    cout << "   o o o   o   o   o o o o   o   o   o o o" << endl << endl;
    cout << "                    MENU" << endl << endl;
    HideCursor(false);

    //OPCJE
    switch (position)
    {
        case 1 :
        wysOpc(240,14,9,4,6,7,8,12);
        break;
        case 2 :
        wysOpc(15,224,9,4,6,7,8,12);
        break;
        case 3 :
        wysOpc(15,14,144,4,6,7,8,12);
        break;
        case 4 :
        wysOpc(15,14,9,64,6,7,8,12);
        break;
        case 5 :
        wysOpc(15,14,9,4,96,7,8,12);
        break;
        case 6 :
        wysOpc(15,14,9,4,6,112,8,12);
        break;
        case 7 :
        wysOpc(15,14,9,4,6,7,128,12);
        break;
        case 8 :
        wysOpc(15,14,9,4,6,7,8,192);
        break;
        default:
        break;
    }
    while(arrow==0)
    {
        if(kbhit())
        {
            arrow = _getch();
            if (arrow!=0 && arrow!=224)
            {
                arrow = _getch();
                arrow = 0;
            }
            arrow = _getch();
        }
    };
}
//WYSWIETLANIE OPCJI MENU
void Menu::wysOpc(int k1, int k2, int k3, int k4, int k5, int k6, int k7, int k8)
{
    SetConsoleTextAttribute(hanMen, k1);
    cout << "1.CLASSIC" << endl << endl;
    SetConsoleTextAttribute(hanMen, k2);
    cout << "2.ARCADE (STILL IN DEVELOPMENT)" << endl << endl;
    SetConsoleTextAttribute(hanMen, k3);
    cout << "3.TWO PLAYERS (COOPERATION) (STILL IN DEVELOPMENT)" << endl << endl;
    SetConsoleTextAttribute(hanMen, k4);
    cout << "4.TWO PLAYERS (LAST-ONE-STANDING) (STILL IN DEVELOPMENT)" << endl << endl;
    SetConsoleTextAttribute(hanMen, k5);
    cout << "5.HIGH-SCORES (STILL IN DEVELOPMENT)" << endl << endl;
    SetConsoleTextAttribute(hanMen, k6);
    cout << "6.CREDITS (STILL IN DEVELOPMENT)" << endl << endl;
    SetConsoleTextAttribute(hanMen, k7);
    cout << "7.CONTROLS AND INSTRUCTION (STILL IN DEVELOPMENT)" << endl << endl;
    SetConsoleTextAttribute(hanMen, k8);
    cout << "8.EXIT" << endl;
    SetConsoleTextAttribute(hanMen, 2);
    cout << "(use up and down arrows to move around the menu, use right arrow to select an option)";
}
//WEJSCIE MENU
void Menu::inpMen()
{
    system("cls");
    switch (arrow)
    {
        case 72:
        position--;
        if(position<1) position = 8;
        break;
        case 80:
        position++;
        if(position>8) position = 1;
        break;
        case 77 :
        selection = true;
        break;
        default :
        break;
    }
    arrow = 0;
}
//PETLA MENU
bool Menu::petla()
{
    while(!selection)
    {
        wysMen();
        inpMen();
    }
    return dalej();
}
//WYBRANIE OPCJI
bool Menu::dalej()
{
    switch (position)
    {
        case 1 :
        {
            CLASSIC c;
            c.gra();
            return false;
            break;
        }
        case 8 :
        {
            EXIT e;
            return e.Exit();
            break;
        }
        default :
        system("cls");
        cout << "learn to read fucking moron\n\n\nSTILL IN DEVELOPMENT!!!!!";
        Sleep(2000);
        break;
    }
}

//CLASSIC
//KONSTRUKTOR CLASSIC
CLASSIC::CLASSIC(int s, int w, int v, int n, bool o, bool go)
{
    speed = v;
    nogon = n;
    czyOwoc = o;
    szerokosc = s;
    wysokosc = w;
    gameOver = go;
}
//DESTRUKTOR CLASSIC
CLASSIC::~CLASSIC()
{
}
//ROZGRYWKA CLASSIC
void CLASSIC::gra()
{
    setup ();
    while (!gameOver)
    {
        draw();
        input();
        logic();
        Sleep(speed);
    }
    system("cls");
    cout << "game over stary";
    cout << endl << endl << "TWOJ WYNIK : " << score << endl;
    getch();
}
//PRZYGOTOWANIE GRY CLASSIC
void CLASSIC::setup()
{
    k = STOP;
    k2=STOP;
    x =(szerokosc/2)- szerokosc % 2;
    y = wysokosc/2- wysokosc % 2;
    owocx = rand() % szerokosc;
    owocy  = rand() % wysokosc;
    score = 0;
    system("color 07");
    for (int i=0;i<100;i++)
    {
        ogonx[i]=101;
        ogony[i]=101;
    }
}
//SILNIK CLASSIC
void CLASSIC::logic()
{
    int poprzednix = ogonx[0];
    int poprzedniy = ogony[0];
    int poprzedni2x, poprzedni2y;
    ogonx[0]=x;
    ogony[0]=y;
    for(int i=1; i<nogon; i++)
    {
            poprzedni2x=ogonx[i];
            poprzedni2y=ogony[i];
            ogonx[i]=poprzednix;
            ogony[i]=poprzedniy;
            poprzednix=poprzedni2x;
            poprzedniy=poprzedni2y;

    }

    switch(k)
    {
    case LEWO:
        if(k2==PRAWO)
        {
            cout << "\a";
            k=k2;
            x++;
        } else x--;
        break;
        case PRAWO:
        if(k2==LEWO)
        {
            cout << "\a";
            k=k2;
            x--;
        } else x++;
        break;
    case DOL:
        if(k2==GORA)
        {
            cout << "\a";
            k=k2;
            y--;
        } else y++;
        break;
    case GORA:
        if(k2==DOL)
        {
            cout << "\a";
            k=k2;
            y++;
        } else y--;
        break;
    default:
        break;
    }
    //FUNKCJA ZE SCIANKAMI
    /*if (szerokosc<(x+1) || x < 0 || (y+1)>wysokosc || y < 0)
    gameOver=true;*/
    //FUNKCJA BEZ SCIANEK
    if (x>=szerokosc) x=0; else if (x<0) x=szerokosc-1;
    if (y>=wysokosc) y=0; else if (y<0) y=wysokosc-1;

    for(int i = 0; i< nogon; i++)
    {
        if(ogonx[i]==x && ogony[i]==y)
            gameOver=true;
    }

    if (x==owocx && y==owocy)
    {
        PlaySound(TEXT("C:\\Program Files\\Snake\\Sounds\\chrup.wav"),NULL,SND_ASYNC);
        score+=10;
        owocx = rand() % szerokosc;
        owocy = rand() % wysokosc;
        for (iteratorOgona=0;iteratorOgona<szerokosc;iteratorOgona++)
        {
            if(owocx==ogonx[iteratorOgona] && owocy==ogony[iteratorOgona])
            {
                owocx = rand() % szerokosc;
                iteratorOgona=0;
            }
        }
        for (iteratorOgona=0;iteratorOgona<szerokosc;iteratorOgona++)
        {
            if(owocy==ogony[iteratorOgona] && owocy==ogony[iteratorOgona])
            {
                owocy  = rand() % wysokosc;
                iteratorOgona=0;
            }
        }
        nogon++;
        czyOwoc = true;
    }
}
//WEJSCIE CLASSIC
void CLASSIC::input()
{
    if (_kbhit())
    {
        switch(getch())
        {
            case'a':
            k2=k;
            k = LEWO;
            break;
            case 'd':
            k2=k;
            k = PRAWO;
            break;
            case 'w':
            k2=k;
            k = GORA;
            break;
            case 's':
            k2=k;
            k = DOL;
            break;
            case'x':
            gameOver=true;
            break;
        }
    }
}
//FUNKCJA RYSOWANIA
void CLASSIC::draw()
{
    system("cls");

    //PIERWSZY RZAD
    for(int i = 0; i<szerokosc+2;i++)
    {
        cout << "# ";
    }
    cout << endl;
    //MAPA I KOLUMNY
    for(int i = 0; i<wysokosc ;i++)
    {
        for(int j = 0; j<szerokosc ;j++)
        {
        //PIERWSZA KOLUMNA
        if (j==0)
            cout << "# " ;
        //MAPA
        if (j==x && i==y)
            cout << "O ";
        else if (j==owocx && i==owocy)
            cout << "Q ";
        else
        {
            bool wyswietlonoOgon = false;
            for(int k = 0; k<nogon; k++)
            {
                if(ogonx[k] == j && ogony[k] == i)
                {
                    cout <<"o ";
                    wyswietlonoOgon=true;
                }
            }
            if(!wyswietlonoOgon)
            cout << "  ";
        }
        //OSTATNIA KOLUMNA
        if(j==szerokosc-1)
             cout << "# ";
        }
        cout << endl;
    }
    //OSTATNI RZAD
    for(int i = 0; i<szerokosc+2;i++)
    {
        cout << "# ";
    }
    //WYNIK
    cout << endl << endl << "TWOJ WYNIK : " << score;
}

//HIGHSCORES
//KONSTRUKTOR HIGHSCORES
HIGHSCORES::HIGHSCORES(int nr, int cn, string n0, int s0, int h, HANDLE hand)
{
    hanHig = hand;
    nrLini = nr;
    czyName = cn;
    help = h;
    for(int i =0;i<300;i++)
    {
        name[i]=n0;
        score[i]=s0;
    }
}
//DESTRUKTOR HIGHSCORES
HIGHSCORES::~HIGHSCORES()
{
}
//CZYTANIE PLIKU HIGHSCORES
void HIGHSCORES::czytaj(string tryb)
{
    if(tryb=="CLASSIC") listaHS.open("C:\\Program Files\\Snake\\HIGH-SCORES\\HIGH-SCORES-CLASSIC.txt", ios::in);
    else cout << "nie otworzyl sie";
    if(listaHS.good()==false)
    {
        cout<<"cos jest nie tak z plikiem nie moge sie do niego dostac\nmozesz to zrobic manualnie popros wojtka";
        getch();
    }
    while(getline(listaHS,linia))
        {
            czyName = nrLini % 2;
            switch(czyName)
            {
            case 1 : name[((nrLini+1)/2)-1] = linia; break;
            case 0 : score[(nrLini/2)-1] = atoi(linia.c_str()); break;
            }
            nrLini++;
        }
    czyName =1;
    nrLini = 1;
    listaHS.close();
}
void HIGHSCORES::wyswietl()
{
    SetConsoleTextAttribute(hanHig, 15);
    cout << "CLASSIC MODE HIGH-SCORES :" << endl << endl;
    while(name[help]!="nic")
    {
        if(help+1==1) SetConsoleTextAttribute(hanHig, 14);
        if(help+1>=4 && ((help+1) % 2)==0) SetConsoleTextAttribute(hanHig, 8);
        if(help+1>=5 && ((help+1) % 2)==1) SetConsoleTextAttribute(hanHig, 7);
        cout << help+1 << "  " << name[help] << " : " << score[help] << endl;
        help++;
    }
    help=0;
    getch();
}
//ZAPISYWANIE HIGHSCORES
void HIGHSCORES::zapisz(string tryb)
{
    listaHS.open("C:\\Program Files\\Snake\\HIGH-SCORES\\HIGH-SCORES-CLASSIC.txt", ios::out);
    if(listaHS.good()==false)
    {
        cout<<"cos jest nie tak z plikiem nie moge sie do niego dostac\nmozesz to zrobic manualnie popros wojtka";
        getch();
    }
    while(name[help]!="nic")
    {
        listaHS << name[help] << endl << score[help] << endl;
        listaHS.close();
        help++;
    }
}

//EXIT
//KONSTRUKTOR EXIT
EXIT::EXIT()
{
}
//DESTRUKTOR EXIT
EXIT::~EXIT()
{
}
bool EXIT::Exit()
{
    cout << "bye bye it was fun";
    return true;
}






