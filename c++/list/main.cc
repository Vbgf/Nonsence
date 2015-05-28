//--------------------------------------------
//NAME: Vasil Kolev
//CLASS: XIb
//NUMBER: 6
//PROBLEM: #3
//FILE NAME: main.cc
//FILE PURPOSE:
//
//This file tests the functionality of the class
//list, as declared in the assignment.
//
//---------------------------------------------

#include <iostream>
#include "list.hh"
using namespace std;

int main(int argc, char* argv[]){
	if(argc > 4){
		//1
		List<int> l1, l2;
		int argv1 = atoi(argv[1]);
		int argv2 = atoi(argv[2]);
		int argv3 = atoi(argv[3]);
		int argv4 = atoi(argv[4]);
		
		for(int i = argv1; i<argv2;i++){
			l1.push_back(i);
		}
		for(int i = argv3; i<argv4;i++){
			l2.push_back(i);
		}
		//2
		cout << "l1: {";
		for(List<int>::Iterator iterator = l1.begin();
		iterator != 0; iterator++){
			cout << *iterator << ",";
		}
		cout << "}" << endl;
		cout << "l2: {";
		for(List<int>::Iterator iterator = l2.begin();
		iterator != 0; iterator++){
			cout << *iterator << ",";
		}
		cout << "}" << endl;
		//3
		int res = 0;
		for(List<int>::Iterator iterator = l1.begin();
		iterator != l1.end(); iterator++){
			for(List<int>::Iterator iterator2 = l2.begin();
			iterator2 != l2.end(); iterator2++){
				if(*iterator == *iterator2){
					res++;
				}
			}
		}
		cout << "equal element in l1 and l2: " << res << endl;
		//4
		l1.push_back(-100);
		l2.push_back(-100);
		cout << "l1: {";
		for(List<int>::Iterator iterator = l1.begin();
		iterator != 0; iterator++){
			cout << *iterator << ",";
		}
		cout << "}" << endl;
		cout << "l2: {";
		for(List<int>::Iterator iterator = l2.begin();
		iterator != 0; iterator++){
			cout << *iterator << ",";
		}
		cout << "}" << endl;
		//5
		List<int> l(l2);
		cout << "l:  {";
		for(List<int>::Iterator iterator = l.begin();
		iterator != 0; iterator++){
			cout << *iterator << ",";
		}
		cout << "}" << endl;		
		//6
		for(List<int>::Reverse_Iterator iterator = l1.rend();
		iterator!=0; iterator++){
			l.push_front(*iterator);
		}
		cout << "l:  {";
		for(List<int>::Iterator iterator = l.begin();
		iterator != 0; iterator++){
			cout << *iterator << ",";
		}
		cout << "}" << endl;
		//7
		List<int>::Iterator bit = 0;
		for(List<int>::Iterator iterator = l.begin();
		iterator != 0; iterator++){	
			if(*iterator == -100){
				bit = iterator;
				break;
			}
		}
		l.erase(bit, l.end());
		cout << "l:  {";
		for(List<int>::Iterator iterator = l.begin();
		iterator != 0; iterator++){
			cout << *iterator << ",";
		}
		cout << "}" << endl;

	}else{
		cout << "Too few argumetns!" << endl;
	}
	return 0;
}
