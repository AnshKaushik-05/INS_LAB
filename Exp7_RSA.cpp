#include <bits/stdc++.h>
using namespace std;

long long mod_pow(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

int main() {
    long long e, d, n;
    cout << "Enter public key (e, n): ";
    cin >> e >> n;
    cout << "Enter private key (d, n): ";
    cin >> d >> n;

    long long message;
    cout << "\nEnter message (number < " << n << "): ";
    cin >> message;

    long long encrypted = mod_pow(message, e, n);
    long long decrypted = mod_pow(encrypted, d, n);

    cout << "\nEncrypted message: " << encrypted << endl;
    cout << "Decrypted message: " << decrypted << endl;

    return 0;
}