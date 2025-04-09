#pragma once

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