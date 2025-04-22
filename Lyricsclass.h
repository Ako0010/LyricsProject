#pragma once

class Lyric {
private:
    static int nextId;
    int id;
    string name;
    string author;
    int year;
    string lyrics;

public:
    Lyric(string namee = "", string authorr = "", int yearr = 0, string lyricss = "")
        : name(namee), author(authorr), year(yearr), lyrics(lyricss) {
		id = nextId++;
    }

    string getName() const { return name; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    string getLyrics() const { return lyrics; }
    int getId() const { return id; }

    void setName(string namee) { name = namee; }
    void setAuthor(string authorr) { author = authorr; }
    void setYear(int yearr) { year = yearr; }
    void setLyrics(string lyricss) { lyrics = lyricss; }

     void display() const {
        cout << "Song Name: " << name << endl;
        cout << "Author: " << author << endl;
        cout << "Year: " << year << endl;
        cout << "Lyrics: " << endl;
        cout << lyrics << endl << endl;
    }


    static int getIdCounter() {
        return nextId;
    }

    static void setIdCounter(int newId) {
        nextId = newId;
    }

    static int resetIdCounter() {
		nextId = 0;
		return nextId;
    }
};

int Lyric::nextId = 0;
