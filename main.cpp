#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <windows.h>

using namespace std;

void color_print(smatch match, string s, string *const_array) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (match[1].matched == true) {
        SetConsoleTextAttribute(hConsole, 8);
        cout << s << " - " << const_array[0] << endl;
    }
    else if (match[2].matched == true){
        SetConsoleTextAttribute(hConsole, 2);
        cout << s << " - " << const_array[1] << endl;
    }
    else if (match[3].matched == true){
        SetConsoleTextAttribute(hConsole, 1);
        cout << s << " - " << const_array[2] << endl;
    }
    else if (match[4].matched == true){
        SetConsoleTextAttribute(hConsole, 3);
        cout << s << " - " << const_array[3] << endl;
    }
    else if (match[5].matched == true){
        SetConsoleTextAttribute(hConsole, 5);
        cout << s << " - " << const_array[4] << endl;
    }
    else if (match[6].matched == true){
        SetConsoleTextAttribute(hConsole, 6);
        cout << s << " - " << const_array[5] << endl;
    }
    else if (match[7].matched == true){
        SetConsoleTextAttribute(hConsole, 11);
        cout << s << " - " << const_array[6] << endl;
    }
    else if (match[8].matched == true){
        SetConsoleTextAttribute(hConsole, 4);
        cout << s << " - " << const_array[7] << endl;
    }
}

int main() {
    string line;
    ifstream File("file.txt");
    if (!File.is_open())
    {
        cout << "Unable to open file";
        return 0;
    }

    string s;
    string const_array[8] = {"Comments","String and character constants", "Operators", "Reserved words",
                             "Numbers", "Punctuation", "Identifiers", "Errors"};
    while ( getline (File,line) )
    {
        s+=(line+'\n');
    }

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 8);
    cout << "1.Comments" << endl;
    SetConsoleTextAttribute(hConsole, 2);
    cout << "2.String and character constants" << endl;
    SetConsoleTextAttribute(hConsole, 1);
    cout << "3.Operators" << endl;
    SetConsoleTextAttribute(hConsole, 3);
    cout << "4.Reserved words" << endl;
    SetConsoleTextAttribute(hConsole, 5);
    cout << "5.Numbers" << endl;
    SetConsoleTextAttribute(hConsole, 6);
    cout << "6.Punctuation" << endl;
    SetConsoleTextAttribute(hConsole, 11);
    cout << "7.Identifiers" << endl;
    SetConsoleTextAttribute(hConsole, 4);
    cout << "8.Errors" << endl;

    regex words_regex("(#.*)|(\"{3}[^\"]+\"{3}|\"[^\"\\n]+\"|'[^'^\\n]+')|"
                      "(\\bnot in\\b|\\bis not\\b|\\band\\b|\\bor\\b|\\bnot\\b|\\bis\\b|\\|\\|\\^|//=|>>=|<<=|\\+=|-=|\\*=|/=|%=|&=|//|\\|=|\\^=|==|!=|>=|<=|\\+|-|\\*|/|%|=|=|>|<|&|~|<<|>>)|"
                      "(False|await|else|import|pass|None|break|except|in|raise|True|class|finally|is|return|and|continue|for|lambda|try|as|def|from|nonlocal|while|assert|del|global|not|with|async|elif|if|or|yield)|"
                      "(?:\\b(-?[0-9\\.]+|[0-9A-Fa-f]+)\\b)|(\\[|\\]|,|\\:|\\(|\\))|"
                      "(\\b[A-Za-z_][\\w]*\\b)|(\\S+)");
    auto words_begin = sregex_iterator(s.begin(), s.end(), words_regex);
    auto words_end = sregex_iterator();

    for (sregex_iterator i = words_begin; i != words_end; ++i)
    {
        smatch match = *i;
        string match_str = match.str();
        if (match_str[match_str.length()-2] == '\\' and match_str[match_str.length()-1] == 'n') {
        }
        color_print(match, match_str, const_array);
    }

    File.close();
    return 0;
}
