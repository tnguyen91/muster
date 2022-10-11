// who: Tu Nguyen
// what: Muster 
// why: project 1
// when: Apr 3, 2022

// includes go here
#include <iostream>
#include <iomanip>
#include <random>
#include <string>
#include <algorithm>

int DICE_QTY = 6;
int START_VAL = 0;
int END_VAL = 5;

void printWelcome();
void play();
bool cont(int, int);
std::string getPlayersName(std::string);
void printScore(std::string, int, std::string, int);
void rollTurn(std::string, int &, std::string, int &);
int getRollCount(std::string);
void rollDice(int[], int, int);
int getPoint(int[], int);
void scoreCases(int[], int, int &);
bool isThreePairs(int[], int);
bool isThreeOf(int[], int);
int getPtsThreeOf(int[], int);
bool contains(int[], int, int);
bool playAgain();
int random(int, int);

int main(int argc, char const *argv[])
{
    // your code goes here
    printWelcome();

    char p;
    std::cout << "\nWould you like to play (Y/N)? ";
    std::cin >> p;

    if (tolower(p) == 'y')
    {
        do
        {
            play();
        } while (playAgain());
    }
    std::cout << "\n---- Hasta La Vista Baby ----\n";
    return 0;
}

void printWelcome()
{
    std::cout << "Welcome to Muster!\nThe first player to reach 1000 and exceed the other players score wins.\n";
    std::cout << "\nScoring:\n";
    std::cout << std::left << std::setw(15) << "\t1" << std::right << std::setw(15) << "2 points\n";
    std::cout << std::left << std::setw(15) << "\t2" << std::right << std::setw(15) << "5 points\n";
    std::cout << std::left << std::setw(15) << "\tThree 1's" << std::right << std::setw(15) << "10 points\n";
    std::cout << std::left << std::setw(15) << "\tThree 2's" << std::right << std::setw(15) << "20 points\n";
    std::cout << std::left << std::setw(15) << "\tThree 3's" << std::right << std::setw(15) << "30 points\n";
    std::cout << std::left << std::setw(15) << "\tThree 4's" << std::right << std::setw(15) << "40 points\n";
    std::cout << std::left << std::setw(15) << "\tThree 5's" << std::right << std::setw(15) << "50 points\n";
    std::cout << std::left << std::setw(15) << "\tThree 6's" << std::right << std::setw(15) << "60 points\n";

    std::cout << std::left << std::setw(15) << "\t1-2-3-4-5-6" << std::right << std::setw(15) << "300 points\n";
}

void play()
{
    std::string p1 = getPlayersName("\nEnter the first player's name: ");
    int score1 = 0;

    std::string p2 = getPlayersName("Enter the second player's name: ");
    int score2 = 0;

    int turnCount = 0;
    printScore(p1, score1, p2, score2);
    while (cont(score1, score2))
    {
        std::cout << "\nTurn " << ++turnCount << '\n';
        std::cout << "------\n";

        rollTurn(p1, score1, p2, score2);
        printScore(p1, score1, p2, score2);
    }
    std::cout << '\n'
              << (score1 > score2 ? p1 : p2) << " Wins!\n";
}

bool cont(int s1, int s2)
{
    if (std::max(s1, s2) >= 1000 && std::min(s1, s2) < 1000)
        return false;
    else if (std::min(s1, s2) >= 1000 && s1 != s2)
        return false;
    else
        return true;
}

std::string getPlayersName(std::string prompt)
{
    std::string name;
    std::cout << prompt;
    std::cin >> name;
    return name;
}

void printScore(std::string p1, int s1, std::string p2, int s2)
{
    p1 = '\t' + p1 + ':';
    p2 = '\t' + p2 + ':';
    std::cout << "\nThe scores are:\n";
    std::cout << std::left << std::setw(15) << p1 << std::right << std::setw(5) << s1 << '\n';
    std::cout << std::left << std::setw(15) << p2 << std::right << std::setw(5) << s2 << '\n';
}

void rollTurn(std::string p1, int &s1, std::string p2, int &s2)
{
    int dice[DICE_QTY];

    int rollCnt1 = getRollCount(p1);
    rollDice(dice, DICE_QTY, rollCnt1);
    int pts1 = getPoint(dice, DICE_QTY);
    std::cout << '\t' << p1 << " earns " << std::to_string(pts1) << " point(s)\n\n";
    s1 += pts1;

    int rollCnt2 = getRollCount(p2);
    rollDice(dice, DICE_QTY, rollCnt2);
    int pts2 = getPoint(dice, DICE_QTY);
    std::cout << '\t' << p2 << " earns " << std::to_string(pts2) << " point(s)\n";
    s2 += pts2;
}

int getRollCount(std::string playersName)
{
    std::cout << "\tHow many times would " << playersName << " like to shake the dice? ";
    int cnt;
    std::cin >> cnt;
    return cnt;
}

void rollDice(int dice[], int size, int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            dice[j] = random(START_VAL, END_VAL);
        }
    }
    std::cout << "\tThe roll is: ";
    for (int i = 0; i < size; ++i)
    {
        std::cout << dice[i] + 1 << ' ';
    }
    std::cout << '\n';
}

int getPoint(int dice[], int size)
{
    int p[size] = {0};
    int pts = 0;
    for (int i = 0; i < size; ++i)
    {
        ++p[dice[i]];
    }
    scoreCases(p, size, pts);

    for (int i = 0; i < size; ++i)
    {
        dice[i] = 0;
    }

    return pts;
}

void scoreCases(int p[], int size, int &pts)
{
    if (p[0] == p[1] && p[0] == p[2] && p[0] == p[3] && p[0] == p[4] && p[0] == p[5])
        pts = 300;
    else if (isThreePairs(p, size))
        pts = 150;
    else if (isThreeOf(p, size))
    {
        pts = getPtsThreeOf(p, size);
    }
    else if (pts == 0)
        if (p[4] != 0)
            pts = 5;
        else if (p[0] != 0)
            pts = 2;
}

bool isThreePairs(int p[], int size)
{
    if (contains(p, size, 4) && contains(p, size, 2) || contains(p, size, 6))
        return true;

    int cnt = 0;
    for (int i = 0; i < size; ++i)
    {
        cnt += (p[i] == 2);
    }
    return cnt == 3;
}

bool contains(int p[], int size, int n)
{
    for (int i = 0; i < size; ++i)
    {
        if (p[i] == n)
        {
            return true;
        }
    }
    return false;
}

bool isThreeOf(int p[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (p[i] >= 3)
            return true;
    }
    return false;
}

int getPtsThreeOf(int p[], int size)
{
    int mx = 0;
    for (int i = 0; i < size; ++i)
    {
        mx = std::max(mx, p[i]);
    }
    for (int i = size - 1; i >= 0; --i)
    {
        if (p[i] == mx)
            return (i + 1) * 10;
    }
}

bool playAgain()
{
    std::cout << "\nWould you like to play again? ";
    char pA;
    std::cin >> pA;
    if (tolower(pA) == 'y')
    {
        return true;
    }
    return false;
}

int random(int start, int end)
{
    static std::random_device rd;
    static std::default_random_engine rndEng(rd());
    static std::uniform_int_distribution<int> uniformDist(start, end);
    return uniformDist(rndEng);
}