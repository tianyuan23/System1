#include <stdio.h>
#include <stdlib.h>

void function1();
void function2();
void function3();
void function4();
void printResult(void(**)());

int main() {
	void (*fp[4])() = {function1, function2, function3, function4};
	printResult(fp);
	return 0;
}

void function1() {
	printf("You chose function 1\n");
}

void function2() {
	printf("You chose function 2\n");
}

void function3() {
	printf("You chose function 3\n");
}

void function4() {
	exit(0);
}

void printResult(void(**fp)()) {
	int option;
	while (1) {
		printf("Please choose a function number from 1 to 4:\n");
		scanf("%i", &option);
		if ((option > 0) && (option <= 4)) {
			fp[option - 1]();
		}
		else {
			printf("Your choice of function number is not one of the possible options. Choose 1, 2, 3 or 4!\n");
		}
	}
}

