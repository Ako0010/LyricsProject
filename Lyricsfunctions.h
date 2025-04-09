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