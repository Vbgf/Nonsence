#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ctime>
#include <unistd.h>
using namespace std;

#define ALL_CARDS 52
#define START_CARDS 26
#define CARD_TYPES 13
#define CARD_TYPES_SIZE 4
#define WAR_COUNT 3
#define FILLER_CARDS 2

static const char lookup_ [CARD_TYPES+FILLER_CARDS] =
{'F', 'F', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K', 'A'};

class Card{
	int power_;
public:
	Card(int power)
	: power_(power)
	{}
	
	int get() const{
		return power_;
	}
	
	void print() const{
		cout << "card: " << lookup_[power_] << endl;
	}

	void change_power(int power){
		power_ = power;
	}
};

class Cards{
	vector<Card> cards_;
public:
	Cards(){
		int card_count_ = ALL_CARDS;
		int array_[CARD_TYPES];
		Card card(0);
		cards_.assign(ALL_CARDS, card);
		fill_n(array_, CARD_TYPES+FILLER_CARDS, CARD_TYPES_SIZE);
		vector<Card>::iterator iterator_ = cards_.begin();
		while(card_count_){
			int num = rand() % CARD_TYPES + FILLER_CARDS;
			if(array_[num] != 0){
				(*iterator_).change_power(num);
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

	void push_front(Card card){
		deck_.push_front(card);
		card_count_++;
	}
};

int main(){
	Cards all;
	Deck deck1(all);
	Deck deck2(all);

	vector<Card> board;
	int turn = 0;
	while(deck1.card_count() && deck2.card_count()){
		turn++;
		if(board.empty()){
			board.push_back(deck1.pop_back());
			board.push_back(deck2.pop_back());
			cout << "Player 1 plays ";
			(*(board.end()-2)).print();
			cout << "Player 2 plays ";
			(*(board.end()-1)).print();
			if((*(board.end()-2)).get() > (*(board.end()-1)).get()){
				deck1.push_front((*(board.end()-1)).get());
				deck1.push_front((*(board.end()-2)).get());
				board.pop_back();
				board.pop_back();
			}else if((*(board.end()-2)).get() < (*(board.end()-1)).get()){
				deck2.push_front((*(board.end()-1)).get());
				deck2.push_front((*(board.end()-2)).get());
				board.pop_back();
				board.pop_back();
			}
		}else{
			cout << "WAR!" << endl;
			if((deck1.card_count()>=WAR_COUNT) && (deck2.card_count()>=WAR_COUNT)){
				for(int i=0; i<WAR_COUNT; i++){
					board.push_back(deck1.pop_back());
					board.push_back(deck2.pop_back());
					cout << "Player 1 plays ";
					(*(board.end()-2)).print();
					cout << "Player 2 plays ";
					(*(board.end()-1)).print();
				}
				if((*(board.end()-2)).get() > (*(board.end()-1)).get()){
					while(!board.empty()){
						deck1.push_front((*(board.end()-1)).get());
						board.pop_back();
					}
				}else if((*(board.end()-2)).get() < (*(board.end()-1)).get()){
					while(!board.empty()){
						deck2.push_front((*(board.end()-1)).get());
						board.pop_back(); 
					}
				}
			}else{
				break;
			}
		}
		cout << "+======================+" << endl; 
		cout << "Card count Player 1: " << deck1.card_count() << endl;
		cout << "Card count Player 2: " << deck2.card_count() << endl;
		cout << "Board count: " << board.size() << endl;
		cout << "+======================+" << endl;
	}

	cout << "Game finished in " << turn << " turns!"<<endl;
	if(deck1.card_count()<deck2.card_count()){
		cout << "Player 2 wins!" << endl;
	}else{
		cout << "Player 1 wins!" << endl;
	}
	return 0;
}
