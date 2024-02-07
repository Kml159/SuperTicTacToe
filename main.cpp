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
#define BROWN  "\033[33m"      /* Brown */
#define GRAY    "\033[37m"      /* Gray */
#define DARKGRAY  "\033[90m"      /* Dark Gray */
#define WHITE   "\033[37m"      /* White */


using namespace std;

// Tic Tac Toe Game

struct ttt{

    vector<vector<char>> mat;
    char currentPlayer;
    char winner;                // 'X' or 'O' or ' ' or 'D' (Draw)
    uint8_t movesPlayed;

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
        movesPlayed = 0;
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

    bool isValidMove(int x, int y){
        if(x < 0 || x > 2 || y < 0 || y > 2 || mat[x][y] != ' '){
            cout << RED << "Invalid move" << RESET << endl;
            return false;
        }
        return true;
    }

    bool isValidMove(int place){
        int x = (place - 1) / 3;
        int y = (place - 1) % 3;
        return isValidMove(x, y);
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

        if(mat[0][0] == player && mat[1][1] == player && mat[2][2] == player){
            winner = player;
            return true;
        }

        if(mat[0][2] == player && mat[1][1] == player && mat[2][0] == player){
            winner = player;
            return true;
        }

        // check if there is a draw
        if(movesPlayed == 9){winner = 'D';}

        return false;
    }

    void play(int coord, char player){
        int x = (coord - 1) / 3;
        int y = (coord - 1) % 3;
        if(isValidMove(x, y)){
            mat[x][y] = player;
            movesPlayed++;
            if(isWinner(player)){winner = player;}
        }
        else{cout << RED << "Invalid move" << RESET << endl;}
    }

    void startGame(char starter){
        this->currentPlayer = starter;
        int x, y;
        while(true){
            print();
            cout << endl;
            cout << "Player " << currentPlayer << " turn" << endl;
            cout << "Enter Coord: ";
            int coord;
            cin >> coord;
            play(coord, currentPlayer);
            if(isWinner(currentPlayer)){
                print();
                cout << YELLOW << "Player " << currentPlayer << " wins!" << RESET << endl;
                break;
            }
            if(movesPlayed == 9){winner = 'D';}
            currentPlayer = currentPlayer == 'X' ? 'O' : 'X';
        }
    }

};

struct super{

    vector<vector<ttt>> mat;
    char currentPlayer;
    char winner;                // 'X' or 'O' or ' ' or 'D' (Draw)

    enum gameModes{
        HumanVHuman,
        RandomVHuman,
        RandomVRandom,
        HumanVAI
    };

    super(){
        mat = vector<vector<ttt>>(3, vector<ttt>(3));
        winner = ' ';
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

                        if(mat[i][k].winner == ' '){
                            cout << BLUE << mat[i][k].mat[j][l] << RESET;
                        }
                        else{
                            if(j == 1 && l == 1){
                                cout << RED <<mat[i][k].winner << RESET;
                            }
                            else{
                                cout << " ";
                            }
                        }
                        if(l < 2) cout << "|";

                    }
                    cout << "|";
                }
                

                cout << endl;
            }
            cout << endl;
        }
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

        cout << "\n\nSuper Tic-Tac-Toe:\n";
        cout << MAGENTA << "https://youtube.com/shorts/_Na3a1ZrX7c?si=rmrq-cYfYPUGTMTm" << RESET << endl;

    }

    bool isValidMove(int boardNum, int coord){
        int boardX = (boardNum - 1) / 3;
        int boardY = (boardNum - 1) % 3;
        int x = (coord - 1) / 3;
        int y = (coord - 1) % 3;
        return isValidMove(boardX, boardY, x, y);
    }

    bool isValidBoard(int boardNum){
        int boardX = (boardNum - 1) / 3;
        int boardY = (boardNum - 1) % 3;
        if(boardX >= 0 && boardX < 3 && boardY >= 0 && boardY < 3 && mat[boardX][boardY].winner == ' '){
            return true;
        }
        cout << RED << "Invalid board" << RESET << endl;
        return false;
    }

    bool checkGameOver(){
        uint8_t gamesDone = 0;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(mat[i][j].winner != ' '){gamesDone++;}
            }
        }
        if(gamesDone == 9){
            winner = 'D';
            cout << YELLOW << "Draw!" << RESET << endl;
            return true;
        }

        if(isWinner(currentPlayer)){
            cout << YELLOW << "Player " << currentPlayer << " wins!" << RESET << endl;
            return true;
        }

        else if(winner == 'D'){
            cout << YELLOW << "Draw!" << RESET << endl;
            return true;
        }
        return false;
    }

    int getRandomBoardNum(){
        int boardNum;
        do{
            cout << "You can play anywhere!" << endl;
            cout << "Enter board number between 1-9: ";
            // cin >> boardNum;
            boardNum = rand() % 9 + 1;
        }while(boardNum < 1 || boardNum > 9 || !isValidBoard(boardNum));
        return boardNum;
    }

    int getRandomLocation(int boardNum){
        int coord;
        do{
            cout << "Your board is " << boardNum << endl;
            cout << "Enter Coordination between 1-9: ";
            // cin >> coord;
            coord = rand() % 9 + 1;
        }while(coord < 1 || coord > 9 || !isValidMove(boardNum, coord));
        return coord;
    }

    int getBoardInput(){
        int boardNum;
        do{
            cout << "You can play anywhere!" << endl;
            cout << "Enter board number between 1-9: ";
            cin >> boardNum;
            // boardNum = rand() % 9 + 1;
        }while(boardNum < 1 || boardNum > 9 || !isValidBoard(boardNum));
        return boardNum;
    }

    int getLocationInput(int boardNum){
        int coord;
        do{
            cout << "Your board is " << boardNum << endl;
            cout << "Enter Coordination between 1-9: ";
            cin >> coord;
            // coord = rand() % 9 + 1;
        }while(coord < 1 || coord > 9 || !isValidMove(boardNum, coord));
        return coord;
    }

    pair<int, int> getInput(int prevMove, bool &isFirst){
        int boardNum = prevMove;
        int coord;

        // If board is finished then player can play anywhere or if it is the first move
        if(mat[(boardNum-1) / 3][(boardNum-1) % 3].winner != ' ' || isFirst == true){
            boardNum = getBoardInput();
            isFirst = false;
        }

        coord = getLocationInput(boardNum);
        return make_pair(boardNum, coord);
    }

    pair<int, int> getRandomInput(int prevMove, bool &isFirst){
        int boardNum = prevMove;
        int coord;

        // If board is finished then player can play anywhere or if it is the first move
        if(mat[(boardNum-1) / 3][(boardNum-1) % 3].winner != ' ' || isFirst == true){
            boardNum = getRandomBoardNum();
            isFirst = false;
        }

        coord = getRandomLocation(boardNum);
        return make_pair(boardNum, coord);
    }

    void startGame_RandomGame(){

        currentPlayer = rand() % 2 == 0 ? 'X' : 'O';    // Randomly select the first player
        int prevMove = -1;
        
        printTemplate();
        cout << "First player is " << currentPlayer << endl;

        bool isGameOver = false;
        bool isFirst = true;

        // Game loop
        while(!isGameOver){
            int boardNum = prevMove;
            int coord;

            cout << "Player " << currentPlayer << " turn" << endl;
            
            // If board is finished then player can play anywhere or if it is the first move
            if(mat[(boardNum-1) / 3][(boardNum-1) % 3].winner != ' ' || isFirst == true){
                boardNum = getRandomBoardNum();
                isFirst = false;
            }

            coord = getRandomLocation(boardNum);

            cout << "\033[2J\033[1;1H";

            play(boardNum, coord);
            print();

            isGameOver = checkGameOver();
            currentPlayer = currentPlayer == 'X' ? 'O' : 'X';
            prevMove = coord;
        }
    }

    void startGame_2player(){

        currentPlayer = rand() % 2 == 0 ? 'X' : 'O';    // Randomly select the first player
        int prevMove = -1;
        
        printTemplate();
        cout << "First player is " << currentPlayer << endl;

        bool isGameOver = false;
        bool isFirst = true;

        // Game loop
        while(!isGameOver){

            auto input = getInput(prevMove, isFirst);
            int boardNum = input.first;
            int coord = input.second;

            cout << "\033[2J\033[1;1H";
            cout << YELLOW <<"Player " << currentPlayer << " turn" << RESET <<  endl;

            play(boardNum, coord);
            print();

            isGameOver = checkGameOver();
            currentPlayer = currentPlayer == 'X' ? 'O' : 'X';
            prevMove = coord;
        }
    }

    void startGame_1player(){ // computer is random

        cout << "\n\n\n";

        char player = 'X';
        char computer = 'O';
        int prevMove = -1;

        currentPlayer = rand() % 2 == 0 ? player : computer;    // Randomly select the first player

        printTemplate();
        cout << "Computer is " << RED << computer << RESET << endl;
        cout << "You are " << GREEN << player << RESET << endl;
        cout << "First player is " << currentPlayer << endl;

        bool isGameOver = false;
        bool isFirst = true;

        {
            cout << "Enter any key to start...\n";
            char any;
            cin >> any;
        }

        // Game loop
        while(!isGameOver){
            int boardNum = prevMove;
            int coord;

            cout << "Player " << currentPlayer << " turn" << endl;
            
            // If board is finished then player can play anywhere or if it is the first move
            if(currentPlayer == player){
                if(mat[(boardNum-1) / 3][(boardNum-1) % 3].winner != ' ' || isFirst == true){
                    boardNum = getBoardInput();
                    isFirst = false;
                }

                coord = getLocationInput(boardNum);
                cout << "\033[2J\033[1;1H";
            }
            else{
                if(mat[(boardNum-1) / 3][(boardNum-1) % 3].winner != ' ' || isFirst == true){
                    boardNum = getRandomBoardNum();
                    isFirst = false;
                }
                coord = getRandomLocation(boardNum);
                cout << "\033[2J\033[1;1H";
                cout << YELLOW << "Computer randomly played " << boardNum << "x" << coord << RESET << endl;
            }

            play(boardNum, coord);
            print();

            isGameOver = checkGameOver();
            currentPlayer = currentPlayer == 'X' ? 'O' : 'X';
            prevMove = coord;
        }
    }


    void startGame_AI(){

        cout << "\n\n\n";
        char player = 'X';
        char computer = 'O';
        int prevMove = -1;

        currentPlayer = rand() % 2 == 0 ? player : computer;    // Randomly select the first player

        printTemplate();
        cout << "Computer is " << RED << computer << RESET << endl;
        cout << "You are " << GREEN << player << RESET << endl;

        bool isGameOver = false;
        bool isFirst = true;

        {
            cout << "Enter any key to start...\n";
            char any;
            cin >> any;
        }

        // Game loop
        while(!isGameOver){
            
            cout << "Player " << currentPlayer << " turn" << endl;

            pair<int, int> input;
            if(currentPlayer == player){
                input = getInput(prevMove, isFirst);
            }
            else{
                input = getRandomInput(prevMove, isFirst);
            }

            int boardNum = input.first;
            int coord = input.second;

            cout << "\033[2J\033[1;1H";
            cout << YELLOW <<"Player " << currentPlayer << " turn" << RESET <<  endl;

            play(boardNum, coord);
            print();

            isGameOver = checkGameOver();
            currentPlayer = currentPlayer == 'X' ? 'O' : 'X';
            prevMove = coord;
        }
    }

    void startGame(gameModes gameMode){

        cout << "\n\n\n";
        char playerA = 'X';
        char playerB = 'O';
        int prevMove = -1;

        currentPlayer = rand() % 2 == 0 ? playerA : playerB;    // Randomly select the first player

        printTemplate();

        bool isGameOver = false;
        bool isFirst = true;

        {
            cout << "Enter any key to start...\n";
            char any;
            cin >> any;
        }

        // Game loop
        while(!isGameOver){
            
            cout << YELLOW << "Player " << currentPlayer << " turn" << RESET << endl;

            pair<int, int> input;

            switch (gameMode){

                case HumanVHuman:
                    input = getInput(prevMove, isFirst);
                    break;
                
                case RandomVHuman:
                    if(currentPlayer == playerA){input = getInput(prevMove, isFirst);}
                    else{input = getRandomInput(prevMove, isFirst);}
                    break;

                case RandomVRandom:
                    input = getRandomInput(prevMove, isFirst);
                    break;

                case HumanVAI:
                    if(currentPlayer == playerA){input = getInput(prevMove, isFirst);}
                    else{input = getRandomInput(prevMove, isFirst);}
                    break;
                
                default:
                    break;
            }

            int boardNum = input.first;
            int coord = input.second;

            cout << "\033[2J\033[1;1H";
            cout << YELLOW << "Player " << currentPlayer << " played " << boardNum << "x" << coord << RESET <<  endl;
            play(boardNum, coord);
            print();

            isGameOver = checkGameOver();
            currentPlayer = currentPlayer == 'X' ? 'O' : 'X';
            prevMove = coord;
        }
    }



    void startGame(){

        cout << "1. Human vs Human" << endl;
        cout << "2. Random vs Human" << endl;
        cout << "3. Random vs Random" << endl;
        cout << "4. Human vs AI" << endl;
        cout << "Select player: ";
        gameModes gameMode;
        int input;
        cin >> input;
        gameMode = (gameModes)(--input);

        startGame(gameMode);
    }

    bool isWinner(char player){
        // check if there is a winner and set the winner
        for(int i = 0; i < 3; i++){
            if(mat[i][0].winner == player && mat[i][1].winner == player && mat[i][2].winner == player){
                return true;
            }
            if(mat[0][i].winner == player && mat[1][i].winner == player && mat[2][i].winner == player){
                return true;
            }
        }

        if(mat[0][0].winner == player && mat[1][1].winner == player && mat[2][2].winner == player){
            return true;
        }

        if(mat[0][2].winner == player && mat[1][1].winner == player && mat[2][0].winner == player){
            return true;
        }

        // if(gamesDone == 9){winner = 'D';}

        return false;
    }
};

int main() {

    srand(time(0));
    
    super game;
    game.startGame();


    return 0;
}
