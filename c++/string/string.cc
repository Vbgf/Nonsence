//--------------------------------------------
//NAME: Vasil Kolev
//CLASS: XIb
//NUMBER: 6
//PROBLEM: #1
//FILE NAME: string.cc
//FILE PURPOSE:
//
//This file contains all the function implementations
//for the string and string::iterator classes
//
//---------------------------------------------

#include <iostream>
#include <stdexcept>
#include "string.hh"
using namespace std;

#define DEFAULT_START_SIZE 10

String::String()
:size_(0),
capacity_(DEFAULT_START_SIZE),
buffer_(new char[DEFAULT_START_SIZE])
{}

String::String(int capacity)
:capacity_(capacity){
	buffer_ = new char[capacity];
	size_ = 0;
}

String::String(const char* str)
{
	capacity_ = 0;
	size_ = 0;
	for(int i = 0;;i++){
		if(str[i] == '\0'){
			capacity_ = i;
			size_ = i;
			break;
		}
	}
	buffer_ = new char[capacity_];
	for(int i = 0;;i++){
		buffer_[i] = str[i];
		if(str[i] == '\0'){
			break;
		}
	}
}

String::~String(){
	delete[] buffer_;
}

int String::size() const{
	return size_;
}

int String::length() const{
	return size_;
}

int String::capacity() const{
	return capacity_;
}

bool String::empty() const{
	if (size_ == 0){
		return true;
	}else{
		return false;
	}
}

void String::clear(){
	delete[] buffer_;
	buffer_ = new char[DEFAULT_START_SIZE];
	capacity_ = DEFAULT_START_SIZE;
	size_ = 0;
}

char& String::operator[](int index) const{
	return *(buffer_ + index);
}

char& String::at(int index){
	if(index>size_){
		throw out_of_range ("OOR");
	}else{
		return *(buffer_ + index);
	}
}

bool String::operator==(const String& other){
	for(int i = 0; i<size_; i++){
		if(buffer_[i] - other[i] != 0){
			return 0;
		}
	}
	return 1;
}

bool String::operator!=(const String& other){
	for(int i = 0; i<size_; i++){
		if(buffer_[i] - other[i] != 0){
			return 1;
		}
	}
	return 0;
}

bool String::operator<(const String& other){
	for(int i = 0; i<size_; i++){
		if(buffer_[i] - other[i] < 0){
			return 1;
		}
	}
	return 0;
}

bool String::operator>(const String& other){
	for(int i = 0; i<size_; i++){
		if(buffer_[i] - other[i] > 0){
			return 1;
		}
	}
	return 0;
}

bool String::operator<=(const String& other){
	for(int i = 0; i<size_; i++){
		if(buffer_[i] - other[i] <= 0){
			return 1;
		}
	}
	return 0;
}

bool String::operator>=(const String& other){
	for(int i = 0; i<size_; i++){
		if(buffer_[i] - other[i] >= 0){
			return 1;
		}
	}
	return 0;
}

String::String(const String& other){
	capacity_ = other.size();
	buffer_ = new char[capacity_];
	for(int i=0; i<other.size(); i++){
		buffer_[i] = other[i];
	}
	size_ = other.size();
}

String& String::operator=(const String& other){
	int other_size = 0;
	for(int i = 0;;i++){
		if(other[i] == '\0'){
			other_size = i;
			break;
		}
	}
	if (other_size > size_){
		delete[] buffer_;
		buffer_ = new char[other_size];
		capacity_ = other_size;
	}
	for(int i = 0; i<other_size; i++){
		buffer_[i] = other[i];
	}
	size_ = other_size;
	return *this;
}

String::Iterator::Iterator(char* in)
:iterator_(in)
{}

String::Iterator& String::Iterator::operator=(const Iterator& it){
	iterator_ = &(*it);
	return *this;
}

String::Iterator String::Iterator::operator++(){
	iterator_ ++;
	return *this;
}

String::Iterator String::Iterator::operator++(int){
	iterator_ ++;
	return *this;
}

bool String::Iterator::operator==(const Iterator& other) const{
	if(*iterator_ == *other){
		return true;
	}else{
		return false;
	}
}

bool String::Iterator::operator!=(const Iterator& other) const{
	if(*iterator_ != *other){
		return true;
	}else{
		return false;
	}
}

char& String::Iterator::operator*() const{
	return *iterator_;
}

String::Iterator String::begin() const{
	Iterator it(buffer_);
	return it;
}

String::Iterator String::end() const{
	Iterator it(buffer_+size_);
	return it;
}

String& String::append(const String& other){
	if(capacity_<size_+other.size()){
		capacity_ = size_+other.size();
		char* temp = new char[capacity_];
		int i;
		for(i=0; i<size_; i++){
			temp[i] = buffer_[i];
		}
		for(i; i<size_+other.size(); i++){
			temp[i] = other[i-size_];
		}
		size_+=other.size();
		buffer_ = temp;
	}else{
		for(int i=size_; i<size_+other.size(); i++){
			buffer_[i] = other[i-size_];
		}
		size_+=other.size();
	}
	return *this;
}

String& String::operator+=(const String& other){
	return this->append(other);
}

void String::push_back(char ch){
	if(size_==capacity_){
		capacity_ = size_+DEFAULT_START_SIZE;
		char* temp = new char[capacity_];
		int i;
		for(i=0; i<size_; i++){
			temp[i] = buffer_[i];
		}
		temp[i] = ch;
		size_++;
		temp[i+1] = '\0';
		buffer_ = temp;
	}else{
		buffer_[size_] = ch;
		size_++;
		buffer_[size_] = '\0';
	}
}

String String::operator+(const String& other){
	String temp(size_+other.size()+1);
	temp.append(*this);
	temp.append(other);
	return temp;
}

ostream& operator<<(ostream& out, const String& str){
	for(int i = 0;i<str.size();i++){
		out << str[i];
	}
	return out;
}
