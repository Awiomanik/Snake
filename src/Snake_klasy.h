//KLASY
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <MMSystem.h>
#include <stdio.h>
#include <fstream>

using namespace std;

//DEKLARACJE WSZYSTKICH UZYTYCH FUNKCJI
void ScrollBar();
void FullScreen();
void SizeCursor(int rozmiar);
void HideCursor(bool);

//DEKLARACJE KLAS
class Intro;
class Menu;
class CLASSIC;
class HIGHSCORES;
class EXIT;

//CIALA KLAS
class Intro
{
protected :
    //ATRYBUTY INTRA
    HANDLE hanInt;

public :
    //METODA RYSOWANIA (KONSTRUKTOR,DESTRUKTOR,THX,TYTUL)
    Intro();
    ~Intro();
    void wysTHX();
    void wysTyt();
};

class Menu
{
public :
    HANDLE hanMen;
    int arrow;
    int position;
    bool selection;

    friend class CLASSIC;
    friend class HIGHSCORES;

public :
    Menu(HANDLE = GetStdHandle(STD_OUTPUT_HANDLE), bool = false, int = 1, int = 0);
    ~Menu();
    void wysMen();
    void inpMen();
    bool petla();
    void wysOpc(int, int, int, int, int, int, int, int);
    bool dalej();
};

class CLASSIC
{
public :
    //ATRYBUTY OGONA
    int nogon;
    int ogonx [100];
    int ogony [100];
    bool czyOwoc;

    //ATRYBUTY MAPY
    int speed;
    int szerokosc;
    int wysokosc;
    bool gameOver;
    int x, y, owocx, owocy;
    float score;
    enum kierunek {STOP = 0, LEWO, PRAWO, GORA, DOL};
    enum kierunek k;
    enum kierunek k2;
    int iteratorOgona;

    friend class Menu;
    friend class HIGHSCORES;

    CLASSIC(int = 10, int = 10, int = 100, int = 0, bool = false, bool = false);
    ~CLASSIC();
    void gra();
    void setup();
    void logic();
    void draw();
    void input();
};

class HIGHSCORES
{
public :
    HANDLE hanHig;
    fstream listaHS;
    string linia;
    int nrLini;
    int czyName;
    string name[300];
    int score[300];
    string mode;
    int help;

    friend class Menu;
    friend class CLASSIC;

    HIGHSCORES(int =1, int =1, string = "nic", int = 0, int = 0, HANDLE = GetStdHandle(STD_OUTPUT_HANDLE));
    ~HIGHSCORES();
    void czytaj(string);
    void wyswietl();
    void zapisz(string);
    };

class EXIT
{
public :
    EXIT();
    ~EXIT();
    bool Exit();
};





