/*

Set bit in a bit array represented by unsigned chars

param[out] dest - The memory area the bit array is stored
param[in] pos -The position of the bit to be written
param[in] len - The length of the array in unsigned chars,
if the bit is outside of the array it is not accepted

return 0 if success, -1 if the destination position is
out of range or val is not acceptable value

int set_bit(unsigned char* dest, unsigned long pos, unsigned long len){
	//
	return -1;
}

*/

#include <stdio.h>
#include <math.h>

int set_bit(unsigned char* dest, unsigned long pos, unsigned long len){
	printf("Inside set_bit:\n");
	printf("Input:\n");
	printf("len: %ld\n", len);
	printf("pos: %ld\n", pos);
	printf("ch: %s\n", dest);
	printf("dest: %p\n", dest);

	if(pos<len*8){
		*dest = *dest | (int)pow(2,pos);
		printf("Output:\n");
		printf("len: %ld\n", len);
		printf("pos: %ld\n", pos);
		printf("ch: %s\n", dest);
		printf("dest: %p\n\n", dest);
		return 0;
	}

	return -1;
}

// Test

int main(){
	unsigned long len = 8;
	unsigned long pos = 2;
	unsigned char ch = 'A';
	unsigned char* dest = &ch;

	printf("Inside main:\n");
	printf("len: %ld\n", len);
	printf("pos: %ld\n", pos);
	printf("ch: %c\n", ch);
	printf("dest: %p\n\n", dest);

	printf("set_bit returned: %d\n", set_bit(dest, pos, len));
	return 0;
}
