//DEFINICJE WSZYSTKICH UZYTYCH FUNKCJI
#include "Snake_klasy.h"

//FUNKCJA GLOWNA
int main()
{
    bool koniec = false;
    //PRZYGOTOWANIE KONSOLI
    ScrollBar();
    FullScreen();
    SizeCursor(1);
    //INTRO
    Intro i;
    i.wysTHX();
    i.wysTyt();
    //MENU
    while(!koniec)
    {
        Menu m;
        koniec = m.petla();
    }
    HIGHSCORES h;
    h.czytaj("CLASSIC");
    h.wyswietl();
    return 0;
}

//CHOWANIE SCROLLBAROW
void ScrollBar()
{
    HANDLE Out;
    CONSOLE_SCREEN_BUFFER_INFO SBI;
    COORD NowySB;
    int status;
    Out =GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(Out, &SBI);
    NowySB.X = 92;
    NowySB.Y = 22;
    status = SetConsoleScreenBufferSize(Out, NowySB);
}
//PELNY EKRAN
void FullScreen()
{
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_RETURN, 0X1c, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}
//ROZMIAR KURSORA
void SizeCursor(int rozmiar)
{
    HANDLE han = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;

    GetConsoleCursorInfo(han, &info);
    info.dwSize = rozmiar;
    SetConsoleCursorInfo(han, &info);
}
//CHOWANIE KURSORA
void HideCursor(bool widocznosc)
{
    HANDLE han = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;

    GetConsoleCursorInfo(han, &info);
    info.dwSize = 1;
    info.bVisible = widocznosc;
    SetConsoleCursorInfo(han, &info);
}


