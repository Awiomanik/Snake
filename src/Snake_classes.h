// CLASSES
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <MMSystem.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;
using redraw = vector<pair<COORD, string>>;

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
    //MAP ATRIBUTES
    short tempo;
    short mapWidth;
    short mapHeight;
    bool gameOver;
    COORD fruit_coords;
    int score;
    enum direction {STOP = 0, LEFT, RIGHT, UP, DOWN};
    queue<direction> inputQueue;

    //SNAKE ATRIBUTES
    short tailLen;
    vector<COORD> snake_coords;
    direction current_direction;

    friend class Menu;
    friend class HIGHSCORES;

    CLASSIC(short mapWidth = 16, short mapHeight = 16, short snakeTempo = 100);
    ~CLASSIC();
    void gameplay();
    void setup();
    redraw logic(bool wheaterMapHasTorusTopology = true);
    void initial_draw();
    void draw(redraw const head);
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
    void displayMenu();
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





