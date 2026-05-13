#include <iostream>
#include <cmath>
#include <string>
using namespace std;

// GCD Function
int gcd(int a, int b) {

    while(b != 0) {

        int temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

// Modular Exponentiation
long long modPower(long long base,
                   long long exponent,
                   long long mod) {

    long long result = 1;

    while(exponent > 0) {

        result = (result * base) % mod;

        exponent--;
    }

    return result;
}

int main() {

    int p, q;

    cout << "Enter prime number p: ";
    cin >> p;

    cout << "Enter prime number q: ";
    cin >> q;

    // Calculate n
    int n = p * q;

    cout << "\nn = p * q = "
         << p << " * "
         << q << " = "
         << n << endl;

    // Calculate phi
    int phi = (p - 1) * (q - 1);

    cout << "phi(n) = "
         << phi << endl;

    // Choose e
    int e;

    cout << "\nEnter e: ";
    cin >> e;

    while(gcd(e, phi) != 1) {

        cout << "Invalid e. Enter again: ";
        cin >> e;
    }

    // Calculate d
    int d;

    for(d = 1; d < phi; d++) {

        if((d * e) % phi == 1)
            break;
    }

    cout << "\nPublic Key  : ("
         << e << "," << n << ")" << endl;

    cout << "Private Key : ("
         << d << "," << n << ")" << endl;

    // Hex plaintext
    string plaintext;

    cout << "\nEnter hexadecimal plaintext: ";
    cin >> plaintext;

    // Convert hex string to decimal
    long long message =
        stoll(plaintext, nullptr, 16);

    cout << "\nHexadecimal Plaintext: "
         << plaintext << endl;

    cout << "Decimal Value: "
         << message << endl;

    // Check range
    if(message >= n) {

        cout << "\nMessage must be smaller than n." << endl;

        cout << "Choose larger prime numbers." << endl;

        return 0;
    }

    // Encryption
    cout << "\n========== ENCRYPTION ==========" << endl;

    cout << "C = M^e mod n" << endl;

    long long cipher =
        modPower(message, e, n);

    cout << "Ciphertext: "
         << cipher << endl;

    // Decryption
    cout << "\n========== DECRYPTION ==========" << endl;

    cout << "M = C^d mod n" << endl;

    long long decrypted =
        modPower(cipher, d, n);

    cout << "Decrypted Decimal: "
         << decrypted << endl;

    cout << "Decrypted Hexadecimal: "
         << hex << uppercase
         << decrypted << endl;

    return 0;
}