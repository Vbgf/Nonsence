#ifndef CONTEXT_HH__
#define CONTEXT_HH__

#include <vector>

class Context{
	std:vector<double> data_stack_;

public:
	bool data_empty() const;
	unsigned data_size() const;
	
	void data_push(double val);
	void data_pop();
	double data_top() const;
};

#endif
