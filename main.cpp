#include "board.h"
#include <utility>
#include <iostream>

typedef pair<string, char> player;

void clearBoard(){
    for(size_t i = 0; i < x.size(); i++){
        for(size_t j = 0; j < y.size(); j++){
            board[x[i]][y[j]] = ' ';
        }
    }
}

void printBoard(){
    for(size_t i = 0; i < board.size(); i++){
        for(size_t j = 0; j < board[i].size(); j++){
            cout << board[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
}

void printDirections(){
    cout <<
    "Objective: to be the first player to get\n" <<
    "three consecutive symbols horizontally, \n" <<
    "vertically, or diagonally             \n\n" <<
    "Directions: When it is your turn,       \n" <<
    "provide the proper coordinates in       \n" <<
    "the form number then letter: 1b         \n\n";
}

void printGameMenu(){
    cout <<
    "############################\n" <<
    "# Press P to print board   #\n" <<
    "# Press D for directions   #\n" <<
    "# Press Q to quit          #\n" <<
    "# Or complete your turn :) #\n" <<
    "############################\n";
}

void printWelcome(){
    cout << 
    "_________________________   \n" <<
    "|Welcome to Tic Tac Toe!|   \n" <<
    "\\(O_O)/  \\(O_O)/  \\(O_O)/\n" <<
    "   |        |        |      \n" <<
    "  / \\      / \\      / \\   \n\n";
}

pair<string, char> getPlayer(int num = 1){
    string pName, symbol;
    cout << "Player "<< num << ", what is your name?\n";
    cin >> pName;
    cout << pName << " what is your symbol?\n";
    cin >> symbol;
    while(symbol.size() != 1 || symbol[0] == ' '){
        cout << "Symbol must be one character long and cannot be a space\n";
        cin >> symbol;
    }
    return {pName, symbol[0]};
}

pair<player, player> welcomeMsg(){
    printWelcome();
    player p1 = getPlayer();  
    player p2 = getPlayer(2); 
    return {p1,p2};
}

bool madeMove(string input, const player &p, char opp){
    if(input.size() == 2){
        int col = input[0] - 49;
        int row = tolower(input[1]) - 97;
        if(row > 2 || row < 0 || col > 2 || col < 0){
            cout << "Incorrect input\n";
            return false;
        }
        if(board[x[row]][y[col]] == ' '){
            board[x[row]][y[col]] = p.second;
            cout << p.first << " just added a " << p.second << "\n\n";
            return true;
        }
        cout << "This spot is already filled!\n";
        return false;
    }
    cout << "Incorrect input\n";
    return false;
}

void takeTurn(const player &p, char opp){
    string input = "`";
    cout << "It's " << p.first << "'s turn!\n";
    printBoard();
    printGameMenu();
    cin >> input;
    while(1){
        if(tolower(input[0]) == 'q'){
            cout << "Thanks for playing\n";
            exit(0);
        }
        else if(tolower(input[0]) == 'd')
            printDirections();
        else if(tolower(input[0]) == 'p')
            printBoard();
        else if(madeMove(input, p, opp)){
            break;
        }
        printGameMenu();
        cin >> input;
    }
}

bool gameover(){
    for(size_t i = 0; i < x.size(); i++){
        // Check the rows
        if(board[x[i]][y[0]] == board[x[i]][y[1]] && 
            board[x[i]][y[1]] == board[x[i]][y[2]] && board[x[i]][y[0]] != ' '){
                return true;
        }
        // Check Cols
        else if(board[x[0]][y[i]] == board[x[1]][y[i]] && board[x[1]][y[i]] == board[x[2]][y[i]] && board[x[0]][y[i]] != ' '){
            return true;
        }
    }
    if(board[x[0]][y[0]] == board[x[1]][y[1]] && board[x[1]][y[1]] == board[x[2]][y[2]] && board[x[0]][y[0]] != ' '){
        return true;
    }
    else if(board[x[0]][y[2]] == board[x[1]][y[1]] && board[x[1]][y[1]] == board[x[2]][y[0]] && board[x[0]][y[2]] != ' '){
        return true;
    }
    return false;
}

void game(){
    clearBoard();
    int counter = 0;
    pair<player,player> player = welcomeMsg();
    string input = "";
    char turn = '1';
    while((input != "quit" || input != "q") && counter != 9){
        if(turn == '1'){
            takeTurn(player.first, player.second.second);
            if(counter >= 4 && gameover()){
                cout << "Good Game! " << player.first.first << " wins!\n";
                break;
            }
            turn = '2';
        }
        else{
            takeTurn(player.second, player.first.second);
            if(counter >= 4 && gameover()){
                cout << "Good Game! " << player.second.first << " wins!\n";
                break;
            }
            turn = '1';
        }
        ++counter;
    }
    if(counter == 9){
        cout << "MEOW - cat's game :)\n";
    }
}

int main(){
    game();
    return 0;
}