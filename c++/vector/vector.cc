#include<iostream>
using namespace std;

#define START_SIZE 10
#define START_DATA 0

template<typename T>
class Vector{
	T* array_;
	int size_count_;	//size of the allocated memory
	int data_count_;    //memory in use
public:
	Vector()
	: array_(new T [START_SIZE]),
	size_count_(START_SIZE),
	data_count_(START_DATA){
		for(int i=0; i<size_count_; i++){
			array_[i] = 0;
		}
	}

	int size() const{
		return size_count_;
	}

	int data() const{
		return data_count_;
	}

	void print() const{
		for(int i=0; i<size_count_; i++){
			cout << "Element " << i << " is " << array_[i] << endl;
		}
	}

	T operator[](int position) const{
		return array_[position];
	}
};

int main(){
	Vector <int> a;
	cout << "Vector size: " << a.size() << endl;
	cout << "Data in vector: " << a.data() << endl;
	cout << "Element 3 is: " << a[3] << endl;;
	a.print();
	return 0;
}
