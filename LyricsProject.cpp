#include <iostream>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;
#include "Lyricsclass.h"
#include "Lyricsfunctions.h"
#include "Lyricsreferralcode.h"
using namespace LyricsProject;


int main()
{
    vector<Lyric> lyrics;
    int lyricCount = 0;
    int highlight = 0;
    bool running = true;

    Lyric::resetIdCounter();

    ReferralCode code1("isaaholic", "Isa Mammadli");
    ReferralCode code2("AZE9999", "Ako");


    while (running) {
        system("cls||clear");
        displayMenu(highlight);

        int ch = _getch();
        if (ch == 72) {
            highlight = (highlight - 1 + 8) % 8;
        }
        else if (ch == 80) {
            highlight = (highlight + 1) % 8;
        }
        else if (ch == 13) {
            system("cls||clear");
            switch (highlight) {
            case 0:
                addLyric(lyrics);
                system("cls||clear");
                break;
            case 1:
            {
                string name;
                cout << "Enter song name to delete: ";
                getline(cin, name);
                loadFromJson(lyrics);
                deleteLyric(lyrics, name);
            }
            break;
            case 2:
            {
                string name;
                cout << "Enter song name to edit: ";
                getline(cin, name);
                loadFromJson(lyrics);
                editLyric(lyrics, name);
            }
            break;
            case 3:
                loadFromJson(lyrics);
                displayLyrics(lyrics);
                break;
            case 4:
            {
                string searchQuery;
                cout << "Enter author to search for: ";
                loadFromJson(lyrics);
                searchByAuthor(lyrics,searchQuery);
            }
            break;
            case 5:
            {
                string searchQuery;
                cout << "Enter keyword to search for: ";
                loadFromJson(lyrics);
                searchByKeyword(lyrics, searchQuery);
            }
            break;
            case 6: {
                string inputCode, username;
                cout << "Enter referral code: ";
                getline(cin, inputCode);
                cout << "Enter your username: ";
                getline(cin, username);

                if (code1.getCode() == inputCode) {
                    if (code1.getStatus()) {
                        cout << "Code already used by: " << code1.getUsedBy() << endl;
                        _getch();
                    }
                    else {
                        code1.markAsUsed(username);
                        cout << "Code successfully used!" << endl;
                        cout << endl;
                        code1.display();
                        _getch();
                    }
                }
                else if (code2.getCode() == inputCode) {
                    if (code2.getStatus()) {
                        cout << "Code already used by: " << code2.getUsedBy() << endl;
                        _getch();
                    }
                    else {
                        code2.markAsUsed(username);
                        cout << "Code successfully used!" << endl;
                        _getch();
                        code2.display();
                        _getch();
                    }
                }
                else {
                    cout << "Referral code not found!" << endl;
                    _getch();
                }


                
            }
                break;
            case 7:
                running = false;
                cout << "\033[38;5;135mSee you again, my friend ;)\033[0m" << endl;
                break;
            }
        }
    }


	return 0;
}
