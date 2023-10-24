#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

char generateRandomChar() {
    return 'A' + (rand() % 26);
}


void wrapAround(char &c1) {
    if (c1 > 'Z') {
        c1 = 'A' + (c1 - 'Z' - 1);
    }
}

char generateNextChar(char c1,int difference) {
    char nextChar = c1 + difference;
    wrapAround(nextChar);
    return nextChar;
}

void generateDifference(int difference[3]){
    difference[0] = (rand() % 4) + 1;
    difference[1] = (rand() % 4) + 1;
    difference[2] = (rand() % 6) + 1;
}

void generateString(char c1, string s[3]) {
    int difference[3];
    generateDifference(difference);
    string nextChar;

    for(int i=0;i<9;i++){
        if(i==0) nextChar[i]=c1;
        else if(i==3 or i==6) nextChar[i]=generateNextChar(nextChar[i-1], difference[2]);
        else if(i==1 or i==4 or i==7) nextChar[i]=generateNextChar(nextChar[i-1], difference[0]);
        else if(i==2 or i==5 or i==8) nextChar[i]=generateNextChar(nextChar[i-1], difference[1]);

        if(i<3) s[0]+=nextChar[i];
        else if(i<6) s[1]+=nextChar[i];
        else s[2]+=nextChar[i];
    }

}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    cout << "Character Sequence Guessing Game" << endl;
    cout << "--------------------------------" << endl;

    int numRounds = 5;
    int currentRound = 1;
    int score=0;

    clock_t start_time = clock();

    while (currentRound <= numRounds) {
        char c1=generateRandomChar();
        string s[3];
        generateString(c1,s);

        cout << "Round " << currentRound << " - Guess the next string based on: " << s[0] << ", " << s[1] << endl;

        string userGuess;
        cout << "Your guess: ";
        cin >> userGuess;

        if (userGuess == s[2]) {
            cout << "Correct! Next round..." << endl;
            currentRound += 1;
            score++;
        } else {
            cout << "Incorrect. The correct answer was: " << s[2] << endl;
        }
        currentRound++;
    }

    clock_t end_time = clock();

    int elapsed_time = (end_time - start_time)/CLOCKS_PER_SEC;
    cout<<"Your score is "<<score<<endl;
    cout<<"Your time is "<<elapsed_time<<" seconds"<<endl;

    return 0;
}