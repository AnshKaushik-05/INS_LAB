#include <iostream>
#include <string>
using namespace std;

string generateKey(const string &text, const string &key) {
    string newKey = "";
    int j = 0;
    for (char c : text) {
        if (isalpha(c)) {
            newKey += toupper(key[j % key.size()]);
            j++;
        } else {
            newKey += c; // preserve spaces/punctuation
        }
    }
    return newKey;
}

string vigenereEncrypt(const string &text, const string &key) {
    string result = "";
    for (int i = 0; i < text.size(); i++) {
        char c = text[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char k = toupper(key[i]) - 'A';
            result += char((toupper(c) - 'A' + k) % 26 + base);
        } else {
            result += c;
        }
    }
    return result;
}

string vigenereDecrypt(const string &cipher, const string &key) {
    string result = "";
    for (int i = 0; i < cipher.size(); i++) {
        char c = cipher[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char k = toupper(key[i]) - 'A';
            result += char((toupper(c) - 'A' - k + 26) % 26 + base);
        } else {
            result += c;
        }
    }
    return result;
}

int main() {
    string text, key;
    cout << "Enter message: ";
    getline(cin, text);
    cout << "Enter key: ";
    getline(cin, key);

    string newKey = generateKey(text, key);
    string encrypted = vigenereEncrypt(text, newKey);
    cout << "\nEncrypted: " << encrypted;

    string decrypted = vigenereDecrypt(encrypted, newKey);
    cout << "\nDecrypted: " << decrypted << endl;

    return 0;
}
