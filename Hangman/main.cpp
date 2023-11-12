#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

string alphabet = "abcdefghijklmnopqrstuvwxyz"; // defining global variable alphabet
vector<string> loadFile(string filename){
    ifstream inFile;
    try
    {
        inFile.open(filename);
        if (inFile.fail()){
            throw filename;
        }
        vector<string> words;
        string line;
        while(getline(inFile, line)){
            stringstream ss(line);
            string word;
            while(getline(ss, word, ' ')){
                words.push_back(word);
            }
        }
        return words;
        }
    
    catch(string e)
    {
        cout << "The filename " << e <<" was correctly loaded" <<endl;
        exit(1);
    }

}
vector<string> words = loadFile("words.txt");

string selectSecretWord(){

    size_t sizeVect = words.size();
    cout <<"Just loaded: " << sizeVect <<" words \n";
    cout <<"Selecting a random Word ... \n";
    srand(time(NULL));
    int randNumber = rand() % (sizeVect - 1);
    string wordtofind = words[randNumber];
    size_t sizeOfWordtofind = wordtofind.size();
    cout << "We randomly selected a word of: " << sizeOfWordtofind << " letters \n";
    return wordtofind;

}

void match_gap_words(string guessed_word) {
    vector<string> matches_word;
    const string::size_type sizeWord = guessed_word.size();
    
    for (string word : words) {
        if (word.size() == sizeWord) {
            bool match = true;
            for (int i = 0; i < sizeWord; i++) {
                if (alphabet.find(guessed_word[i]) != string::npos && word[i] != guessed_word[i]) {
                    match = false;
                    break; // Exit the loop as soon as a mismatch is found
                }
            }
            if (match) {
                matches_word.push_back(word);
            }
        }
    }
    
    for (string word : matches_word) {
        cout << word << " ";
    }
}

bool is_word_guessed(string secretWord, vector<char> letter_guessed){
    for (char letter: secretWord){
        if (std::find(letter_guessed.begin(), letter_guessed.end(), letter) == letter_guessed.end()){
            return false;
        }
    }
    return true;
}
string get_guessed_word(string secretWord, vector<char> letter_guessed){
    string guessed_word(secretWord.size(), '_');
        for (char letter: secretWord){
        if (std::find(letter_guessed.begin(), letter_guessed.end(), letter) != letter_guessed.end()){
            for (int i=0; i<secretWord.size(); i++){
                if (secretWord[i] == letter){
                    guessed_word[i] = letter;
                }
            }
        }
    }
    return guessed_word;
}

string get_available_letters(vector<char> letter_guessed){
    string available_letters;
    for (int i = 0; i < alphabet.size(); i++) {
        if (std::find(letter_guessed.begin(), letter_guessed.end(), alphabet[i]) == letter_guessed.end()) {
            available_letters += alphabet[i];
        }
    }
    return available_letters;
}
int main(){
    
    string secretWord = selectSecretWord();
    bool game = true;
    vector<char> letter_guessed;
    
    cout <<get_guessed_word(secretWord, letter_guessed) <<"\n";
    int guess = 10;
    int good_guess = 0;
    int warnings = 3;
    while (game && guess >=1)
    {
        cout << "Available letters: " << get_available_letters(letter_guessed) << "\n";
        char letter;
        cout <<"Please guess a letter: ";
        cin >> letter;
        
        if (letter == '*' && good_guess >=3){
            cout <<"Matched words : ";
            match_gap_words(get_guessed_word(secretWord, letter_guessed));
            cout<<endl;
            
        }
        else if (std:: find(alphabet.begin(), alphabet.end(), letter) == alphabet.end()){
            cout << " warnings: Invalid input" <<endl;
            warnings -= 1;
        }
     
        
        else if (std::find(letter_guessed.begin(), letter_guessed.end(), letter) != letter_guessed.end()){
            cout<<"This letter is already guessed: " << get_guessed_word(secretWord, letter_guessed) << "\n";
            
            warnings -= 1;
        }
        else{
            
            letter_guessed.push_back(letter);
            if (secretWord.find(letter) != string:: npos){
                cout<<"Good guess: "<< get_guessed_word(secretWord, letter_guessed) <<"\n";
                good_guess += 1;
            }
            else{
                guess -= 1;
                cout <<"Oops! That letter is not in my word: " <<get_guessed_word(secretWord, letter_guessed)<<"\n";
                
            }
        }
        if (warnings == 0)
        {
            guess -= 1;
            warnings = 3;
        }
        if(is_word_guessed(secretWord, letter_guessed)){
            cout << "Congratulations, you won !\n";
            game = false;
            break;
        }
        cout << "You've " << warnings <<" warnings and " << guess << " guesses left\n";
        
    }
    if (guess == 0)
    {
        cout <<" Oops! No more guess left, you've lost"<<endl;
        cout <<"The secret word was ...: " <<secretWord <<endl;
    }

}