#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int EASY_GRID_SIZE = 2;
const int MEDIUM_GRID_SIZE = 3;
const int HARD_GRID_SIZE = 4;

const int EASY_NUM_CARDS = EASY_GRID_SIZE * EASY_GRID_SIZE;
const int MEDIUM_NUM_CARDS = MEDIUM_GRID_SIZE * MEDIUM_GRID_SIZE;
const int HARD_NUM_CARDS = HARD_GRID_SIZE * HARD_GRID_SIZE;

const int EASY_SHOW_TIME_SECONDS = 3;
const int MEDIUM_SHOW_TIME_SECONDS = 5;
const int HARD_SHOW_TIME_SECONDS = 7;

int gameGrid[EASY_GRID_SIZE][EASY_GRID_SIZE];
int shuffledNumbers[EASY_NUM_CARDS];

void InitializeGame(int gridSize) {
  for (int i = 0; i < gridSize * gridSize; ++i) {
    shuffledNumbers[i] = i + 1;
  }

  srand(time(NULL)); 
  for (int i = 0; i < gridSize * gridSize; ++i) {
    int j = rand() % (gridSize * gridSize);
    int temp = shuffledNumbers[i];
    shuffledNumbers[i] = shuffledNumbers[j];
    shuffledNumbers[j] = temp;
  }

  for (int i = 0; i < gridSize; ++i) {
    for (int j = 0; j < gridSize; ++j) {
      gameGrid[i][j] = shuffledNumbers[i * gridSize + j];
    }
  }
}

void RenderGame(int gridSize, bool reveal) {
  system("cls"); 
  for (int i = 0; i < gridSize; ++i) {
    for (int j = 0; j < gridSize; ++j) {
      if (reveal) {
        cout << gameGrid[i][j] << '\t';
      } else {
        cout << "X\t"; 
      }
    }
    cout << endl;
  }
}

void ShowCardsForDuration(int gridSize, int showTimeSeconds) {
  RenderGame(gridSize, true); 
  cout << "Remember the numbers for " << showTimeSeconds << " seconds..." << endl;

  time_t startTime = time(NULL);

  while (time(NULL) - startTime < showTimeSeconds) {
  }

  RenderGame(gridSize, false); 
}

int GuessCards(int gridSize) {
  int score = 0;

  time_t startTime = time(NULL);

  for (int i = 0; i < gridSize; ++i) {
    for (int j = 0; j < gridSize; ++j) {
      cout << "Enter your guess for row " << i + 1 << ", column " << j + 1 << ": ";
      int guess;
      cin >> guess;

      if (guess == gameGrid[i][j]) {
        cout << "Correct!" << endl;
        score++;
      } else {
        cout << "Wrong!" << endl;
      }
    }
  }

  time_t endTime = time(NULL);

  int timeTakenSeconds = endTime - startTime;

  cout << "Time taken to solve the puzzle: " << timeTakenSeconds << " seconds" << endl;

  return score;
}


int main() {
  int difficulty;

  cout << "Welcome to the Memory Game!" << endl;
  cout << "Select the difficulty level:" << endl;
  cout << "1. Easy" << endl;
  cout << "2. Medium" << endl;
  cout << "3. Hard" << endl;
  cout << "Enter your choice (1/2/3): ";
  cin >> difficulty;

  int gridSize, showTimeSeconds;

  switch (difficulty) {
        case 1:
            gridSize = EASY_GRID_SIZE;
            showTimeSeconds = EASY_SHOW_TIME_SECONDS;
            break;
        case 2:
            gridSize = MEDIUM_GRID_SIZE;
            showTimeSeconds = MEDIUM_SHOW_TIME_SECONDS;
            break;
        case 3:
            gridSize = HARD_GRID_SIZE;
            showTimeSeconds = HARD_SHOW_TIME_SECONDS;
            break;
        default:
            cout << "Invalid choice. Exiting." << endl;
            return 1;
    }
    
    InitializeGame(gridSize);
    cin.ignore(); 
    cout << "Press Enter to reveal the numbers for " << showTimeSeconds << " seconds..." << endl;
    cin.ignore(); 
    ShowCardsForDuration(gridSize, showTimeSeconds);
    
    cout << "Now, guess the positions of the numbers:" << endl;
    int score = GuessCards(gridSize);
    
    cout<<"Your score is: "<<score<<endl;
    cout << "Game over!" << endl;
    
    return 0;
}