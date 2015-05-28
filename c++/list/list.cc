//--------------------------------------------
//NAME: Vasil Kolev
//CLASS: XIb
//NUMBER: 6
//PROBLEM: #3
//FILE NAME: list.cc
//FILE PURPOSE:
//
//This file contains all the function declarations
//and implementations for the List class
//
//---------------------------------------------
#include <iostream>
#include <stdlib.h>
using namespace std;

template<class T> class List{
	struct Elem{
		T data_;
		Elem* next_;
		Elem* prev_;

		Elem(T val)
		: data_(val),
		  next_(0),
		  prev_(0)
		{}
	};
	Elem* head_;
	Elem* tail_;
	int size_;
public:
//--------------------------------------------
//FUNCTION: List()
//The default constructor for the list class
//
//PARAMETERS:
//None
//----------------------------------------------
	List()
	: head_(0),
	  tail_(0),
	  size_(0)
	{}
//--------------------------------------------
//FUNCTION: ~List()
//The default destructor for the list class
//
//PARAMETERS:
//None
//----------------------------------------------
	~List(){
		while(!empty()){
			pop_back();
		}
	}
//--------------------------------------------
//FUNCTION: void push_back(const T& data)
//This function adds an element at the end of the list
//
//PARAMETERS:
//const T& data - the new element's value
//----------------------------------------------
	void push_back(const T& data){
		Elem* e = new Elem(data);
		if((head_ == 0) && (tail_ == 0)){
			head_ = e;
			tail_ = e;
		}else{
			e->prev_ = tail_;
			tail_->next_ = e;
			tail_ = e;
		}
		size_++;
	}
//--------------------------------------------
//FUNCTION: void pop_back()
//This function removes an element at the end of the list
//
//PARAMETERS:
//None
//----------------------------------------------
	void pop_back(){
		if(tail_ == 0){
			cout << "You are trying to delete a nonexistent object!" << endl;
		}else{
			if(tail_->prev_ == 0){
				delete tail_;
				tail_ = 0;
				head_ = 0;
			}else{
				tail_ = tail_->prev_;
				delete tail_->next_;
				tail_->next_ = 0;
			}
			size_--;
		}
	}
//--------------------------------------------
//FUNCTION: void push_front(const T& data)
//This function adds an element at the start of the list
//
//PARAMETERS:
//const T& data - the new element's value
//----------------------------------------------
	void push_front(const T& data){
		Elem* e = new Elem(data);
		if((head_ == 0) && (tail_ == 0)){
			head_ = e;
			tail_ = e;
		}else{
			e->next_ = head_;
			head_->prev_ = e;
			head_ = e;
		}
		size_++;
	}
//--------------------------------------------
//FUNCTION: void pop_front()
//This function removes an element at the start of the list
//
//PARAMETERS:
//None
//----------------------------------------------
	void pop_front(){
		if(head_ == 0){
			cout << "You are trying to delete a nonexistent object!" << endl;
		}else{
			if(head_->next_ == 0){
				delete head_;
				tail_ = 0;
				head_ = 0;
			}else{
				head_ = head_->next_;
				delete head_->prev_;
				head_->prev_ = 0;
			}
			size_--;
		}
	}
//--------------------------------------------
//FUNCTION: T& front()
//This function returnes the value of the first element
//
//PARAMETERS:
//None
//----------------------------------------------
	T& front(){
		if(head_ == 0){
			cout << "You are trying to get a nonexistent object!" << endl;
		}else{
			return head_->data_;
		}
	}
//--------------------------------------------
//FUNCTION: const T& front() const
//This function returnes the value of the first element
//For constant objects only
//
//PARAMETERS:
//None
//----------------------------------------------
	const T& front() const{
		if(head_ == 0){
			cout << "You are trying to get a nonexistent object!" << endl;
		}else{
			return head_->data_;
		}
	}
//--------------------------------------------
//FUNCTION: T& back()
//This function returnes the value of the last element
//
//PARAMETERS:
//None
//----------------------------------------------
	T& back(){
		if(head_ == 0){
			cout << "You are trying to get a nonexistent object!" << endl;
		}else{
			return tail_->data_;
		}
	}
//--------------------------------------------
//FUNCTION: const T& back() const
//This function returnes the value of the last element
//For constant objects only
//
//PARAMETERS:
//None
//----------------------------------------------
	const T& back() const{
		if(head_ == 0){
			cout << "You are trying to get a nonexistent object!" << endl;
		}else{
			return tail_->data_;
		}
	}
//--------------------------------------------
//FUNCTION: int size() const
//This function returnes the size of the list
//
//PARAMETERS:
//None
//----------------------------------------------
	int size() const{
		return size_;
	}
//--------------------------------------------
//FUNCTION: int size() const
//Returns true if list is empty. Else returns false
//
//PARAMETERS:
//None
//----------------------------------------------
	bool empty() const{
		if(size_ == 0){
			return true;
		}else{
			return false;
		}
	}
//--------------------------------------------
//FUNCTION: void clear()
//Removes all the objects in the list
//
//PARAMETERS:
//None
//----------------------------------------------
	void clear(){
		while(!empty()){
			pop_back();
		}
	}
//--------------------------------------------
//FUNCTION: void swap(List& other)
//Swaps the objects of two lists
//
//PARAMETERS:
//List& other - the second list
//----------------------------------------------
	void swap(List& other){
		Elem* temp_head = other.head_;
		Elem* temp_tail = other.tail_;
		other.head_ = head_;
		other.tail_ = tail_;
		head_ = temp_head;
		tail_ = temp_tail;
		int temp_size = size_;
		size_ = other.size_;
		other.size_ = temp_size;
	}
//--------------------------------------------
//FUNCTION: List(const List& other)
//The copy constructor of the list class
//
//PARAMETERS:
//const List& other - the list to be copied
//----------------------------------------------
	List(const List& other)
	: head_(0),
	  tail_(0),
	  size_(0){
		Elem* iterator= other.head_;
		while(iterator != 0){
			push_back(iterator->data_);
			iterator = iterator->next_;
		}
	}
//--------------------------------------------
//FUNCTION: List& operator=(const List& other)
//Enables the use of the operator= between list objects
//
//PARAMETERS:
//const List& other - the list to be copied
//----------------------------------------------
	List& operator=(const List& other){
		return List(other);
	}
//--------------------------------------------
//CLASS: Iterator
//One of the iterator classes in the list
//
//PARAMETERS:
//None
//----------------------------------------------
	class Iterator{
		Elem* iterator_;
	public:
//--------------------------------------------
//FUNCTION: Iterator(Elem* position)
//The constructor of the Iterator class
//
//PARAMETERS:
//Elem* position - the start position of the iterator
//----------------------------------------------
		Iterator(Elem* position)
		: iterator_(position)
		{}
//--------------------------------------------
//FUNCTION: Elem* get_pointer()
//Returns the address of the currently pointed
//object by the iterator
//
//PARAMETERS:
//None
//----------------------------------------------
		Elem* get_pointer(){
			return iterator_;
		}
//--------------------------------------------
//FUNCTION: Iterator operator++()
//Enables incrementing the iterator with the operator++
//(prefix)
//
//PARAMETERS:
//None
//----------------------------------------------
		Iterator operator++(){
			iterator_ = iterator_->next_;
			return iterator_;
		}
//--------------------------------------------
//FUNCTION: Iterator operator++(int)
//Enables incrementing the iterator with the operator++
//(postfix)
//
//PARAMETERS:
//None - the int is reserved
//----------------------------------------------
		Iterator operator++(int){
			iterator_ = iterator_->next_;
			return iterator_;
		}
//--------------------------------------------
//FUNCTION: bool operator==(const Iterator& other) const
//Enables comparing two iterators
//Returns true if same
//
//PARAMETERS:
//const Iterator& other - the second pointer
//----------------------------------------------
		bool operator==(const Iterator& other) const{
			if(iterator_ == other.iterator_){
				return true;
			}else{
				return false;
			}
		}
//--------------------------------------------
//FUNCTION: bool operator!=(const Iterator& other) const
//Enables comparing two iterators
//Returns false if same
//
//PARAMETERS:
//const Iterator& other - the second pointer
//----------------------------------------------
		bool operator!=(const Iterator& other) const{
			if(iterator_ != other.iterator_){
				return true;
			}else{
				return false;
			}
		}
//--------------------------------------------
//FUNCTION: T& operator*()
//Enables the usage of the object trough the iterator
//
//PARAMETERS:
//None
//----------------------------------------------
		T& operator*(){
			return iterator_->data_;
		}
//--------------------------------------------
//FUNCTION: T& operator->()
//Enables the usage of operator->
//
//PARAMETERS:
//None
//----------------------------------------------
		T* operator->(){
			return &(iterator_->data_);
		}
	};
//--------------------------------------------
//FUNCTION: Iterator begin()
//Returns a iterator, pointed at the first element
//
//PARAMETERS:
//None
//----------------------------------------------
	Iterator begin(){
		Iterator iterator = head_;
		return iterator;
	}
//--------------------------------------------
//FUNCTION: Iterator begin()
//Returns a iterator, pointed at the last element
//
//PARAMETERS:
//None
//----------------------------------------------
	Iterator end(){
		Iterator iterator = tail_;
		return iterator;
	}
//--------------------------------------------
//CLASS: Const_Iterator
//Same as Iterator, just const
//
//PARAMETERS:
//None
//----------------------------------------------
	class Const_Iterator{
		Elem* iterator_;
	public:
		Const_Iterator(Elem* position)
		: iterator_(position)
		{}

		Const_Iterator operator++(){
			iterator_ = iterator_->next_;
			return iterator_;
		}

		Const_Iterator operator++(int){
			iterator_ = iterator_->next_;
			return iterator_;
		}

		bool operator==(const Const_Iterator& other) const{
			if(iterator_ == other.iterator_){
				return true;
			}else{
				return false;
			}
		}

		bool operator!=(const Const_Iterator& other) const{
			if(iterator_ != other.iterator_){
				return true;
			}else{
				return false;
			}
		}

		const T& operator*(){
			return iterator_->data_;
		}

		const T* operator->(){
			return &(iterator_->data_);
		}
	};

	Const_Iterator begin() const{
		Const_Iterator iterator = head_;
		return iterator;
	}

	Const_Iterator end() const{
		Const_Iterator iterator = tail_;
		return iterator;
	}
//--------------------------------------------
//CLASS: Reverse_Iterator
//A iterator that decrements rather than increments
//from operator++
//
//PARAMETERS:
//None
//----------------------------------------------
	class Reverse_Iterator{
		Elem* iterator_;
	public:
		Reverse_Iterator(Elem* position)
		: iterator_(position)
		{}

		Reverse_Iterator operator++(){
			iterator_ = iterator_->prev_;
			return iterator_;
		}

		Reverse_Iterator operator++(int){
			iterator_ = iterator_->prev_;
			return iterator_;
		}

		bool operator==(const Reverse_Iterator& other) const{
			if(iterator_ == other.iterator_){
				return true;
			}else{
				return false;
			}
		}

		bool operator!=(const Reverse_Iterator& other) const{
			if(iterator_ != other.iterator_){
				return true;
			}else{
				return false;
			}
		}

		T& operator*(){
			return iterator_->data_;
		}

		T* operator->(){
			return &(iterator_->data_);
		}
	};
//--------------------------------------------
//FUNCTION: Reverse_Iterator rbegin() const
//Returns a reverse_iterator, pointed at the fist element
//
//PARAMETERS:
//None
//----------------------------------------------
	Reverse_Iterator rbegin(){
		Reverse_Iterator iterator = head_;
		return iterator;
	}
//--------------------------------------------
//FUNCTION: Reverse_Iterator rend() const
//Returns a reverse_iterator, pointed at the last element
//
//PARAMETERS:
//None
//----------------------------------------------
	Reverse_Iterator rend(){
		Reverse_Iterator iterator = tail_;
		return iterator;
	}
//--------------------------------------------
//CLASS: Const_Reverse_Iterator
//Same as Reverse_Iterator, just const
//
//PARAMETERS:
//None
//----------------------------------------------
	class Const_Reverse_Iterator{
		Elem* iterator_;
	public:
		Const_Reverse_Iterator(Elem* position)
		: iterator_(position)
		{}

		Const_Reverse_Iterator operator++(){
			iterator_ = iterator_->prev_;
			return iterator_;
		}

		Const_Reverse_Iterator operator++(int){
			iterator_ = iterator_->prev_;
			return iterator_;
		}

		bool operator==(const Const_Reverse_Iterator& other) const{
			if(iterator_ == other.iterator_){
				return true;
			}else{
				return false;
			}
		}

		bool operator!=(const Const_Reverse_Iterator& other) const{
			if(iterator_ != other.iterator_){
				return true;
			}else{
				return false;
			}
		}

		const T& operator*(){
			return iterator_->data_;
		}

		const T* operator->(){
			return &(iterator_->data_);
		}
	};

	Const_Reverse_Iterator rbegin() const{
		Const_Reverse_Iterator iterator = head_;
		return iterator;
	}

	Const_Reverse_Iterator rend() const{
		Const_Reverse_Iterator iterator = tail_;
		return iterator;
	}
//--------------------------------------------
//FUNCTION: Iterator insert(Iterator pos, const T& x)
//Inserts an element in the list just before the pos iterator
//
//PARAMETERS:
//Iterator pos - iterator, shows where to insert the element
//const T& x - the value of the new element
//----------------------------------------------
	Iterator insert(Iterator pos, const T& x){
		if(pos == begin()){
			push_front(x);
		}else{
			Elem* e = new Elem(x);
			e->next_ = pos.get_pointer();
			e->prev_ = pos.get_pointer()->prev_;
			pos.get_pointer()->prev_->next_ = e;
			pos.get_pointer()->prev_ = e;
			size_++;
		}
	}
//--------------------------------------------
//FUNCTION: Iterator erase(Iterator pos)
//Deletes an object, pointed to by the iterator
//
//PARAMETERS:
//Iterator pos - iterator, shows where to insert the element
//----------------------------------------------
	Iterator erase(Iterator pos){
		if(pos == end()){
			pop_back();
		}else if(pos == begin()){
			pop_front();
		}else{
			pos.get_pointer()->prev_->next_ = pos.get_pointer()->next_;
			pos.get_pointer()->next_->prev_ = pos.get_pointer()->prev_;
			size_--;
			delete pos.get_pointer();
		}
	}
//--------------------------------------------
//FUNCTION: Iterator erase(Iterator first, Iterator last)
//Deletes all objects in a given range
//
//PARAMETERS:
//Iterator first - start position, included in the deleting
//Iterator last - stop position, not included in the deleting
//----------------------------------------------
	Iterator erase(Iterator first, Iterator last){
		Elem* temp = first.get_pointer()->next_;
		while(first != last){
			erase(first);
			first = temp;
			temp = temp->next_;
		}
		erase(first);
	}
};

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
