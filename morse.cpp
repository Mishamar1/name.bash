#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Функция для поиска индекса символа в массиве Morse
int bulkhead(const string& x, const vector<string>& morse) {
    auto it = find(morse.begin(), morse.end(), x);
    return (it != morse.end()) ? distance(morse.begin(), it) : -1;
}

// Функция для декодирования
void decoding(const string& str, string& cod, const string& symbols, 
              const vector<string>& morse) {
    vector<int> indices;
    size_t i = 0;
    
    while (i < str.size()) {
        string x;
        while (i < str.size() && str[i] != ' ' && x.size() <= 6) {
            x += str[i++];
        }
        
        indices.push_back(bulkhead(x, morse));
        if (i < str.size() && str[i] == ' ') i++;  // Пропускаем пробел
    }

    for (int idx : indices) {
        if (idx == -1) {
            cod += '+';  // Если символ не удалось расшифровать
        } else {
            cod += toupper(symbols[idx]);
        }
    }
}

// Функция для поиска индекса символа в массиве symbols
int yasy(char bukv, const string& symbols) {
    size_t pos = symbols.find(bukv);
    return (pos != string::npos) ? static_cast<int>(pos) : -1;
}

// Функция для кодирования
void encoding(const string& str, string& cod, const string& symbols, 
              const vector<string>& morse) {
    for (char c : str) {
        char bukva = toupper(c);
        int idx = yasy(bukva, symbols);
        if (idx != -1) {
            cod += morse[idx] + " ";
        }
    }
    
    if (!cod.empty()) {
        cod.pop_back(); 
    }
}

int main() {
    cout << "Specify the desired action with a number.\n"
         << "Encrypt text: \"1\"\n"
         << "Decrypt text: \"2\"\n";

    int x;
    cin >> x;
    cin.ignore(); 

    if (x == 1) {
        cout << "Enter the text you want to encrypt:\n";
    } else if (x == 2) {
        cout << "*Decryption of the text will be a caption*\n"
             << "Enter the text you want to decrypt:\n";
    } else {
        cerr << "Error. An invalid character has been entered\n";
        return 1;
    }

    string str;
    getline(cin, str);

    string cod;
    const string symbols = "AJS2BKT3CLU4DMV5ENW6FOX7GPY8HQZ9IR10 ?!,";
    const vector<string> morse = {
        ".-", ".---", "...", "..---", "-...", "-.-", "-", "...--",
        "-.-.", ".-..", "..-", "....-", "-..", "--", "...-", ".....",
        ".", "-.", ".--", "-....", "..-.", "---", "-..-", "--...",
        "--.", ".--.", "-.--", "---..", "....", "--.-", "--..", "----.",
        "..", ".-.", ".----", "-----", "-...-", "..--..", "--..--", ".-.-.-"
    };

    switch (x) {
        case 1:
            encoding(str, cod, symbols, morse);
            break;
        case 2:
            decoding(str, cod, symbols, morse);
            break;
    }

    cout << cod << endl;

    return 0;
}