#ifndef GAME_H
#define GAME_H
#include "DataSave.h"
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
private:
    Data data;
    char close_symbol = '*';
    vector <string> selected_theme = {
    "0. Exit\n1. **** (sel.)\n2. ????\n3. ||||\n4. ^^^^\n5. ####\n6. $$$$\n7. @@@@\n8. ____\n9. ----\n10. &&&&\nEnter: ",
    "0. Exit\n1. ****\n2. ???? (sel.)\n3. ||||\n4. ^^^^\n5. ####\n6. $$$$\n7. @@@@\n8. ____\n9. ----\n10. &&&&\nEnter: ",
    "0. Exit\n1. ****\n2. ????\n3. |||| (sel.)\n4. ^^^^\n5. ####\n6. $$$$\n7. @@@@\n8. ____\n9. ----\n10. &&&&\nEnter: ",
    "0. Exit\n1. ****\n2. ????\n3. ||||\n4. ^^^^ (sel.)\n5. ####\n6. $$$$\n7. @@@@\n8. ____\n9. ----\n10. &&&&\nEnter: ",
    "0. Exit\n1. ****\n2. ????\n3. ||||\n4. ^^^^\n5. #### (sel.)\n6. $$$$\n7. @@@@\n8. ____\n9. ----\n10. &&&&\nEnter: ",
    "0. Exit\n1. ****\n2. ????\n3. ||||\n4. ^^^^\n5. ####\n6. $$$$ (sel.)\n7. @@@@\n8. ____\n9. ----\n10. &&&&\nEnter: ",
    "0. Exit\n1. ****\n2. ????\n3. ||||\n4. ^^^^\n5. ####\n6. $$$$\n7. @@@@ (sel.)\n8. ____\n9. ----\n10. &&&&\nEnter: ",
    "0. Exit\n1. ****\n2. ????\n3. ||||\n4. ^^^^\n5. ####\n6. $$$$\n7. @@@@\n8. ____ (sel.)\n9. ----\n10. &&&&\nEnter: ",
    "0. Exit\n1. ****\n2. ????\n3. ||||\n4. ^^^^\n5. ####\n6. $$$$\n7. @@@@\n8. ____\n9. ---- (sel.)\n10. &&&&\nEnter: ",
    "0. Exit\n1. ****\n2. ????\n3. ||||\n4. ^^^^\n5. ####\n6. $$$$\n7. @@@@\n8. ____\n9. ----\n10. &&&& (sel.)\nEnter: "
    };
    string text = selected_theme[0];
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
            data.Load("Attempts", &tries);
            return 0;
            break;
        }
    };

    int Settings() {
        while (true) {
            int choice;
            system("cls");
            cout << "0. Go to main\n1. Set attempts\n2. closed symbols theme\nEnter: ";
            cin >> choice;
            if (choice == 0) {
                system("cls");
                return 1;
            }
            else if (choice == 1) {
                while (true) {
                    cout << "------------------------" << endl;
                    int atts;
                    cout << "Set attempts value: ";
                    cin >> atts;
                    if (atts > 25) {
                        cout << "The number of attempts should not exceed 25!" << endl;
                    } else {
                        data.Save("Attempts", atts);
                        break;
                    }
                }
            }
            else if (choice == 2) {
                bool menu = true;                
                int choicee;
                data.Load("Theme_symbol", &close_symbol);
                while (menu) {
                    system("cls");
                    if (close_symbol == '*') {
                        text = selected_theme[0];
                    } else if (close_symbol == '?') {
                        text = selected_theme[1];
                    }else if (close_symbol == '|') {
                        text = selected_theme[2];
                    }else if (close_symbol == '^') {
                        text = selected_theme[3];
                    }else if (close_symbol == '#') {
                        text = selected_theme[4];
                    }else if (close_symbol == '$') {
                        text = selected_theme[5];
                    }else if (close_symbol == '@') {
                        text = selected_theme[6];
                    }else if (close_symbol == '_') {
                        text = selected_theme[7];
                    }else if (close_symbol == '-') {
                        text = selected_theme[8];
                    }else if (close_symbol == '&') {
                        text = selected_theme[9];
                    }
                    cout << text << endl;
                    cin >> choicee;
                    switch(choicee) {
                        case 0: {system("cls"); menu = false;}break;
                        case 1: {close_symbol = '*'; text = selected_theme[0]; data.Save("Theme_symbol", close_symbol);}break;
                        case 2: {close_symbol = '?'; text = selected_theme[1]; data.Save("Theme_symbol", close_symbol);}break;
                        case 3: {close_symbol = '|'; text = selected_theme[2]; data.Save("Theme_symbol", close_symbol);}break;
                        case 4: {close_symbol = '^'; text = selected_theme[3]; data.Save("Theme_symbol", close_symbol);}break;
                        case 5: {close_symbol = '#'; text = selected_theme[4]; data.Save("Theme_symbol", close_symbol);}break;
                        case 6: {close_symbol = '$'; text = selected_theme[5]; data.Save("Theme_symbol", close_symbol);}break;
                        case 7: {close_symbol = '@'; text = selected_theme[6]; data.Save("Theme_symbol", close_symbol);}break;
                        case 8: {close_symbol = '_'; text = selected_theme[7]; data.Save("Theme_symbol", close_symbol);}break;
                        case 9: {close_symbol = '-'; text = selected_theme[8]; data.Save("Theme_symbol", close_symbol);}break;
                        case 10: {close_symbol = '&'; text = selected_theme[9]; data.Save("Theme_symbol", close_symbol);}break;
                        default: break;
                    }
                }
            }
        }
    };

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
        data.Load("Theme_symbol", &close_symbol);
        // data.Load("Theme_text", &text);
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
            vector <char> used_letter1 = {};
            vector <char> used_letter2 = {};
            WordChoose(word1);
            WordChoose(word2);
            for (int i = 0; i < word1.length(); i++) {
                hidden_word1 += close_symbol;
            }
            for (int i = 0; i < word2.length(); i++) {
                hidden_word2 += close_symbol;
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
                            if (find(used_letter1.begin(), used_letter1.end(), letter1[0]) != used_letter1.end()) {
                                if (*find(hidden_word1.begin(), hidden_word1.end(), letter1[0]) != letter1[0]) {
                                    for (int i = 0; i < word1.length(); i++) {
                                        if (letter1[0] == word1[i]) {newWord1 += letter1[0];}
                                        else {newWord1 += hidden_word1[i];}
                                    }
                                    hidden_word1 = newWord1;
                                    cout << "Letter found!" << endl;
                                    used_letter1.push_back(letter1[0]);
                                    if (word1 == hidden_word1) {win1 = true; break;}
                                } else {cout << "Letter is already there!" << endl;}
                            } else {cout << "You've already called this letter!" << endl;}
                        } else {
                            if (find(used_letter1.begin(), used_letter1.end(), letter1[0]) != used_letter1.end()) {
                                cout << "You've already called this letter!" << endl;
                            } else {
                                tries1 -=1;
                                cout << "Letter not found!\n" << name1 << " tries: " << tries1 << endl;
                                used_letter1.push_back(letter1[0]);
                                if (LooseCheck(tries1)==true) {loose1 = true; break;}
                                fucks1++;
                            }
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
                            if (find(used_letter2.begin(), used_letter2.end(), letter2[0]) != used_letter2.end()) {
                                if (*find(hidden_word2.begin(), hidden_word2.end(), letter2[0]) != letter2[0]) {
                                    for (int i = 0; i < word2.length(); i++) {
                                        if (letter2[0] == word2[i]) {newWord2 += letter2[0];}
                                        else {newWord2 += hidden_word2[i];}
                                    }
                                    hidden_word2 = newWord2;
                                    cout << "Letter found!" << endl;
                                    used_letter2.push_back(letter2[0]);
                                    if (word2 == hidden_word2) {win2 = true; break;}
                                } else {cout << "Letter is already there!" << endl;}
                            } else {cout << "You've already called this letter!" << endl;}
                        } else {
                            if (find(used_letter2.begin(), used_letter2.end(), letter2[0]) != used_letter2.end()) {
                                cout << "You've already called this letter!" << endl;
                            } else {
                                tries2 -=1;
                                cout << "Letter not found!\n" << name2 << " tries: " << tries2 << endl;
                                used_letter2.push_back(letter2[0]);
                                if (LooseCheck(tries2)==true) {loose2 = true; break;}
                                fucks2++;
                            }
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
        data.Load("Theme_symbol", &close_symbol);
        // data.Load("Theme_text", &text);
        while (true) {
            vector <char> used_letters = {};
            system("cls");
            Load(tries, true);
            string word, closed_word, letter;
            bool loose;
            WordChoose(word);
            for (int i = 0; i < word.length(); i++) {
                closed_word += close_symbol;
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
                    if (find(used_letters.begin(), used_letters.end(), letter[0]) != used_letters.end()) {
                        cout << "You've already called this letter!" << endl;
                    }
                    else {
                        tries -= 1;
                        cout << "Letter not found!\nTries have: " << tries << endl;
                        used_letters.push_back(letter[0]);
                        if (LooseCheck(tries)==true) {break;}
                    }
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
        cout << "\nUPDATES INFO:\nv1.0\n - Game release\nv1.1\n - Fixed bug with winning with a single move\nv1.2\n - Added menu\n - `words.txt` updated(at upd moment 285 words)\n - Some phrases have been changed\n - Other bug fix\nv1.3\n - Added two player mode\n - Some phrases have been changed\n - the import of attempts has been moved to a file `settings.txt `\n - file `words.txt` renamed to 'eng_words.txt'\n - `eng_words.txt` updated(at upd moment 520)\n - added the `Settings` item for setting attempts\nv1.4 <= THIS\n - Two player mode bug fix\n - When you re-enter the letter that was named, the attempts are no longer removed" << endl;
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