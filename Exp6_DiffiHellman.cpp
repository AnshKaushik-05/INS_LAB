#include <bits/stdc++.h>
using namespace std;

using u128 = unsigned long long;

// Modular exponentiation function: (a^e) % m
u128 modexp(u128 a, u128 e, u128 m)
{
    u128 r = 1;
    while (e)
    {
        if (e & 1)
            r = (r * a) % m;   // multiply when the bit is 1
        a = (a * a) % m;       // square base
        e >>= 1;               // shift exponent right
    }
    return r;
}

int main()
{
    // --- Input section ---
    u128 p, g; // Public parameters
    u128 a, b; // Private keys

    cout << "Enter prime number p: ";
    cin >> p;
    cout << "Enter primitive root g: ";
    cin >> g;
    cout << "Enter private key of A: ";
    cin >> a;
    cout << "Enter private key of B: ";
    cin >> b;

    // --- Diffie–Hellman computation ---
    u128 A = modexp(g, a, p); // A sends this
    u128 B = modexp(g, b, p); // B sends this

    // Each computes the shared key
    u128 Ka = modexp(B, a, p); // A’s key
    u128 Kb = modexp(A, b, p); // B’s key

    // --- Output section ---
    cout << "\n--- Diffie-Hellman Key Exchange ---\n";
    cout << "Public parameters: p = " << p << ", g = " << g << "\n";
    cout << "A sends: " << A << "\n";
    cout << "B sends: " << B << "\n";
    cout << "Shared key computed by A: " << Ka << "\n";
    cout << "Shared key computed by B: " << Kb << "\n";

    if (Ka == Kb)
        cout << "\n Shared key match confirmed!\n";
    else
        cout << "\n Shared key mismatch!\n";

    return 0;
}