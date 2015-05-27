#include <iostream>
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
	List()
	: head_(0),
	  tail_(0),
	  size_(0)
	{}

	~List(){
		//while(head_ && tail_){
		//	pop_back();
		//}
	}

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

	T& front(){
		return head_->data_;
	}

	const T& front() const{
		return head_->data_;
	}

	T& back(){
		return tail_->data_;
	}

	const T& back() const{
		return tail_->data_;
	}

	int size() const{
		return size_;
	}

	bool empty() const{
		if(size_ == 0){
			return 1;
		}else{
			return 0;
		}
	}

	void clear(){

	}

	void swap(List& other){

	}
};

int main(){
	List<int> l1;
	cout << "Size after last change = " << l1.size() << endl;
	cout << "is it empty? = " << l1.empty() << endl;
	l1.push_back(123);
	l1.push_back(123);
	cout << "Size after last change = " << l1.size() << endl;
	cout << "is it empty? = " << l1.empty() << endl;
	l1.pop_back();
	l1.pop_back();
	l1.pop_back();
	cout << "Size after last change = " << l1.size() << endl;
	cout << "is it empty? = " << l1.empty() << endl;
	l1.push_front(222);
	l1.push_front(222);
	cout << "Size after last change = " << l1.size() << endl;
	cout << "is it empty? = " << l1.empty() << endl;
	l1.pop_front();
	l1.pop_front();
	l1.pop_front();
	cout << "Size after last change = " << l1.size() << endl;
	cout << "is it empty? = " << l1.empty() << endl;
	l1.push_back(11);
	l1.push_back(22);
	cout << "Size after last change = " << l1.size() << endl;
	cout << "is it empty? = " << l1.empty() << endl;
	cout << l1.front() << endl;
	cout << l1.back() << endl;
	const List<int> l2 = l1; //tested before the copy constr was made
	cout << l2.front() << endl;
	cout << l2.back() << endl;
	cout << "Size after last change = " << l2.size() << endl;
	cout << "is it empty? = " << l1.empty() << endl;

	//TODO
	//fix the destructor because it's leaking memory left and right
	//make the clear funct and continue on with the rest
	return 0;
}
