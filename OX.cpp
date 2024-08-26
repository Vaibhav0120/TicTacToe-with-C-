#include<iostream>
#include<cstdlib>
#include <random>
#include <time.h>
using namespace std;

//--------------------- GLOBAL VARIABLES ---------------------
void play();
int board[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
// 11 = X    15 = O
int userInput;
int winner=0;
int playBot = 0;  // 0 = 2 player     1 = 1 player
int random_number;
int warning_repeated=11;

//---------------------- MANAGE GRID -------------------------
void showGrid() {
    int ptrBoard = 0;
    
    // Printing Board values according to array with X and Y
    for(int i = 0; i<3;i++){
        for(int j=0;j<3;j++) {
            if(board[ptrBoard] == 11) {
                cout<<"| X |";
            }
            else if(board[ptrBoard] == 15) {
                cout<<"| O |";
            }
            else {
                cout<<"| "<<board[ptrBoard]<<" |";
            }
            ptrBoard++;
        }
        cout<<endl;
    }
}

void resetGrid() {
    // reseting board array
    for(int i = 0; i < 9; i++) {
        board[i] = i;
    }
    winner=0;
    //starting game again
    cout<<"\n";
    play();
}

//-----------------------INPUT [FOR HUMANS AND BOT] ------------------------
int input() {
    cout<<"Enter:";
    cin>>userInput;
     
     // checking invalid or previously used inputs
    while(userInput > 9 || userInput < 0 || board[userInput] == 11 || board[userInput] == 15){
        cout<<"INVALID INPUT"<<endl;
        cout<<"Enter:";
        cin>>userInput;
    } 

        return userInput;
}

void smartMove() {
    if((board[4] == board[8] || board[1] == board[2] || board[3] == board[6]) && warning_repeated != 0) {
        random_number = 0;
    }
    else if((board[0] == board[2] || board[4] == board[7]) && warning_repeated != 1) {
        random_number = 1;
    }
    else if((board[0] == board[1] || board[4] == board[6] || board[5] == board[8]) && warning_repeated != 2) {
        random_number = 2;
    }
    else if((board[0] == board[6] || board[4] == board[5]) && warning_repeated != 3) {
        random_number = 3;
    }
    else if((board[0] == board[8] || board[1] == board[7] || board[2] == board[6] || board[5] == board[3]) && warning_repeated != 4) {
        random_number = 4;
    }
    else if((board[2] == board[8] || board[3] == board[4]) && warning_repeated != 5) {
        random_number = 5;
    }
    else if((board[0] == board[3] || board[2] == board[4] || board[7] == board[8]) && warning_repeated != 6) {
        random_number = 6;
    }
    else if((board[1] == board[4] || board[6] == board[8]) && warning_repeated != 7) {
        random_number = 7;
    }
    else if((board[2] == board[5] || board[0] == board[4] || board[6] == board[7]) && warning_repeated != 8) {
        random_number = 8;
    }
}

int inputBot() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator with the current time
    
    while (true) {
        random_number = rand() % 9;  // Generate a random number between 0 and 8

        // Check if the random move is valid
        if (board[random_number] != 11 && board[random_number] != 15) {
            break; // Exit loop if the move is valid
        }
    }

    // Check if smartMove is possible
    smartMove();
    
    // Check if smartMove already present else recheck smartMove
    if(board[random_number] == 11 || board[random_number] == 15) {
        warning_repeated = random_number;
        smartMove();
    }
    
    // If no smart move found and random number is already occupied then re-get random no
    while (board[random_number] == 11 || board[random_number] == 15) {
        random_number = rand() % 9;
    }

    cout<<"Bot: "<<random_number<<endl;
    warning_repeated=11;  // Reseting warning_repeat
    return random_number;
}

//----------------------------- SHOW OR CHECK WINNER -------------------------
void showWinner() {
    if(winner == 11) {
        if(playBot == 1) {
            cout<<endl<<"WINNER: Player";
        }
        else {
            cout<<endl<<"WINNER: X";
        }
    }
    else if(winner == 15) {
        if(playBot == 1) {
            cout<<endl<<"WINNER: BOT";
        }
        else {
            cout<<endl<<"WINNER: O";
        }
    }
    else{
        cout<<endl<<"----- D R A W -----";
    }
    // asking to play again
    cout<<endl<<"\nPlay Again?\nPress 1. 1-Player     [Bot]\nPress 2. 2-Player\nEnter:";
    int askUserPlay;
    cin>>askUserPlay;
    if(askUserPlay == 1) {
        playBot = 1;
        resetGrid();
    }
    else if(askUserPlay == 2) {
        playBot = 0;
        resetGrid();
    }
    else {
        cout<<"Quiting...";
        exit(0);
    }
}

void checkWinner() {
    //horizontal
    if(board[0] == board[1] && board [1] == board[2]) {
        winner = board[0];
    }
    else if(board[3] == board[4] && board[4] == board[5]) {
        winner = board[3];
    }
    else if(board[6] == board[7] && board[7] == board[8]) {
        winner = board[6];
    }
    //vertical
    else if(board[0] == board[3] && board[3] == board[6]) {
        winner = board[0];
    }
    else if(board[1] == board[4] && board[4] == board[7]) {
        winner = board[1];
    }
    else if(board[2] == board[5] && board[5] == board[8]) {
        winner = board[2];
    }
    //Angled
    else if(board[0] == board[4] && board[4] == board[8]) {
        winner = board[0];
    }else if(board[2] == board[4] && board[4] == board[6]) {
        winner = board[2];
    }

    if(winner != 0) {
    showWinner();
    }
}

//----------------------- PLAYING GAME TURN BY TURN -------------------------------

void play() {

    for(int turn = 0; turn < 9; turn++) {
        cout<<"------------"<<turn+1<<"th Turn------------"<<endl;;

        // check for player Human or Bot
        if(playBot == 0) {
            showGrid();
            userInput = input();
        }
        else if(playBot == 1) {
            if(turn%2 == 0) {
                showGrid();
                userInput = input();
            }
            else {
                userInput = inputBot();
            }
        }
        else {
            cout<<"INVALID INPUT\nQuitting...";
            exit(0);
        }

        // pasting input on board
        if(turn%2==0) {
            board[userInput] = 11;
        }
        else {
            board[userInput] = 15;
        }
        checkWinner();
    }
    //for draw
    showWinner();
}



int main(){
    cout<<"Welcome to OX!!!"<<endl<<"1. 1-Players    [Bot]"<<endl<<"2. 2-Player"<<endl<<"Enter:";

    int ans;
    cin>>ans;

    if(ans == 1) {
        playBot = 1;
        play();
    }
    else if(ans == 2) {
        play();
    }
    else {
        cout<<"Quiting Game...";
    }

    return 0;
}