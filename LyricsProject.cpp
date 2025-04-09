#include <iostream>
#include <string>
#include <conio.h>
#include <stdio.h>
using namespace std;
#include "Lyricsclass.h"
#include "Lyricsfunctions.h"

int main()
{
    Lyric lyrics[MAX_LYRICS];
    int lyricCount = 0;
    int highlight = 0;
    bool running = true;

    Lyric::resetIdCounter();
    lyrics[lyricCount++] = Lyric("Impossible", "James Arthur", 2013, "I remember,years ago Someone told me I should take caution when it comes to love, I did and you were strong and I was not my illiuson my mistake I was careless");
    lyrics[lyricCount++] = Lyric("Ego", "Willy William", 2016, "Miroir, dis-moi qui est le plus beau Quitte à devenir mégalo  Viens donc chatouiller mon ego Allez, allez, allez! Laisse - moi entrer dans ta matrice Goûter à tes délicesPersonne ne peut m  en dissuader Allez, allez, allez!");


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
                addLyric(lyrics, lyricCount);
                system("cls||clear");
                break;
            case 1:
            {
                string name;
                cout << "Enter song name to delete: ";
                getline(cin, name);
                deleteLyric(lyrics, lyricCount, name);
            }
            break;
            case 2:
            {
                string name;
                cout << "Enter song name to edit: ";
                getline(cin, name);
                editLyric(lyrics, lyricCount, name);
            }
            break;
            case 3:
                displayLyrics(lyrics, lyricCount);
                break;
            case 4:
            {
                string searchQuery;
                cout << "Enter author to search for: ";
                searchByAuthor(lyrics, lyricCount,searchQuery);
            }
            break;
            case 5:
            {
                string searchQuery;
                cout << "Enter keyword to search for: ";
                searchByKeyword(lyrics, lyricCount, searchQuery);
            }
            break;
            case 6:
            {
                char fileName[256];
                cout << "Enter file name to save lyrics: ";
                cin.ignore();
                cin.getline(fileName, 256);
                saveLyricsToFiles(lyrics, lyricCount);
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
