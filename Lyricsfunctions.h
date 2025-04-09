#pragma once
const int MAX_LYRICS = 100;

void displayMenu(int highlight) {
    system("cls||clear");

    cout << endl;

    string options[] = {
        "1. Add lyric",
        "2. Delete lyric",
        "3. Edit lyric",
        "4. Display all lyrics",
        "5. Search lyrics by author",
        "6. Search lyrics by keyword",
        "7. Save lyrics to file",
        "8. Exit"
    };

    for (int i = 0; i < 8; ++i) {
        if (i == highlight) {
            cout << options[i] << " <-" << endl;
        }
        else {
            cout << options[i] << endl;
        }
    }
}



bool isValidNameOrAuthor(const string& input) {
    for (size_t i = 0; i < input.length(); ++i) {
        if ((input[i] < 65 || (input[i] > 90 && input[i] < 97) || input[i] > 122) && input[i] != ' ') {
            return false;
        }
    }
}

bool isValidNumeric(const string& yearStr) {
    for (size_t i = 0; i < yearStr.length(); i++)
    {
        if (!isdigit(yearStr[i])) {
			return false;
        }
    }
	return true;
}

bool isValidYear(const string& yearStr) {
    if (yearStr.length() != 4 || !isValidNumeric(yearStr)) {
        return false;
    }

    int year = stoi(yearStr);
    return year >= 1950 && year <= 2025;
}

void addLyricFromFile(Lyric lyrics[], int& lyricCount, const char* fileName);

bool isValidChoice(const string& choice) {
    return choice == "1" || choice == "2";
}

void addLyric(Lyric lyrics[], int& lyricCount) 
{
    if (lyricCount >= MAX_LYRICS) {
		cout << "Maximum number of lyrics reached." << endl;
        return;
    }
    string choice;

    while (true) {
        cout << "Choose how to add lyrics:" << endl;
        cout << "1. Manually enter lyrics" << endl;
        cout << "2. Upload lyrics from a file" << endl;
        cout << "Enter your choice (1 or 2): ";

        getline(cin, choice);

        if (isValidChoice(choice)) {
            break;
        }
        else {
            cout << "\033[31mInvalid choice! Please enter a valid number (1 or 2).\033[0m" << endl;
        }
    }

    if (choice == "1") {
        string name, author, lyricsContent, yearStr;
        int year;

        do {
            cout << "Enter song name: ";
            getline(cin, name);
            if (!isValidNameOrAuthor(name)) {
                cout << "\033[31mInvalid name. Please enter a valid name (letters and spaces only).\033[0m" << endl;
            }
        } while (!isValidNameOrAuthor(name));

        do {
            cout << "Enter author: ";
            getline(cin, author);
            if (!isValidNameOrAuthor(author)) {
                cout << "\033[31mInvalid Author name. Please enter a valid name (letters and spaces only).\033[0m" << endl;
            }
        } while (!isValidNameOrAuthor(author));

        do {
            cout << "Enter year: ";
            getline(cin, yearStr);
            if (!isValidYear(yearStr)) {
                cout << "\033[31mInvalid year. Please enter a valid year only digits.\033[0m" << endl;
            }
        } while (!isValidYear(yearStr));

        year = stoi(yearStr);

        cout << "Enter lyrics: ";
        getline(cin, lyricsContent);

        lyrics[lyricCount++] = Lyric(name, author, year, lyricsContent);
        cout << "Lyric added!" << endl;
    }
    else if (choice == "2") {
        char fileName[256];
        cout << "Enter file name to upload lyrics from: ";
        cin.getline(fileName, 256);
        for (int i = strlen(fileName) - 1; i >= 0 && fileName[i] == ' '; i--) {
            fileName[i] = '\0';
        }
        addLyricFromFile(lyrics, lyricCount, fileName);
    }
    else {
        cout << "\033[31mInvalid choice! Returning to the menu.\033[0m" << endl;
        _getch();
    }
}

void addLyricFromFile(Lyric lyrics[], int& lyricCount, const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        cout << "\033[31mError opening file: " << fileName << "!\033[0m" << endl;
        _getch();
        return;
    }

    char buffer[1024];
    string name, author, lyricsContent;
    int year = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        name = buffer;
        name = name.substr(0, name.find('\n'));

        if (fgets(buffer, sizeof(buffer), file)) {
            author = buffer;
            author = author.substr(0, author.find('\n'));
        }

        if (fgets(buffer, sizeof(buffer), file)) {
            year = stoi(buffer);
        }

        lyricsContent.clear();
        while (fgets(buffer, sizeof(buffer), file) && buffer[0] != '\n') {
            lyricsContent += buffer;
        }

        if (lyricCount < MAX_LYRICS) {
            lyrics[lyricCount] = Lyric(name, author, year, lyricsContent);
            lyricCount++;
        }

        fgets(buffer, sizeof(buffer), file);
    }

    fclose(file);
    cout << "\033[32mLyrics successfully loaded from file!\033[0m" << endl;
}

void deleteLyric(Lyric lyrics[], int& lyricCount, const string& name) {
    for (int i = 0; i < lyricCount; ++i) {
        if (lyrics[i].getName() == name) {
            for (int j = i; j < lyricCount - 1; ++j) {
                lyrics[j] = lyrics[j + 1];
            }
            lyricCount--;
            cout << "\033[32mSuccessfully Lyric deleted!\033[0m" << endl;
            return;
        }
    }
    cout << "\033[31mLyric not found!\033[0m" << endl;
}

void editLyric(Lyric lyrics[], int lyricCount, const string& name) {
    for (int i = 0; i < lyricCount; ++i) {
        if (lyrics[i].getName() == name) {
            cout << "Editing lyric: " << lyrics[i].getName() << endl;

            string newName, newAuthor, newLyrics, yearStr;
            int newYear;

            do {
                cout << "Enter new name: ";
                getline(cin, newName);
                if (!isValidNameOrAuthor(newName)) {
                    cout << "\033[31mInvalid name. Please enter a valid name letters and spaces only.\033[0m" << endl;
                }
            } while (!isValidNameOrAuthor(newName));

            do {
                cout << "Enter new author: ";
                getline(cin, newAuthor);
                if (!isValidNameOrAuthor(newAuthor)) {
                    cout << "\033[31mInvalid Author name. Please enter a valid name letters and spaces only.\033[0m" << endl;
                }
            } while (!isValidNameOrAuthor(newAuthor));

            do {
                cout << "Enter new year: ";
                getline(cin, yearStr);
                if (!isValidYear(yearStr)) {
                    cout << "\033[31mInvalid year. Please enter a valid year only digits.\033[0m" << endl;
                }
            } while (!isValidYear(yearStr));

            newYear = stoi(yearStr);

            cout << "Enter new lyrics: ";
            getline(cin, newLyrics);

            lyrics[i].setName(newName);
            lyrics[i].setAuthor(newAuthor);
            lyrics[i].setYear(newYear);
            lyrics[i].setLyrics(newLyrics);

            cout << "Lyric updated!" << endl;
            return;
        }
    }

    cout << "\033[31mLyric not found!\033[0m" << endl;
    _getch();
}

void displayLyrics(Lyric lyrics[], int lyricCount) {
    if (lyricCount == 0) {
        cout << "\033[31mNo lyrics available.\033[0m" << endl;
        _getch();
        return;
    }

    cout << "Displaying all lyrics:" << endl;
    for (int i = 0; i < lyricCount; ++i) {
        lyrics[i].display();
    }

    cout << "Press Enter to return to the menu..." << endl;
    int ch = _getch();
    if (ch == 13) {
        return;
    }
}

bool isValidChar(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

bool toLower(char& ch) {
    if (ch >= 'A' && ch <= 'Z') {
        ch += 32;
        return true;
    }
    return false;
}

bool containsSubstring(const string& str, const string& searchQuery) {

    if (searchQuery.length() > str.length()) {
        return false;
    }

    string strLower = str;
    string queryLower = searchQuery;

    for (int i = 0; i < strLower.length(); ++i) {
        toLower(strLower[i]);
    }

    for (int i = 0; i < queryLower.length(); ++i) {
        toLower(queryLower[i]);
    }

    for (size_t i = 0; i <= strLower.length() - queryLower.length(); ++i) {
        bool match = true;
        for (size_t j = 0; j < queryLower.length(); ++j) {
            if (strLower[i + j] != queryLower[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            return true;
        }
    }
    return false;
}

void searchByAuthor(Lyric lyrics[], int lyricCount, string& searchQuery) {
    while (true) {
        system("cls||clear");
        cout << "\033[33mIf you want to exit, press the Esc key.\033[0m" << std::endl;
        cout << endl;


        bool foundAuthor = false;
        for (int i = 0; i < lyricCount; ++i) {
            if (containsSubstring(lyrics[i].getAuthor(), searchQuery)) {
                lyrics[i].display();
                foundAuthor = true;
            }
        }

        if (!foundAuthor) {
            cout << "\033[31mNo lyrics found for this author.\033[0m" << endl;

        }

        cout << "Search author: ";
        for (size_t i = 0; i < searchQuery.length(); ++i) {
            cout << searchQuery[i];
        }

        char ch = _getch();

        if (ch == 27) {
            break;
        }
        else if (ch == 8 && searchQuery.length() > 0) {
            searchQuery.pop_back();
        }
        else if (isValidChar(ch) && ch != ' ') {
            searchQuery += ch;
        }
        else if (ch == ' ') {
            searchQuery += ' ';
        }
    }
}

void searchByKeyword(Lyric lyrics[], int lyricCount, string& searchQuery) {
    while (true) {
        system("cls||clear");
        cout << "\033[33mIf you want to exit, press the Esc key.\033[0m" << std::endl;
        cout << endl;

        bool foundKeyword = false;
        for (int i = 0; i < lyricCount; ++i) {
            if (containsSubstring(lyrics[i].getLyrics(), searchQuery)) {
                lyrics[i].display();
                foundKeyword = true;
            }
        }

        if (!foundKeyword) {
            cout << "\033[31mNo lyrics found with this keyword.\033[0m" << endl;
        }

        cout << "Search keyword: ";
        for (size_t i = 0; i < searchQuery.length(); ++i) {
            cout << searchQuery[i];
        }

        char ch = _getch();

        if (ch == 27) {
            break;
        }
        else if (ch == 8 && searchQuery.length() > 0) {
            searchQuery.pop_back();
        }
        else if (isValidChar(ch) && ch != ' ') {
            searchQuery += ch;
        }
        else if (ch == ' ') {
            searchQuery += ' ';
        }
    }
}