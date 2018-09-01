#include <stdio.h>
#include <stdlib.h>

struct Data {
	char title[40];
	char author[40];
	int stockNumber;
	float wholesalePrice;
	float retailPrice;
	int wholesaleQuantity;
	int retailQuantity;
};
typedef struct Node {
	struct Data book;
	struct Node *next;
} Node;

void getDataAndBuildList(Node **);
Node *createNodeAndGetData(void);
void insert(Node **, Node *);
void delete(Node **, int);
void getUserOption(Node **);
float calculateTotalRevenue(const Node *);
float calculateTotalWholesaleCost(const Node *);
float calculateTotalProfit(const Node *);
int calculateTotalBooksSold(const Node *);
float calculateAverageProfit(const Node *);
void printList(const Node *);
void freeNodes(Node **);

/*
Author: Tianyuan Li
This program is to store and process data of books. The user will enter data of books and the program will sort and store them into linked list by their stock numbers in an increasing order. After that, the program will repeatly prompt the user to choose one of nine options for processing the data.
*/
int main() {
	Node *head = NULL;
	getDataAndBuildList(&head);
	getUserOption(&head);
	return 0;
}

/* This function is to get the book data and store it into the linked list. */
void getDataAndBuildList(Node **const headAdr) {
	Node *newNodePtr;
	printf("Please enter data about the books.\n\n");
	while (newNodePtr = createNodeAndGetData()) {
		insert(headAdr, newNodePtr);
	}
}

/* This function is to create a Node to store the book data. */
Node *createNodeAndGetData(void) {
	Node *newNodePtr;
	newNodePtr = malloc (sizeof(Node));
	if (newNodePtr == NULL) {
		printf("Error: memory could not be allocated for enough nodes. ");
		printf("Terminating program!\n");
		exit (0);
	}
	else {
		scanf("%[^\n]", newNodePtr->book.title);
		/* determine if reach "END_DATA" or not*/
		if (strcmp(newNodePtr->book.title, "END_DATA") == 0) {
			/* free Node if end of book data detected */
			free(newNodePtr);			
			return NULL;
		}
		else {
			/* consume newline before author string */
			getchar();				
			scanf("%[^\n]s", newNodePtr->book.author);
			scanf("%i", &newNodePtr->book.stockNumber);
			scanf("%f", &newNodePtr->book.wholesalePrice);
			scanf("%f", &newNodePtr->book.retailPrice);
			scanf("%i", &newNodePtr->book.wholesaleQuantity);
			scanf("%i", &newNodePtr->book.retailQuantity);
			/* consume newline before next title string */
			getchar();				
		}
		return newNodePtr;
	}
}

/* This function is to insert a new Node into the linked list. */
void insert(Node **const headAdr,Node *newNodePtr) {
	Node *traversePtr = *headAdr;
	/* if it is an empty list */
	if (traversePtr == NULL) {
		*headAdr = newNodePtr;
		newNodePtr->next = NULL;
	}
	/* if the new Node stocknumber is less than the first Node stocknumber */
	else if (newNodePtr->book.stockNumber < traversePtr->book.stockNumber) {
		*headAdr = newNodePtr;
		newNodePtr->next = traversePtr;
	}
	/* if the new node stocknumber is in the middle of the list */
	else {
		Node *priorNode = traversePtr;
		traversePtr = traversePtr->next;
		/* moving the prioeNode and traversePtr */
		while ((traversePtr !=NULL) && (newNodePtr->book.stockNumber > traversePtr->book.stockNumber)) {
			priorNode = traversePtr;
			traversePtr = traversePtr->next;
		}
		newNodePtr->next = traversePtr;
		priorNode->next = newNodePtr;
	}
}

/* This function is to delete a Node from the linked list. */
void delete(Node ** const headAdr, int stockNumToDelete) {
	Node *traversePtr = *headAdr;
	if (traversePtr == NULL) {
		printf("ERROR: The list is empty. There are no books to delete!\n");
	}
	else if (stockNumToDelete == traversePtr->book.stockNumber) {
		*headAdr = traversePtr->next;
		free(traversePtr);
	}
	else {
		Node *priorNode = traversePtr;
		traversePtr = traversePtr->next;
		while ((traversePtr !=NULL) && (stockNumToDelete != traversePtr->book.stockNumber)) {
			priorNode = traversePtr;
			traversePtr = traversePtr->next;
		}
		if (traversePtr == NULL) {
			printf("\nERROR: Book stock number %i was not found in the list!\n", stockNumToDelete);
		}
		else {
			priorNode->next = traversePtr->next;
			free(traversePtr);
		}
	}
}

/* This function is to get the user's option and print the result. */
void getUserOption(Node **const headAdr) {
	int option;
	Node *newNodePtr;
	int stockNumToDelete;
	
	printf("\nPlease enter an integer between 1 and 9 to select an operation on the data:\n");
	scanf("%i", &option);
	/* consume newline */
	getchar();
	/* repeatly ask the user's option until option 9 is chosen */
	while (option != 9) {
		/* switch 9 options */
		switch (option) {
			case 1:
				printf("\nTotal revenue: %.2f\n", calculateTotalRevenue(*headAdr));
				break;
			case 2:
				printf("\nTotal wholesale cost: %.2f\n", calculateTotalWholesaleCost(*headAdr));
				break;
			case 3:
				printf("\nTotal profit: %.2f\n", calculateTotalProfit(*headAdr));
				break;
			case 4:
				printf("\nTotal numbers of books sold = %i\n", calculateTotalBooksSold(*headAdr));
				break;
			case 5:
				printf("\nAverage profit: %.2f\n", calculateAverageProfit(*headAdr));
				break;
			case 6:
				printList(*headAdr);
				break;
			case 7:
				newNodePtr = createNodeAndGetData();
				insert(headAdr, newNodePtr);
				break;
			case 8:
				printf("\nPlease enter the book stock number of the book you wish to delete,followed by enter.\n");
				scanf("%i", &stockNumToDelete);
				delete(headAdr, stockNumToDelete);
				break;
			case 9:
				freeNodes(headAdr);
				break;
			default:
				printf("It is not a valid option. Please choose again!\n");
				break;
		}
		printf("\nPlease enter an integer between 1 and 9 to select an operation on the data:\n");
		scanf("%i", &option);
		getchar();
	}
}

/* This function is to calculate the total revenue. */
float calculateTotalRevenue(const Node *head) {
	float totalRevenue = 0;
	const Node *traversePtr = head;
	/* reach every book in the list */
	while (traversePtr != NULL) {
		totalRevenue += traversePtr->book.retailPrice * traversePtr->book.retailQuantity;
		traversePtr = traversePtr->next;
	}
	return totalRevenue;
}

/* This function is to calculate the total wholesale cost. */
float calculateTotalWholesaleCost(const Node *head) {
	float totalWholesaleCost = 0;
	const Node *traversePtr = head;
	/* reach every book in the list */
	while (traversePtr != NULL) {
		totalWholesaleCost += traversePtr->book.wholesalePrice * traversePtr->book.wholesaleQuantity;
		traversePtr = traversePtr->next;
	}
	return totalWholesaleCost;
}

/* This function is to calculate the total profit. */
float calculateTotalProfit(const Node *head) {
	return (calculateTotalRevenue(head) - calculateTotalWholesaleCost(head));
}

/* This function is to calculate the total number of the sold books. */
int calculateTotalBooksSold(const Node *head) {
	int totalBooksSold = 0;
	const Node *traversePtr = head;
	/* reach every book in the list */
	while (traversePtr != NULL) {
		totalBooksSold += traversePtr->book.retailQuantity;
		traversePtr = traversePtr->next;
	}
	return totalBooksSold;
}

/* This function is to calculate the average profit. */
float calculateAverageProfit(const Node *head) {
	return (calculateTotalProfit(head) / calculateTotalBooksSold(head));
}

/* This functions is to print the title list of the books. */
void printList(const Node *head) {
	const Node *traversePtr = head;
	printf("\nBook list:\n");
	while (traversePtr != NULL) {
		printf("%s\n", traversePtr->book.title);
		traversePtr = traversePtr->next;
	}
	printf("\n");
}

/* This functions is to free all the Nodes in the linked list. */
void freeNodes(Node **headAdr) {
	Node *traversePtr = *headAdr;
	Node *restOfListPtr = *headAdr;
	while (restOfListPtr != NULL) {
		restOfListPtr = restOfListPtr->next;
		free(traversePtr);
		traversePtr = restOfListPtr;
	}
}


		
		

