#include <iostream>
#include <stdexcept>
#include <cstring>
using namespace std;

#define DEFAULT_START_SIZE 10

class String{
	int size_;
	int capacity_;
	char* buffer_;
public:
	String()
	:size_(0),
	capacity_(DEFAULT_START_SIZE),
	buffer_(new char[DEFAULT_START_SIZE])
	{
		cout << "In String()" << endl;
	}

	String(int capacity)
	:capacity_(capacity){
		buffer_ = new char[capacity];
		size_ = 0;
		cout << "In String(int capacity)" << endl;
	}

	String(const char* str)
	{
		cout << "In String(const char* str)" << endl;
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

	~String(){
		delete[] buffer_;
	}
	
	int size() const{
		return size_;
	}

	int length() const{
		return size_;
	}

	int capacity() const{
		return capacity_;
	}

	bool empty() const{
		if (size_ == 0){
			return true;
		}else{
			return false;
		}
	}

	void clear(){
		delete[] buffer_;
		buffer_ = new char[DEFAULT_START_SIZE];
		capacity_ = DEFAULT_START_SIZE;
		size_ = 0;
	}

	char& operator[](int index) const{
		return *(buffer_ + index);
	}

	char& at(int index){
		if(index>size_){
			throw out_of_range ("OOR");
		}else{
			return *(buffer_ + index);
		}
	}

	bool operator==(const String& other){
		for(int i = 0; i<size_; i++){
			if(buffer_[i] - other[i] != 0){
				return 0;
			}
		}
		return 1;
	}

	bool operator!=(const String& other){
		for(int i = 0; i<size_; i++){
			if(buffer_[i] - other[i] != 0){
				return 1;
			}
		}
		return 0;
	}

	bool operator<(const String& other){
		for(int i = 0; i<size_; i++){
			if(buffer_[i] - other[i] < 0){
				return 1;
			}
		}
		return 0;
	}

	bool operator>(const String& other){
		for(int i = 0; i<size_; i++){
			if(buffer_[i] - other[i] > 0){
				return 1;
			}
		}
		return 0;
	}

	bool operator<=(const String& other){
		for(int i = 0; i<size_; i++){
			if(buffer_[i] - other[i] <= 0){
				return 1;
			}
		}
		return 0;
	}

	bool operator>=(const String& other){
		for(int i = 0; i<size_; i++){
			if(buffer_[i] - other[i] >= 0){
				return 1;
			}
		}
		return 0;
	}

	String(const String& other){
		cout << "In String(const String& other)" << endl;
		buffer_ = new char[other.size()];
		for(int i=0; i<other.size(); i++){
			buffer_[i] = other[i];
		}
	}

	String& operator=(const String& other){
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

	class Iterator{
		char* iterator_;
	public:
		Iterator(char* in)
		:iterator_(in)
		{}

		Iterator& operator=(const Iterator& it){
			iterator_ = &(*it);
			return *this;
		}

		Iterator operator++(){
			iterator_ ++;
			return *this;
		}

		Iterator operator++(int){
			iterator_ ++;
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

		char& operator*() const{
			return *iterator_;
		}
	};

	Iterator begin() const{
		Iterator it(buffer_);
		return it;
	}

	Iterator end() const{
		Iterator it(buffer_+size_);
		return it;
	}

	String& append(const String& other){

	}

	String& operator+=(const String& other){

	}

	void push_back(char ch){
		if(size_==capacity_){
			capacity_ = size_+DEFAULT_START_SIZE;
			char* temp = new char[capacity_];
			int i =0;
			for(i=0; i<size_; i++){
				temp[i] = buffer_[i];
			}
			temp[(i)] = ch;
			size_++;
			temp[i+1] = '\0';
			buffer_ = temp;
		}else{
			buffer_[size_] = ch;
			size_++;
			buffer_[size_] = '\0';
		}
	}

	String operator+(const String& other){

	}
};

ostream& operator<<(ostream& out, const String& str){
	for(int i = 0;i<str.size();i++){
		out << str[i];
	}
	return out;
}

int main(){
	String s1(3);
	cout << "size of s1 = " << s1.size() << endl;
	String s2;
	cout << "size of s2 = " << s2.size() << endl;
	String s3 = "Ha";
	cout << "Is s3 empty? " << s3.empty() << endl;
	cout << "size of s3 = " << s3.size() << endl;
	cout << "length of s3 = " << s3.length() << endl;
	cout << "capacity of s3 = " << s3.capacity() << endl;
	cout << "the second element of s3 = " << s3[1] <<  endl;
	cout << "the s3 element = " << s3 << endl;
	cout << "the at(1) = " << s3.at(1) << endl;
	try{
		cout << "the at(10) = " << s3.at(10) << endl;
	}catch(const out_of_range){
		cout << "Exception cought, out of range boyy!" << endl;
	}
	s3.clear();
	cout << "s3 after clear = " << s3 << "|<- end here" << endl; 
	cout << "Is s3 empty? " << s3.empty() << endl;
	String s4 = "Hell";
	cout << "the s4 element = " << s4 << endl;
	s4 = "LOL NOPE";
	cout << "the s4 element after the change = " << s4 << endl;
	String s5 = "LOL NOPE";
	bool result = s4==s5;
	cout << "s4==s5 (should be true) = " << result << endl;
	result = s4!=s5;
	cout << "s4!=s5 (should be false) = " << result << endl;
	result = s4<=s5;
	cout << "s4<=s5 (should be true) = " << result << endl;
	result = s4>=s5;
	cout << "s4>=s5 (should be true) = " << result << endl;
	s4 = "aaa";
	s5 = "bbb";
	result = s4>s5;
	cout << "s4>s5 (should be false) = " << result << endl;
	result = s4<s5;
	cout << "s4<s5 (should be true) = " << result << endl;
	String s6(s5);
	String s7 = "BLAH";
	String::Iterator it = s7.begin();
	cout << "String::Iterator it points to (should be begin)= " << *it << endl;
	result = it==s7.end();
	cout << "it==s7.end() (should be false) = " << result << endl;
	for(int i =0; i<s7.size(); i++){
		cout << "String::Iterator it points to = " << *it << endl;
		++it;
	}
	cout << "String::Iterator it points to (should be end)= " << *it << "|<- end here" << endl;
	result = it==s7.end();
	cout << "it==s7.end() (should be true) = " << result << endl;
	cout << "it==s7.end() (should be true) = " << result << endl;
	it = s7.begin();
	cout << "String::Iterator it points to = " << *it << endl;
	it++;
	cout << "String::Iterator it points to = " << *it << endl;
	++it;
	cout << "String::Iterator it points to = " << *it << endl;
	cout << "the s1 element = " << s1 << "|<- end here" << endl;
	s1.push_back('A');
	cout << "the s1 element after push_back= " << s1 << endl;

	for(int i=0; i<1000; i++){
		s1.push_back('A');
		cout << "the s1 element after push_back= " << s1 << endl;
	}
	cout << "If you are here, there is no crash!" << endl;
	String s8 = "ABCDEFGH";
	cout << "s8 size = " << s8.size() << endl;
	cout << "s8 capcaity = " << s8.capacity() << endl;
	cout << "s8 is = " << s8 << endl;
	s8.push_back('I');
	cout << "s8 size = " << s8.size() << endl;
	cout << "s8 capcaity = " << s8.capacity() << endl;
	cout << "s8 is = " << s8 << endl;
	return 0;
}
