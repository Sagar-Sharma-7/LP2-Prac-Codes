#include <iostream>
#include <string>
using namespace std;

// XOR function
string xorOperation(string a, string b) {

    string result = "";

    for(int i = 0; i < a.length(); i++) {

        if(a[i] == b[i])
            result += '0';
        else
            result += '1';
    }

    return result;
}

// Expansion function (4 bits -> 8 bits)
string expansion(string right) {

    return "" + string(1, right[0]) +
           string(1, right[1]) +
           string(1, right[2]) +
           string(1, right[3]) +
           string(1, right[0]) +
           string(1, right[1]) +
           string(1, right[2]) +
           string(1, right[3]);
}

// Improved S-Box (all 4-bit cases)
string sbox(string bits) {

    if(bits == "0000") return "111";
    if(bits == "0001") return "010";
    if(bits == "0010") return "001";
    if(bits == "0011") return "110";
    if(bits == "0100") return "011";
    if(bits == "0101") return "100";
    if(bits == "0110") return "101";
    if(bits == "0111") return "000";

    if(bits == "1000") return "110";
    if(bits == "1001") return "101";
    if(bits == "1010") return "011";
    if(bits == "1011") return "001";

    if(bits == "1100") return "100";
    if(bits == "1101") return "010";
    if(bits == "1110") return "000";
    if(bits == "1111") return "111";

    return "000";
}

// Feistel Function
string feistel(string right, string key) {

    cout << "\nRight Half: " << right << endl;

    // Expansion
    string expanded = expansion(right);

    cout << "Expanded:   " << expanded << endl;

    // XOR
    string xored = xorOperation(expanded, key);

    cout << "After XOR:  " << xored << endl;

    // Split into two halves
    string leftPart = xored.substr(0,4);
    string rightPart = xored.substr(4,4);

    // S-Box
    string s1 = sbox(leftPart);
    string s2 = sbox(rightPart);

    string sboxOutput = s1 + s2;

    cout << "S-Box Out:  " << sboxOutput << endl;

    return sboxOutput;
}

int main() {

    string plaintext;
    string key;

    cout << "Enter 8-bit plaintext: ";
    cin >> plaintext;

    cout << "Enter 8-bit key: ";
    cin >> key;

    // Split plaintext
    string left = plaintext.substr(0,4);
    string right = plaintext.substr(4,4);

    cout << "\nInitial Left  : " << left << endl;
    cout << "Initial Right : " << right << endl;

    // ================= ENCRYPTION =================

    // Round 1
    string temp = right;

    string fOutput = feistel(right, key);

    right = xorOperation(left, fOutput);

    left = temp;

    cout << "\nAfter Round 1" << endl;
    cout << "Left  : " << left << endl;
    cout << "Right : " << right << endl;

    // Round 2
    temp = right;

    fOutput = feistel(right, key);

    right = xorOperation(left, fOutput);

    left = temp;

    cout << "\nAfter Round 2" << endl;
    cout << "Left  : " << left << endl;
    cout << "Right : " << right << endl;

    // Ciphertext
    string cipher = left + right;

    cout << "\nEncrypted Text: " << cipher << endl;

    // ================= DECRYPTION =================

    cout << "\n========== DECRYPTION ==========" << endl;

    // Split cipher text
    left = cipher.substr(0,4);
    right = cipher.substr(4,4);

    cout << "\nCipher Left  : " << left << endl;
    cout << "Cipher Right : " << right << endl;

    // Reverse Round 2
    temp = left;

    fOutput = feistel(left, key);

    left = xorOperation(right, fOutput);

    right = temp;

    cout << "\nAfter Reverse Round 2" << endl;
    cout << "Left  : " << left << endl;
    cout << "Right : " << right << endl;

    // Reverse Round 1
    temp = left;

    fOutput = feistel(left, key);

    left = xorOperation(right, fOutput);

    right = temp;

    cout << "\nAfter Reverse Round 1" << endl;
    cout << "Left  : " << left << endl;
    cout << "Right : " << right << endl;

    // Final Plaintext
    string decrypted = left + right;

    cout << "\nDecrypted Text: " << decrypted << endl;

    return 0;
}
