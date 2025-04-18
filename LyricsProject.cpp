#include <iostream>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <fstream>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;
#include "Lyricsclass.h"
#include "Lyricsfunctions.h"


int main()
{
    Lyric lyrics[MAX_LYRICS];
    int lyricCount = 0;
    int highlight = 0;
    bool running = true;

    Lyric::resetIdCounter();


    while (running) {
        system("cls||clear");
        displayMenu(highlight);

        int ch = _getch();
        if (ch == 72) {
            highlight = (highlight - 1 + 7) % 7;
        }
        else if (ch == 80) {
            highlight = (highlight + 1) % 7;
        }
        else if (ch == 13) {
            system("cls||clear");
            switch (highlight) {
            case 0:
                addLyric(lyrics, lyricCount);
                system("cls||clear");
                break;
            case 1:
            {
                string name;
                cout << "Enter song name to delete: ";
                getline(cin, name);
                loadFromJson(lyrics, lyricCount);
                deleteLyric(lyrics, lyricCount, name);
            }
            break;
            case 2:
            {
                string name;
                cout << "Enter song name to edit: ";
                getline(cin, name);
                loadFromJson(lyrics, lyricCount);
                editLyric(lyrics, lyricCount, name);
            }
            break;
            case 3:
                loadFromJson(lyrics, lyricCount);
                displayLyrics(lyrics, lyricCount);
                break;
            case 4:
            {
                string searchQuery;
                cout << "Enter author to search for: ";
                loadFromJson(lyrics, lyricCount);
                searchByAuthor(lyrics, lyricCount,searchQuery);
            }
            break;
            case 5:
            {
                string searchQuery;
                cout << "Enter keyword to search for: ";
                loadFromJson(lyrics, lyricCount);
                searchByKeyword(lyrics, lyricCount, searchQuery);
            }
            break;
            case 6:
                running = false;
                cout << "\033[38;5;135mSee you again, my friend ;)\033[0m" << endl;
                break;
            }
        }
    }


	return 0;
}
