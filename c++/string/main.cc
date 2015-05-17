#include <iostream>
#include "string.hh"
using namespace std;

int main(int argc, char* argv[]){
	if(argc < 3){
		cout << "Too few arguments!" << endl;
	}else{
		try{
			//2
			String str1 = argv[1];
			String str2 = argv[2];
			//3
			cout << "string 1: <" << str1 << ">" << endl;
			cout << "string 2: <" << str2 << ">" << endl;
			//4
			cout << "string 1 lenght: " << str1.size() << endl;
			cout << "string 2 lenght: " << str2.size() << endl;
			//5
			int count = 0;
			for(String::Iterator it = str1.begin(); it!=str1.end(); it++){
				if (*it == ' '){
					count++;
				}
			}
			cout << "string 1 spaces: " << count << endl;
			count = 0;
			for(String::Iterator it = str2.begin(); it!=str2.end(); it++){
				if (*it == ' '){
					count++;
				}
			}
			cout << "string 2 spaces: " << count << endl;
			//6
			if(str1<str2){
				cout << "<" << str1 << "> is smaller than <" << str2 << ">" << endl;
			}else if(str1>str2){
				cout << "<" << str1 << "> is greater than <" << str2 << ">" << endl;
			}else{
				cout << "<" << str1 << "> is equal to <" << str2 << ">" << endl;
			}
			//7
			str1.push_back('!');
			str2.push_back('!');
			cout << "string 1: <" << str1 << ">" << endl;
			cout << "string 2: <" << str2 << ">" << endl;
			//8		
			String str = str1 + str2;
			cout << "concatenation: <" << str << ">" << endl;
			//9
			cout << "concatenatoin length: " << str.size() << endl;
			//10
			count = 0;
			for(String::Iterator it = str.begin(); it!=str.end(); it++){
				if (*it == ' '){
					count++;
				}
			}
			cout << "concatenation spaces: " << count << endl;
		}catch(const out_of_range){
			cout << "Exception cought, out of range!" << endl;
		}
	}
	return 0;
}
