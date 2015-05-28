//--------------------------------------------
//NAME: Vasil Kolev
//CLASS: XIb
//NUMBER: 6
//PROBLEM: #3
//FILE NAME: list.hh
//FILE PURPOSE:
//
//This file contains all the function declarations
//for the List class
//
//---------------------------------------------

#ifndef LIST_H
#define LIST_H

#include <iostream>

template<class T> class List{
	struct Elem{
		T data_;
		Elem* next_;
		Elem* prev_;
		Elem(T val);
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
	List();
//--------------------------------------------
//FUNCTION: ~List()
//The default destructor for the list class
//
//PARAMETERS:
//None
//----------------------------------------------
	~List();
//--------------------------------------------
//FUNCTION: void push_back(const T& data)
//This function adds an element at the end of the list
//
//PARAMETERS:
//const T& data - the new element's value
//----------------------------------------------
	void push_back(const T& data);
//--------------------------------------------
//FUNCTION: void pop_back()
//This function removes an element at the end of the list
//
//PARAMETERS:
//None
//----------------------------------------------
	void pop_back();
//--------------------------------------------
//FUNCTION: void push_front(const T& data)
//This function adds an element at the start of the list
//
//PARAMETERS:
//const T& data - the new element's value
//----------------------------------------------
	void push_front(const T& data);
//--------------------------------------------
//FUNCTION: void pop_front()
//This function removes an element at the start of the list
//
//PARAMETERS:
//None
//----------------------------------------------
	void pop_front();
//--------------------------------------------
//FUNCTION: T& front()
//This function returnes the value of the first element
//
//PARAMETERS:
//None
//----------------------------------------------
	T& front();
//--------------------------------------------
//FUNCTION: const T& front() const
//This function returnes the value of the first element
//For constant objects only
//
//PARAMETERS:
//None
//----------------------------------------------
	const T& front() const;
//--------------------------------------------
//FUNCTION: T& back()
//This function returnes the value of the last element
//
//PARAMETERS:
//None
//----------------------------------------------
	T& back();
//--------------------------------------------
//FUNCTION: const T& back() const
//This function returnes the value of the last element
//For constant objects only
//
//PARAMETERS:
//None
//----------------------------------------------
	const T& back() const;
//--------------------------------------------
//FUNCTION: int size() const
//This function returnes the size of the list
//
//PARAMETERS:
//None
//----------------------------------------------
	int size();
//--------------------------------------------
//FUNCTION: int size() const
//Returns true if list is empty. Else returns false
//
//PARAMETERS:
//None
//----------------------------------------------
	bool empty() const;
//--------------------------------------------
//FUNCTION: void clear()
//Removes all the objects in the list
//
//PARAMETERS:
//None
//----------------------------------------------
	void clear();
//--------------------------------------------
//FUNCTION: void swap(List& other)
//Swaps the objects of two lists
//
//PARAMETERS:
//List& other - the second list
//----------------------------------------------
	void swap(List& other);
//--------------------------------------------
//FUNCTION: List(const List& other)
//The copy constructor of the list class
//
//PARAMETERS:
//const List& other - the list to be copied
//----------------------------------------------
	List(const List& other);
//--------------------------------------------
//FUNCTION: List& operator=(const List& other)
//Enables the use of the operator= between list objects
//
//PARAMETERS:
//const List& other - the list to be copied
//----------------------------------------------
	List& operator=(const List& other);
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
		Iterator(Elem* position);
//--------------------------------------------
//FUNCTION: Elem* get_pointer()
//Returns the address of the currently pointed
//object by the iterator
//
//PARAMETERS:
//None
//----------------------------------------------
		Elem* get_pointer();
//--------------------------------------------
//FUNCTION: Iterator operator++()
//Enables incrementing the iterator with the operator++
//(prefix)
//
//PARAMETERS:
//None
//----------------------------------------------
		Iterator operator++();
//--------------------------------------------
//FUNCTION: Iterator operator++(int)
//Enables incrementing the iterator with the operator++
//(postfix)
//
//PARAMETERS:
//None - the int is reserved
//----------------------------------------------
		Iterator operator++(int);
//--------------------------------------------
//FUNCTION: bool operator==(const Iterator& other) const
//Enables comparing two iterators
//Returns true if same
//
//PARAMETERS:
//const Iterator& other - the second pointer
//----------------------------------------------
		bool operator==(const Iterator& other) const;
//--------------------------------------------
//FUNCTION: bool operator!=(const Iterator& other) const
//Enables comparing two iterators
//Returns false if same
//
//PARAMETERS:
//const Iterator& other - the second pointer
//----------------------------------------------
		bool operator!=(const Iterator& other) const;
//--------------------------------------------
//FUNCTION: T& operator*()
//Enables the usage of the object trough the iterator
//
//PARAMETERS:
//None
//----------------------------------------------
		T& operator*();
//--------------------------------------------
//FUNCTION: T& operator->()
//Enables the usage of operator->
//
//PARAMETERS:
//None
//----------------------------------------------
		T* operator->();
	};
//--------------------------------------------
//FUNCTION: Iterator begin()
//Returns a iterator, pointed at the first element
//
//PARAMETERS:
//None
//----------------------------------------------
	Iterator begin();
//--------------------------------------------
//FUNCTION: Iterator begin()
//Returns a iterator, pointed at the last element
//
//PARAMETERS:
//None
//----------------------------------------------
	Iterator end();
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
		Const_Iterator(Elem* position);

		Const_Iterator operator++();

		Const_Iterator operator++(int);

		bool operator==(const Const_Iterator& other) const;

		bool operator!=(const Const_Iterator& other) const;

		const T& operator*();

		const T* operator->();
	};

	Const_Iterator begin() const;

	Const_Iterator end() const;
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
		Reverse_Iterator(Elem* position);

		Reverse_Iterator operator++();

		Reverse_Iterator operator++(int);

		bool operator==(const Reverse_Iterator& other) const;

		bool operator!=(const Reverse_Iterator& other) const;

		T& operator*();

		T* operator->();
	};
//--------------------------------------------
//FUNCTION: Reverse_Iterator rbegin() const
//Returns a reverse_iterator, pointed at the fist element
//
//PARAMETERS:
//None
//----------------------------------------------
	Reverse_Iterator rbegin();
//--------------------------------------------
//FUNCTION: Reverse_Iterator rend() const
//Returns a reverse_iterator, pointed at the last element
//
//PARAMETERS:
//None
//----------------------------------------------
	Reverse_Iterator rend();
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
		Const_Reverse_Iterator(Elem* position);

		Const_Reverse_Iterator operator++();

		Const_Reverse_Iterator operator++(int);

		bool operator==(const Const_Reverse_Iterator& other) const;

		bool operator!=(const Const_Reverse_Iterator& other) const;

		const T& operator*();

		const T* operator->();
	};

	Const_Reverse_Iterator rbegin() const;

	Const_Reverse_Iterator rend() const;
//--------------------------------------------
//FUNCTION: Iterator insert(Iterator pos, const T& x)
//Inserts an element in the list just before the pos iterator
//
//PARAMETERS:
//Iterator pos - iterator, shows where to insert the element
//const T& x - the value of the new element
//----------------------------------------------
	Iterator insert(Iterator pos, const T& x);
//--------------------------------------------
//FUNCTION: Iterator erase(Iterator pos)
//Deletes an object, pointed to by the iterator
//
//PARAMETERS:
//Iterator pos - iterator, shows where to insert the element
//----------------------------------------------
	Iterator erase(Iterator pos);
//--------------------------------------------
//FUNCTION: Iterator erase(Iterator first, Iterator last)
//Deletes all objects in a given range
//
//PARAMETERS:
//Iterator first - start position, included in the deleting
//Iterator last - stop position, not included in the deleting
//----------------------------------------------
	Iterator erase(Iterator first, Iterator last);
};
#endif
