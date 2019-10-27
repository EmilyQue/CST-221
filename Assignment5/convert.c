//References: 

#include <stdio.h>

unsigned int decimal, shift, add;
int final, result;
int binary[32];

//function to convert decimal to binary
void binaryConvert(int n) {
	int i = 0;
	//stores remainder of decimal in array
	while (n > 0) {
		binary[i] = n % 2;
		n = n / 2;
		i++;
	}
	//prints reverse order of binary array
	for (int j = i - 1; j >= 0; j--) {
		printf("%d ", binary[j]);
	}

}

//function to convert decimal to hexadecimal
void hexadecimal(int n) {
	printf("%X\n", decimal);
}

//function to shift input number 
void shiftDecimal() {
	//shift number 16 bits to the left
	shift = decimal << 16;
	//mask out bottom 16 bits
	shift &= ~0xFFFF;
	//add hex number (decimal = 2047)
	shift |= 0x07FF;
	//print shifted decimal result
	printf("Shifted Decimal Result: %d\n", shift);
	//print shifted binary result
	printf("Shifted Decimal to Binary Conversion: ");
	binaryConvert(shift);
	//print shifted hexadecimal result
	printf("\nShifted Decimal to Hexadecimal: ");
	hexadecimal(shift);
}

int main() {
	//receives and reads user input
	printf("Please enter an integer between 0 and 4095: ");
	scanf("%d", &decimal);

	//notifies user if integer is out of range
	if (decimal < 0 || decimal > 4095) {
	printf("Integer is out of range");
	}
	//converts input to binary and hexadecimal, and shifts input numbers
	else {
	printf("Decimal to Binary Conversion: ");
	binaryConvert(decimal);
	printf("\nDecimal to Hexadecimal: ");
	hexadecimal(decimal);
	printf("\nShifting Numbers...\n");
	shiftDecimal();
	}

	return 0;
}
