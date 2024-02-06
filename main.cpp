#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <iomanip>


// Define colors
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

using namespace std;

// Tic Tac Toe Game

struct ttt{

    vector<vector<char>> mat;
    char currentPlayer;
    char winner;

    /*
        Coordinates for the board:
            |1|2|3|
            |4|5|6|
            |7|8|9|
    */

    ttt(){
        mat = vector<vector<char>>(3, vector<char>(3, ' '));
        winner = ' ';
        currentPlayer = ' ';
    }

    void print(){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                cout << mat[i][j];
                if(j < 2) cout << "|";
            }
            cout << endl;
        }
    }

    void print(int align){
        if(winner == 'X'){
            // Put big X in 3x9 grid
            cout << setw(align) << "_  _" << endl;
            cout << setw(align) << " \\/ " << endl;
            cout << setw(align) << "_/\\_ " << endl;
        }
        else if(winner == 'O'){
            // Put big O in 3x9 grid
            cout << setw(align) << "  __  " << endl;
            cout << setw(align) << " /  \\ " << endl;
            cout << setw(align) << " \\__/ " << endl;
        }
        else{
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    cout << setw(align) << mat[i][j];
                    if(j < 2) cout << setw(align) << "|";
                }
                cout << setw(align) << endl;
            }
        }
    }

    bool isValidMove(int x, int y){
        return x >= 0 && x < 3 && y >= 0 && y < 3 && mat[x][y] == ' ';
    }

    bool isWinner(char player){
        // check if there is a winner and set the winner
        for(int i = 0; i < 3; i++){
            if(mat[i][0] == player && mat[i][1] == player && mat[i][2] == player){
                winner = player;
                return true;
            }
            if(mat[0][i] == player && mat[1][i] == player && mat[2][i] == player){
                winner = player;
                return true;
            }
        }
        return false;
    }

    void play(int coord, char player){
        int x = (coord - 1) / 3;
        int y = (coord - 1) % 3;
        if(isValidMove(x, y)){mat[x][y] = player;}
        else{cout << "Invalid move" << endl;}
    }

    void startGame(char starter){
        this->currentPlayer = starter;
        int x, y;
        while(true){
            print();
            cout << "Player " << currentPlayer << " turn" << endl;
            cout << "Enter Coord: ";
            int coord;
            cin >> coord;
            play(coord, currentPlayer);
            if(isWinner(currentPlayer)){
                print();
                cout << "Player " << currentPlayer << " wins!" << endl;
                break;
            }
            currentPlayer = currentPlayer == 'X' ? 'O' : 'X';
        }
    }

};

struct super{

    vector<vector<ttt>> mat;
    char currentPlayer;

    super(){
        mat = vector<vector<ttt>>(3, vector<ttt>(3));
    }

    /*
        Coordinates for the board:
        
            |1|2|3| |1|2|3| |1|2|3|
            |4|5|6| |4|5|6| |4|5|6|
            |7|8|9| |7|8|9| |7|8|9|
            -----------------------
            |1|2|3| |1|2|3| |1|2|3|
            |4|5|6| |4|5|6| |4|5|6|
            |7|8|9| |7|8|9| |7|8|9|
            -----------------------
            |1|2|3| |1|2|3| |1|2|3|
            |4|5|6| |4|5|6| |4|5|6|
            |7|8|9| |7|8|9| |7|8|9|
    */

   void print(){
        cout << endl << endl;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                for(int k = 0; k < 3; k++){
                    cout << "|";
                    for(int l = 0; l < 3; l++){
                        cout << mat[i][k].mat[j][l];
                        if(l < 2) cout << "|";
                    }
                    cout << "|";
                }
                cout << endl;
            }
            cout << endl;
        }
    }

    void printR(){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                mat[i][j].print(7*i);
                cout << endl;
            }
        }
    }

    void chooseRandomPlayer(){
        currentPlayer = rand() % 2 == 0 ? 'X' : 'O';
    }

    bool isValidMove(int boardX, int boardY, int x, int y){
        return boardX >= 0 && boardX < 3 && boardY >= 0 && boardY < 3 && mat[boardX][boardY].isValidMove(x, y);
    }

    void play(int boardNum, int coord){
        int boardX = (boardNum - 1) / 3;
        int boardY = (boardNum - 1) % 3;
        int x = (coord - 1) / 3;
        int y = (coord - 1) % 3;
        if(isValidMove(boardX, boardY, x, y)){mat[boardX][boardY].play(coord, currentPlayer);}
        else{cout << RED << "Invalid move" << RESET << endl;}
    }

    void printTemplate() {
        int size = 3;
        for (int row = 0; row < size; ++row) {
            for (int block = 0; block < 3; ++block) {
                for (int col = 1; col <= size; ++col) {
                    for (int num = block * 3 + 1; num <= block * 3 + 3; ++num) {
                        cout << "|" << num << "|";
                    }
                    cout << " ";
                }
                cout << endl;
            }

            if (row < size - 1) {
                for (int col = 0; col < 3 * size - 1; ++col) {
                    cout << " ";
                }
                cout << endl;
            }
        }
    }

    void startGame(){

        // Clear the screen
        cout << "\033[2J\033[1;1H";

        chooseRandomPlayer();
        int prevMove = -1;
        
        printTemplate();
        cout << "First player is " << currentPlayer << endl;

        // First player can play wherever they want
        int boardNum;
        do{
            cout << "Enter board number between 1-9: ";
            cin >> boardNum;
        }while(boardNum < 1 || boardNum > 9);
        prevMove = boardNum;
        int coord;
        do{
            cout << "Enter Coordination between 1-9: ";
            cin >> coord;
        }while(coord < 1 || coord > 9);
        play(boardNum, coord);
        print();

        // Game loop
        bool isGameOver = false;
        while(!isGameOver){
            int boardNum = prevMove;
            int coord;
            cout << "Player " << currentPlayer << " turn" << endl;
            do{
                cout << "Your board is " << boardNum << endl;
                cout << "Enter Coordination between 1-9: ";
                cin >> coord;
            }while(coord < 1 || coord > 9);
            cout << "\033[2J\033[1;1H";
            play(boardNum, coord);
            currentPlayer = currentPlayer == 'X' ? 'O' : 'X';
            prevMove = coord;
            print();
        }
            
    }

};

int main() {

    srand(time(0));
    
    super game;
    game.startGame();

    return 0;
}
