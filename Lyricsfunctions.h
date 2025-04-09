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