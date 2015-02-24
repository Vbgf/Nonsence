#ifndef BINARY_OPERATION_HH__
#define BINARY_OPERATION_HH__

#include "operation.hh"

class BinaryOperation: public Operation{
	
protected:
	virtual double op(double a1, double a2) const = 0;
public:
	BinaryOperation(const std:string& token);
	
	void eval(Context&) const;
	
}

#endif
