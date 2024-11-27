// CLASSES DEFINITIONS
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <MMSystem.h>
#include <stdio.h>
#include <fstream>
#include <vector>

#include "Snake_classes.h"
#include "resource.h"

using namespace std;

//INTRO
//INTRO CONSTRUCTOR
Intro::Intro(COORD bufferSize) : bufferSize(bufferSize) { hanInt = GetStdHandle(STD_OUTPUT_HANDLE);}
//INTRO DESTRUCTOR
Intro::~Intro() {}
//THX INTRO
void Intro::displayTHX() {
        system("cls");
        system("color 8f");

        int x = bufferSize.X / 2 - 3;
        int y = bufferSize.Y / 2 - 3;

        write(x, y, "T H X");
        write(x - 4, y + 2, "sound system");

        PlaySound(MAKEINTRESOURCE(IDR_WAVE4), GetModuleHandle(NULL), SND_RESOURCE | SND_SYNC);
        
        system("cls");
        system("color 0a");
}
//SNAKE INTRO (TITLE SCREEN)
void Intro::displayTitle() {
    int GREEN = 10;
    int RED = 12;
    int DARK_GREEN = 2;
    int WHITE = 15;
    int WHITE_B = 120;
    
    // Snake
    PlaySound(MAKEINTRESOURCE(IDR_WAVE3), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);

    SetConsoleTextAttribute(hanInt, GREEN);
    cout << endl;
    Sleep(500);
    cout << "   o o O";

    SetConsoleTextAttribute(hanInt, RED);
    cout << "~";

    SetConsoleTextAttribute(hanInt, GREEN);
    cout << "                    o" << endl;
    cout << "   o                         o" << endl;
    cout << "   o o o   o o o   o o o     o   o   o o o" << endl;
    cout << "       o   o   o   o   o     o o     o o " << endl;
    cout << "   o o o   o   o   o o o o   o   o   o o o" << endl;
    
    Sleep(3000);
    
    // Keyboard
    PlaySound(MAKEINTRESOURCE(IDR_WAVE2), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
    
    cout << "\n\n";
    SetConsoleTextAttribute(hanInt, DARK_GREEN);
    cout << "                W";
    setCursorSize(50, true);
    for (char c : "K-K STUDIOS"){
        cout << c;
        cout.flush(); 
        Sleep(100);
    }

    // WKK-STUDIOS
    PlaySound(MAKEINTRESOURCE(IDR_WAVE5), GetModuleHandle(NULL), SND_RESOURCE | SND_SYNC);

    SetConsoleTextAttribute(hanInt, WHITE_B);
    setCursorSize(1, false);
    cout << "\n\n\n\n\n\n\n";
    while (true){
        SetConsoleTextAttribute(hanInt, WHITE);
        cout << "PRESS ANY BUTTON TO CONTINUE\r";
        Sleep(500);
        if(kbhit()) break;

        SetConsoleTextAttribute(hanInt, WHITE_B);
        cout << "PRESS ANY BUTTON TO CONTINUE\r";
        Sleep(500);

        if(kbhit()) break;
    }
    getch();
    system("cls");
}

//MENU
//MENU CONSTRUCTOR
Menu::Menu():
handle(GetStdHandle(STD_OUTPUT_HANDLE)), selection_happened(false), current_option(0), 
key_pressed(0), previous_option(-1) {
    options = {
        "CLASSIC",
        "ARCADE (STILL IN DEVELOPMENT)",
        "TWO PLAYERS (COOPERATION) (STILL IN DEVELOPMENT)",
        "TWO PLAYERS (LAST-ONE-STANDING) (STILL IN DEVELOPMENT)",
        "HIGH-SCORES (STILL IN DEVELOPMENT)",
        "CREDITS (STILL IN DEVELOPMENT)",
        "CONTROLS AND INSTRUCTION (STILL IN DEVELOPMENT)",
        "EXIT"
    };
    amount_of_options = options.size();
    option_colors = {15, 14, 9, 4, 6, 7, 8, 12};
    option_colors_chosen = {240, 224, 144, 64, 96, 112, 128, 192};
}
//MENU DESTRUCTOR
Menu::~Menu() {}
// CLIP TO AMOUNT OF OPTIONS
int Menu::clip(int num) { 
    return ((num % amount_of_options) + amount_of_options) % amount_of_options; 
}
//DISPLAY MENU
void Menu::displayMenu() {
    system("cls");

    //TITLE
    system("color 0a");
    SetConsoleTextAttribute(handle, 10);
    cout << endl;
    cout << "   o o O";
    SetConsoleTextAttribute(handle, 12);
    cout << "~";
    SetConsoleTextAttribute(handle, 10);
    cout << "                    o" << endl;
    cout << "   o                         o" << endl;
    cout << "   o o o   o o o   o o o     o   o   o o o" << endl;
    cout << "       o   o   o   o   o     o o     o o " << endl;
    cout << "   o o o   o   o   o o o o   o   o   o o o" << endl << endl;
    cout << "                    MENU" << endl << endl;

    //OPTIONS
    displayOptions();
}
//DISPLAY MNEU OPTIONS
void Menu::displayOptions()
{
    SetConsoleTextAttribute(handle, 240);
    cout << options[0]<< endl << endl;

    for (size_t i = 1; i < options.size(); ++i) {
        SetConsoleTextAttribute(handle, option_colors[i]);
        cout << options[i] << endl << endl;
    }

    // Reset color and display navigation instructions
    SetConsoleTextAttribute(handle, 2);
    std::cout << endl << "Navigate the menu using the [UP] and [DOWN] arrows,"
              << endl << "and press [ENTER] to select an option.";
}
//EVALUATE INPUT
bool Menu::parseInput() {
    // Get input
    while (key_pressed == 0) {
        if (_kbhit()) {  // Check if a key is pressed
            key_pressed = _getch(); // Get the first character of input

            // Handle special keys (arrows, function keys)
            if (key_pressed == 224 || key_pressed == 0) {
                key_pressed = _getch(); // Get the second character for special keys
            }
        }
    }
    
    // Parse input
    switch (key_pressed)
    {
        // Arrow DOWN
        case 72:
        previous_option = current_option;
        current_option = clip(current_option - 1);
        key_pressed = 0;
        return true;

        // Arrow UP
        case 80:
        previous_option = current_option;
        current_option = clip(current_option + 1);
        key_pressed = 0;
        return true;

        // Enter key
        case 13 :
        selection_happened = true;
        return false;

        default :
        return false;
    }
}
//GET INPUT AND UPDATE SELECTED OPTION
void Menu::updateMenu(){
    // Get index of last position in previous option string
    int previous_option_length = options[previous_option].length();
    int row = 10 + 2 * previous_option; // 8 rows for title and then every other

    // clean the prevoius position row
    SetConsoleTextAttribute(handle, option_colors[previous_option]);
    for (int x = previous_option_length; x > 0; x--){
        write(x, row, string(1, options[previous_option][x - 1]));
    }

    // current position
    int current_option_length = options[current_option].length();
    row = 10 + 2 * current_option;

    // check new row
    SetConsoleTextAttribute(handle, option_colors_chosen[current_option]);
    for (int x = 1; x <= current_option_length; x++){
        write(x, row, string(1, options[current_option][x - 1]));
    }
}
//MENU MAIN LOOP
void Menu::runMenu() {
    // main programm loop
    while(true){
        // reset variables
        previous_option = -1;
        selection_happened = false;
        current_option = 0;
        key_pressed = 0;

        // display initial menu
        displayMenu();

        // menu loop
        while(!selection_happened){
            if(parseInput()) updateMenu();
        }
        
        // run option
        if (executeOption()) break;
    }
}
//EXECUTE CHOOSEN OPTION
bool Menu::executeOption() {
    switch (current_option + 1){
        
        // CLASSIC - MODE
        case 1 : {
            CLASSIC classic;
            classic.gameplay();
            return false;
            break;
        }

        // HIGH - SCORES
        case 5: {
            HIGHSCORES highscores;
            highscores.readScores("CLASSIC");
            highscores.displayScores();
        }

        // EXIT    
        case 8 : { 
            EXIT exit;
            return exit.Exit();
            break;
        }

        // NOT IMPLEMENTED YET
        default :{
            system("cls");
            cout << "Unfortunately this option is still under development.\n"
                << "You'll be send back to main menu in a few seconds";
            Sleep(3000);
            return NULL;
            break;
        }
    }
}

//CLASSIC
//CLASSIC-MODE GAME CONSTRUCTOR
CLASSIC::CLASSIC(int mapWidth, int mapHeight, int snakeTempo): 
mapWidth(mapWidth), mapHeight(mapHeight), tempo(snakeTempo), 
snake_coords({COORD(mapWidth / 2 - mapWidth % 2, mapHeight / 2 - mapHeight % 2)}), 
gameOver(false), digesting(false) {}
//CLASSIC-MODE GAME DESTRUCTOR
CLASSIC::~CLASSIC() {}
// GAMEPLAY
void CLASSIC::gameplay() {
    // preparation
    setup ();
    initial_draw();

    // gameplay loop
    while (!gameOver){
        draw();
        input();
        logic();
        Sleep(tempo);
    }

    // final screen
    system("cls");
    cout << "GAME OVER" << endl << endl << "YOUR SCORE : " << score << endl;
    _getch();
}
//GAMEPLAY SETUP
void CLASSIC::setup() {
    current_direction = STOP;
    future_direction = STOP;

    fruitX = rand() % mapWidth;
    fruitY  = rand() % mapHeight;

    score = 0;

    system("color 07");
}
//GAME ENGINE
void CLASSIC::logic(bool wheaterMapHasTorusTopology) {
    int prevoiusX = snake_coords[0].X;
    int prevoiusY = snake_coords[0].Y;
    int prePrevoiusX, prePrevoiusY;

    // HERE HERE HERE HERE HERE HERE HERE HERE HERE HERE HERE HERE pop element from vector and move further

    // move tail
    for(int i = 1; i < tailLen; i++){
            prePrevoiusX=tailX[i];
            prePrevoiusY=tailY[i];

            tailX[i]=prevoiusX;
            tailY[i]=prevoiusY;

            prevoiusX=prePrevoiusX;
            prevoiusY=prePrevoiusY;
    }

    // check directions
    switch(current_direction){
    case LEFT:
        if(future_direction == RIGHT){
            current_direction = future_direction;
            x++;
        } else x--;
        break;

        case RIGHT:
        if(future_direction == LEFT){
            current_direction = future_direction;
            x--;
        } else x++;
        break;

    case DOWN:
        if(future_direction == UP){
            current_direction = future_direction;
            y--;
        } else y++;
        break;

    case UP:
        if(future_direction == DOWN){
            current_direction = future_direction;
            y++;
        } else y--;
        break;

    default:
        break;
    }

    // borders
    if(wheaterMapHasTorusTopology){
        if (x>=mapWidth) x=0; else if (x<0) x=mapWidth-1;
        if (y>=mapHeight) y=0; else if (y<0) y=mapHeight-1;

    }else{
        if (mapWidth<(x+1) || x < 0 || (y+1)>mapHeight || y < 0)
        gameOver=true;
    }

    // Whether snake bit himself
    for(int i = 0; i< tailLen; i++)
    {
        if(tailX[i] == x && tailY[i] == y)
            gameOver=true;
    }

    // Fruit eaten
    if (x == fruitX && y == fruitY){
        PlaySound(MAKEINTRESOURCE(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
        score += 10;
        fruitX = rand() % mapWidth;
        fruitY = rand() % mapHeight;

        for (tailIterator=0; tailIterator<mapWidth; tailIterator++){
            if(fruitX == tailX[tailIterator] && fruitY == tailY[tailIterator]){
                fruitX = rand() % mapWidth;
                tailIterator = 0;
            }
        }
        for (tailIterator=0;tailIterator<mapWidth;tailIterator++){
            if(fruitY == tailY[tailIterator] && fruitY == tailY[tailIterator]){
                fruitY  = rand() % mapHeight;
                tailIterator = 0;
            }
        }
        
        tailLen++;
        digesting = true;
    }
}
//GET USER INPUT
void CLASSIC::input() {
    if (_kbhit()){
        switch(getch()){
            case 'a':
            future_direction = current_direction;
            current_direction = LEFT;
            break;

            case 'd':
            future_direction = current_direction;
            current_direction = RIGHT;
            break;

            case 'w':
            future_direction = current_direction;
            current_direction = UP;
            break;

            case 's':
            future_direction = current_direction;
            current_direction = DOWN;
            break;

            case 'x':
            gameOver = true;
            break;
        }
    }
}
//DRAWING INITIAL FRAME
void CLASSIC::initial_draw() {
    system("cls");

    // First row
    for(int i = 0; i < mapWidth + 2; i++) { cout << "# "; }
    cout << endl;

    // map and columns
    for(int i = 0; i < mapHeight; i++){
        for(int j = 0; j < mapWidth; j++){
            // first column
            if (j == 0) { cout << "# "; }

            // map
            if (j == x && i == y) { cout << "O "; }
            else if (j == fruitX && i == fruitY) { cout << "Q "; }
            else { cout << "  "; }

            //last column
            if(j == mapWidth - 1) { cout << "# "; } cout << endl;
        }
    }
    
    // last row
    for(int i = 0; i < mapWidth + 2; i++) { cout << "# "; }
    
    // score
    cout << endl << endl << "YOUR SCORE : 0";
}
//DRAWING THE GAMEPLAY
void CLASSIC::draw() {

}

//HIGHSCORES
//HIGHSCORES CONSTRUCTOR
HIGHSCORES::HIGHSCORES() {}
//HIGHSCORES DESTRUCTOR
HIGHSCORES::~HIGHSCORES() {}
//READ HIGHSCORES FROM FILE
void HIGHSCORES::readScores(const string& mode) {
    // Build the file path
    string filePath = scoresDirectory + "HIGH-SCORES-" + mode + ".dat";

    // Open the file
    highScoresFile.open(filePath, std::ios::in);
    if (!highScoresFile.is_open()) {
        cerr << "Error: Unable to open high scores file: " << filePath << "\n";
        return;
    }

    // Read the file content
    string line;
    int lineNum = 0;

    while (getline(highScoresFile, line)) {
        if (lineNum % 2 == 0) {
            // Even lines contain names
            names.push_back(line);
        } else {
            // Odd lines contain scores
            try {
                scores.push_back(stoi(line));
            } catch (const invalid_argument& e) {
                cerr << "Error: Invalid score in file at line " << lineNum + 1 << ": " << line << "\n";
                scores.push_back(0); // Default to 0 if invalid
            }
        }
        lineNum++;
    }

    // Close the file
    highScoresFile.close();

    // Check for missmatch
    if (names.size() != scores.size()) {
        cerr << "Warning: High scores file has mismatched names and scores.\n";
    }

    // Optional: Display the high scores for debugging
    cout << "High Scores (" << mode << "):\n";
    for (size_t i = 0; i < names.size(); ++i) {
        cout << names[i] << ": " << scores[i] << "\n";
    }
}
//DISPLAY HIGHCORES
void HIGHSCORES::displayScores() {

    const int COLOR_TOP_SCORE = 14;
    const int COLOR_EVEN_ENTRY = 8;
    const int COLOR_ODD_ENTRY = 7;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(handle, 15);
    cout << "CLASSIC MODE HIGH-SCORES :" << endl << endl;

    if (names.empty() || scores.empty()) {
        std::cout << "No high scores available to display.\n";
        return;
    }

    for (size_t i = 0; i < names.size(); ++i) {
        if (i == 0) SetConsoleTextAttribute(handle, COLOR_TOP_SCORE);
        else if (i >= 3 && (i % 2 == 0)) SetConsoleTextAttribute(handle, COLOR_EVEN_ENTRY);
        else if (i >= 4) SetConsoleTextAttribute(handle, COLOR_ODD_ENTRY);
        std::cout << i + 1 << "  " << names[i] << " : " << scores[i] << "\n";
    }

    system("pause");
}
//SAVE HIGHSCORES TO A FILE
void HIGHSCORES::saveScores(const string& mode) {
    // Build the file path using a relative directory
    std::string filePath = scoresDirectory + "HIGH-SCORES-" + mode + ".dat";

    // Open the file in output mode
    std::ofstream highScoresFile(filePath, std::ios::out);
    if (!highScoresFile.is_open()) {
        std::cerr << "Error: Unable to open high scores file for saving: " << filePath << "\n";
        return;
    }

    // Write names and scores to the file
    for (size_t i = 0; i < names.size(); ++i) {
        highScoresFile << names[i] << "\n" << scores[i] << "\n";
    }

    // Close the file
    highScoresFile.close();

    // Debug message
    std::cout << "High scores saved successfully to " << filePath << "\n";
}

//EXIT
//KONSTRUKTOR EXIT
EXIT::EXIT() {}
//DESTRUKTOR EXIT
EXIT::~EXIT() {}
bool EXIT::Exit() {
    cout << "Bye bye...";
    return true;
}






