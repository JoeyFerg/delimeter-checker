/**
 * CheckDelimiters.cpp -- a program that checks for properly balanced
 * delimiters and marks the problems using the caret ('^') symbol.
 * @author Joey Ferguson
 * @date 18 February 2016
 */

#include <iostream>
#include <cstring>
#include <stack>
#include <iomanip>

void checkDelimiters( char line[] );

const int LINESIZE = 1024;
bool verbose = false;

using namespace std;


int main( int argc, char *argv[] ) {
    char line[LINESIZE];

    if (argc == 2 && strcmp(argv[1], "-v") == 0) {
        verbose = true;
    }

    if (verbose) {
        cout << "This program checks a line of characters for balanced delimiter." << endl
             << "{ }, [ ], < >, ( )" << endl
             << "Enter a line (<ENTER> to quit): ";
    }

    // Loop, processing lines one at a time, until reach EOF or empty string.
    cin.getline(line, sizeof line, '\n');

    while( cin && strlen(line) > 0 ) {
        checkDelimiters(line);
        cout << "Enter a line (<ENTER> to quit): ";
        cin.getline(line, sizeof line, '\n');
    }
}


void checkDelimiters( char line[] ) {
    stack<char> delimStack;
    stack<int> locationStack;
    stack<int> errorLocationStack;

    bool error=false;

    int caret = 0;

    for (int i = 0; line[i] != char(0); i++) {
        locationStack.push(i);

        switch (line[i]) {
            case '(':
                delimStack.push(line[i]);
                errorLocationStack.push(i);
                break;
            case '{':
                delimStack.push(line[i]);
                errorLocationStack.push(i);
                break;
            case '[':
                delimStack.push(line[i]);
                errorLocationStack.push(i);
                break;
            case '<':
                delimStack.push(line[i]);
                errorLocationStack.push(i);
                break;

            case ')':
                if (delimStack.empty()) {
                    cout << setw(i + 1) << "^" << endl;
                    cout << "ERROR - UNMATCHED CLOSING DELIMITER" << endl;
                    error = true;
                    break;
                }
                if (delimStack.top()=='(') {
                    delimStack.pop();
                    locationStack.pop();
                    errorLocationStack.pop();
                    break;
                }
                else {
                    cout << setw(errorLocationStack.top() + 1) << "^";
                    cout << setw((i)-errorLocationStack.top()) << "^" << endl;
                    cout << "ERROR - NON-MATCHING DELIMITERS" << endl;
                    error = true;
                    break;
                }
            case '}':
                if (delimStack.empty()) {
                    cout << setw(i + 1) << "^" << endl;
                    cout << "ERROR - UNMATCHED CLOSING DELIMITER" << endl;
                    error = true;
                    break;
                }
                if (delimStack.top()=='{') {
                    delimStack.pop();
                    locationStack.pop();
                    errorLocationStack.pop();
                    break;
                }
                else {
                    cout << setw(errorLocationStack.top() + 1) << "^";
                    cout << setw((i)-errorLocationStack.top()) << "^" << endl;
                    cout << "ERROR - NON-MATCHING DELIMITERS" << endl;
                    error = true;
                    break;
                }
            case ']':
                if (delimStack.empty()) {
                    cout << setw(i + 1) << "^" << endl;
                    cout << "ERROR - UNMATCHED CLOSING DELIMITER" << endl;
                    error = true;
                    break;
                }
                if (delimStack.top()=='[') {
                    delimStack.pop();
                    locationStack.pop();
                    errorLocationStack.pop();
                    break;
                }
                else {
                    cout << setw(errorLocationStack.top() + 1) << "^";
                    cout << setw((i)-errorLocationStack.top()) << "^" << endl;
                    cout << "ERROR - NON-MATCHING DELIMITERS" << endl;
                    error = true;
                    break;
                }
            case '>':
                if (delimStack.empty()) {
                    cout << setw(i + 1) << "^" << endl;
                    cout << "ERROR - UNMATCHED CLOSING DELIMITER" << endl;
                    error = true;
                    break;
                }
                if (delimStack.top()=='<') {
                    delimStack.pop();
                    locationStack.pop();
                    errorLocationStack.pop();
                    break;
                }
                else {
                    cout << setw(errorLocationStack.top() + 1) << "^";
                    cout << setw((i)-errorLocationStack.top()) << "^" << endl;
                    cout << "ERROR - NON-MATCHING DELIMITERS" << endl;
                    error = true;
                    break;
                }
            default:
                break;
        }
        if (error) {
            break;
        }
    }

    if (!errorLocationStack.empty()) {
        if (!error) {
            cout << setw(errorLocationStack.top() + 1) << "^" << endl;
            cout << "ERROR - UNMATCHED OPENING DELIMITER" << endl;
            error=true;
        }
    }

    if (!error) {
        cout << "VALID" << endl;
    }
    else {
        caret += 1;
    }
}