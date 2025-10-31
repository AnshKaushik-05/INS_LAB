#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

char keyMatrix[5][5];

void generateKeyMatrix(string key) {
    bool used[26] = {false};
    used['J' - 'A'] = true;
    int row = 0, col = 0;

    for (char c : key) {
        c = toupper(c);
        if (c == 'J') c = 'I';
        if (!used[c - 'A']) {
            keyMatrix[row][col++] = c;
            used[c - 'A'] = true;
            if (col == 5) { row++; col = 0; }
        }
    }

    for (char c = 'A'; c <= 'Z'; c++) {
        if (!used[c - 'A']) {
            keyMatrix[row][col++] = c;
            used[c - 'A'] = true;
            if (col == 5) { row++; col = 0; }
        }
    }
}

void displayMatrix() {
    cout << "Key Matrix:\n";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) cout << keyMatrix[i][j] << " ";
        cout << endl;
    }
}

pair<int, int> getPosition(char c) {
    if (c == 'J') c = 'I';
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (keyMatrix[i][j] == c)
                return {i, j};
    return {-1, -1};
}

string encryptDigraph(char a, char b) {
    auto p1 = getPosition(a);
    auto p2 = getPosition(b);
    if (p1.first == p2.first)
        return {keyMatrix[p1.first][(p1.second + 1) % 5],
                keyMatrix[p2.first][(p2.second + 1) % 5]};
    else if (p1.second == p2.second)
        return {keyMatrix[(p1.first + 1) % 5][p1.second],
                keyMatrix[(p2.first + 1) % 5][p2.second]};
    else
        return {keyMatrix[p1.first][p2.second],
                keyMatrix[p2.first][p1.second]};
}

string decryptDigraph(char a, char b) {
    auto p1 = getPosition(a);
    auto p2 = getPosition(b);
    if (p1.first == p2.first)
        return {keyMatrix[p1.first][(p1.second + 4) % 5],
                keyMatrix[p2.first][(p2.second + 4) % 5]};
    else if (p1.second == p2.second)
        return {keyMatrix[(p1.first + 4) % 5][p1.second],
                keyMatrix[(p2.first + 4) % 5][p2.second]};
    else
        return {keyMatrix[p1.first][p2.second],
                keyMatrix[p2.first][p1.second]};
}

string preprocessForEncryption(string text) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            c = toupper(c);
            if (c == 'J') c = 'I';
            result += c;
        }
    }

    string modified = "";
    for (size_t i = 0; i < result.length(); i++) {
        modified += result[i];
        if (i + 1 < result.length() && result[i] == result[i + 1])
            modified += 'X';
    }
    if (modified.length() % 2 != 0)
        modified += 'X';
    return modified;
}

string encrypt(string plaintext) {
    string processed = preprocessForEncryption(plaintext);
    string cipher = "";
    for (size_t i = 0; i < processed.length(); i += 2)
        cipher += encryptDigraph(processed[i], processed[i + 1]);
    return cipher;
}

string decrypt(string ciphertext, const string &original) {
    string plain = "";
    for (size_t i = 0; i < ciphertext.length(); i += 2)
        plain += decryptDigraph(ciphertext[i], ciphertext[i + 1]);

    // Remove filler 'X' used during encryption
    string cleaned = "";
    for (size_t i = 0; i < plain.size(); i++) {
        if (i > 0 && plain[i] == 'X' && plain[i - 1] == plain[i + 1])
            continue;
        cleaned += plain[i];
    }
    if (!cleaned.empty() && cleaned.back() == 'X')
        cleaned.pop_back();

    // Restore case and spaces from original text
    string finalText = "";
    size_t j = 0;
    for (char c : original) {
        if (isalpha(c)) {
            finalText += islower(c) ? tolower(cleaned[j++]) : cleaned[j++];
        } else {
            finalText += c;
        }
    }
    return finalText;
}

int main() {
    string key, text;
    cout << "Enter key: ";
    cin >> key;
    generateKeyMatrix(key);
    displayMatrix();

    cout << "\nEnter text: ";
    cin.ignore();
    getline(cin, text);

    string encrypted = encrypt(text);
    string decrypted = decrypt(encrypted, text);

    cout << "\nOriginal Text : " << text;
    cout << "\nEncrypted Text: " << encrypted;
    cout << "\nDecrypted Text: " << decrypted << endl;
    return 0;
}
