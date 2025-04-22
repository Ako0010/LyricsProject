#pragma once

class ReferralCode {
private:
    string code;
    string owner;
    string usedBy;
    bool isUsed;

public:
    ReferralCode(string code = "", string owner = "")
        : code(code), owner(owner), usedBy(""), isUsed(false) {
    }

    string getCode() const { return code; }
    string getOwner() const { return owner; }
    string getUsedBy() const { return usedBy; }
    bool getStatus() const { return isUsed; }

    void markAsUsed(const string& username) {
        usedBy = username;
        isUsed = true;
    }

    void display() const {
        cout << "Referral Code: " << code << endl;
        cout << "Owner: " << owner << endl;
        if (isUsed) {
            cout << "Used By: " << usedBy << endl;
            cout << "Status: Used" << endl;
        }
        else {
            cout << "Status: Not Used" << endl;
        }
        cout << endl;
    }
};