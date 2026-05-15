#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string toLowerCase(string text) {

    for (int i = 0; i < text.length(); i++) {

        text[i] = tolower(text[i]);
    }

    return text;
}

int main() {

    string userInput;

    ofstream file("unknown_queries.txt", ios::app);

    cout << "======================================" << endl;
    cout << " CUSTOMER SUPPORT CHATBOT " << endl;
    cout << "======================================" << endl;

    cout << "\nType 'exit' to end conversation.\n" << endl;

    while (true) {

        cout << "You: ";

        getline(cin, userInput);
        userInput = toLowerCase(userInput);


        if (userInput == "exit") {

            cout << "Bot: Thank you for visiting. Goodbye!" << endl;

            break;
        }

        else if (userInput.find("hello") != string::npos ||
                 userInput.find("hi") != string::npos) {

            cout << "Bot: Hello! How can I assist you today?" << endl;
        }

        else if (userInput.find("delivery") != string::npos) {

            cout << "Bot: Delivery usually takes 3 to 5 business days." << endl;
        }

        else if (userInput.find("return") != string::npos) {

            cout << "Bot: Products can be returned within 7 days." << endl;
        }

        else if (userInput.find("payment") != string::npos) {

            cout << "Bot: We support UPI, Debit Card, Credit Card and Net Banking." << endl;
        }

        else if (userInput.find("product") != string::npos) {

            cout << "Bot: Please visit the product section for latest products." << endl;
        }

        else if (userInput.find("help") != string::npos) {

            cout << "Bot: I can help with delivery, returns, payment and products." << endl;
        }

        else {

            cout << "Bot: Sorry, I did not understand your query." << endl;

            file << userInput << endl;
        }
    }

    file.close();

    return 0;
}


/*

=====================================================
DUMMY INPUT / OUTPUT
=====================================================

You: hello

Bot: Hello! How can I assist you today?


You: what is your refund process?

Bot: Sorry, I did not understand your query.


You: tell me delivery time

Bot: Delivery usually takes 3 to 5 business days.


You: exit

Bot: Thank you for visiting. Goodbye!


=====================================================
FILE OUTPUT
=====================================================

A file named:

unknown_queries.txt

will automatically store:

what is your refund process?


=====================================================
WHY THIS FEATURE IS IMPORTANT
=====================================================

This is actually how many real chatbots improve.

Unknown questions are stored so that:

1. Developer checks them later
2. Understands missing features
3. Adds better responses
4. Improves chatbot gradually


=====================================================
WORKING OF THE CODE
=====================================================

1. User enters message

2. Message converted to lowercase

3. Chatbot checks keywords using:
   string.find()

4. If keyword matches:
   predefined response printed

5. If chatbot fails:
   - default message shown
   - query saved into text file

6. Loop continues until:
   user types "exit"


=====================================================
AI CONCEPT USED
=====================================================

RULE-BASED CHATBOT

The bot uses:
- keyword matching
- predefined responses

No machine learning is used.


=====================================================
LIMITATIONS / BREAKING POINTS
=====================================================

1. NO REAL UNDERSTANDING

Bot only checks keywords.


2. SPELLING ERRORS FAIL

Example:

"delivary"

instead of:

"delivery"


3. NO CONTEXT MEMORY

Bot cannot remember previous conversation.


4. STATIC RESPONSES

Responses are fixed and repetitive.


5. COMPLEX QUESTIONS FAIL

Logical or dynamic questions cannot be answered.


=====================================================
TIME COMPLEXITY
=====================================================

O(n)

where:
n = length of user input


=====================================================
SPACE COMPLEXITY
=====================================================

O(1)

*/
/*

=====================================================
9. ELEMENTARY CHATBOT
APPLICATIONS
=====================================================

1. Customer Support Systems
2. FAQ Bots
3. Banking Assistance Bots
4. Hospital Appointment Bots
5. College Inquiry Systems
6. Railway/Airline Information Systems
7. Food Ordering Assistants
8. E-commerce Support Systems

*/
