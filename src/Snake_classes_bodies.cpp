// CLASSES DEFINITIONS
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <MMSystem.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <limits>
#include<algorithm>

#include "Snake_classes.h"
#include "resource.h"

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27


//INTRO
//INTRO CONSTRUCTOR
Intro::Intro(COORD bufferSize) : bufferSize(bufferSize) { hanInt = GetStdHandle(STD_OUTPUT_HANDLE);}
//INTRO DESTRUCTOR
Intro::~Intro() {}
//THX INTRO
void Intro::displayTHX() {
        system("cls");
        system("color 8f");

        int x = bufferSize.X / 2 + 30;
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
        "HIGH-SCORES",
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
        case KEY_DOWN:
        previous_option = current_option;
        current_option = clip(current_option + 1);
        key_pressed = 0;
        return true;

        // Arrow UP
        case KEY_UP:
        previous_option = current_option;
        current_option = clip(current_option - 1);
        key_pressed = 0;
        return true;

        // Enter key
        case KEY_ENTER:
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
        if (x % 5 == 0) Sleep(1);
    }

    // current position
    int current_option_length = options[current_option].length();
    row = 10 + 2 * current_option;

    // check new row
    SetConsoleTextAttribute(handle, option_colors_chosen[current_option]);
    for (int x = 1; x <= current_option_length; x++){
        write(x, row, string(1, options[current_option][x - 1]));
        if (x % 5 == 0) Sleep(1);
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
bool Menu::executeOption() { // TO DO: ESC key freezes the screen
    switch (current_option + 1){
        
        // CLASSIC - MODE
        case 1 : {
            CLASSIC classic;
            classic.gameplay();
            return false;
        }

        // COOPERATION CLASSIC - MODE
        case 3 : {
            CLASSIC_MULTI_COOP coop;
            coop.gameplay();
            return false;
        }

        // HIGH - SCORES
        case 5: {
            HIGHSCORES highscores;
            highscores.displayMenu();
            return false;
        }

        // EXIT    
        case 8 : { 
            EXIT exit;
            return exit.Exit();
            return true;
        }

        // NOT IMPLEMENTED YET
        default :{
            system("cls");
            cout << endl << "Unfortunately this option is still under development.\n"
                 << "You'll be send back to main menu in a few seconds";
            Sleep(2500);
            return false;
        }
    }
}


//1. CLASSIC
//CLASSIC-MODE GAME CONSTRUCTOR
CLASSIC::CLASSIC(short mapWidth, short mapHeight, short snakeTempo): 
mapWidth(mapWidth), mapHeight(mapHeight), tempo(snakeTempo), gameOver(false),
snake_coords({COORD{(short)(mapWidth / 2 - mapWidth % 2), (short)(mapHeight / 2 - mapHeight % 2)}}) {}
//CLASSIC-MODE GAME DESTRUCTOR
CLASSIC::~CLASSIC() {}
// GAMEPLAY
void CLASSIC::gameplay() {
    // preparation
    setup ();
    initial_draw();
    DWORD lastUpdate = GetTickCount();
    bool escaped;

    // gameplay loop
    while (!gameOver){
        // Get input continuously (every 2 ms)
        escaped = input();

        // Update game every tempo milisecounds
        DWORD now = GetTickCount();
        if (now - lastUpdate >= tempo){
            draw(logic());
            lastUpdate = now;
        }
        // Sleep for a short time to prevent high CPU usage
        Sleep(2);
    }
    Sleep(700);

    if (escaped) postGameScreen();
}
// DISPLAY POST GAME SCREEN WITH SCORE
void CLASSIC::postGameScreen() {
    // final screen
    fflush(stdin);
    system("cls");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD buffer = getMaxBufferSize();
    int width = buffer.X / 2;
    int height = buffer.Y / 2;
    string scoreStr = "YOUR SCORE : " + to_string(score);

    cout << string(height - 12, '\n') << string(width - 13, ' ') << "~   G A M E   O V E R   ~" 
         << endl << endl <<  endl <<endl << string(width - (scoreStr.size() / 2) - 1, ' ') 
         << scoreStr << endl;

    HIGHSCORES hs;
    int place = hs.checkScore("CLASSIC", score);
    string placeStr;
    if (place == 1) {
        placeStr = "Congratulations! You achieved the highest score!";
    } else if (place == 2) {
        placeStr = "Great job! You secured the second-highest score!";
    } else if (place == 3) {
        placeStr = "Well done! You made it to the podium with the third-highest score!";
    } else {
        placeStr = "You achieved the " + to_string(place) + "-th highest score. Keep striving for the top!";
    }

    cout << endl << endl << endl << string(width - (placeStr.size() / 2), ' ') << placeStr
         << endl << endl << string(width - 13, ' ') << "Would you like to save it?"
         << endl << endl << endl << string(width - 7, ' ');
    
    const int CHECKED_COLOR = 240;
    const int UNCHECKED_COLOR = 7;
    bool checked_yes = true;
    int key_pressed = -1;

    SetConsoleTextAttribute(hConsole, (checked_yes ? CHECKED_COLOR : UNCHECKED_COLOR));
    cout << " YES ";       
    SetConsoleTextAttribute(hConsole, UNCHECKED_COLOR);
    cout << string(5, ' ');
    SetConsoleTextAttribute(hConsole, (checked_yes ? UNCHECKED_COLOR : CHECKED_COLOR));
    cout <<  " NO ";

    while(true){
        if (_kbhit()) {
            key_pressed = _getch();
        
            if (key_pressed == KEY_LEFT) { checked_yes = true;
            } else if (key_pressed == KEY_RIGHT) { checked_yes = false;
            } else if (key_pressed == KEY_ENTER) break;

            cout << string(14, '\b');
            SetConsoleTextAttribute(hConsole, (checked_yes ? CHECKED_COLOR : UNCHECKED_COLOR));
            cout << " YES ";       
            SetConsoleTextAttribute(hConsole, UNCHECKED_COLOR);
            cout << string(5, ' ');
            SetConsoleTextAttribute(hConsole, (checked_yes ? UNCHECKED_COLOR : CHECKED_COLOR));
            cout <<  " NO ";
        }

        Sleep(5);
    }
    SetConsoleTextAttribute(hConsole, UNCHECKED_COLOR);

    if (checked_yes) {
        string name;
        cout << endl << endl << string(width - 8, ' ') << "Input Your name:";

        // Loop to get characters until Enter is pressed
        char symbol;
        int xPos = width;
        while (true) {
            if (_kbhit()) { // Check if a key is pressed
                symbol = _getch(); // Get the character

                // If Enter (newline character) is detected, break the loop
                if (symbol == KEY_ENTER) break;


                if (symbol == '\b' && !name.empty()) { 
                    name.pop_back();
                } else if (symbol >= 32 && symbol <= 126) { // Printable characters
                    name += symbol;
                } 
                    xPos = width - name.size() / 2;

                    COORD position = {(short)(0), (short)32};
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
                    cout << string(width + name.size() + 1, ' ');
                    position = {static_cast<SHORT>(xPos), (short)32};
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
                    cout << name;
            }
            Sleep(2);
        }
        hs.addScore("CLASSIC", name, score, place - 1);
        hs.displayScores("CLASSIC");
    }
}
//GAMEPLAY SETUP
void CLASSIC::setup() {
    current_direction = STOP;

    fruit_coords = { (short)(rand() % mapWidth), (short)(rand() % mapHeight) };

    score = 0;

    system("color 07");
}
//GAME ENGINE
redraw CLASSIC::logic(bool wheaterMapHasTorusTopology) {
    // Process the input queue
    if (!inputQueue.empty()) {
        current_direction = inputQueue.front();
        inputQueue.pop();
    }

    // Initialize vector of elements to be redawn
    redraw elements;

    // Get head
    COORD head = snake_coords[0];

    // Check directions
    switch (current_direction){
        case LEFT:
            head.X--;
            break;

        case RIGHT:
            head.X++;
            break;

        case DOWN:
            head.Y++;
            break;

        case UP:
            head.Y--;
            break;

        default:
            break;
    }

    // Borders
    if (wheaterMapHasTorusTopology){
        if (head.X >= mapWidth) head.X = 0; 
        else if (head.X < 0) head.X = mapWidth - 1;

        if (head.Y >= mapHeight) head.Y = 0; 
        else if (head.Y < 0) head.Y = mapHeight - 1;

    } else{
        if (mapWidth < (head.X + 1) || head.X < 0 || 
           (head.Y + 1) > mapHeight || head.Y < 0)
        gameOver = true;
    }

    // Whether snake bit himself
    for (auto segment = snake_coords.begin() + 1; segment != snake_coords.end(); segment++) {
        if (segment->X == head.X && segment->Y == head.Y) {
            gameOver = true;
            break;
        }
    }

    // Fruit eaten
    if (head.X == fruit_coords.X && head.Y == fruit_coords.Y) {
        PlaySound(MAKEINTRESOURCE(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
        
        elements.push_back({{fruit_coords.X, fruit_coords.Y}, "  "});

        // Draw random fruit position and check if it's valid
        bool isInvalid = true;
        while (isInvalid) {
            // Generate random fruit coordinates
            fruit_coords = { (short)(rand() % mapWidth), (short)(rand() % mapHeight) };

            // Set initial validity
            isInvalid = false;

            // Check if the coordinates overlap with any part of the snake
            for (auto segment = snake_coords.begin(); segment != snake_coords.end(); ++segment) {
                if (segment->X == fruit_coords.X && segment->Y == fruit_coords.Y) {
                    isInvalid = true;  // Overlap found, mark as invalid
                    break;
                }
            }
        }

        elements.push_back({{fruit_coords.X, fruit_coords.Y}, "Q "});

        score += 10;
        elements.push_back({{(short)5, (short)(mapHeight + 2)}, to_string(score)});

    } else {
        // Do not pop tail end if fruit was eaten
        elements.push_back({{snake_coords.back().X, snake_coords.back().Y}, "  "});
        snake_coords.pop_back();
    }

    // Move snake
    if (snake_coords.size() > 0) elements.push_back({{snake_coords[0].X, snake_coords[0].Y}, "o "});
    snake_coords.insert(snake_coords.begin(), head);
    elements.push_back({{head.X, head.Y}, "O "});

    return elements;
}
//GET USER INPUT
bool CLASSIC::input() {
    while (_kbhit()){
        // Get prevoius direction
        int last_direction = current_direction;
        if (!inputQueue.empty()) last_direction = inputQueue.back();
        switch(_getch()){
            case KEY_LEFT:
                if (last_direction != RIGHT) inputQueue.push(LEFT);
                break;

            case KEY_RIGHT:
                if (last_direction != LEFT) inputQueue.push(RIGHT);
                break;

            case KEY_UP:
                if (last_direction != DOWN) inputQueue.push(UP);
                break;

            case KEY_DOWN:
                if (last_direction != UP) inputQueue.push(DOWN);
                break;

            case KEY_ESC:
                gameOver = true;
                return false;
        }
    }
    return true;
}
//DRAWING INITIAL FRAME
void CLASSIC::initial_draw() {
    system("cls");

    // First row
    for(int i = 0; i < mapWidth + 2; i++) { cout << "# "; }
    cout << endl;

    // map and columns
    short headX = snake_coords[0].X;
    short headY = snake_coords[0].Y;

    for(int i = 0; i < mapHeight; i++){
        for(int j = 0; j < mapWidth; j++){
            // first column
            if (j == 0) cout << "# ";

            // map
            if (j == headX && i == headY) cout << "O ";
            else if (j == fruit_coords.X && i == fruit_coords.Y) cout << "Q ";
            else cout << "  ";

            //last column
            if(j == mapWidth - 1) cout << "# " << endl;
        }
    }
    
    // last row
    for(int i = 0; i < mapWidth + 2; i++) { cout << "# "; }
    
    // score
    cout << endl << endl << "YOUR SCORE: 0";

    // instruction
    cout << endl << endl << "Controls:" << endl 
         << " - Use [ARROW KEYS] to control the snake." << endl
         << " - Press [ESCAPE] to go back to main menu (progress will be lost).";
}
//DRAWING THE GAMEPLAY
void CLASSIC::draw(redraw const elements) {
    for (pair<COORD, string> element : elements) {
        write(element.first.X * 2 + 3, element.first.Y + 2, element.second);
    }
}


//2. CLASSIC_MULTI_COOP
//MULTIPLAYER-COOPERATION CLASSIC-MODE GAME CONSTRUCTOR
/**
 * @brief Constructs a multiplayer cooperation classic-mode snake game.
 * 
 * Initializes the game map and player-controlled snake positions based on the number of players.
 * Ensures a valid number of players (between 2 and 10) and assigns initial snake positions
 * according to predefined fractional coordinates for fair distribution on the map.
 * 
 * @param mapWidth The width of the game map.
 * @param mapHeight The height of the game map.
 * @param snakeTempo The speed of the snake movement (lower value means faster tempo).
 * @param numOfPlayers The number of players (must be between 2 and 10).
 */
CLASSIC_MULTI_COOP::CLASSIC_MULTI_COOP(short mapWidth, short mapHeight, short snakeTempo, short numOfPlayers): 
mapWidth(mapWidth), mapHeight(mapHeight), tempo(snakeTempo), gameOver(false), 
numOfPlayers(std::max((short)2, std::min(numOfPlayers, (short)10))) {}
//CLASSIC-MODE GAME DESTRUCTOR
CLASSIC_MULTI_COOP::~CLASSIC_MULTI_COOP() {}
// GAMEPLAY
void CLASSIC_MULTI_COOP::gameplay() {
    // preparation
    setup (); // TO DO: make an starting screen to choose num of players and stearing
    initial_draw();
    DWORD lastUpdate = GetTickCount();
    bool escaped;

    // gameplay loop
    while (!gameOver){
        // Get input continuously (every 2 ms)
        escaped = input();

        // Update game every tempo milisecounds
        DWORD now = GetTickCount();
        if (now - lastUpdate >= tempo){
            draw(logic());
            lastUpdate = now;
        }
        // Sleep for a short time to prevent high CPU usage
        Sleep(2);
    }
    Sleep(700);

    //if (escaped) postGameScreen(); // TO DO: Create post game screen based on singleplayer
}
// DISPLAY POST GAME SCREEN WITH SCORE
void CLASSIC_MULTI_COOP::postGameScreen() {
    // final screen
    fflush(stdin);
    system("cls");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD buffer = getMaxBufferSize();
    int width = buffer.X / 2;
    int height = buffer.Y / 2;
    string scoreStr = "YOUR SCORE : " + to_string(score);

    cout << string(height - 12, '\n') << string(width - 13, ' ') << "~   G A M E   O V E R   ~" 
         << endl << endl <<  endl <<endl << string(width - (scoreStr.size() / 2) - 1, ' ') 
         << scoreStr << endl;

    HIGHSCORES hs;
    int place = hs.checkScore("CLASSIC", score);
    string placeStr;
    if (place == 1) {
        placeStr = "Congratulations! You achieved the highest score!";
    } else if (place == 2) {
        placeStr = "Great job! You secured the second-highest score!";
    } else if (place == 3) {
        placeStr = "Well done! You made it to the podium with the third-highest score!";
    } else {
        placeStr = "You achieved the " + to_string(place) + "-th highest score. Keep striving for the top!";
    }

    cout << endl << endl << endl << string(width - (placeStr.size() / 2), ' ') << placeStr
         << endl << endl << string(width - 13, ' ') << "Would you like to save it?"
         << endl << endl << endl << string(width - 7, ' ');
    
    const int CHECKED_COLOR = 240;
    const int UNCHECKED_COLOR = 7;
    bool checked_yes = true;
    int key_pressed = -1;

    SetConsoleTextAttribute(hConsole, (checked_yes ? CHECKED_COLOR : UNCHECKED_COLOR));
    cout << " YES ";       
    SetConsoleTextAttribute(hConsole, UNCHECKED_COLOR);
    cout << string(5, ' ');
    SetConsoleTextAttribute(hConsole, (checked_yes ? UNCHECKED_COLOR : CHECKED_COLOR));
    cout <<  " NO ";

    while(true){
        if (_kbhit()) {
            key_pressed = _getch();
        
            if (key_pressed == KEY_LEFT) { checked_yes = true;
            } else if (key_pressed == KEY_RIGHT) { checked_yes = false;
            } else if (key_pressed == KEY_ENTER) break;

            cout << string(14, '\b');
            SetConsoleTextAttribute(hConsole, (checked_yes ? CHECKED_COLOR : UNCHECKED_COLOR));
            cout << " YES ";       
            SetConsoleTextAttribute(hConsole, UNCHECKED_COLOR);
            cout << string(5, ' ');
            SetConsoleTextAttribute(hConsole, (checked_yes ? UNCHECKED_COLOR : CHECKED_COLOR));
            cout <<  " NO ";
        }

        Sleep(5);
    }
    SetConsoleTextAttribute(hConsole, UNCHECKED_COLOR);

    if (checked_yes) {
        string name;
        cout << endl << endl << string(width - 8, ' ') << "Input Your name:";

        // Loop to get characters until Enter is pressed
        char symbol;
        int xPos = width;
        while (true) {
            if (_kbhit()) { // Check if a key is pressed
                symbol = _getch(); // Get the character

                // If Enter (newline character) is detected, break the loop
                if (symbol == KEY_ENTER) break;


                if (symbol == '\b' && !name.empty()) { 
                    name.pop_back();
                } else if (symbol >= 32 && symbol <= 126) { // Printable characters
                    name += symbol;
                } 
                    xPos = width - name.size() / 2;

                    COORD position = {(short)(0), (short)32};
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
                    cout << string(width + name.size() + 1, ' ');
                    position = {static_cast<SHORT>(xPos), (short)32};
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
                    cout << name;
            }
            Sleep(2);
        }
        hs.addScore("CLASSIC", name, score, place - 1);
        hs.displayScores("CLASSIC");
    }
}
//GAMEPLAY SETUP
void CLASSIC_MULTI_COOP::setup() {

    // Set initial positions
    std::vector<std::pair<float, float>> positions;
    switch (numOfPlayers) {
        case 2:
            positions = {{0.33f, 0.5f}, {0.67f, 0.5f}};
            break;
        case 3:
            positions = {{0.25f, 0.5f}, {0.5f, 0.5f}, {0.75f, 0.5f}};
            break;
        case 4:
            positions = {{0.25f, 0.25f}, {0.75f, 0.25f}, 
                         {0.25f, 0.75f}, {0.75f, 0.75f}};
            break;
        case 5:
            positions = {{0.25f, 0.25f}, {0.75f, 0.25f}, 
                                {0.5f, 0.5f}, 
                         {0.75f, 0.75f}, {0.25f, 0.75f}};
            break;
        case 6:
            positions = {{0.25f, 0.25f}, {0.5f, 0.25f}, {0.75f, 0.25f},
                         {0.75f, 0.75f}, {0.5f, 0.75f}, {0.25f, 0.75f}};
            break;
        case 7:
            positions = {{0.25f, 0.25f}, {0.5f, 0.25f}, {0.75f, 0.25f}, 
                                         {0.5f, 0.5f},
                         {0.25f, 0.75f}, {0.5f, 0.75f}, {0.75f, 0.75f}};
            break;
        case 8:
            positions = {{0.25f, 0.25f}, {0.5f, 0.25f}, {0.75f, 0.25f}, 
                                {0.25f, 0.5f}, {0.75f, 0.5f},
                         {0.25f, 0.75f}, {0.5f, 0.75f}, {0.75f, 0.75f}};
            break;
        case 9:
            positions = {{0.25f, 0.25f}, {0.5f, 0.25f}, {0.75f, 0.25f}, 
                         {0.25f, 0.5f}, {0.5f, 0.5f}, {0.75f, 0.5f},
                         {0.25f, 0.75f}, {0.5f, 0.75f}, {0.75f, 0.75f}};
            break;
        case 10:
            positions = {{0.25f, 0.25f}, {0.5f, 0.25f}, {0.75f, 0.25f}, 
                         {0.2f, 0.5f}, {0.4f, 0.5f}, {0.6f, 0.5f}, {0.8f, 0.5f}, 
                         {0.25f, 0.75f}, {0.5f, 0.75f}, {0.75f, 0.75f}};
            break;
    }

    // Convert fractional positions to integer coordinates
    for (const auto& pos : positions) {
        Snake snk;
        snk.current_direction = UP;
        snk.snake_coords.push_back(COORD{
            (short)(mapWidth * pos.first), 
            (short)(mapHeight * pos.second)
        });
        snakes.push_back(snk);
    }

    fruit_coords = { (short)(rand() % mapWidth), (short)(rand() % mapHeight) };

    score = 0;

    system("color 07");
}
//GAME ENGINE
redraw CLASSIC_MULTI_COOP::logic(bool wheaterMapHasTorusTopology) {
    // Process the input queue // TO DO: process input properely 
    if (!inputQueue.empty()) {
        direction newDirection = inputQueue.front();
        inputQueue.pop();
        for (auto& snk : snakes) {
            snk.current_direction = newDirection;
        }
    }

    // Initialize vector of elements to be redawn
    redraw elements;

    // Get heads
    for (auto snake : snakes) {
        COORD head = snake.snake_coords[0];

        // Check directions
        switch (snake.current_direction){
            case LEFT:
                head.X--;
                break;

            case RIGHT:
                head.X++;
                break;

            case DOWN:
                head.Y++;
                break;

            case UP:
                head.Y--;
                break;

            default:
                break;
        }

        // Borders
        if (wheaterMapHasTorusTopology){
            if (head.X >= mapWidth) head.X = 0; 
            else if (head.X < 0) head.X = mapWidth - 1;

            if (head.Y >= mapHeight) head.Y = 0; 
            else if (head.Y < 0) head.Y = mapHeight - 1;

        } else{
            if (mapWidth < (head.X + 1) || head.X < 0 || 
            (head.Y + 1) > mapHeight || head.Y < 0)
            gameOver = true;
        }

        // Whether snake bit himself or other players
        bool collisionDetected = false;
        for (const auto& snake2 : snakes) {
            for (auto segment = snake2.snake_coords.begin() + 1; segment != snake2.snake_coords.end(); ++segment) {
                if (segment->X == head.X && segment->Y == head.Y) {
                    gameOver = true;
                    collisionDetected = true;
                    break; // Break from inner loop
                }
            }
            if (collisionDetected) break; // Break from outer loop
        }

        // Fruit eaten
        if (head.X == fruit_coords.X && head.Y == fruit_coords.Y) {
            PlaySound(MAKEINTRESOURCE(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
            
            elements.push_back({{fruit_coords.X, fruit_coords.Y}, "  "});

            // Draw random fruit position and check if it's valid
            bool isInvalid = true;
            while (isInvalid) {
                // Generate random fruit coordinates
                fruit_coords = { (short)(rand() % mapWidth), (short)(rand() % mapHeight) };

                // Set initial validity
                isInvalid = false;

                // Check if the coordinates overlap with any part of the snake
                for (const auto& snake2 : snakes) {
                    for (auto segment = snake2.snake_coords.begin(); segment != snake2.snake_coords.end(); ++segment) {
                        if (segment->X == fruit_coords.X && segment->Y == fruit_coords.Y) {
                            isInvalid = true;  // Overlap found, mark as invalid
                            break;
                        }
                    }
                }
            }

        elements.push_back({{fruit_coords.X, fruit_coords.Y}, "Q "});

        score += 10;
        elements.push_back({{(short)5, (short)(mapHeight + 2)}, to_string(score)});

    } else {
        // Do not pop tail end if fruit was eaten
        elements.push_back({{snake.snake_coords.back().X, snake.snake_coords.back().Y}, "  "});
        snake.snake_coords.pop_back();
    }

        // Move snake
        if (snake.snake_coords.size() > 0) elements.push_back({{snake.snake_coords[0].X, snake.snake_coords[0].Y}, "o "});
        snake.snake_coords.insert(snake.snake_coords.begin(), head);
        elements.push_back({{head.X, head.Y}, "O "});
    }
    return elements;
}
//GET USER INPUT
bool CLASSIC_MULTI_COOP::input() { // TEMPORARY ONLY ONE INPUT TAKEN
    while (_kbhit()){
        // Get prevoius direction
        int last_direction = snakes[0].current_direction;
        if (!inputQueue.empty()) last_direction = inputQueue.back();
        switch(_getch()){
            case KEY_LEFT:
                if (last_direction != RIGHT) inputQueue.push(LEFT);
                break;

            case KEY_RIGHT:
                if (last_direction != LEFT) inputQueue.push(RIGHT);
                break;

            case KEY_UP:
                if (last_direction != DOWN) inputQueue.push(UP);
                break;

            case KEY_DOWN:
                if (last_direction != UP) inputQueue.push(DOWN);
                break;

            case KEY_ESC:
                gameOver = true;
                return false;
                break;
        }
    }
    return true;
}
//DRAWING INITIAL FRAME
void CLASSIC_MULTI_COOP::initial_draw() {
    system("cls");

    // First row
    for(int i = 0; i < mapWidth + 2; i++) { cout << "# "; }
    cout << endl;

    // map and columns
    vector<COORD> heads;
    for (auto snake : snakes) {
        heads.push_back(snake.snake_coords[0]);
    }

    for(int i = 0; i < mapHeight; i++){
        for(int j = 0; j < mapWidth; j++){
            // first column
            if (j == 0) cout << "# ";

            // map
            if (find_if(heads.begin(), heads.end(), [i, j](const COORD& coord) {
                    return coord.X == i && coord.Y == j;
                }) != heads.end()) { 
                    cout << "O "; 
            } else if (j == fruit_coords.X && i == fruit_coords.Y) cout << "Q ";
            else cout << "  ";

            //last column
            if(j == mapWidth - 1) cout << "# " << endl;
        }
    }
    
    // last row
    for(int i = 0; i < mapWidth + 2; i++) { cout << "# "; }
    
    // score
    cout << endl << endl << "YOUR SCORE: 0";

    // instruction
    cout << endl << endl << "Controls:" << endl 
         << " - Use [ARROW KEYS] to control the snake." << endl
         << " - Press [ESCAPE] to go back to main menu (progress will be lost).";
}
//DRAWING THE GAMEPLAY
void CLASSIC_MULTI_COOP::draw(redraw const& elements) {
    for (pair<COORD, string> element : elements) {
        write(element.first.X * 2 + 3, element.first.Y + 2, element.second);
    }
}


//5. HIGHSCORES
//HIGHSCORES CONSTRUCTOR
HIGHSCORES::HIGHSCORES() {}
//HIGHSCORES DESTRUCTOR
HIGHSCORES::~HIGHSCORES() {}
// MENU OF HIGHSCORES
void HIGHSCORES::displayMenu() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    const int CONSOLE_COLOR_CODE = 14; // 103 - silver on gold

    while (true) {
        SetConsoleTextAttribute(hConsole, CONSOLE_COLOR_CODE);
        system("cls");

        // Menu display
        cout << endl 
             << "*****************************************" << endl
             << "*    -    H I G H   S C O R E S    -    *" << endl
             << "*****************************************" << endl << endl
             << "*---------------------------------------*" << endl
             << "* Pick a game mode to view high scores: *" << endl
             << "*---------------------------------------*" << endl
             << "* [1] - CLASSIC MODE                    *" << endl
             << "* [2] - ARCADE MODE                     *" << endl
             << "* [3] - TWO PLAYERS (COOP) MODE         *" << endl
             << "* [4] - TWO PLAYERS (LOS) MODE          *" << endl
             << "* [0] - Exit High Scores                *" << endl
             << "*---------------------------------------*" << endl;

        // Prompt the user for input
        cout << endl <<">> Enter your choice: ";
        int choice;
        cin >> choice;

        // Clear the input buffer
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            SetConsoleTextAttribute(hConsole, CONSOLE_COLOR_CODE - 2);  // Red text for error
            cout << endl <<"Invalid input! Please enter a valid number (0-4)." << endl;
            SetConsoleTextAttribute(hConsole, CONSOLE_COLOR_CODE);  // Reset to menu color
            Sleep(1000);
            continue;
        }

        // Process the user's choice
        string mode;
        switch (choice) {
            case 1:
                mode = "CLASSIC";
                break;

            case 2:
                mode = "ARCADE";
                break;

            case 3:
                mode = "TWO PLAYERS (COOP)";
                break;

            case 4:
                mode = "TWO PLAYERS (LOS)";
                break;

            case 0:
                return;
                
            default:
                SetConsoleTextAttribute(hConsole, CONSOLE_COLOR_CODE - 2);  // Red text for error
                cout << endl << "Invalid choice! Please select a valid option (0-4)." << endl;
                SetConsoleTextAttribute(hConsole, CONSOLE_COLOR_CODE);  // Reset to menu color
                Sleep(1000);
                continue;
        }

        readScores(mode);
        displayScores(mode);
    }
}
//READ HIGHSCORES FROM FILE
void HIGHSCORES::readScores(const string& mode) {
    names.clear();
    scores.clear();

    // Build the file path
    string filePath = scoresDirectory + mode + ".dat";

    // Open the file
    highScoresFile.open(filePath, std::ios::in);
    if (!highScoresFile.is_open()) {
        cerr << "Error: Unable to open high scores file: " << filePath << "\n";
        _getch();
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
                _getch();
            }
        }
        lineNum++;
    }

    // Close the file
    highScoresFile.close();

    // Check for missmatch
    if (names.size() != scores.size()) {
        cerr << "Warning: High scores file has mismatched names and scores.\n";
        _getch();
    }
}
//DISPLAY HIGHCORES
void HIGHSCORES::displayScores(const string& mode) {
    // Constants
    const int COLOR_TOP_SCORE = 110;
    const int COLOR_EVEN_ENTRY = 111;
    const int COLOR_ODD_ENTRY = 103;
    const int COLOR_BLACK_ON_GOLD = 96;
    const string TITLE = insertSpaces(" ~ " + mode + " MODE HIGH-SCORES ~ ", 2);
    const int HALF_TITLE = TITLE.size() / 2 + 1;

    // Get utils
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    const int middle = getMaxBufferSize().X / 2;
    const string spaces = string(middle - HALF_TITLE - 4, ' ');

    // Title
    SetConsoleTextAttribute(handle, COLOR_BLACK_ON_GOLD);
    system("cls");

    cout << endl << endl
         << spaces << string(TITLE.size() + 4, '*') << endl
         << spaces << "* " << string(TITLE.size(), ' ') << " *" << endl
         << spaces << "* " << TITLE << " *" << endl
         << spaces << "* " << string(TITLE.size(), ' ') << " *" << endl
         << spaces << string(TITLE.size() + 4, '*') << endl << endl << endl;

    if (names.empty() || scores.empty()) {
        std::cout << "No high scores available to display.\n";
        _getch();
        return;
    }

    int mid = TITLE.size() / 2;
    for (size_t i = 0; i < names.size() && i < 20; ++i) {
        // Set color
        if (i == 0) SetConsoleTextAttribute(handle, COLOR_TOP_SCORE);
        else if (i >= 3 && (i % 2 == 0)) SetConsoleTextAttribute(handle, COLOR_EVEN_ENTRY);
        else if (i >= 3) SetConsoleTextAttribute(handle, COLOR_ODD_ENTRY);
        string scoreStr = to_string(scores[i]);
        cout << spaces << ((i < 9) ? " " : "") << i + 1 << "  " 
             << truncateString(names[i], mid) << rightJust(scoreStr, mid) << endl << endl;
    }

    SetConsoleTextAttribute(handle, COLOR_BLACK_ON_GOLD);
    cout << endl << endl
         << string(middle - 16, ' ')
         << "Press any button to go back...";
    _getch();
}
//SAVE HIGHSCORES TO A FILE
void HIGHSCORES::saveScores(const string& mode) {
    // Build the file path using a relative directory
    string filePath = scoresDirectory + mode + ".dat";

    // Open the file in output mode
    ofstream highScoresFile(filePath, ios::out);
    if (!highScoresFile.is_open()) {
        cerr << "Error: Unable to open high scores file for saving: " << filePath << "\n";
        return;
    }

    // Write names and scores to the file
    for (size_t i = 0; i < names.size(); ++i) {
        highScoresFile << names[i] << "\n" << scores[i] << "\n";
    }

    // Close the file
    highScoresFile.close();
}
//CHECK GIVEN SCORE PLACE IN HIGH SCORES (INDEXING FROM 1 !)
int HIGHSCORES::checkScore(const string& mode, int score) {
    // Get high scores for a given mode
    readScores(mode);

    // Find the place in the high scores
    for (size_t i = 0; i < scores.size(); ++i) {
        if (scores[i] < score) {
            return i + 1;
        }
    }

    // Default case
    return -1;
}
//ADD SCORE
void HIGHSCORES::addScore(const string& mode, const string name, int score, int place) {
    readScores(mode);

    names.insert(names.begin() + place, name);
    scores.insert(scores.begin() + place, score);

    saveScores(mode);
}


//8. EXIT
//KONSTRUKTOR EXIT
EXIT::EXIT() {}
//DESTRUKTOR EXIT
EXIT::~EXIT() {}
bool EXIT::Exit() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    system("cls");
    string snake = "       ~Ooooooooooo";
    string bye =   "     Bye Bye...    ";

    for (int i=snake.length(); i >=0 ; i--) {
        Sleep(150);
        cout << "\r" << snake.substr(snake.length() - i, i) << bye.substr(i);
    }

    Sleep(1000);
    system("cls");

    return true;
}






