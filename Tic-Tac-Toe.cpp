#include <iostream>
#include<cstdlib>
#include<ctime>
#include<algorithm>

using namespace std;

char player1 = 'X';
char player2 = 'O';

void drawBoard(char board[3][3]); 
int checkWin(char board[3][3]); 
void playerMove(char board[3][3], char playerSymbol);
int minimax(char board[3][3], int depth, bool isMaximizing, bool firstTime);
void computerMove(char board[3][3], char computerSymbol, int difficulty);
void chooseMode(char board[3][3], int mode, int difficulty);


int main(){
    
    srand(time(0));
    char replay;
    do{
        int mode;
        int difficulty;
        char board[3][3] = {
        {'1','2','3'},
        {'4','5','6'},
        {'7','8','9'}};


        cout << endl << "***Welcome to Tic Tac Toe Game!***" << endl << endl;
        cout << "Select Game Mode:" << endl;
        cout << "[1] Player vs Player (1v1)" << endl;
        cout << "[2] Player vs Computer" << endl;
        cout << ">> Enter your choice: ";
        cin >> mode;

        while(mode != 1 && mode != 2){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "choose the mode correctly: ";  
            cin >> mode;
        }
        if (mode == 2){
            cout << endl << "Select Game difficulty:" << endl;
            cout << "[1] Easy" << endl;
            cout << "[2] Hard" << endl;
            cout << ">> Enter your choice: ";
            cin >> difficulty;
            while(difficulty != 1 && difficulty != 2){
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Choose correctly: ";  
                cin >> difficulty;
            }
        }

     
        chooseMode(board, mode, difficulty);

        while (true){
            cout << "Do you want to play again? (y/n): ";
            cin >> replay;
            if (replay == 'y' || replay == 'Y' || replay == 'n' || replay == 'N'){
                if (replay == 'n'||replay == 'N') cout<<"Thank you for playing.";
                break; 
            }

            cout << "Please type 'y' to play or 'n' to exit." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    } while (replay == 'y' || replay == 'Y');   
}

void drawBoard(char board[3][3]){
    cout <<endl;
    cout << "     |     |     "<<endl;
    cout << "  " << board[0][0]  << "  |  " << board[0][1] << "  |  " << board[0][2] << endl;
    cout << "-----|-----|-----" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << board[1][0]  << "  |  " << board[1][1] << "  |  " << board[1][2] << endl;
    cout << "-----|-----|-----" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << board[2][0]  << "  |  " << board[2][1] << "  |  " << board[2][2] << endl;
    cout << "     |     |     "<< endl << endl;
}

int checkWin(char board[3][3]){

    //Rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return board[i][0] == 'X' ? 2 : -2;;
        }
    }

    //Columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return board[0][i] == 'X' ? 2 : -2;;
        }
    }

    //Diameter1
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return board[0][0] == 'X' ? 2 : -2;
    }
    //Diameter2
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return board[0][2] == 'X' ? 2 : -2;
    }

    //Tie
    bool tie = true;
    for(int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if(board[i][j] != 'X' && board[i][j] != 'O'){
                tie = false;
            }
        }
    }
    if (tie) return 0;
    else return 1;
}

void playerMove(char board[3][3], char playerSymbol){
    int place;
    int row, col;
    cout << "Enter the place to play: ";
    cin >> place;
    row = (place - 1) / 3;
    col = (place - 1) % 3;
    while (cin.fail() || place < 1 || place > 9 || (board[row][col] == 'X' || board[row][col] == 'O')){
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Enter place correctly: ";
        cin >> place;
        row = (place - 1) / 3;
        col = (place - 1) % 3;
    }
    board[row][col] = playerSymbol;
}

int minimax(char board[3][3], int depth, bool isMaximizing, bool firstTime = true){
    int result = checkWin(board);
    if (depth == 0 || result != 1)
        return result;
    if(isMaximizing){
        int finalscore = -100;
        char temp;
        for(int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if(board[i][j] != 'X' && board[i][j] != 'O'){
                    temp = board[i][j];
                    board[i][j] = 'X';
                    int score = minimax(board, depth - 1, false, false);
                    board[i][j] = temp;
                    finalscore = max(score, finalscore);
                }
            }
        }
        return finalscore;
    } else{
        int finalscore = 100;
        char temp;
        int bestI, bestJ;
        for(int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if(board[i][j] != 'X' && board[i][j] != 'O'){
                    temp = board[i][j];
                    board[i][j] = 'O';
                    int score = minimax(board, depth - 1, true, false);
                    board[i][j] = temp;
                    if(score < finalscore){
                        finalscore = score;
                        bestI = i;
                        bestJ = j;
                    }
                }
            }
        }
        if (firstTime){
            board[bestI][bestJ] = 'O';
        }
        return finalscore;
    }
}

void computerMove(char board[3][3], char computerSymbol, int difficulty){
    char temp;
    if(difficulty == 1){
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if(board[i][j] != 'X' && board[i][j] != 'O'){
                    temp = board[i][j];
                    board[i][j] = 'O';
                    if (checkWin(board) == -2){
                        board[i][j] = 'O';
                        return;
                    }
                    board[i][j] = temp;
                }
            }
        }

        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if(board[i][j] != 'X' && board[i][j] != 'O'){
                    temp = board[i][j];
                    board[i][j] = 'X';
                    if (checkWin(board) == 2){
                        board[i][j] = 'O';
                        return;
                    }
                    board[i][j] = temp;
                }
            }
        }        
        int place = rand() % 9 + 1;
        int row = (place - 1) / 3;
        int col = (place - 1) % 3;
        while ((board[row][col] == 'X' || board[row][col] == 'O')){
            place = rand() % 9 + 1;
            row = (place - 1) / 3;
            col = (place - 1) % 3;
        }
    
        board[row][col] = 'O';
    } else{
        minimax(board, 100, false, true);
    }

}

void chooseMode(char board[3][3], int mode, int difficulty){
    drawBoard(board);
    for (int i = 0; i < 9; i++){
        if (i % 2 == 0){
             
            playerMove(board, player1);
        }
        else{
            if (mode == 1){
                 
                playerMove(board, player2);
            }
            else
                computerMove(board, player2, difficulty);
        }    
        drawBoard(board);
        if (i >= 4){
            int winResult = checkWin(board);
            if (winResult == 2){
                if (mode == 2){
                    cout << "\n*** You Won! ***\n"; 
                }
                else{
                    cout << "\n*** Player 1 Won! ***\n";
                }
                return;          
            }
            else if(winResult == -2){
                if (mode == 2){
                    cout << "\n*** Computer won! ***\n";
                }
                else{
                    cout << "\n*** Player 2 Won! ***\n";
                } 
                return;
            }
            else if (winResult == 0){
                cout << "Draw!" << endl;
                return;
            }
        }
    }
}