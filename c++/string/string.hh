#ifndef STRING_H
#define STRING_H

#include <iostream>

class String{
	int size_;
	int capacity_;
	char* buffer_;
public:
	String();

	String(int capacity);

	String(const char* str);

	~String();
	
	int size() const;

	int length() const;

	int capacity() const;

	bool empty() const;

	void clear();

	char& operator[](int index) const;

	char& at(int index);

	bool operator==(const String& other);

	bool operator!=(const String& other);

	bool operator<(const String& other);

	bool operator>(const String& other);

	bool operator<=(const String& other);

	bool operator>=(const String& other);

	String(const String& other);

	String& operator=(const String& other);

	class Iterator{
		char* iterator_;
	public:
		Iterator(char* in);

		Iterator& operator=(const Iterator& it);

		Iterator operator++();

		Iterator operator++(int);

		bool operator==(const Iterator& other) const;
		
		bool operator!=(const Iterator& other) const;

		char& operator*() const;
	};

	Iterator begin() const;

	Iterator end() const;

	String& append(const String& other);

	String& operator+=(const String& other);

	void push_back(char ch);

	String operator+(const String& other);
};

ostream& operator<<(ostream& out, const String& str);

#endif
