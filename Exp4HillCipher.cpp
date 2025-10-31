#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

int determinant(vector<vector<int>> key) {
    return (key[0][0]*key[1][1] - key[0][1]*key[1][0]) % 26;
}

int modInverse(int a, int m=26) {
    a = (a % m + m) % m;
    for (int x=1; x<m; x++) if ((a*x)%m==1) return x;
    return -1;
}

string toUpperLetters(const string &text, vector<int> &positions) {
    string result;
    for (int i=0; i<text.size(); i++)
        if (isalpha(text[i])) { result += toupper(text[i]); positions.push_back(i); }
    if (result.size()%2!=0) result += 'X';
    return result;
}

string encryptBlock(const string &plain, vector<vector<int>> key) {
    string cipher;
    for (int i=0; i<plain.size(); i+=2) {
        int a = plain[i]-'A', b = plain[i+1]-'A';
        int c1 = (key[0][0]*a + key[0][1]*b) % 26;
        int c2 = (key[1][0]*a + key[1][1]*b) % 26;
        cipher += (c1+'A'); cipher += (c2+'A');
    }
    return cipher;
}

string decryptBlock(const string &cipher, vector<vector<int>> key, bool padded) {
    int det = determinant(key), invDet = modInverse(det);
    vector<vector<int>> invKey(2, vector<int>(2));
    invKey[0][0]=key[1][1]; invKey[1][1]=key[0][0];
    invKey[0][1]=-key[0][1]; invKey[1][0]=-key[1][0];
    for(int i=0;i<2;i++) for(int j=0;j<2;j++)
        invKey[i][j]=((invKey[i][j]*invDet)%26+26)%26;
    string dec;
    for(int i=0;i<cipher.size();i+=2){
        int a=cipher[i]-'A',b=cipher[i+1]-'A';
        int p1=(invKey[0][0]*a+invKey[0][1]*b)%26;
        int p2=(invKey[1][0]*a+invKey[1][1]*b)%26;
        dec+=(p1+'A'); dec+=(p2+'A');
    }
    if(padded) dec.pop_back();
    return dec;
}

int main() {
    string plaintext;
    cout << "Enter plaintext: ";
    getline(cin, plaintext);

    vector<vector<int>> key={{3,3},{2,5}};
    vector<int> positions;
    string upper = toUpperLetters(plaintext, positions);
    bool padded = (upper.size()%2!=0);
    string cipher = encryptBlock(upper, key);
    string decrypted = decryptBlock(cipher, key, padded);

    string finalDecrypted = plaintext;
    for(int i=0;i<positions.size();i++){
        char c = decrypted[i];
        if(islower(plaintext[positions[i]])) c = tolower(c);
        finalDecrypted[positions[i]] = c;
    }

    cout << "\nOriginal Message: " << plaintext;
    cout << "\nEncrypted Text  : " << cipher;
    cout << "\nDecrypted Text  : " << finalDecrypted << endl;
    return 0;
}
