#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

extern const string vowels;
extern const string consonnants;
extern int handSize;
extern string letters;
extern vector<int> letter_weight;


void display_hand_dict(vector<char> hand);
string lowerstr(string word);
vector<int> hand_weights(vector<char> hand);
vector<char> update_hand(vector<char> hand, string word);
bool is_a_valid_word(string word, vector<char> hand, vector<string> word_list);
int word_scores(string word, int n);
vector <char> deal_hand(int n);
int play_hand(vector<char> hand, vector<string> word_list);
vector<char> substitute_hand(vector<char> hand, char letter);
void play_game(vector<string> word_list);