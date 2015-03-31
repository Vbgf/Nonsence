class B {
public:
         void fun(void)const{};
};

class D: public B {
public:
      	 virtual void fun(void)const{};
};

int main() {
        D d;
        B* pb=&d;
        pb->fun();
}
