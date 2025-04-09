#pragma once

bool isValidNameOrAuthor(const string& input) {
    for (size_t i = 0; i < input.length(); ++i) {
        if ((input[i] < 65 || (input[i] > 90 && input[i] < 97) || input[i] > 122) && input[i] != ' ') {
            return false;
        }
    }
}