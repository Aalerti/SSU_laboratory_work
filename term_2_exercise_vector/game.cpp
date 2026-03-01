#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <vector>


const std::vector<std::string> WORD_LIST = {
    "elephant","butterfly","strawberry","programming","infrastructure","comfortable",
    "international","universities","atmospheric","description","celebration", "championship"
};

const std::vector<std::string> HANGMAN_STAGES = {
    "  +---+\n"
    "  |   |\n"
    "      |\n"
    "      |\n"
    "      |\n"
    "      |\n"
    "=========",

    "  +---+\n"
    "  |   |\n"
    "  O   |\n"
    "      |\n"
    "      |\n"
    "      |\n"
    "=========",

    "  +---+\n"
    "  |   |\n"
    "  O   |\n"
    "  |   |\n"
    "      |\n"
    "      |\n"
    "=========",

    "  +---+\n"
    "  |   |\n"
    "  O   |\n"
    " /|   |\n"
    "      |\n"
    "      |\n"
    "=========",

    "  +---+\n"
    "  |   |\n"
    "  O   |\n"
    " /|\\  |\n"
    "      |\n"
    "      |\n"
    "=========",

    "  +---+\n"
    "  |   |\n"
    "  O   |\n"
    " /|\\  |\n"
    " /    |\n"
    "      |\n"
    "=========",

    "  +---+\n"
    "  |   |\n"
    "  O   |\n"
    " /|\\  |\n"
    " / \\  |\n"
    "      |\n"
    "========="
};

const int MAX_HANGMAN_ERRORS = 6;
const int MAX_MOVES_MODE1    = 8;


struct GameState {
    std::string secretWord;
    std::string maskedWord;
    std::string alphabet;
    int  errors;
    int  movesLeft;
    int  gameMode;
    bool gameOver;
    bool playerWon;
};


std::string pickRandomWord() {
    return WORD_LIST[std::rand() % WORD_LIST.size()];
}

std::string buildMaskedWord(const std::string& word) {
    return std::string(word.size(), '_');
}

std::string buildAlphabet() {
    return "abcdefghijklmnopqrstuvwxyz";
}

GameState initGame(int gameMode) {
    std::srand(std::time(0));
    GameState state;
    state.secretWord = pickRandomWord();
    state.maskedWord = buildMaskedWord(state.secretWord);
    state.alphabet   = buildAlphabet();
    state.errors     = 0;
    state.movesLeft  = MAX_MOVES_MODE1;
    state.gameMode   = gameMode;
    state.gameOver   = false;
    state.playerWon  = false;
    return state;
}

void displayHangman(int errors) {
    std::cout << HANGMAN_STAGES[errors] << "\n";
}

void displayMaskedWord(const std::string& maskedWord) {
    for (size_t i = 0; i < maskedWord.size(); ++i) {
        std::cout << maskedWord[i];
        if (i + 1 < maskedWord.size()) std::cout << ' ';
    }
    std::cout << "\n";
}

void displayAlphabet(const std::string& alphabet) {
    std::cout << "Letters: ";
    for (char c : alphabet) std::cout << c << ' ';
    std::cout << "\n";
}

void displayBoard(const GameState& state) {
    std::cout << "\n" << std::string(50, '-') << "\n";

    if (state.gameMode == 2) {
        displayHangman(state.errors);
    } else {
        std::cout << "Wrong guesses left: " << state.movesLeft << "\n";
    }

    std::cout << "\nWord: ";
    displayMaskedWord(state.maskedWord);
    std::cout << "\n";
    displayAlphabet(state.alphabet);
    std::cout << std::string(50, '-') << "\n";
}

int chooseGameMode() {
    int mode = 0;
    while (mode != 1 && mode != 2) {
        std::cout << "Choose game mode:\n";
        std::cout << "  1 - Move counter (max " << MAX_MOVES_MODE1 << " wrong guesses)\n";
        std::cout << "  2 - Hangman drawing\n";
        std::cout << "Yout choice: ";
        std::cin >> mode;
        if (mode != 1 && mode != 2)
            std::cout << "Please enter 1 or 2.\n";
    }
    return mode;
}

char chooseAction() {
    char action = 0;
    while (action != 'L' && action != 'W') {
        std::cout << "Enter Letter [L] or Word [W] ? ";
        std::cin >> action;
        action = static_cast<char>(std::toupper(action));
        if (action != 'L' && action != 'W')
            std::cout << "Please enter L or W.\n";
    }
    return action;
}


char inputLetter() {
    char letter = 0;
    while (true) {
        std::cout << "Enter a letter: ";
        std::cin >> letter;
        letter = static_cast<char>(std::tolower(letter));
        if (letter >= 'a' && letter <= 'z') break;
        std::cout << "Invalid input. Please enter a letter a-z.\n";
    }
    return letter;
}


std::string inputWord() {
    std::string word;
    while (true) {
        std::cout << "Enter the word: ";
        std::cin >> word;
        std::transform(word.begin(), word.end(), word.begin(),
                       [](char c){ return static_cast<char>(std::tolower(c)); });
        bool valid = std::all_of(word.begin(), word.end(),
                                 [](char c){ return c >= 'a' && c <= 'z'; });
        if (valid) break;
        std::cout << "Use letters only.\n";
    }
    return word;
}

bool processLetterGuess(char letter, GameState& state) {
    bool found = false;
    for (size_t i = 0; i < state.secretWord.size(); ++i) {
        if (state.secretWord[i] == letter) {
            state.maskedWord[i] = letter;
            found = true;
        }
    }
    state.alphabet.erase(std::remove(state.alphabet.begin(), state.alphabet.end(), letter),state.alphabet.end());
    return found;
}

bool processWordGuess(const std::string& word, GameState& state) {
    if (word == state.secretWord) {
        state.maskedWord = state.secretWord;
        return true;
    }
    return false;
}


void handleWrongGuess(GameState& state) {
    std::cout << "Wrong guess!\n";
    state.errors++;
    if (state.gameMode == 1) {
        state.movesLeft--;
        std::cout << "Wrong guesses left: " << state.movesLeft << "\n";
    }
}

bool isWordGuessed(const std::string& maskedWord) {
    return std::find(maskedWord.begin(), maskedWord.end(), '_') == maskedWord.end();
}


void checkGameOver(GameState& state) {
    if (isWordGuessed(state.maskedWord)) {
        state.playerWon = true;
        state.gameOver  = true;
        return;
    }
    if (state.gameMode == 1 && state.movesLeft <= 0) {
        state.gameOver = true;
    }
    if (state.gameMode == 2 && state.errors >= MAX_HANGMAN_ERRORS) {
        state.gameOver = true;
    }
}





void displayResult(const GameState& state) {
    std::cout << "\n" << std::string(50, '=') << "\n";
    if (state.playerWon) {
        std::cout << "  YOU WIN! Congratulations!\n";
    } else {
        if (state.gameMode == 2) displayHangman(MAX_HANGMAN_ERRORS);
        std::cout << "  YOU LOSE! The word was: " << state.secretWord << "\n";
    }
    std::cout << std::string(50, '=') << "\n";
}


void runGameLoop(GameState& state) {
    while (!state.gameOver) {
        displayBoard(state);
        char action = chooseAction();

        if (action == 'W') {
            std::string word = inputWord();
            if (!processWordGuess(word, state)) {
                std::cout << "Wrong word! Game over.\n";
                state.gameOver = true;
            }
        } else {
            char letter = inputLetter();
            if (state.alphabet.find(letter) == std::string::npos) {
                std::cout << "Letter '" << letter << "' was already used! Try another.\n";
                continue;
            }
            if (!processLetterGuess(letter, state)) {
                handleWrongGuess(state);
            }
        }

        checkGameOver(state);
    }
}


int main() {
    std::cout << "=== HANGMAN GAME ===\n\n";

    int mode = chooseGameMode();
    GameState state = initGame(mode);
    runGameLoop(state);
    displayResult(state);

    return 0;
}