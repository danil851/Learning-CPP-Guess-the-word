// Игра угадай слово
#include "game.h"

// Главное меню
int main() {
    Game game;
    system("cls");
    setlocale(LC_ALL, "rus");
    int choice, tries;
    cout << "Welcome to game 'Guess the word'! v1.3\n";
    while (true) {
        cout << "Select an action:\n1. Play\n2. Info\n3. Settings\n4. Exit\n";
        cin >> choice;
        if (choice == 1) {if (game.words.size() > 1 || game.words.size() != 0) {game.GameModeSwitch(tries);} else {if (game.Load(tries, false) != 1 && game.Load(tries, false) == 0 || game.Load(tries, false) != 2 && game.Load(tries, false) == 0) {game.GameModeSwitch(tries);}}} 
        else if (choice == 4) {system("pause"); return 0;}
        else if (choice == 3) {game.Settings();}
        else if (choice == 2) {game.Info();}
    }
}