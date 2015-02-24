#include "context.hh"

bool
Context::data_empty() const{
	return data_stack_.empty();
}

unsigned 
Context::data_size() const{
	return data_stack_.size();
}

void 
Context::data_push(double val){
	return data_stack_.push_back(val);
}

void 
Context::data_pop(){
	return data_stack_.pop_back();
}

double 
Context::data_top() const{
	return data_stack_.back();
}
