#include <iostream>
class X{
public:
	int x_;
X& operator=(const X& x){
  if(this==&x)  
    return *this;
  x.x_++;
 }
};
int main()
{
	X x, y;
	x = y;
	std::cout << x.x_ << y.x_;
	return 0;
}