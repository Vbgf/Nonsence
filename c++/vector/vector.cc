//--------------------------------------------
//NAME: Vasil Kolev
//CLASS: XIb
//NUMBER: 6
//PROBLEM: #2
//FILE NAME: vector.cc
//FILE PURPOSE:
//
//This file contains the class vector and it's
//implementation
//---------------------------------------------
#include <iostream>
#include <stdlib.h>
using namespace std;

#define DEFAULT_START_SIZE 10

template <class T> class Vector{
	int capacity_;
	int size_;
	T* buffer_;
public:
//--------------------------------------------
//FUNCTION: Vector()
//Constructor with no parameters
//
//PARAMETERS:
//None
//----------------------------------------------
	Vector()
	:capacity_(DEFAULT_START_SIZE),
	size_(0),
	buffer_(new T [DEFAULT_START_SIZE])
	{}
//--------------------------------------------
//FUNCTION: Vector(int capacity)
//This constructor makes a new object with
//a defined capacity 
//
//PARAMETERS:
//capacity - the custom start capacity
//----------------------------------------------
	Vector(int capacity)
	:capacity_(capacity),
	size_(0),
	buffer_(new T [capacity])
	{}
//--------------------------------------------
//FUNCTION: ~Vector()
//Destructor, executes when the object is deleted
//
//PARAMETERS:
//None
//----------------------------------------------
	~Vector(){
		delete[] buffer_;
	}
//--------------------------------------------
//FUNCTION: int size() const
//Function that returns the size of the vector
//
//PARAMETERS:
//None
//----------------------------------------------
	int size() const{
		return size_;
	}
//--------------------------------------------
//FUNCTION: bool empty() const
//Checks if the vector is empty
//
//PARAMETERS:
//None
//----------------------------------------------
	bool empty() const{
		if(size_==0){
			return true;
		}else{
			return false;
		}
	}
//--------------------------------------------
//FUNCTION: T& operator[](T n)
//Enables the use of the operator[] on the
//vector object
//
//PARAMETERS:
//n - which element in order to extract
//----------------------------------------------
	T& operator[](T n){
		return *(buffer_ + n);
	}
//--------------------------------------------
//FUNCTION: const T& operator[](T n) const
//Enables the use of the operator[] on a
//constant vector object
//
//PARAMETERS:
//n - which element in order to extract
//----------------------------------------------
	const T& operator[](T n) const{
		return *(buffer_ + n);
	}
//--------------------------------------------
//FUNCTION: void clear()
//Clears all the data in the vector
//
//PARAMETERS:
//None
//----------------------------------------------
	void clear(){
		delete[] buffer_;
		buffer_ = new T[DEFAULT_START_SIZE];
		capacity_ = DEFAULT_START_SIZE;
		size_ = 0;
	}
//--------------------------------------------
//FUNCTION: int capacity() const
//Returns the allocated memory for the vector
//
//PARAMETERS:
//None
//----------------------------------------------
	int capacity() const{
		return capacity_;
	}
//--------------------------------------------
//FUNCTION: Vector(const Vector& other)
//This is a copy constructor
//
//PARAMETERS:
//const Vector& other - the object to be copied
//----------------------------------------------
	Vector(const Vector& other)
	:capacity_(other.size()),
	size_(0){
		buffer_ = new T[other.size()];
		for(int i=0;i<other.size();i++){
			buffer_[i] = other[i];
			size_++;
		}
	}
//--------------------------------------------
//FUNCTION: Vector& operator=(const Vector& other)
//This function enables inheriting by the operator=
//
//PARAMETERS:
//const Vector& other - the object to inherited
//----------------------------------------------
	Vector& operator=(const Vector& other){
		size_ = 0;
		if(other.size()>capacity_){
			delete[] buffer_;
			capacity_ = other.size();
			buffer_ = new T[capacity_];
			for(int i=0;i<other.size();i++){
				buffer_[i] = other[i];
				size_++;
			}
		}else{
			for(int i=0;i<other.size();i++){
				buffer_[i] = other[i];
				size_++;
			}
		}
	}

	class Iterator{
		T* iterator_;
	public:
		Iterator(T* it)
		:iterator_(it)
		{}

		Iterator operator++(){
			iterator_++;
			return *this;
		}

		Iterator operator++(int){
			iterator_++;
			return *this;
		}

		bool operator==(const Iterator& other) const{
			if(*iterator_ == *other){
				return true;
			}else{
				return false;
			}
		}

		bool operator!=(const Iterator& other) const{
			if(*iterator_ != *other){
				return true;
			}else{
				return false;
			}	
		}
		
		T& operator*(){
			return *iterator_;
		}

		T* operator->(){
			return iterator_;
		}
	};

	Iterator begin(){
		Iterator it(buffer_);
		return it;
	}

	Iterator end(){
		Iterator it(buffer_ + size_);
		return it;
	}

	class Const_Iterator{
		T* iterator_;
	public:
		Const_Iterator(T* it)
		:iterator_(it)
		{}
	
		Const_Iterator operator++(){
			iterator_++;
			return *this;
		}

		Const_Iterator operator++(int){
			iterator_++;
			return *this;
		}

		bool operator==(const Iterator& other) const{
			if(*iterator_ == *other){
				return true;
			}else{
				return false;
			}
		}

		bool operator!=(const Iterator& other) const{
			if(*iterator_ != *other){
				return true;
			}else{
				return false;
			}	
		}
		
		const T& operator*(){
			return *iterator_;
		}

		const T* operator->(){
			return iterator_;
		}
	};

	Const_Iterator begin() const{
		Iterator it(buffer_);
		return it;
	}

	Const_Iterator end() const{
		Iterator it(buffer_ + size_);
		return it;
	}

	class Reverse_Iterator{
		T* iterator_;
	public:
		Reverse_Iterator(T* it)
		:iterator_(it)
		{}

		Reverse_Iterator operator++(){
			iterator_--;
			return *this;
		}

		Reverse_Iterator operator++(int){
			iterator_--;
			return *this;
		}

		bool operator==(const Iterator& other) const{
			if(*iterator_ == *other){
				return true;
			}else{
				return false;
			}
		}

		bool operator!=(const Iterator& other) const{
			if(*iterator_ != *other){
				return true;
			}else{
				return false;
			}	
		}
		
		T& operator*(){
			return *iterator_;
		}

		T* operator->(){
			return iterator_;
		}
	};

	Reverse_Iterator rbegin(){
		Reverse_Iterator it(buffer_);
		return it;
	}

	Reverse_Iterator rend(){
		Reverse_Iterator it(buffer_ + size_);
		return it;
	}

	class Const_Reverse_Iterator{
		T* iterator_;
	public:
		Const_Reverse_Iterator(T* it)
		:iterator_(it)
		{}

		Const_Reverse_Iterator operator++(){
			iterator_--;
			return *this;
		}

		Const_Reverse_Iterator operator++(int){
			iterator_--;
			return *this;
		}

		bool operator==(const Iterator& other) const{
			if(*iterator_ == *other){
				return true;
			}else{
				return false;
			}
		}

		bool operator!=(const Iterator& other) const{
			if(*iterator_ != *other){
				return true;
			}else{
				return false;
			}	
		}
		
		const T& operator*(){
			return *iterator_;
		}

		const T* operator->(){
			return iterator_;
		}		
	};

	Const_Reverse_Iterator rbegin() const{
		Reverse_Iterator it(buffer_);
		return it;
	}

	Const_Reverse_Iterator rend() const{
		Reverse_Iterator it(buffer_ + size_);
		return it;
	}

	T& front(){
		return *buffer_;
	}

	const T& front() const{
		return *buffer_;
	}

	T& back(){
		return buffer_[size_ -1];
	}

	const T& back() const{
		return buffer_[size_ -1];
	}

	void push_back(const T& element){
		if(size_ == capacity_){
			capacity_ += DEFAULT_START_SIZE;
			T* temp = new T[capacity_];
			for(int i=0;i<size_;i++){
				temp[i] = buffer_[i];
			}
			size_++;
			temp[size_] = element;
			delete[] buffer_;
			buffer_ = temp;
		}else{
			buffer_[size_] = element;
			size_++;
		}
	}

	void pop_back(){
		if(size_>=0){
			size_--;
		}
	}

	Iterator insert(Iterator pos, const T& x){
		
	}

	Iterator erase(Iterator pos){

	}

	Iterator erase(Iterator first, Iterator last){

	}
};

//--------------------------------------------
//FUNCTION: int main()
//The main objective is met here
//
//PARAMETERS:
//int argc - number of arguments
//char* argv[] - the input arguments
//----------------------------------------------
int main(int argc, char* argv[]){
	if(argc>1){
		if(argc%2==1){
			//1
			Vector<int> v1, v2;
			int v1_b = atoi(argv[1]);
			int v1_e = atoi(argv[2]);
			int v2_b = atoi(argv[3]);
			int v2_e = atoi(argv[4]);
			for(int i=v1_b; i<v1_e; i++){
				v1.push_back(i);
			}
			for(int i=v2_b; i<v2_e;i++){
				v2.push_back(i);
			}
			//2
			cout << "v1:   {";
			for(int i = 0; i<v1.size(); i++){
				cout << v1[i] << ",";
			}
			cout << "}" << endl;
			cout << "v2:   {";
			for(int i = 0; i<v2.size(); i++){
				cout << v2[i] << ",";
			}
			cout << "}" << endl;
			//3
			//4
			v1.push_back(-100);
			v2.push_back(-100);
			cout << "v1:   {";
			for(int i = 0; i<v1.size(); i++){
				cout << v1[i] << ",";
			}
			cout << "}" << endl;
			cout << "v2:   {";
			for(int i = 0; i<v2.size(); i++){
				cout << v2[i] << ",";
			}
			cout << "}" << endl;
			//5
			Vector<int> v(v2);
			cout << "v:    {";
			for(int i = 0; i<v.size(); i++){
				cout << v[i] << ",";
			}
			cout << "}" << endl;
			//6
			//7
		}else{
			cout << "Argument error! - Must define an interval" << endl;
			return 0;
		}
	}else{
		cout << "Argument error! - Too few arguments" << endl;
		return 0;
	}
	return 0;
}
