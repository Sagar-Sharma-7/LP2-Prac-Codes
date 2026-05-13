#include <iostream>
#include <string>
using namespace std;

// S-Box
char sbox[4][4] = {

    {'A','B','C','D'},
    {'E','F','0','1'},
    {'2','3','4','5'},
    {'6','7','8','9'}
};

// Convert hex char to integer
int hexToInt(char ch) {

    if(ch >= '0' && ch <= '9')
        return ch - '0';

    return ch - 'A' + 10;
}

// Convert integer to hex char
char intToHex(int num) {

    if(num < 10)
        return num + '0';

    return num - 10 + 'A';
}

// Substitute using S-Box
char substitute(char ch) {

    int value = hexToInt(ch);

    int row = value / 4;
    int col = value % 4;

    return sbox[row][col];
}

// Reverse Substitute
char reverseSubstitute(char ch) {

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {

            if(sbox[i][j] == ch) {

                int value = i * 4 + j;

                return intToHex(value);
            }
        }
    }

    return ch;
}

// SubBytes
void subBytes(char state[2][2]) {

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {

            state[i][j] = substitute(state[i][j]);
        }
    }
}

// Reverse SubBytes
void reverseSubBytes(char state[2][2]) {

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {

            state[i][j] = reverseSubstitute(state[i][j]);
        }
    }
}

// ShiftRows
void shiftRows(char state[2][2]) {

    swap(state[1][0], state[1][1]);
}

// Reverse ShiftRows
void reverseShiftRows(char state[2][2]) {

    swap(state[1][0], state[1][1]);
}

// MixColumns
void mixColumns(char state[2][2]) {

    swap(state[0][0], state[1][0]);
    swap(state[0][1], state[1][1]);
}

// Reverse MixColumns
void reverseMixColumns(char state[2][2]) {

    swap(state[0][0], state[1][0]);
    swap(state[0][1], state[1][1]);
}

// AddRoundKey
void addRoundKey(char state[2][2], char key[2][2]) {

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {

            int a = hexToInt(state[i][j]);
            int b = hexToInt(key[i][j]);

            int result = a ^ b;

            state[i][j] = intToHex(result);
        }
    }
}

// Print State
void printState(char state[2][2]) {

    for(int i = 0; i < 2; i++) {

        for(int j = 0; j < 2; j++) {

            cout << state[i][j] << " ";
        }

        cout << endl;
    }
}

int main() {

    string plaintext, keyInput;

    char state[2][2];
    char key[2][2];

    cout << "Enter 4 hexadecimal characters for plaintext: ";
    cin >> plaintext;

    cout << "Enter 4 hexadecimal characters for key: ";
    cin >> keyInput;

    int index = 0;

    // Fill plaintext matrix
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {

            state[i][j] = plaintext[index++];
        }
    }

    index = 0;

    // Fill key matrix
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {

            key[i][j] = keyInput[index++];
        }
    }

    cout << "\nInitial State:\n";
    printState(state);

    // ================= ENCRYPTION =================
    for(int round = 1; round <= 2; round++) {

        cout << "\n========== ROUND " << round << " ==========\n";

        // SubBytes
        subBytes(state);

        cout << "\nAfter SubBytes:\n";
        printState(state);

        // ShiftRows
        shiftRows(state);

        cout << "\nAfter ShiftRows:\n";
        printState(state);

        // MixColumns
        mixColumns(state);

        cout << "\nAfter MixColumns:\n";
        printState(state);

        // AddRoundKey
        addRoundKey(state, key);

        cout << "\nAfter AddRoundKey:\n";
        printState(state);
    }

    // Final Ciphertext
    string cipher = "";

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {

            cipher += state[i][j];
        }
    }

    cout << "\nEncrypted Text: " << cipher << endl;

    // ================= DECRYPTION =================
    for(int round = 1; round <= 2; round++) {

        cout << "\n========== DECRYPT ROUND " << round << " ==========\n";

        // Reverse AddRoundKey
        addRoundKey(state, key);

        cout << "\nAfter Reverse AddRoundKey:\n";
        printState(state);

        // Reverse MixColumns
        reverseMixColumns(state);

        cout << "\nAfter Reverse MixColumns:\n";
        printState(state);

        // Reverse ShiftRows
        reverseShiftRows(state);

        cout << "\nAfter Reverse ShiftRows:\n";
        printState(state);

        // Reverse SubBytes
        reverseSubBytes(state);

        cout << "\nAfter Reverse SubBytes:\n";
        printState(state);
    }

    // Final Decrypted Text
    string decrypted = "";

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {

            decrypted += state[i][j];
        }
    }

    cout << "\nDecrypted Text: " << decrypted << endl;

    return 0;
}