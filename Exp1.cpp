#include <iostream>
#include <string>
using namespace std;

string encrypt(string text, int shift) {
    string result = "";
    for (char c : text) {
        if (isupper(c)) {
            result += char(int(c + shift - 'A') % 26 + 'A');
        } else if (islower(c)) {
            result += char(int(c + shift - 'a') % 26 + 'a');
        } else {
            result += c; // non-alphabetic characters unchanged
        }
    }
    return result;
}

string decrypt(string text, int shift) {
    return encrypt(text, 26 - (shift % 26));
}

int main() {
    string text;
    int shift;

    cout << "Enter the text: ";
    getline(cin, text);

    cout << "Enter shift value: ";
    cin >> shift;

    string encrypted = encrypt(text, shift);
    string decrypted = decrypt(encrypted, shift);

    cout << "\nOriginal Text: " << text;
    cout << "\nEncrypted Text: " << encrypted;
    cout << "\nDecrypted Text: " << decrypted << endl;

    return 0;
}
