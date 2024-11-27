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
    int current_option;
    bool selection_happened;
    vector<std::string> options;
    int amount_of_options;
    vector<short> option_colors;
    vector<short> option_colors_chosen;

    friend class CLASSIC;
    friend class HIGHSCORES;

public :
    Menu();
    ~Menu();
    void displayMenu();
    int clip(int num);
    bool parseInput();
    void updateMenu();
    void runMenu();
    void displayOptions();
    bool executeOption();
};

class CLASSIC {
public :
    //SNAKE ATRIBUTES
    int tailLen;
    vector<COORD> snake_coords;
    bool digesting;
    enum direction current_direction;
    enum direction future_direction;

    //MAP ATRIBUTES
    int tempo;
    int mapWidth;
    int mapHeight;
    bool gameOver;
    int fruitX, fruitY;
    float score;
    enum direction {STOP = 0, LEFT, RIGHT, UP, DOWN};

    friend class Menu;
    friend class HIGHSCORES;

    CLASSIC(int mapWidth = 10, int mapHeight = 20, int snakeTempo = 40);
    ~CLASSIC();
    void gameplay();
    void setup();
    void logic(bool wheaterMapHasTorusTopology = true);
    void initial_draw();
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





