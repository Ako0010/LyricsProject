#pragma once

class Lyric {
private:
    string name;
    string author;
    int year;
    string lyrics;

public:
    Lyric(string namee = "", string authorr = "", int yearr = 0, string lyricss = "")
        : name(namee), author(authorr), year(yearr), lyrics(lyricss) {
    }

    string getName() const { return name; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    string getLyrics() const { return lyrics; }

    void setName(string namee) { name = namee; }
    void setAuthor(string authorr) { author = authorr; }
    void setYear(int yearr) { yearr = yearr; }
    void setLyrics(string lyricss) { lyrics = lyricss; }

    void display() const {
        cout << "Song Name: " << name << endl;
        cout << "Author: " << author << endl;
        cout << "Year: " << year << endl;
        cout << "Lyrics: " << endl;
        cout << lyrics << endl << endl;
    }
};