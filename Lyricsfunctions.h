#pragma once
#pragma warning(disable : 6031)
#pragma warning(disable : 4996)
const int MAX_LYRICS = 100;
#define JSON_FILE "lyrics.json"

void displayMenu(int highlight) {
    system("cls||clear");

    cout << "\033[32m           _  __  ____            _      __     __ _____   _____   _____   _____" << endl;
    cout << "    /\\    | |/ / / __ \\          | |     \\ \\   / /|  __ \\ |_   _| / ____| / ____|" << endl;
    cout << "   /  \\   | ' / | |  | |         | |      \\ \\_/ / | |__) |  | |  | |     | (___" << endl;
    cout << "  / /\\ \\  |  <  | |  | |         | |       \\   /  |  _  /   | |  | |      \\___ \\" << endl;
    cout << " / ____ \\ | . \\ | |__| |         | |____    | |   | | \\ \\  _| |_ | |____  ____) |" << endl;
    cout << "/_/    \\_\\|_|\\_\\ \\____/          |______|   |_|   |_|  \\_\\|_____| \\_____||_____/\033[0m" << endl;

    cout << endl;

    cout << endl;

    string options[] = {
        "1. Add lyric",
        "2. Delete lyric",
        "3. Edit lyric",
        "4. Display all lyrics",
        "5. Search lyrics by author",
        "6. Search lyrics by keyword",
        "7. Referral Code",
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


bool isValidChoice(const string& choice) {
    return choice == "1" || choice == "2";
}

void saveToJson(const Lyric lyrics[], int lyricCount) {

    if (lyricCount == 0) {
        cout << "\033[33mNo lyrics to save (array is empty).\033[0m" << endl;
        return;
    }


    FILE* file = fopen(JSON_FILE, "w");
    if (!file) {
        cout << "\033[31mError: Could not open file for writing!\033[0m" << endl;
        return;
    }

    json jArray = json::array();
    for (int i = 0; i < lyricCount; ++i) {
        json jLyric;
        jLyric["id"] = lyrics[i].getId();
        jLyric["name"] = lyrics[i].getName();
        jLyric["author"] = lyrics[i].getAuthor();
        jLyric["year"] = lyrics[i].getYear();
        jLyric["lyrics"] = lyrics[i].getLyrics();
        jArray.push_back(jLyric);
    }


    string jsonString = jArray.dump(4);


    for (size_t i = 0; i < jsonString.length(); ++i) {
        fputc(jsonString[i], file);
    }


    fclose(file);


    cout << "\033[32mLyrics saved to " << JSON_FILE << "!\033[0m" << endl;
}


void loadFromJson(Lyric lyrics[], int& lyricCount) {
    ifstream file(JSON_FILE);
    if (!file.is_open()) {
        cout << "\033[31mNo existing data file found. Starting fresh.\033[0m" << endl;
        lyricCount = 0;
        return;
    }

    string fullBuffer;
    string line;
    while (getline(file, line)) {
        fullBuffer += line + "\n";
    }
    file.close();

    if (fullBuffer.empty()) {
        cout << "\033[31mFile is empty. Starting fresh.\033[0m" << endl;
        lyricCount = 0;
        return;
    }

    if (!json::accept(fullBuffer)) {
        cout << "\033[31mError: Invalid JSON format in file!\033[0m" << endl;
        lyricCount = 0;
        return;
    }

    json jArray = json::parse(fullBuffer);
    int currentNextId = Lyric::getIdCounter();

    for (const auto& jLyric : jArray) {
        if (lyricCount >= MAX_LYRICS) {
            cout << "\033[31mMaximum number of lyrics reached while loading!\033[0m" << endl;
            break;
        }

        if (jLyric.contains("id") && jLyric.contains("name") && jLyric.contains("author") &&
            jLyric.contains("year") && jLyric.contains("lyrics")) {

            bool alreadyExists = false;
            for (int i = 0; i < lyricCount; ++i) {
                if (lyrics[i].getId() == jLyric["id"]) {
                    alreadyExists = true;
                    break;
                }
            }

            if (!alreadyExists) {
                string name = jLyric["name"];
                string author = jLyric["author"];
                int year = jLyric["year"];
                string lyricsText = jLyric["lyrics"];

                lyrics[lyricCount] = Lyric(name, author, year, lyricsText);
                lyricCount++;

                if (lyrics[lyricCount - 1].getId() >= currentNextId) {
                    currentNextId = lyrics[lyricCount - 1].getId() + 1;
                }
            }
        }
        else {
            cout << "\033[33mWarning: Skipping an entry with missing fields.\033[0m" << endl;
        }
    }

    Lyric::setIdCounter(currentNextId);
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
        cout << "2. Exit" << endl;
        cout << "Enter your choice 1,or 2 : ";

        getline(cin, choice);

        if (isValidChoice(choice)) {
            break;
        }
        else {
            cout << "\033[31mInvalid choice! Please enter a valid number (1 or 2 3).\033[0m" << endl;
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
        saveToJson(lyrics, lyricCount);
        cout << "Lyric added!" << endl;
    }
	else if (choice == "2") {
		return;
	}
    else {
        cout << "\033[31mInvalid choice! Returning to the menu.\033[0m" << endl;
        _getch();
    }
}


void deleteLyric(Lyric lyrics[], int& lyricCount, const string& name) {
    for (int i = 0; i < lyricCount; ++i) {
        if (lyrics[i].getName() == name) {
            for (int j = i; j < lyricCount - 1; ++j) {
                lyrics[j] = lyrics[j + 1];
            }
            lyricCount--;

            saveToJson(lyrics, lyricCount);
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

            saveToJson(lyrics, lyricCount);
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

    srand(static_cast<unsigned int>(time(0)));

    int displayCount = lyricCount < 3 ? lyricCount : 3;

    cout << "Displaying all lyrics:" << endl;

    bool used[100] = { false };

    int count = 0;
    while (count < displayCount) {
        int randIndex = rand() % lyricCount;
        if (!used[randIndex]) {
            lyrics[randIndex].display();
            used[randIndex] = true;
            count++;
        }
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


