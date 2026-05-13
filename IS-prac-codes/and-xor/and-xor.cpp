#include <iostream>
#include <string>
using namespace std;

int main() {
    string text;

    cout << "Enter a string: ";
    getline(cin, text);

    cout << "\nResult after AND with 127:\n";

    for(int i = 0; i < text.length(); i++) {
        char ch = text[i] & 127;
        cout << ch;
    }

    cout << "\n\nResult after XOR with 127:\n";

    for(int i = 0; i < text.length(); i++) {
        char ch = text[i] ^ 127;
        // Print only printable characters
        if(ch >= 32 && ch <= 126) {
            cout << ch;
        }
        else {
            cout << ".";
        }
    }

    return 0;
}