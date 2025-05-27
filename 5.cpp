#include <iostream>
#include <fstream>
#include <stack>
#include <map>
#include <string>


bool СheckBrackets( const std::string& filename ) {

    char ch;
    std::stack<char> bracketStack;
    std::ifstream inFile( filename );

    std::map<char, char> bracketPairs = {
    {')', '('},
    {']', '['},
    {'}', '{'}
    };

    if ( !inFile.is_open() ) {
        std::cout << "Couldn't open file for some reason =( " << std::endl;
        return false;
    }

    while ( inFile.get( ch ) ) {
        if ( ch == '(' || ch == '[' || ch == '{' ) {
            bracketStack.push( ch );
        }

        else if ( ch == ')' || ch == ']' || ch == '}' ) {
            if ( bracketStack.empty() || bracketStack.top() != bracketPairs[ch] ) {
                return false;
            }
            bracketStack.pop();
        }
    }

    return bracketStack.empty();
}

int main() {
    const std::string IN_FILE_PATH = "in5.txt";

    if ( СheckBrackets( IN_FILE_PATH ) ) {
        std::cout << "There are no errors in file" << std::endl;
    }
    else {
        std::cout << "There are errors found in file" << std::endl;
    }

    return 0;
}