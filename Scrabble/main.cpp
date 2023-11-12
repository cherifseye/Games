/*
Cherif Ahmad Seye
Scrablle Games
C++
formula general: randNumber = a + rand() % (b - a + 1);
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "game.h"

using namespace std;

vector<string> load_words(string filename);
vector<string> words = load_words("words.txt");


int main(){
    srand(time(NULL));
    play_game(words);
}

vector<string> load_words(string filename){
    try
    {
        ifstream inFile;
        inFile.open(filename);
        if (inFile.fail()){
            throw filename;
        }
        vector<string> words;
        string word;
        while (getline(inFile, word)){
            word = lowerstr(word);
            words.push_back(word);
        }
        return words;
        
    }
    catch(const string e)
    {
        std::cerr << "Please if "<< e << "exists, or if your enter the right filename." << '\n';
        exit(1);
    }
    
}
string lowerstr(string word){
    const int word_size = word.size();
    for (int i = 0; i < word_size; i++){
        if (isupper(static_cast<unsigned char>(word[i]))){
            word[i] = tolower(static_cast<unsigned char>(word[i]));
        }
    }
    return word;
}
