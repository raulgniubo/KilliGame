/*

    Raul Gutierrez Niubo

    Date: 4 / 30/ 2018

    I hereby certify that this code is my work and my work alone and understand the syllabus regarding plagiarized code.

    Extra credit: Menu when game begins
                  Being able to rearrange the board with all characters with different coordinates
                  Being able to set the difficulty of the game changing parameters like human hearts
                  Being able to always see the last action, human hearts left, human actions, all keys,
                    and instructions while playing

    Hope you enjoy it!
*/

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <cmath>
#include <iomanip>

const int SIZE = 30;
struct Sim;
struct Target;
struct ISI;
struct VSI;
struct GameParameters;

void createTheBoard(char [][SIZE], Sim &,
                    std::vector<Target> , std::vector<ISI>
        , std::vector<VSI>, GameParameters);
void printMenu (GameParameters &);
void reArrangeBoard(char [][SIZE], Sim &,
                    std::vector<Target> &, std::vector<ISI>
                    &, std::vector<VSI>vicSI,
                    GameParameters &);
bool movementValidation(char [][SIZE], int , int);
char characterToPrint(char [][SIZE], int , int , Sim &,
                      std::vector<Target> , std::vector<ISI>
                      IncredSI, std::vector<VSI>);
bool moveCoordinates(char [][SIZE], int &, int &, char);
bool percentValidation (int x);
char moveToHuman(int , int , int , int );
void ISITurn(char [][SIZE], Sim &, std::vector<Target> &,
             std::vector<ISI> &, std::vector<VSI> &, GameParameters &);
void VSITurn(char [][SIZE], Sim &, std::vector<Target> &,
             std::vector<ISI> &, std::vector<VSI> &, GameParameters &);
void humanTurn(char [][SIZE], Sim &, std::vector<Target> &,
               std::vector<ISI> &, std::vector<VSI> &, GameParameters &);
bool closeTarget(int , int, int, std::vector<Target> &, GameParameters &);
bool ISICloseHuman(ISI &, Sim &, GameParameters &);
bool VSICloseHuman(VSI &, Sim &, GameParameters &);
void netFilter(Sim &, std::vector<ISI> &, std::vector<VSI> &);
void snopesDestroyer(Sim &, std::vector<ISI> &, std::vector<VSI> &,
                     GameParameters &);
bool gameOver(Sim *, std::vector<Target> ,
              std::vector<ISI> , std::vector<VSI>);

struct Sim {
    char image;
    int x;
    int y;
    int numActions = 3;
    double hearts;
    int effectivenessNetFilter1Square = 66;
    int effectivenessNetFilter2Square = 33;
    int effectivenessSnopesDestroyerISI = 75;
    int effectivenessSnopesDestroyerVSIFullHealth = 63;
    int effectivenessSnopesDestroyerVSIHalfHealth = 77;
    int scopeSnopesDestroyer;

    char getImage() {
        return image;
    }
    int getX() {
        return x;
    }
    int getY() {
        return y;
    }
    void setX(int a) {
        x = a;
    }
    void setY(int a) {
        y = a;
    }

    void moveTheSim(char inBoard [][SIZE], char moveDirection) {
        moveCoordinates(inBoard, x, y, moveDirection);
    }
};

struct Target {
    char image;
    int x;
    int y;

    int getX() {
        return x;
    }
    int getY() {
        return y;
    }
};

struct ISI {  // Incredibly Stupid Ideas (ISI)
    char image;
    int x;
    int y;
    int numActions = 1;
    int effectivenessInAttack = 75;
    bool stuck = false;
    bool stunned = false;
    bool fullHealth = true;

    int getX() {
        return x;
    }
    int getY() {
        return y;
    }
    void setX(int a) {
        x = a;
    }
    void setY(int a) {
        y = a;
    }
    void moveTheISI(char inBoard [][SIZE], char moveDirection) {
        moveCoordinates(inBoard, x, y, moveDirection);
    }
};

struct VSI {  // Viciously Stupid Ideas (VCI)
    char image;
    int x;
    int y;
    int numActions = 2;
    int effectivenessToTarget = 90;
    int effectivenessToHuman1Square = 90;
    int effectivenessToHuman2Squares = 65;
    bool stuck = false;
    bool stunned = false;
    bool fullHealth = true;

    int getX() {
        return x;
    }
    int getY() {
        return y;
    }
    void moveTheVSI(char inBoard [][SIZE], char moveDirection) {
        moveCoordinates(inBoard, x, y, moveDirection);
    }
};

struct GameParameters {
    std::string levelOfDifficulty;
    std::string lastAction;
    int startingHumanHearts;
    int startingScopeOfSnopesDestroyer;
    bool gameOver = false;
    std::string winner;
};

void charactersAppear(char[][SIZE], Sim &, std::vector<Target>,
                      std::vector<ISI>, std::vector<VSI>,
                      GameParameters gameParam);
void moveTheISI(char[][SIZE], Sim *, ISI&, GameParameters &);
void moveTheVSI(char[][SIZE], Sim *, VSI&, GameParameters &);

int main() {

    char theBoard[SIZE][SIZE];
    srand(std::time(0));

    GameParameters gameParam;
    printMenu(gameParam);

    Sim human;
    human.image = 229;
    human.x = 15;
    human.y = 15;
    human.hearts = gameParam.startingHumanHearts;
    human.scopeSnopesDestroyer = gameParam.startingScopeOfSnopesDestroyer;

    std::vector<Target> targets;

    Target target01;
    target01.image = 254;
    target01.x = 6;
    target01.y = 8;
    targets.push_back(target01);

    Target target02;
    target02.image = 254;
    target02.x = 20;
    target02.y = 22;
    targets.push_back(target02);

    Target target03;
    target03.image = 254;
    target03.x = 3;
    target03.y = 15;
    targets.push_back(target03);

    Target target04;
    target04.image = 254;
    target04.x = 20;
    target04.y = 8;
    targets.push_back(target04);

    Target target05;
    target05.image = 254;
    target05.x = 6;
    target05.y = 22;
    targets.push_back(target05);

    std::vector<ISI> incredSI;
    ISI incredStupIdeas01;
    incredStupIdeas01.image = 157;
    incredStupIdeas01.x = 26;
    incredStupIdeas01.y = 22;
    incredSI.push_back(incredStupIdeas01);

    std::vector<VSI> vicSI;
    VSI vicStupIdeas01;
    vicStupIdeas01.image = 232;
    vicStupIdeas01.x = 26;
    vicStupIdeas01.y = 6;
    vicSI.push_back(vicStupIdeas01);

    createTheBoard(theBoard, human, targets, incredSI, vicSI, gameParam);
    charactersAppear(theBoard, human, targets, incredSI, vicSI, gameParam);

    char isK = ' ';
    std::cin >> isK;
    std::cin.ignore(100, '\n');

    while (isK == 'k') {
        reArrangeBoard(theBoard, human, targets, incredSI, vicSI, gameParam);
        std::cin.get(isK);
        std::cin.ignore(100, '\n');
    }
    gameParam.lastAction = "Game Running";
    createTheBoard(theBoard, human, targets, incredSI, vicSI, gameParam);

    do {
        humanTurn(theBoard, human, targets, incredSI, vicSI, gameParam);
        ISITurn(theBoard, human, targets, incredSI, vicSI, gameParam);
        VSITurn(theBoard, human, targets, incredSI, vicSI, gameParam);
    } while (!gameOver(&human, targets, incredSI, vicSI));

    std::cin.get();
    return 0;
}

void createTheBoard(char inBoard[][SIZE], Sim &human,
                    std::vector<Target> targets, std::vector<ISI>
                    incredSI, std::vector<VSI>vicSI,
                    GameParameters gameParam) {

    char characterPrint = ' ';

    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            characterPrint = characterToPrint(inBoard, r, c, human, targets,
                                              incredSI, vicSI);
            inBoard[r][c] = characterPrint;
            if (c == 0 || c == SIZE - 1) {
                inBoard[r][c] = 186;
            }
            if (r == 0 || r == SIZE - 1) {
                inBoard[r][c] = 205;
            }
        }
    }

    inBoard[0][0] = 201;
    inBoard[0][SIZE - 1] = 187;
    inBoard[SIZE - 1][0] = 200;
    inBoard[SIZE - 1][SIZE - 1] = 188;

    system("cls");
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            std::cout << inBoard[r][c];
        }
        switch (r){
            case 1: std::cout << "\t\t\t\t\tStop the Madness";
                break;
            case 3: std::cout << "\t\tLevel of Difficulty: ";
                break;
            case 4: std::cout << "\t\t" << gameParam.levelOfDifficulty;
                break;
            case 6: std::cout << "\t\tHuman Hearts: " << human.hearts;
                break;
            case 7: std::cout << "\t\tHuman Total Actions: "
                              << human.numActions;
                break;
            case 9:
                if (gameParam.lastAction == "Init") {
                    std::cout << "\t-----------> !!!PRESS (k) TO RE-ARRANGE "
                                 "THE BOARD OR OTHER TO BEGIN!!! <-----------";
                } else {
                    std::cout << "\t\tLast Action: " << gameParam.lastAction;
                }
                break;
            case 10:
                if (gameParam.lastAction == "Init") {
                    std::cout << "\t-----------------------"
                                 "-----------------------------"
                                 "-------------------------------";
                }
                if (gameParam.gameOver) {
                    std:: cout << "\t\tGAME IS OVER, WINNER: "
                               << gameParam.winner;
                }
                break;
            case 12: std::cout << "\t\t" << std::setw(20) << std::left
                               << "Characters:" << "Action Keys:";
                break;
            case 13: std::cout << "\t\t" << std::setw(10) << std::left
                               << "Human: " << std::setw(10)
                               << static_cast<char>(229) << std::setw(13)
                               << "w: up" << std::setw(19) << "q: up & left"
                               << "r: Net Filter";
                break;
            case 14: std::cout << "\t\t" << std::setw(10) << std::left
                               << "Targets: " << std::setw(10)
                               << static_cast<char>(254) << std::setw(13)
                               << "s: down" << std::setw(19) << "e: up & right"
                               << "f: Snopes Destroyer";
                break;
            case 15: std::cout << "\t\t" << std::setw(10) << std::left
                               << "ISI: " << std::setw(10)
                               << static_cast<char>(157) << std::setw(13)
                               << "a: left" << "z: down & left";
                break;
            case 16: std::cout << "\t\t" << std::setw(10) << std::left
                               << "VSI: " << std::setw(10)
                               << static_cast<char>(232) << std::setw(13)
                               << "d: right" << "c: down & right";
                break;
            case 18: std::cout << "\t\t\t\t\tIntructions: ";
                break;
            case 19: std::cout << "\t\tDefend the Targets at all cost!";
                break;
            case 20: std::cout << "\t\tCondition to win: Kill all the Stupid "
                                  "Ideas before they destroy ";
                break;
            case 21: std::cout << "\t\tthe Targets or kill the Human";
                break;
            case 23: std::cout << "\t\tNet Filter: Stuns the ISI or VSI if "
                                  "successful";
                break;
            case 24: std::cout << "\t\tSnopes Destroyer: "
                                  "Removes half of energy"
                                  " of ISI or VSI if successful";
                break;
        }
        std::cout << "\n";
    }
}

void printMenu (GameParameters &gameParam) {
    gameParam.lastAction = "Init";
    int levelOfDifficulty = 2;
    const std::string easy = "Easy (Starting Human Hearts = 8, Scope of"
                             " Snopes Destroyer = 3)";
    const std::string normal = "Normal (Starting Human Hearts = 5, Scope "
                               "of Snopes Destroyer = 2)";
    const std::string hard = "Hard (Starting Human Hearts = 4, Scope of "
                             "Snopes Destroyer = 1)";

    std::cout << "Stop the Madness:\n\n";
    std::cout << "Stupid Ideas have been proliferating "
                 "across the interwebs with the speed of a Miami "
                 "driver in the rain!\nYour mission!!, should you decide "
                 "to accept it, is stop the Stupid Ideas from multiplying.\n\n";
    std::cout << "Select the level of difficulty and press enter to start "
                 "the game:\n";
    std::cout << "1. " << easy
              << "\n2. " << normal
              << "\n3. " << hard << " \n";

    std::cout << "\nDifficulty: ";
    std::cin >> levelOfDifficulty;
    std::cin.ignore(100, '\n');

    while (std::cin.fail()) {
        std::cout << "Please, choose a valid number\n";
        std::cout << "Difficulty: ";
        std::cin.clear();
        std::cin.ignore(100, '\n');
        std::cin >> levelOfDifficulty;
    }

    switch (levelOfDifficulty) {
        case 1:
            gameParam.levelOfDifficulty = easy;
            gameParam.startingHumanHearts = 8;
            gameParam.startingScopeOfSnopesDestroyer = 3;
            break;
        case 2:
            gameParam.levelOfDifficulty = normal;
            gameParam.startingHumanHearts = 5;
            gameParam.startingScopeOfSnopesDestroyer = 2;
            break;
        case 3:
            gameParam.levelOfDifficulty = hard;
            gameParam.startingHumanHearts = 4;
            gameParam.startingScopeOfSnopesDestroyer = 1;
            break;
    }
}

void reArrangeBoard(char inBoard[][SIZE], Sim &human,
                    std::vector<Target> &targets, std::vector<ISI>
                    &incredSI, std::vector<VSI>vicSI,
                    GameParameters &gameParam) {
    int randX = 0;
    int randY= 0;
    char pointBoard = 249;
    do {
        randX = rand() % 28 + 1;
        randY = rand() % 28 + 1;
    } while (characterToPrint(inBoard, randX, randY, human,
                              targets, incredSI, vicSI) != pointBoard);
    human.x = randX;
    human.y = randY;
    for (int i = 0; i < targets.size(); i++) {
        do {
            randX = rand() % 28 + 1;
            randY = rand() % 28 + 1;
        } while (characterToPrint(inBoard, randX, randY, human,
                                  targets, incredSI, vicSI) != pointBoard);
        targets[i].x = randX;
        targets[i].y = randY;
    }

    for (int i = 0; i < incredSI.size(); i++) {
        do {
            randX = rand() % 28 + 1;
            randY = rand() % 28 + 1;
        } while (characterToPrint(inBoard, randX, randY, human, targets,
                                  incredSI, vicSI) != pointBoard);
        incredSI[i].x = randX;
        incredSI[i].y = randY;
    }

    for (int i = 0; i < vicSI.size(); i++) {
        do {
            randX = rand() % 28 + 1;
            randY = rand() % 28 + 1;
        } while (characterToPrint(inBoard, randX, randY, human, targets,
                                  incredSI, vicSI) != pointBoard);
        vicSI[i].x = randX;
        vicSI[i].y = randY;
    }
    createTheBoard(inBoard, human, targets, incredSI, vicSI, gameParam);
}

void charactersAppear(char inBoard[][SIZE],
                      Sim &human, std::vector<Target> targets,
                      std::vector<ISI> incredStupIdeas,
                      std::vector<VSI> vicStupIdeas,
                      GameParameters gameParam) {

    inBoard[human.x][human.y] = human.image;

    for (int i = 0; i < targets.size(); i++) {
        inBoard[targets[i].x][targets[i].y] = targets[i].image;
    }
    for (int i = 0; i < incredStupIdeas.size(); i++) {
        inBoard[incredStupIdeas[i].x][incredStupIdeas[i].y] =
                incredStupIdeas[i].image;
    }
    for (int i = 0; i < vicStupIdeas.size(); i++) {
        inBoard[vicStupIdeas[i].x][vicStupIdeas[i].y] =
                vicStupIdeas[i].image;
    }
    system("cls");
    createTheBoard(inBoard, human, targets, incredStupIdeas,
                   vicStupIdeas, gameParam);

}

void moveTheISI(char inBoard[][SIZE], Sim *human, ISI &incredSI,
                GameParameters &gameParam) {
    if (!gameParam.gameOver) {
        char moveDirection = ' ';

        if (incredSI.stuck == false) {
            const int numControls = 8;
            char movementControls[numControls] =
                    {'a', 'w', 'd', 's', 'q', 'e', 'z', 'c'};
            int randMove;

            randMove = rand() % 8;
            moveDirection = movementControls[randMove];
        } else {
            moveDirection = moveToHuman(incredSI.x, incredSI.y,
                                        human->x, human->y);
        }

        incredSI.moveTheISI(inBoard, moveDirection);
        gameParam.lastAction = "ISI Movement";
    }
}

void moveTheVSI(char inBoard[][SIZE], Sim *human, VSI &vicSI,
                GameParameters &gameParam) {
    if (!gameParam.gameOver) {
        char moveDirection = ' ';

        moveDirection = moveToHuman(vicSI.x, vicSI.y,
                                    human->x, human->y);

        vicSI.moveTheVSI(inBoard, moveDirection);
        gameParam.lastAction = "VSI Movement";
    }
}

char moveToHuman(int initX, int initY, int destX, int destY) {

    char moveDirection = ' ';

    int auxX = initX - destX;
    int auxY = initY - destY;

    if (auxY > 0 && auxX == 0) {
        moveDirection = 'a';
    } else if (auxY < 0 && auxX == 0) {
        moveDirection = 'd';
    } else if (auxY == 0 && auxX > 0) {
        moveDirection = 'w';
    } else if (auxY == 0 && auxX < 0) {
        moveDirection = 's';
    } else if (auxY < 0 && auxX < 0) {
        moveDirection = 'c';
    } else if (auxY < 0 && auxX > 0) {
        moveDirection = 'e';
    } else if (auxY > 0 && auxX < 0) {
        moveDirection = 'z';
    } else {
        moveDirection = 'q';
    }
    return moveDirection;
}

bool moveCoordinates(char inBoard[][SIZE], int &a, int &b,
                     char moveDirection) {
    int x = 0;
    int y = 0;

    if (moveDirection == 'w') {
        x = a - 1;
        y = b;
    } else if (moveDirection == 's') {
        x = a + 1;
        y = b;
    } else if (moveDirection == 'a') {
        x = a;
        y = b - 1;
    } else if (moveDirection == 'd') {
        x = a;
        y = b + 1;
    } else if (moveDirection == 'q') {
        x = a - 1;
        y = b - 1;
    } else if (moveDirection == 'e') {
        x = a - 1;
        y = b + 1;
    } else if (moveDirection == 'z') {
        x = a + 1;
        y = b - 1;
    } else if (moveDirection == 'c') {
        x = a + 1;
        y = b + 1;
    }

    if (movementValidation(inBoard, x, y)) {
        a = x;
        b = y;
        return true;
    } else {
        return false;
    }
}


bool movementValidation(char inBoard[][SIZE], int x, int y) {

    char pointBoard = 249;
    bool movementValidation = true;

    if (inBoard[x][y] == pointBoard) {
        return movementValidation;
    } else {
        return false;
    }
}

char characterToPrint(char inBoard[][SIZE], int x, int y, Sim &human,
                      std::vector<Target> targets, std::vector<ISI>
                      IncredSI, std::vector<VSI>vicSI) {

    char pointBoard = 249;

    if (human.x == x && human.y == y) {
        return human.image;
    }
    for (int i = 0; i < targets.size(); i++) {
        if (targets[i].getX() == x && targets[i].getY() == y) {
            return targets[i].image;
        }
    }
    for (int i = 0; i < IncredSI.size(); i++) {
        if (IncredSI[i].getX() == x && IncredSI[i].getY() == y) {
            return IncredSI[i].image;
        }
    }
    for (int i = 0; i < vicSI.size(); i++) {
        if (vicSI[i].getX() == x && vicSI[i].getY() == y) {
            return vicSI[i].image;
        }
    }
    return pointBoard;
}

bool gameOver(Sim *human, std::vector<Target> targets,
              std::vector<ISI> incredSI, std::vector<VSI>vicSI) {

    if (human->hearts == 0 || targets.size() == 0 ||
        (incredSI.size() == 0 && vicSI.size() == 0)) {
        return true;
    } else {
        return false;
    }
}

void ISITurn(char inBoard[][SIZE], Sim &human, std::vector<Target> &targets,
             std::vector<ISI> &incredSI, std::vector<VSI> &vicSI,
             GameParameters &gameParam) {
    for (int i = 0; (i < incredSI.size()) && (!gameParam.gameOver); i++) {
        bool stuckBeforeTheTurn = incredSI[i].stuck;

        if (incredSI[i].stunned && incredSI[i].stuck) {
            incredSI[i].stunned = false;
            incredSI[i].stuck = false;
            if (human.numActions <= 3) {
                human.numActions++;
            }
        }

        if (incredSI[i].stunned) {
            incredSI[i].stunned = false;
        } else {
            if (!closeTarget(incredSI[i].x, incredSI[i].y,
                             incredSI[i].effectivenessInAttack,
                             targets, gameParam)) {
                if (!incredSI[i].stuck) {
                    if (!ISICloseHuman(incredSI[i], human, gameParam)) {
                        moveTheISI(inBoard, &human, incredSI[i], gameParam);
                    }
                } else {
                    moveTheISI(inBoard, &human, incredSI[i], gameParam);
                }
            }
        }

        if (incredSI[i].stuck && stuckBeforeTheTurn) {
            human.hearts--;
            if (human.hearts < 0) {
                human.hearts = 0;
            }
            if (human.hearts == 0) {
                human.image = 'X';
                gameParam.gameOver = true;
                gameParam.winner = "Stupid Ideas";
            }
        }

        createTheBoard(inBoard, human, targets, incredSI, vicSI, gameParam);
        for (int i = 0; (i < 500000000) && (!gameParam.gameOver); i++);  // Delay in order to watch movement
    }
}

bool percentValidation (int x) {
    int randomNum = 0;
    randomNum = (rand() % 100) + 1;

    if (randomNum <= x) {
        return true;
    } else {
        return false;
    }
}

bool closeTarget(int x, int y, int percent, std::vector<Target>&targets,
                 GameParameters &gameParam) {
    bool closeTarget = false;
    int i = 0;

    if (targets.size() >= 1) {
        while (!closeTarget && i < targets.size()) {
            if (std::abs(x - targets[i].x) < 6 &&
                std::abs(y - targets[i].y) < 6) {  // 5 squares
                closeTarget = true;
                gameParam.lastAction = "Target Attacked";
                if (percentValidation(percent)) {
                    targets.erase(targets.begin() + i);
                    gameParam.lastAction = "Target Destroyed";
                }
            }
            i++;
        }
    }
    if (targets.size() == 0) {
        gameParam.gameOver = true;
        gameParam.winner = "Stupid Ideas";
    }
    return closeTarget;
}

bool ISICloseHuman(ISI &incredIS, Sim &human, GameParameters &gameParam) {
    bool closeHuman = false;

    if (std::abs(incredIS.x - human.x) < 2 &&
        std::abs(incredIS.y - human.y) < 2) {  // 1 square
        closeHuman = true;
        gameParam.lastAction = "ISI attacked Human";
        if (percentValidation(incredIS.effectivenessInAttack)) {
            incredIS.stuck = true;
            gameParam.lastAction = "ISI stuck to Human";
            if (human.numActions > 0) {
                human.numActions--;
            }
        }
    }
    return closeHuman;
}

void VSITurn(char inBoard[][SIZE], Sim &human, std::vector<Target> &targets,
             std::vector<ISI> &incredSI, std::vector<VSI> &vicSI,
             GameParameters &gameParam) {
    const int SIZEOFVSI = vicSI.size();

    for (int i = 0; (i < SIZEOFVSI) && (!gameParam.gameOver); i++) {
        if (vicSI[i].stuck) {
            human.hearts -= 1.5;
            if (human.hearts < 0) {
                human.hearts = 0;
            }

            if (human.hearts == 0) {
                human.image = 'X';
                gameParam.gameOver = true;
                gameParam.winner = "Stupid Ideas";
            }
            VSI multipledVicSI;
            int randX = 0;
            int randY= 0;
            do {
                randX = rand() % 30;
                randY = rand() % 30;
            } while (!movementValidation(inBoard, randX, randY));

            multipledVicSI.x = randX;
            multipledVicSI.y = randY;
            multipledVicSI.image = 232 ;
            vicSI.push_back(multipledVicSI);
        }

        for (int j = 0; j < vicSI[i].numActions; j++) {
            if (vicSI[i].stunned && vicSI[i].stuck) {
                vicSI[i].stunned = false;
                vicSI[i].stuck = false;
                human.numActions += 2;
                if (human.numActions > 3) {
                    human.numActions = 3;
                }
            }

            if (vicSI[i].stunned) {
                vicSI[i].stunned = false;
                gameParam.lastAction = "VSI stunned -> skipped";
            } else {
                if (!closeTarget(vicSI[i].x, vicSI[i].y,
                                 vicSI[i].effectivenessToTarget,
                                 targets, gameParam)) {
                    if (!vicSI[i].stuck) {
                        if (!VSICloseHuman(vicSI[i], human, gameParam)) {
                            moveTheVSI(inBoard, &human, vicSI[i], gameParam);
                        }
                    } else {
                        moveTheVSI(inBoard, &human, vicSI[i], gameParam);
                    }
                }
            }

            createTheBoard(inBoard, human, targets, incredSI,
                           vicSI, gameParam);
            for (int i = 0; (i < 500000000) && (!gameParam.gameOver); i++);  // Delay in order to watch movement
        }
    }
}

bool VSICloseHuman(VSI &vicIS, Sim &human, GameParameters &gameParam) {
    bool closeHuman = false;

    if (std::abs(vicIS.x - human.x) < 2 && std::abs(vicIS.y - human.y) < 2) {  // 1 square
        closeHuman = true;
        gameParam.lastAction = "VSI attacked Human";
        if (percentValidation(vicIS.effectivenessToHuman1Square)) {
            vicIS.stuck = true;
            gameParam.lastAction = "VSI stuck to Human";
            human.numActions -= 2;
            if (human.numActions < 0) {
                human.numActions = 0;
            }
        }
    } else if (std::abs(vicIS.x - human.x) < 3 &&
               std::abs(vicIS.y - human.y) < 3) {  // 2 squares
        closeHuman = true;
        gameParam.lastAction = "VSI attacked Human";
        if (percentValidation(vicIS.effectivenessToHuman2Squares)) {
            vicIS.stuck = true;
            gameParam.lastAction = "VSI stuck to Human";
            human.numActions -= 2;
            if (human.numActions < 0) {
                human.numActions = 0;
            }
        }
    }
    return closeHuman;
}

void humanTurn(char inBoard[][SIZE], Sim &human,
               std::vector<Target> &targets,
               std::vector<ISI> &incredSI, std::vector<VSI> &vicSI,
               GameParameters &gameParam) {

    for (int i = 0; (i < human.numActions) &&
                    (gameParam.gameOver == false); i++) {
        char moveDirection = ' ';
        bool validKey = false;

        do {
            std::cin.get(moveDirection);
            std::cin.ignore(100, '\n');

            if (moveDirection == 'w' || moveDirection == 'a' ||
                moveDirection == 'd' || moveDirection == 's' ||
                moveDirection == 'q' || moveDirection == 'e' ||
                moveDirection == 'z' || moveDirection == 'c') {
                human.moveTheSim(inBoard, moveDirection);
                gameParam.lastAction = "Human Movement";
                validKey = true;
            } else if (moveDirection == 'r') {
                netFilter(human, incredSI, vicSI);
                gameParam.lastAction = "Human used Net Filter";
                validKey = true;
            } else if (moveDirection == 'f') {
                snopesDestroyer(human, incredSI, vicSI, gameParam);
                gameParam.lastAction = "Human used Snopes Destroyer";
                validKey = true;
            } else {
                std::cout << "Error on input! Press a valid key"
                          << std::endl;
            }
        } while (!validKey);

        createTheBoard(inBoard, human, targets, incredSI,
                       vicSI, gameParam);

        if (human.numActions == i && gameParam.gameOver == false) {
            for (int i = 0; i < 500000000; i++);  // Delay in order to watch movement
        }
    }
}

void netFilter(Sim &human, std::vector<ISI> &incredSI,
               std::vector<VSI> &vicSI) {
    bool netFilter = false;

    for (int i = 0; i < vicSI.size(); i++) {
        if (std::abs(vicSI[i].x - human.x) < 2 &&
            std::abs(vicSI[i].y - human.y) < 2) {  // 1 square
            netFilter = true;
            if (percentValidation(human.effectivenessNetFilter1Square)) {
                vicSI[i].stunned = true;
            }
        } else if (std::abs(vicSI[i].x - human.x) < 3 &&
                   std::abs(vicSI[i].y - human.y) < 3) {  // 2 squares
            netFilter = true;
            if (percentValidation(human.effectivenessNetFilter2Square)) {
                vicSI[i].stunned = true;
            }
        }
    }
    if (!netFilter) {
        for (int i = 0; i < incredSI.size(); i++) {
            if (std::abs(incredSI[i].x - human.x) < 2 &&
                std::abs(incredSI[i].y - human.y) < 2) {  // 1 square
                netFilter = true;
                if (percentValidation(human.effectivenessNetFilter1Square)) {
                    incredSI[i].stunned = true;
                }
            } else if (std::abs(incredSI[i].x - human.x) < 3 &&
                       std::abs(incredSI[i].y - human.y) < 3) {  // 2 squares
                netFilter = true;
                if (percentValidation(human.effectivenessNetFilter2Square)) {
                    incredSI[i].stunned = true;
                }
            }
        }
    }
}

void snopesDestroyer(Sim &human, std::vector<ISI> &incredSI,
                     std::vector<VSI> &vicSI, GameParameters &gameParam) {
    bool snopesDestroyer = false;
    for (int i = 0; (i < vicSI.size()) && !snopesDestroyer; i++) {
        if (std::abs(vicSI[i].x - human.x) <= human.scopeSnopesDestroyer &&
            std::abs(vicSI[i].y - human.y) <= human.scopeSnopesDestroyer) {
            snopesDestroyer = true;
            gameParam.lastAction = "Human attacked VSI";
            if (vicSI[i].fullHealth) {
                if (percentValidation(
                        human.effectivenessSnopesDestroyerVSIFullHealth)) {
                    vicSI[i].fullHealth = false;
                    gameParam.lastAction = "VSI Health dropped to Half";
                }
            } else {
                if (percentValidation(
                        human.effectivenessSnopesDestroyerVSIHalfHealth)) {
                    if (vicSI[i].stuck) {
                        human.numActions += 2;
                        if (human.numActions > 3) {
                            human.numActions = 3;
                        }
                    }
                    vicSI.erase(vicSI.begin() + i);
                    gameParam.lastAction = "VSI Destroyed";
                }
            }
        }
    }

    if (!snopesDestroyer) {
        for (int i = 0; (i < incredSI.size()) && !snopesDestroyer; i++) {
            if (std::abs(incredSI[i].x - human.x) <=
                human.scopeSnopesDestroyer &&
                std::abs(incredSI[i].y - human.y) <=
                human.scopeSnopesDestroyer) {
                snopesDestroyer = true;
                gameParam.lastAction = "Human attacked ISI";
                if (percentValidation(
                        human.effectivenessSnopesDestroyerISI)) {
                    if (incredSI[i].fullHealth) {
                        incredSI[i].fullHealth = false;
                        gameParam.lastAction = "ISI Health dropped to Half";
                    } else {
                        if (incredSI[i].stuck) {
                            human.numActions += 2;
                            if (human.numActions > 3) {
                                human.numActions = 3;
                            }
                        }
                        incredSI.erase(incredSI.begin() + i);
                        gameParam.lastAction = "ISI Destroyed";
                    }
                }
            }
        }
    }
    if (incredSI.size() == 0 && vicSI.size() == 0) {
        gameParam.gameOver = true;
        gameParam.winner = "Human (You Win!!)";
    }
}
