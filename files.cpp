#include <iostream>
#include <vector>
#include<fstream>
#include <string>
#include <algorithm>
#include <windows.h>
using namespace std;

void removePunctuationFromWords(vector<string>& words) {
    for (auto& word : words) {          
        while (!word.empty() && ispunct(static_cast<unsigned char>(word.back()))) {
            word.pop_back();            // Удаляем последний символ, если это знак препинания
        }
    }
}


int main()
{
    SetConsoleOutputCP(CP_UTF8);
    string word;
    ifstream text("tolstoy_voyna-i-mir__xoraa_436421.txt");
    ofstream text2("Tolstoy.txt");
    char ch;
    vector <string> words;
    

    
    if (text.is_open())
    {
        while (text>>word)
        {
            
            words.push_back(word);

        }
    }
    removePunctuationFromWords(words);
    sort(words.begin(), words.end(), [](const string& a, const string& b) {
    return a.length() > b.length();
    });
    for(int i=0; i<5; i++)
    {
        cout<<words[i]<<" ";
    }
    
}