#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ctime>
using namespace std;

#define ALL_CARDS 52
#define START_CARDS 26
#define CARD_TYPES 13
#define CARD_TYPES_SIZE 4
#define WAR_COUNT 3

class Card{
	char power_;
public:
	Card(char power)
	: power_(power)
	{}
	
	char get() const{
		return power_;
	}
	
	void print() const{
		cout << "Card: " << power_ << endl;
	}

	void change_power(char power){
		power_ = power;
	}
};

class Cards{
	vector<Card> cards_;
public:
	Cards(){
		int card_count_ = 0;
		int array_[CARD_TYPES];
		Card card('F');
		cards_.assign(ALL_CARDS, card);
		fill_n(array_, CARD_TYPES, CARD_TYPES_SIZE);
		char lookup_ [CARD_TYPES] =
		{'2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K', 'A'};
		for(int i=0; i<CARD_TYPES; i++){
			card_count_ += array_[i];
		}
		vector<Card>::iterator iterator_ = cards_.begin();
		while(card_count_){
			int num = rand() % CARD_TYPES;
			if(array_[num] != 0){
				(*iterator_).change_power(lookup_[num]);
				array_[num] --;
				card_count_ --;
				iterator_ ++;
			}
		}
		srand(time(NULL));
		random_shuffle(cards_.begin(), cards_.end());
	}
	
	void print() const{
		vector<Card>::const_iterator iterator_;
		for(iterator_ = cards_.begin();
		iterator_ != cards_.end();
		iterator_ ++){
			(*iterator_).print();
		}
	}

	vector<Card>::const_iterator begin() const{
		return cards_.begin();
	}

	vector<Card>::const_iterator end() const{
		return cards_.end();
	}

	Card pop_back(){
		Card res = *(cards_.end()-1);
		cards_.pop_back();
		return res;
	}
	
	int size() const{
		return cards_.size();
	}
	
	int empty() const{
		return cards_.empty();
	}
};

class Deck{
	deque<Card> deck_;
	int card_count_;
public:
	Deck(Cards &all)
	:card_count_(0){
		if(!all.empty()){
			vector<Card>::const_iterator end = all.end();
			for(vector<Card>::const_iterator iterator = end;
			iterator > end - START_CARDS;
			iterator--){
				deck_.push_front(all.pop_back());
				card_count_++;
			}
		}
	}

	void print() const{
		deque<Card>::const_iterator iterator_;
		for(iterator_ = deck_.begin();
		iterator_ != deck_.end();
		iterator_ ++){
			(*iterator_).print();
		}
	}

	int card_count() const{
		return card_count_;
	}

	deque<Card>::const_iterator begin() const{
		return deck_.begin();
	}

	deque<Card>::const_iterator end() const{
		return deck_.end();
	}

	Card pop_back(){
		Card res = *(deck_.end()-1);
		deck_.pop_back();
		card_count_--;
		return res;
	}
};

int main(){
	Cards all;
	Deck deck1(all);
	Deck deck2(all);

	cout << "+===================+" << endl;
	cout << "Card count deck 1: " << deck1.card_count() << endl;
	cout << "Card count deck 2: " << deck2.card_count() << endl;
	cout << "+===================+" << endl;

	vector<Card> board;
	int turn = 0;
	while(deck1.card_count() && deck2.card_count()){
		turn++;
		board.push_back(deck1.pop_back());
		board.push_back(deck2.pop_back());

		cout << "+===================+" << endl; 
		cout << "Card count deck 1: " << deck1.card_count() << endl;
		cout << "Card count deck 2: " << deck2.card_count() << endl;
		cout << "Board count: " << board.size() << endl;
		cout << "+===================+" << endl;
		cout << "player 1 cards: " << (*(board.end()-2)).get() << endl;
		cout << "player 2 cards: " << (*(board.end()-1)).get() << endl;

	//work here, compare and assign

	//change containter from 'A' char to int and make a lookup array if needed
	// 2->2 10->10 J->11 Q->12 K->13 A->14   then simply compare if(12>10)...
	}
	return 0;
}
