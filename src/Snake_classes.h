// CLASSES
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <MMSystem.h>
#include <stdio.h>
#include <fstream>
#include <vector>

using namespace std;

// DECLARATIONS OF USED FUNCTIONS
void hideScrollBar();
void setFullScreen();
void setCursorSize(short size, bool visible);
void setFontSize(short width, short height);
COORD getMaxBufferSize(short fontWidth, short fontHeight);
void setBufferSize(COORD size);
COORD prepareConsole();
void write(int x, int y, const string& message);

// DECLARATIONS OF CLASSES
class Intro;
class Menu;
class CLASSIC;
class HIGHSCORES;
class EXIT;

// BODIES OF CLASSES
class Intro {
protected :
    // ATRIBUTES
    HANDLE hanInt;
    COORD bufferSize;

public :
    // METHODS
    Intro(COORD bufferSize);
    ~Intro();
    void displayTHX();
    void displayTitle();
};

class Menu {
public :
    HANDLE handle;
    int previous_option;
    int key_pressed;
    int current_position;
    bool selection_happened;
    vector<std::string> options;
    vector<short> option_colors;
    vector<short> option_colors_chosen;

    friend class CLASSIC;
    friend class HIGHSCORES;

public :
    Menu();
    ~Menu();
    void displayMenu();
    bool parseInput();
    void updateMenu();
    bool runMenu();
    void displayOptions();
    bool executeOption();
};

class CLASSIC {
public :
    //ATRYBUTY OGONA
    int tailLen;
    int tailX [100];
    int tailY [100];
    bool digesting;

    //ATRYBUTY MAPY
    int tempo;
    int mapWidth;
    int mapHeight;
    bool gameOver;
    int x, y, fruitX, fruitY;
    float score;
    enum direction {STOP = 0, LEFT, RIGHT, UP, DOWN};
    enum direction current_direction;
    enum direction future_direction;
    int tailIterator;

    friend class Menu;
    friend class HIGHSCORES;

    CLASSIC(int mapWidth = 10, int mapHeight = 10, int snakeTempo = 100, int tailLen = 0);
    ~CLASSIC();
    void gameplay();
    void setup();
    void logic(bool wheaterMapHasTorusTopology = true);
    void draw();
    void input();
};

class HIGHSCORES{
private:
    ifstream highScoresFile;
    vector<string> names;
    vector<int> scores;
    const string scoresDirectory = "./HIGH-SCORES/";

public:
    HIGHSCORES();
    ~HIGHSCORES();
    void readScores(const string& mode);
    void displayScores();
    void saveScores(const string&);
};

class EXIT{
public :
    EXIT();
    ~EXIT();
    bool Exit();
};





