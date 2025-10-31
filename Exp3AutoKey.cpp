#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string encrypt(const string &plaintext, const string &keyword) {
    string key = "";
    for (char c : keyword)
        if (isalpha(c))
            key += toupper(c);

    int keyIndex = 0;
    string ciphertext = "";

    for (char c : plaintext) {
        if (isalpha(c)) {
            char p = toupper(c) - 'A';
            char k = toupper(key[keyIndex]) - 'A';
            char enc = (p + k) % 26 + 'A';
            ciphertext += islower(c) ? tolower(enc) : enc;
            key += toupper(c);  // Autokey extension
            keyIndex++;
        } else {
            ciphertext += c;
        }
    }
    return ciphertext;
}

string decrypt(const string &ciphertext, const string &keyword) {
    string key = "";
    for (char c : keyword)
        if (isalpha(c))
            key += toupper(c);

    int keyIndex = 0;
    string plaintext = "";

    for (char c : ciphertext) {
        if (isalpha(c)) {
            char ciph = toupper(c) - 'A';
            char k = toupper(key[keyIndex]) - 'A';
            char dec = (ciph - k + 26) % 26 + 'A';
            plaintext += islower(c) ? tolower(dec) : dec;
            key += dec;  // Add decrypted char to key
            keyIndex++;
        } else {
            plaintext += c;
        }
    }
    return plaintext;
}

int main() {
    string message, keyword;
    cout << "Enter message: ";
    getline(cin, message);
    cout << "Enter keyword: ";
    cin >> keyword;

    string enc = encrypt(message, keyword);
    cout << "\nEncrypted: " << enc;

    string dec = decrypt(enc, keyword);
    cout << "\nDecrypted: " << dec << endl;

    return 0;
}
