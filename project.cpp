#include <iostream>
#include <string>
using namespace std;

class HiddenWord {
    string targetWord;
    string currentProgress;
    char incorrectLetters[6];
    int incorrectCount;
    int maxAttempts;

public:
    HiddenWord(string word, int attempts)
        : targetWord(word), currentProgress(string(word.length(), '_')),
          maxAttempts(attempts), incorrectCount(0) {}

    bool makeGuess(char letter) {
        bool isFound = false;
        for (size_t i = 0; i < targetWord.length(); i++) {
            if (targetWord[i] == letter) {
                currentProgress[i] = letter;
                isFound = true;
            }
        }
        if (!isFound && incorrectCount < maxAttempts) {
            incorrectLetters[incorrectCount++] = letter;
        }
        return isFound;
    }

    bool isSolved() const {
        return currentProgress == targetWord;
    }

    void showProgress() const {
        cout << "Current word: " << currentProgress << endl;
        cout << "Incorrect letters: ";
        for (int i = 0; i < incorrectCount; i++) {
            cout << incorrectLetters[i] << " ";
        }
        cout << endl;
    }

    int guessesLeft() const {
        return maxAttempts - incorrectCount;
    }

    string getTargetWord() const {
        return targetWord;
    }

    int getIncorrectCount() const {
        return incorrectCount;
    }
};

class HangmanDisplay {
public:
    void render(int mistakes) const {
        switch (mistakes) {
        case 0:
            cout << "  -----  \n  |   |  \n        \n        \n        \n        \n";
            break;
        case 1:
            cout << "  -----  \n  |   |  \n  O     \n        \n        \n        \n";
            break;
        case 2:
            cout << "  -----  \n  |   |  \n  O     \n  |     \n        \n        \n";
            break;
        case 3:
            cout << "  -----  \n  |   |  \n  O     \n /|     \n        \n        \n";
            break;
        case 4:
            cout << "  -----  \n  |   |  \n  O     \n /|\\    \n        \n        \n";
            break;
        case 5:
            cout << "  -----  \n  |   |  \n  O     \n /|\\    \n /      \n        \n";
            break;
        case 6:
            cout << "  -----  \n  |   |  \n  O     \n /|\\    \n / \\    \n        \n";
            break;
        default:
            cout << "Invalid state!" << endl;
        }
    }
};

class HangmanGame {
    HiddenWord wordHandler;
    HangmanDisplay hangman;

public:
    HangmanGame(string secretWord, int maxAttempts)
        : wordHandler(secretWord, maxAttempts) {}

    void start() {
        char guess;
        while (wordHandler.guessesLeft() > 0 && !wordHandler.isSolved()) {
            cout << "\n";
            hangman.render(wordHandler.getIncorrectCount());
            wordHandler.showProgress();
            cout << "Attempts left: " << wordHandler.guessesLeft() << endl;
            cout << "Enter your guess (a single letter): ";
            cin >> guess;

            if (!isalpha(guess)) {
                cout << "Please enter a valid alphabet letter!" << endl;
                continue;
            }

            if (wordHandler.makeGuess(guess)) {
                cout << "Nice! You guessed a letter!" << endl;
            } else {
                cout << "Oops! That letter is incorrect." << endl;
            }
        }

        if (wordHandler.isSolved()) {
            cout << "Congratulations! You've successfully guessed the word: " 
                 << wordHandler.getTargetWord() << endl;
        } else {
            cout << "Game Over! The word was: " << wordHandler.getTargetWord() << endl;
        }
    }
};

int main() {
    string wordList[] = {"developer", "algorithm", "function", "variable", "syntax", "debugging"};
    int totalWords = 6;

    int chosenIndex;
    cout << "Choose a word (Enter a number between 0 and " << totalWords - 1 << "): ";
    cin >> chosenIndex;

    int selectedWordIndex = chosenIndex % totalWords;

    HangmanGame game(wordList[selectedWordIndex], 6);
    game.start();

    return 0;
}
