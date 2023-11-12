#include <cmath>
#include "game.h"
/*---------------------------------------------//defining variables -------------------------------------------*/
             

const string vowels = "aeiou";
const string consonants = "bcdfghjklmnopqrstvwxyz";
int handSize = 7;
string letters = "abcdefghijklmnopqrstuvwxyz*";
vector<int> letter_weight = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10, 0};
//-------------------------------------------------------------------------------------------------------------*/
int word_scores(string word, int n){
    int points = 0;
    int max_ = 0;
    const int word_length = word.size();
    for(char letter: word){
        int pos = letters.find(letter);
        points += letter_weight[pos];
    }
    
    int value = 7 *word_length - 3 *(n - word_length);
   // cout <<value << endl;
    max_ = max(1, value);
    return points * max_;
    
}
void display_hand_dict(vector<char> hand){
    int size_hand = hand.size();
    vector<int> weights = hand_weights(hand);
    cout<<"{";
    for (int i=0; i<size_hand; i++){
        cout << hand[i] <<": " << weights[i];
        if (i < size_hand - 1){
            cout <<", ";
        }
    }
    cout <<"}"<<endl;

}
vector<char> deal_hand(int n){
    vector<char> newhand;
    int num_vowels = static_cast<int>(ceil(float(n) / 3));
    int num_consonants = n - num_vowels - 1;
    for (int i=0; i<num_vowels; i++){
        int randNumber = rand() % vowels.size();
        newhand.push_back(vowels[randNumber]);
    }
    for (int i=0; i<num_consonants; i++){
        int randNumber = rand() % consonants.size();
        newhand.push_back(consonants[randNumber]);
        
    }
    newhand.push_back('*');
    return newhand;

}
vector<int> hand_weights(vector<char> hand){
    vector <int> weights;
    for (char letter: hand){
        int pos = letters.find(letter);
        weights.push_back(letter_weight[pos]);
    }
    return weights;
}
vector<char> update_hand(vector<char> hand, string word){
    for(char letter: word){
        auto it = find(hand.begin(), hand.end(), letter);
        if (it != hand.end()){hand.erase(it);}
    }
    return hand;
}
bool is_a_valid_word(string word, vector<char> hand, vector<string> word_list) {
    const string alphabet = "abcdefghijklmnopqrstuvwxyz";
    

    for (char letter: word) {
        if (count(word.begin(), word.end(), letter) > count(hand.begin(), hand.end(), letter)) {
            return false;
        }
    }

    size_t ind = word.find('*');
    if (ind == string::npos) {
        return find(word_list.begin(), word_list.end(), word) != word_list.end();
    } else {
        for (char letter: alphabet) {
            word[ind] = letter;
            if (find(word_list.begin(), word_list.end(), word) != word_list.end()) {
                return true;
            }
        }
    }
    return false;  // Return false if no valid substitution for wildcard is found
}
int play_hand(vector<char> hand, vector<string> word_list){
    auto size = [](vector<char> h){return h.size();};
    string word;
    int scores = 0;
    bool hand_game = true;
    while (hand_game){
            cout<<"Current Hand: ";
        display_hand_dict(hand);
        cout <<"Enter a word, or '!!' is you are finished: ";
        cin >> word;
        if (word == "!!"){
            cout << "Total Scores: " << scores << " points" <<endl;
            hand_game = false;
        }
        else if (is_a_valid_word(word, hand, word_list)){
            scores += word_scores(word, size(hand));
            cout << word << " earned " << word_scores(word, size(hand)) << " points"<<endl;
            hand = update_hand(hand, word);
        }
        else{
            cout <<"Please choose a valid word"<<endl;
            cout <<endl;
        }
        
    }
    return scores;
}

vector<char> substitute_hand(vector<char> hand, char letter){
    string alphabet ="abcdefghijklmnopqrstuvwxyz";
    auto it = find(hand.begin(), hand.end(), letter);
    if (it != hand.end()){
        hand.erase(it);
        int pos = alphabet.find(letter);
        alphabet.erase(pos, 1);
    }
    char newLetter;
    do {
        int choice = rand() % alphabet.size();
        newLetter = alphabet[choice];
    } while(find(hand.begin(), hand.end(), newLetter) != hand.end()); // Ensure the new letter isn't already in the hand

    hand.push_back(newLetter);
    return hand;
}

void play_game(vector<string> word_list){
    cout << "Enter total number of hands: ";
    int game_scores = 0;
    int score_hand = 0;
    int number_hand;
    cin >> number_hand;
    while (number_hand > 0){
        vector<char> hand = deal_hand(handSize);
        display_hand_dict(hand);
        cout<< "Would you like to substitute a letter to annother y/n: ";
        char answer;
        cin >> answer;
        if (answer == 'y'){
            cout <<"Please the letter that yout want to substitute: ";
            cin >> answer;
            hand = substitute_hand(hand, answer);
            cout << "Your new hand is: "<<endl;
            display_hand_dict(hand);
        }
        score_hand = play_hand(hand, word_list);
        game_scores += score_hand;
        number_hand -= 1;
    }
    cout<< "End of the game\n"
        <<"Your total score is: "
        << game_scores
        << " points"
        <<endl;
}