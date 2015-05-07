#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

#define START_CARDS 26
 
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
		int card_count_;
		int array_[13];
		Card card('F');
		cards_.assign(52, card);
		fill_n(array_, 13, 4);
		char lookup_ [13] =
		{'2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K', 'A'};
		card_count_ = 0;
		for(int i=0; i<13; i++){
			card_count_ += array_[i];
		}
		vector<Card>::iterator iterator_ = cards_.begin();
		while(card_count_){
			int num = rand() % 13;
			if(array_[num] != 0){
				cards_[iterator_ - cards_.begin()].change_power(lookup_[num]);
				array_[num] --;
				card_count_ --;
				iterator_ ++;
			}
		}
	}
	
	void print() const{
		vector<Card>::const_iterator iterator_;
		for(iterator_ = cards_.begin();
		iterator_ != cards_.end();
		iterator_ ++){
			cards_[iterator_ - cards_.begin()].print();
		}
	}

	vector<Card>::const_iterator begin() const{
		return cards_.begin();
	}

	vector<Card>::const_iterator end() const{
		return cards_.end();
	}

	vector<Card>::const_iterator half() const{
		return cards_.begin() + (cards_.end() - cards_.begin())/2;
	}

	Card pop_back(){
		Card res = cards_[cards_.end()-cards_.begin()];
		cards_.pop_back();
		cout << "           " << cards_.size() << endl;
		return res;
	}
	
	int size() const{
		return cards_.size();
	}
	
	int empty() const{
		return cards_.empty();
	}
};
/*
class Deck{
	deque<Card> deck_;
public:
	Deck(Cards all){
		if(!all.empty()){
			
			vector<Card>::const_iterator iterator_;
			vector<Card>::const_iterator half = all.half();
			for(iterator_ = all.end();
			iterator_ != half;
			iterator_ --){
				deck_.push_front(all.pop_back());
			}
			
			//for(int i = 0; i<26; i++){
		//		deck_.push_front(all.pop_back());
	//			cout << (all.end() - all.begin())/2 << endl;
//			}
		}
	}

	void print() const{
		deque<Card>::const_iterator iterator_;
		for(iterator_ = deck_.begin();
		iterator_ != deck_.end();
		iterator_ ++){
			deck_[iterator_ - deck_.begin()].print();
		}
	}
};
*/
int main(){
	Cards all;
	all.print();
	cout << "+==================+" << endl;	

//	Deck deck1(all);
//	deck1.print();
cout << "           " << all.size() << endl;
	cout << "+==================+" << endl;	
/*
	Deck deck2(all);
	deck2.print();
cout << "           " << all.size() << endl;
	cout << "+==================+" << endl;	

	Deck deck3(all);
	deck3.print();
*/	return 0;
}
