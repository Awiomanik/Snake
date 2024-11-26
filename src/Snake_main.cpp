// DEFINITIONS OF USED FUNCTIONS
#include "Snake_classes.h"

//MAIN FUNCTION
int main(){
    bool finnished = false;

    // Preparation of the console
    COORD consoleBufferSize = prepareConsole();
    
    // INTRO
    Intro introScreen(consoleBufferSize);
    //introScreen.displayTHX();
    //introScreen.displayTitle();

    //MENU
    Menu menuScreen;
    while(!finnished) { finnished = menuScreen.runMenu(); }
    
    //HIGHSCORES
    //HIGHSCORES highscoresScreen;
    //highscoresScreen.readScores("CLASSIC");
    //highscoresScreen.displayScores();
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
    HWND hwnd = GetConsoleWindow();
    
    if (hwnd == NULL) {
        cerr << "Failed to get console window handle.\n";
        return;
    }

    // Remove window decorations and set fullscreen style
    SetWindowLong(hwnd, GWL_STYLE, WS_POPUP);
    SetWindowPos(hwnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), 
                 GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED);
    ShowWindow(hwnd, SW_MAXIMIZE);
}
// CHANGE SIZE OF COURSOR OR HIDE IT
void setCursorSize(short size, bool visible) {
    HANDLE han = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;

    if (!GetConsoleCursorInfo(han, &info)) {
        std::cerr << "Failed to get console cursor info.\n";
        return;
    }

    info.dwSize = (size < 1 ? 1 : (size > 100 ? 100 : size)); // Clamp size to valid range (1-100)
    info.bVisible = visible;
    if (!SetConsoleCursorInfo(han, &info)) {
        std::cerr << "Failed to set console cursor info.\n";
    }
}
// SET FONT SIZE
void setFontSize(short width, short height) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to get console handle.\n";
        return;
    }

    CONSOLE_FONT_INFOEX fontInfo = {0};
    fontInfo.cbSize = sizeof(fontInfo);

    // Set the font name
    wcscpy_s(fontInfo.FaceName, L"Consolas");

    // Set font size
    fontInfo.dwFontSize.X = width;   // Character width
    fontInfo.dwFontSize.Y = height; // Character height
    if (!SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo)) {
        std::cerr << "Failed to set console font size.\n";
    }
}
// GET MAXIMUM BUFFER SIZE THAT WILL NOT EXCEED THE SCREEN DIMENTIONS
COORD getMaxBufferSize(short fontWidth, short fontHeight) { 
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to get console handle.\n";
        return {0, 0};
    }

    // Get screen resolution
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Get console dimentions
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        std::cerr << "Failed to get console screen buffer info.\n";
        return {0, 0};
    }
    COORD bufferSize = {
        static_cast<SHORT>(csbi.srWindow.Right - csbi.srWindow.Left), // Visible columns
        static_cast<SHORT>(csbi.srWindow.Bottom - csbi.srWindow.Top) // Visible rows
    };


    // Calculate gap
    COORD gap = {
        static_cast<SHORT>(screenWidth / bufferSize.X - fontWidth),
        static_cast<SHORT>(screenHeight / bufferSize.Y - fontHeight)
    };

    // Calculate number of rows and columns on the screen
    COORD bufferSizeInt = {
        static_cast<short>(screenWidth / (fontWidth + gap.X)),
        static_cast<short>(screenHeight / (fontHeight + gap.Y))
    };

    return bufferSizeInt;
}
// SET BUFFER SIZE
void setBufferSize(COORD size) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to get console handle.\n";
        return;
    }

    if (!SetConsoleScreenBufferSize(hConsole, size)) {
        std::cerr << "Failed to set screen buffer size.\n";
    }
}
// SET ALL THE CONSOLE ATRIBUTES FOR THE PROGRAMM
COORD prepareConsole() {
    short fontWidth = 80;
    short fontHeight = 80;
    setFontSize(fontWidth, fontHeight);
    setFullScreen();
    COORD maxSize = getMaxBufferSize(fontWidth, fontHeight);
    setBufferSize(maxSize);
    setCursorSize(1, false);
    hideScrollBar();

    return maxSize;
}
// WRITE TO CONSOLE AT A GIVEN COORDINATES (INDEXING FROM 1 !)
void write(int x, int y, const string& message) {
    std::cout << "\033[" << y << ";" << x << "H" << message;
}