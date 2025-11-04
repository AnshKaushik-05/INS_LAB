#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int gcd(int a, int b) {
    while(b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while(exp > 0) {
        if(exp % 2 == 1) result = (result * base) % mod;
        exp = exp / 2;
        base = (base * base) % mod;
    }
    return result;
}

int modInverse(int e, int phi) {
    for(int d = 1; d < phi; d++) {
        if((e*d) % phi == 1) return d;
    }
    return -1;
}

int main() {
    int p, q;
    cout << "Enter prime 1: ";
    cin >> p;
    cout << "Enter prime 2: ";
    cin >> q;
    
    int n = p * q;
    int phi = (p-1)*(q-1);
    
    int e;
    cout << "Enter public exponent e: ";
    cin >> e;
    if(gcd(e, phi) != 1) return 0;
    
    int d = modInverse(e, phi);
    if(d == -1) return 0;
    
    string message;
    cout << "Enter plain text: ";
    cin >> message;
    
    cout << "\nEncrypting message" << endl;
    string encrypted = "";
    for(char c : message) {
        long long m = (int)c;
        long long cipher = modPow(m, e, n);
        encrypted += (char)cipher;
    }
    cout << "Encrypted message: " << encrypted << endl;
    
    cout << "\nDecrypting message" << endl;
    string decrypted = "";
    for(char c : encrypted) {
        long long cipher = (int)c;
        long long m = modPow(cipher, d, n);
        decrypted += (char)m;
    }
    cout << "Decrypted message: " << decrypted << endl;
    
    return 0;
}
