//--------------------------------------------
//NAME: Vasil Kolev
//CLASS: XIb
//NUMBER: 6
//PROBLEM: #1
//FILE NAME: string.hh
//FILE PURPOSE:
//
//This file contains all the function declarations
//for the string and string::iterator classes
//
//---------------------------------------------

#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <stdexcept>
using namespace std;

class String{
	int size_;
	int capacity_;
	char* buffer_;
public:
//--------------------------------------------
//FUNCTION: String()
//The default constructor for the string class
//
//PARAMETERS:
//None
//----------------------------------------------
	String();
//--------------------------------------------
//FUNCTION: String(int capacity)
//A constructor that makes a string object with
//a given capacity
//
//PARAMETERS:
//int capacity - the capacity of the new object
//----------------------------------------------
	String(int capacity);
//--------------------------------------------
//FUNCTION: String(const char* str)
//A constructor that makes a string object
//from an array of chars
//
//PARAMETERS:
//const char* str - the string which will be 
//copied in the new object
//----------------------------------------------
	String(const char* str);
//--------------------------------------------
//FUNCTION: ~String()
//The destructor of the string class, which frees
//all the allocated dynamic memory for the object
//
//PARAMETERS:
//None
//----------------------------------------------
	~String();
//--------------------------------------------
//FUNCTION: int size() const
//This function returns the size of the string
//
//PARAMETERS:
//None
//----------------------------------------------	
	int size() const;
//--------------------------------------------
//FUNCTION: int length() const
//This function returns the length of the string
//The same as int size() const
//
//PARAMETERS:
//None
//----------------------------------------------	
	int length() const;
//--------------------------------------------
//FUNCTION: int capacity() const
//This function returns the size if the
//currently allocated memory for the string object
//
//PARAMETERS:
//None
//----------------------------------------------	
	int capacity() const;
//--------------------------------------------
//FUNCTION: bool empty() const
//This function returns true(1) if the string is
//empty and false(0) if it isn't
//
//PARAMETERS:
//None
//----------------------------------------------	
	bool empty() const;
//--------------------------------------------
//FUNCTION: void clear()
//This function wipes the allocated memory
//for the object
//
//PARAMETERS:
//None
//----------------------------------------------	
	void clear();
//--------------------------------------------
//FUNCTION: char& operator[](int index) const
//This function allows for the use of the []
//operator on the string object
//Doesn't check if "index"  is in range.
//
//PARAMETERS:
//int index - specify the possition of the
//char you want returned
//----------------------------------------------	
	char& operator[](int index) const;
//--------------------------------------------
//FUNCTION: char& at(int index)
//This function returns the char at "index"
//from the string.
//Same as operator[].
//Checks if "index" is in range.
//
//PARAMETERS:
//int index - specify the possition of the
//char you want returned
//----------------------------------------------	
	char& at(int index);
//--------------------------------------------
//FUNCTION: char& at(int index)
//Allows the use of the == operator
//for comparing two string objects
//
//PARAMETERS:
//const String& other - the second string object
//----------------------------------------------
	bool operator==(const String& other);
//--------------------------------------------
//FUNCTION: char& at(int index)
//Allows the use of the != operator
//for comparing two string objects
//
//PARAMETERS:
//const String& other - the second string object
//----------------------------------------------
	bool operator!=(const String& other);
//--------------------------------------------
//FUNCTION: char& at(int index)
//Allows the use of the < operator
//for comparing two string objects
//
//PARAMETERS:
//const String& other - the second string object
//----------------------------------------------
	bool operator<(const String& other);
//--------------------------------------------
//FUNCTION: char& at(int index)
//Allows the use of the > operator
//for comparing two string objects
//
//PARAMETERS:
//const String& other - the second string object
//----------------------------------------------
	bool operator>(const String& other);
//--------------------------------------------
//FUNCTION: char& at(int index)
//Allows the use of the <= operator
//for comparing two string objects
//
//PARAMETERS:
//const String& other - the second string object
//----------------------------------------------
	bool operator<=(const String& other);
//--------------------------------------------
//FUNCTION: char& at(int index)
//Allows the use of the >= operator
//for comparing two string objects
//
//PARAMETERS:
//const String& other - the second string object
//----------------------------------------------
	bool operator>=(const String& other);
//--------------------------------------------
//FUNCTION: String(const String& other)
//The copy constructor for the string class.
//Returns a new object, identical to the
//one copied
//
//PARAMETERS:
//const String& other - the string object that
//needs to be copied
//----------------------------------------------
	String(const String& other);
//--------------------------------------------
//FUNCTION: String& operator=(const String& other)
//Enables the use of the operator=
//The string object inherits the "other"
//string object, coppying it's data
//
//PARAMETERS:
//const String& other - the string object that
//needs to be inherited
//----------------------------------------------
	String& operator=(const String& other);
//--------------------------------------------
//CLASS: String::Iterator
//Enables the use of iterators on the string class
//----------------------------------------------
	class Iterator{
		char* iterator_;
	public:
//--------------------------------------------
//FUNCTION: Iterator(char* in)
//The constructor of the iterator class
//
//PARAMETERS:
//char* in - the char that the iterator points to
//----------------------------------------------
		Iterator(char* in);
//--------------------------------------------
//FUNCTION: Iterator& operator=(const Iterator& it)
//Enables inherting from other iterators
//of the same type
//
//PARAMETERS:
//const Iterator& it - the iterator to inherit from
//----------------------------------------------
		Iterator& operator=(const Iterator& it);
//--------------------------------------------
//FUNCTION: Iterator operator++()
//Enables incrementing the iterator with
//the prefix operator++ (++it)
//
//PARAMETERS:
//None
//----------------------------------------------
		Iterator operator++();
//--------------------------------------------
//FUNCTION: Iterator operator++()
//Enables incrementing the iterator with
//the postfix operator++ (it++)
//
//PARAMETERS:
//None - the int is just for seperating the
//pre and postfix operators.
//----------------------------------------------
		Iterator operator++(int);
//--------------------------------------------
//FUNCTION: bool operator==(const Iterator& other) const
//Enables comparing of two itrators with
//the operator==
//
//PARAMETERS:
//const Iterator& other - the second iterator
//----------------------------------------------
		bool operator==(const Iterator& other) const;
//--------------------------------------------
//FUNCTION: bool operator!=(const Iterator& other) const
//Enables comparing of two itrators with
//the operator!=
//
//PARAMETERS:
//const Iterator& other - the second iterator
//----------------------------------------------		
		bool operator!=(const Iterator& other) const;
//--------------------------------------------
//FUNCTION: char& operator*() const
//Enables the use of the operator* (prefix)
//which allows the user to get the element
//the iterator is pointing to
//
//PARAMETERS:
//None
//----------------------------------------------
		char& operator*() const;
	};
//--------------------------------------------
//FUNCTION: Iterator begin() const
//Returns a iterator pointing to the first
//element of the string
//
//PARAMETERS:
//None
//----------------------------------------------
	Iterator begin() const;
//--------------------------------------------
//FUNCTION: Iterator end() const
//Returns a iterator pointing one element
//after the end of the string
//
//PARAMETERS:
//None
//----------------------------------------------
	Iterator end() const;
//--------------------------------------------
//FUNCTION: String& append(const String& other)
//This function joins two string objects together
//
//PARAMETERS:
//const String& other - the second string
//----------------------------------------------
	String& append(const String& other);
//--------------------------------------------
//FUNCTION: String& operator+=(const String& other)
//This function allows the user to append with
//the operator+= .
//Identical to the append() function
//
//PARAMETERS:
//const String& other - the second string
//----------------------------------------------
	String& operator+=(const String& other);
//--------------------------------------------
//FUNCTION: void push_back(char ch)
//Allows the inserting of new characters at
//the end of the string
//
//PARAMETERS:
//char ch - the character to be added
//----------------------------------------------
	void push_back(char ch);
//--------------------------------------------
//FUNCTION: String operator+(const String& other)
//Allows the use of operator+ for joining two
//strings together, simmilarly to append()
//and opearotr+=, but it returns an entirely new
//string object, and not changing anything
//in the other two strings
//
//PARAMETERS:
//const String& other - the second string
//----------------------------------------------
	String operator+(const String& other);
};
//--------------------------------------------
//FUNCTION: ostream& operator<<(ostream& out, const String& str)
//Allows easy printing of the whole
//string with the operator<< and cout
//
//PARAMETERS:
//ostream& out - the output stream
//const String& str - the string to be printed
//----------------------------------------------
ostream& operator<<(ostream& out, const String& str);

#endif
