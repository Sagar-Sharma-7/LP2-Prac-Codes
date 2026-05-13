#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {

    string text;

    cout << "Enter plaintext: ";
    getline(cin, text);

    // Remove spaces and convert to uppercase
    string plain = "";

    for(char ch : text) {
        if(ch != ' ')
            plain += toupper(ch);
    }

    int cols;

    cout << "Enter number of columns/key size: ";
    cin >> cols;

    vector<int> key(cols);

    cout << "Enter key values:\n";

    for(int i = 0; i < cols; i++) {
        cin >> key[i];
    }

    // Calculate rows
    int rows;

    if(plain.length() % cols == 0)
        rows = plain.length() / cols;
    else
        rows = (plain.length() / cols) + 1;

    // Encryption Matrix
    vector<vector<char>> matrix(rows, vector<char>(cols, ' '));

    int index = 0;

    // Fill matrix row-wise
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {

            if(index < plain.length()) {
                matrix[i][j] = plain[index];
                index++;
            }
        }
    }

    cout << "\nEncryption Matrix:\n";

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    // Encryption
    string cipher = "";

    for(int num = 1; num <= cols; num++) {

        int col;

        for(int j = 0; j < cols; j++) {

            if(key[j] == num) {
                col = j;
                break;
            }
        }

        for(int i = 0; i < rows; i++) {

            if(matrix[i][col] != ' ')
                cipher += matrix[i][col];
        }
    }

    cout << "\nEncrypted Text: " << cipher << endl;

    // Decryption Matrix
    vector<vector<char>> decryptMatrix(rows, vector<char>(cols, ' '));

    int totalChars = plain.length();

    int fullCols = totalChars % cols;

    if(fullCols == 0)
        fullCols = cols;

    int index2 = 0;

    for(int num = 1; num <= cols; num++) {

        int col;

        for(int j = 0; j < cols; j++) {

            if(key[j] == num) {
                col = j;
                break;
            }
        }

        int currentRows = rows;

        if(col >= fullCols)
            currentRows = rows - 1;

        for(int i = 0; i < currentRows; i++) {

            decryptMatrix[i][col] = cipher[index2];
            index2++;
        }
    }

    cout << "\nDecryption Matrix:\n";

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cout << decryptMatrix[i][j] << " ";
        }
        cout << endl;
    }

    // Final Decrypted Text
    string decrypted = "";

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {

            if(decryptMatrix[i][j] != ' ')
                decrypted += decryptMatrix[i][j];
        }
    }

    cout << "\nDecrypted Text: " << decrypted << endl;

    return 0;
}