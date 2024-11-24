// DEFINITIONS OF USED FUNCTIONS
#include "Snake_classes.h"

//MAIN FUNCTION
int main(){
    bool finnished = false;

    // Preparation of the console
    hideScrollBar();
    setFullScreen();
    setCoursorSize(1);
    
    // INTRO
    Intro introScreen;
    introScreen.displayTHX();
    introScreen.displayTitle();

    //MENU
    while(!finnished){
        Menu menuScreen;
        finnished = menuScreen.runMenu();
    }
    
    //HIGHSCORES
    HIGHSCORES highscoresScreen;
    highscoresScreen.readScores("CLASSIC");
    highscoresScreen.displayScores();
    return 0;
}

// HIDING SCROLLBAR
void hideScrollBar(){
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
// SET CONSOLE WINDOW TO FULL-SCREEN MODE
void setFullScreen(){
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_RETURN, 0X1c, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}
// CHANGE SIZE OF COURSOR
void setCoursorSize(int size)
{
    HANDLE han = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;

    GetConsoleCursorInfo(han, &info);
    info.dwSize = size;
    SetConsoleCursorInfo(han, &info);
}
// HIDE THE COURSOR
void setCoursorVisability(bool visability)
{
    HANDLE han = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;

    GetConsoleCursorInfo(han, &info);
    info.dwSize = 1;
    info.bVisible = visability;
    SetConsoleCursorInfo(han, &info);
}


