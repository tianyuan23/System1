#include <stdio.h>
#include <stdlib.h>

void function1(int);
void function2(int);
void function3(int);
void function4(int);
void printResult(void(**)(int));

/*
Author: Tianyuan Li

This program prompts the user to enter a choice of noe of the four numbered functiuons, and output a message of which function the user chose.
*/
int main() {
	void (*fp[4])(int) = {function1, function2, function3, function4};
	printResult(fp);
	return 0;
}

/*This function is to print function1.*/
void function1(int option) {
	printf("You chose function %i!\n", option);
}

/*This function is to print function2.*/
void function2(int option) {
	printf("You chose function %i!\n", option);
}

/*This function is to print function3.*/
void function3(int option) {
	printf("You chose function %i!\n", option);
}

/*This function is to terminate the program.*/
void function4(int option) {
	exit(0);
}

/*This function pointer is to get the option teh user choose and then print the result.*/
void printResult(void(**fp)(int)) {
	int option;
	while (1) {
		printf("Please choose a function number from 1 to 4:\n");
		scanf("%i", &option);
		if ((option > 0) && (option <= 4)) {
			fp[option - 1](option);
		}
		else {
			printf("Your choice of function number is not one of the possible options. Choose 1, 2, 3 or 4!\n");
		}
	}
}

