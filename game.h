#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
#define str string
class Game {
public:
    vector <string> words = {};
    // Загрузка слов из файла в вектор
    int Load(int &tries, bool only_tries=false) {
        while (true) {
            if (only_tries != true) {
                string line;
                ifstream file{"eng_words.txt"};
                if (!file) {
                    std::cout << "File 'eng_words.txt' not found! Create him in main.exe directory" << endl;
                    return 2;
                    break;
                }
                while (getline(file, line)) { if (line != " " && line != "") { words.push_back(line); }}
                if (words.size() == 0 && words.size() < 1) {
                    cout << "Words not found!" << endl;
                    return 1;
                    break;
                }
            }
            ifstream fileone{"settings.bin", ios_base::binary};
            fileone.read((char*)&tries, sizeof(int));
            cout << tries << endl;
            fileone.close();
            return 0;
            break;
        }
    };

    int Settings() {
        int choice;
        system("cls");
        cout << "1. Set attempts\n2. Go to main\nEnter: ";
        cin >> choice;
        if (choice == 1) {
            while (true) {
                system("cls");
                int atts;
                cout << "Set attempts value: ";
                cin >> atts;
                if (atts > 25) {
                    cout << "The number of attempts should not exceed 25!" << endl;
                } else {
                    ofstream file{"settings.bin", ios_base::binary};
                    if (!file) {
                        cout << "File `settings.bin` was not found! Create him in game directory!" << endl;
                    } else {
                        file.clear();
                        file.write((char*)&atts, sizeof(int));
                        file.close();
                        break;
                    }
                }
            }
        }
        else if (choice == 2) {
            return 1;
        }
        return 0;
    }

    // Проверка проиграл ли игрок
    bool LooseCheck(int& tries) {
        if (tries <= 0) {
            return true;
        } else {
            return false;
        }
    };
    // Выбор рандомного слова из вектора
    void WordChoose(string& word) {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(0,int(words.size()-1));
        word = words[dist6(rng)];
    };
    // Перезапуск игры
    bool Repeat() {
        cout << "Play again?(yes,no): ";
        str choice;
        cin >> choice;
        if (choice == "yes" || choice == "Yes") {
            return true;
        } else {
            return false;
        }
    };
    // Выбор следующего хода
    void Step(str name1, str name2, str &step) {
        if (step == name1) {step = name2;} 
        else if (step == name2) {step = name1;}
    };
    // Режим двух игроков
    int GameMainTwoPlayers(int &tries) {
        string name1, name2;
        int first = 0;
        while (true) {
            first++;
            cout << "Enter first player name: ";
            if (first == 1) {cin.ignore();}
            getline(cin, name1, '\n');
            if (name1 != "" && name1 != " ") {
                if (name1.length() < 10) {break;}
                else {cout << "The length of the name must be less than 10!"<<endl;}
            } else {
                cout << "The name should not be empty!" << endl;
            }
        }
        while (true) {
            cout << "Enter second player name: ";
            getline(cin, name2);
            if (name2 != "" && name2 != " ") {
                if (name2.length() < 10) {break;}
                else {cout << "The length of the name must be less than 10!"<<endl;}
            } else {
                cout << "The name should not be empty!" << endl;
            }
        }
        string step = name2;
        while (true) {
            // system("cls");
            Load(tries, true);
            int tries1 = tries, tries2 = tries;
            string word1, word2, hidden_word1, hidden_word2, letter1, letter2;
            bool loose1 = false, loose2 = false, win1 = false, win2 = false;
            WordChoose(word1);
            WordChoose(word2);
            for (int i = 0; i < word1.length(); i++) {
                hidden_word1 += "*";
            }
            for (int i = 0; i < word2.length(); i++) {
                hidden_word2 += "*";
            }
            while (hidden_word1 != word1 || hidden_word2 != word2 || win1 != true || win2 != true || loose1 != true || loose2 != true) {
                string newWord1 = "", newWord2 = "";
                int fucks1 = 0, fucks2 = 0;
                Step(name1, name2, step);
                cout << "-----------------------------" << endl;
                cout << "Step player: " << step << endl;
                if (step == name1 && loose1 != true) {
                    while (fucks1 < 1) {
                        if (word1 == hidden_word2) {win1 = true; break;}
                        string newWord1 = "";
                        cout << name1 << " attempts: " << tries1 << endl;
                        cout << name1 << " hidden word: " << hidden_word1 << endl;
                        cout << "Enter the letter: ";
                        cin >> letter1;
                        if (word1.find(letter1) <= word1.length()) {
                            if (*find(hidden_word1.begin(), hidden_word1.end(), letter1[0]) != letter1[0]) {
                                for (int i = 0; i < word1.length(); i++) {
                                    if (letter1[0] == word1[i]) {newWord1 += letter1[0];}
                                    else {newWord1 += hidden_word1[i];}
                                }
                                hidden_word1 = newWord1;
                                if (word1 == hidden_word1) {win1 = true; break;}
                            } else {cout << "Letter is already there!" << endl;}
                        } else {
                            tries1 -=1;
                            cout << "Letter not found!\n" << name1 << " tries: " << tries1 << endl;
                            if (LooseCheck(tries1)==true) {loose1 = true; break;}
                            fucks1++;
                        }
                    }
                    if (win1 == true || win2 == true || loose1 == true && loose2 == true) {break;}
                } else if (step == name2 && loose2 != true) {
                    while (fucks2 < 1) {
                        if (word2 == hidden_word2) {win2 = true; break;}
                        string newWord2 = "";
                        cout << name2 << " attempts: " << tries2 << endl; 
                        cout << name2 << " hidden word: " << hidden_word2 << endl;
                        cout << "Enter the letter: ";
                        cin >> letter2;
                        if (word2.find(letter2) <= word2.length()) {
                            if (*find(hidden_word2.begin(), hidden_word2.end(), letter2[0]) != letter2[0]) {
                                for (int i = 0; i < word2.length(); i++) {
                                    if (letter2[0] == word2[i]) {newWord2 += letter2[0];}
                                    else {newWord2 += hidden_word2[i];}
                                }
                                hidden_word2 = newWord2;
                                if (word2 == hidden_word2) {win2 = true; break;}
                            } else {cout << "Letter is already there!" << endl;}
                        } else {
                            tries2 -=1;
                            cout << "Letter not found!\n" << name2 << " tries: " << tries2 << endl;
                            if (LooseCheck(tries2)==true) {loose2 = true; break;}
                            fucks2++;
                        }
                    }
                    if (win1 == true || win2 == true || loose1 == true && loose2 == true) {break;}
                }
            }
            if (win1 == true) {
                cout << "Player " << name1 << " guessed the word faster than player " << name2 << "!!!" << endl;
            } else if (win2 == true) {
                cout << "Player " << name2 << " guessed the word faster than player " << name1 << "!!!" << endl;
            } else if (loose1 == true || win2 == true) {
                cout << "Player " << name2 << " guessed the word, but player " << name1 << " was loose!" << endl;
            } else if (loose2 == true || win1 == true) {
                cout << "Player " << name1 << " guessed the word, but player " << name2 << " was loose!" << endl;
            } else if (loose1 == true && loose2 == true) {
                cout << name1 << " and " << name2 << "LOOSE!" << endl;
            }
            if (Repeat() != true) {system("cls"); return 228; break;}
        }
    };
    // Режим одного игрока
    int GameMain(int &tries) {
        int exit = 0;
        while (true) {
            vector <char> used_letters = {};
            system("cls");
            Load(tries, true);
            string word, closed_word, letter;
            bool loose;
            WordChoose(word);
            for (int i = 0; i < word.length(); i++) {
                closed_word += "*";
            }
            cout << "Attempts: " << tries << endl;
            while (closed_word != word) {
                string neww = "";
                cout << "Hidden word: " << closed_word << endl;
                cout << "Enter the letter: ";
                cin >> letter;
                if (letter == "exit" || letter == "Exit") {exit = 1; break;}
                cout << "-----------------------------" << endl;
                if (word.find(letter) <= word.length()) {
                    if (find(used_letters.begin(), used_letters.end(), letter[0]) == used_letters.end()) {
                        if (*find(closed_word.begin(), closed_word.end(), letter[0]) != letter[0]) {
                            for (int i = 0; i < word.length(); i++) {
                                    if (letter[0] == word[i]) {neww += letter[0];} 
                                    else {neww += closed_word[i];}
                            }
                            closed_word = neww;
                            cout << "Letter found!" << endl;            
                            used_letters.push_back(letter[0]);
                            if (word == closed_word) {cout << "Hidden word: " << word << endl; break;}
                        } else {cout << "Letter is already there!" << endl;}
                    } else {cout << "You've already called this letter!" << endl;}
                } else {
                    tries -= 1;
                    cout << "Letter not found!\nTries have: " << tries << endl;
                    if (LooseCheck(tries)==true) {break;}
                }
            }
            if (exit != 1) {if (LooseCheck(tries) != true) {cout << "You guessed it!" << endl; } else if (LooseCheck(tries) == true) {cout << "You loose!\nThe hidden word was: " << word << endl;}}
            if (exit != 1) {if (Repeat() != true) {system("cls"); return 1; break;}}
            if (exit == 1) {
                cout << "You've finished the game." << endl;
                return 0;
                break;
            }
        }
    };

    // Информация
    int Info() {
        system("cls");
        // Цель игры, импорт слов и попыток
        cout << "ABOUT:\n Try to guess the words without wasting all your attempts.\n It sounds simple, but it's not like that at all. Test your vocabulary!\n When you select `Play`, words are imported from the file `eng_words.txt`.\n You can set the number of attempts in the `Settings` item in the main menu (limit of 25 attempts)." << endl;
        // Об обновлениях
        cout << "\nUPDATES INFO:\nv1.0\n - Game release\nv1.1\n - Fixed bug with winning with a single move\nv1.2\n - Added menu\n - `words.txt` updated(at upd moment 285 words)\n - Some phrases have been changed\n - Other bug fix\nv1.3 <= THIS\n - Added two player mode\n - Some phrases have been changed\n - the import of attempts has been moved to a file `settings.txt `\n - file `words.txt` renamed to 'eng_words.txt'\n - `eng_words.txt` updated(at upd moment 520)\n - added the `Settings` item for setting attempts" << endl;
        // Планы на будущее
        cout << "\nFUTURE PLANS:\n - Add multiplayer/online two player mode\n - Add language switch\n" << endl;
        return 0;
    };

    // Выбор режима игры
    void GameModeSwitch(int &tries) {
        bool in_switch = true;
        while (in_switch) {
            int choice;
            system("cls");
            cout << "Enter game mode:\n1. Single player mode\n2. Two player mode" << endl;
            cin >> choice;
            switch(choice) {
                case 1: {
                    GameMain(tries);
                }break;
                case 2: {
                    if (words.size() != 1 && words.size() >= 2) {GameMainTwoPlayers(tries);}
                    else {cout << "For a two player mode you need at least 2 words!" << endl;}                
                }break;
                default: break;
            }
            in_switch = false;
        }
    };
};

#endif