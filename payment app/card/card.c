


#include<stdio.h>

#include<string.h>
#include<ctype.h>
#include "card.h"

#include <stdbool.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	uint8_t HolderName[30];
	printf("please enter card holder name\n");
	gets(HolderName);

	strcpy((*cardData).cardHolderName, HolderName);
	int i, x, y;
	bool counter;
	bool alphbitic;

	for (i = 0; HolderName[i] != '\0'; i++) {
		x = strlen(HolderName);
		if (HolderName[i] == ' ') {
			y = 1;
		}
		else
		{
			y = isalpha(HolderName[i]);
		}
		if ((x > 19 && x < 25)) {
			counter = 1;
		}
		else {
			counter = 0;

		}
		//if (counter && cardHolderName[i] == '\0') {
		//	break;
		//}
		if (counter && (y != 0)) {

			return CARD_OK;

			printf("card ok");

		}
		else {
			printf("wrong name\n");
			return	WRONG_NAME;
		}
	}
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	char MMYY[9];


	printf("please enter MM/YY\n");
	gets(MMYY);
	strcpy((*cardData).cardExpirationDate, MMYY);

	if ((MMYY[2] == '/') && ((MMYY[0] == '0') || (MMYY[0] == '1' && (MMYY[1] == '0' || MMYY[1] == '1' || MMYY[1] == '2')))) {
		return CARD_OK;

		//printf("card ok");

	}
	else {


		//printf("wrong Expiration Date");
		return WRONG_EXP_DATE;
	}

}

EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	int i;
	char pan[20];
	printf("please enter card pan\n");
	gets(pan);

	strcpy((*cardData).primaryAccountNumber, pan);
	i = strlen(pan);
	if (i != 16) {
		return WRONG_PAN;
		printf("wrong pan");

	}
	else {

		return CARD_OK;
		printf("card ok");

	}


}


void getCardHolderNameTest(void) {

	ST_cardData_t cardData;



	printf("tester name : Osama Hatem \n");
	printf("function name : getCardHolderName\n");


	printf("test case 1:\n");



	if (getCardHolderName(&cardData) == CARD_OK) {
		printf("input data:\t%s\n", cardData.cardHolderName);
		printf("expected output :\tcard ok\n");

	}
	else {
		printf("input data:\t%s\n", cardData.cardHolderName);
		printf("expected output :\twrong name\n");
	}

}

void getCardExpiryDateTest(void) {
	ST_cardData_t cardData;



	printf("tester name : Osama Hatem \n");
	printf("function name : getCardExpiryDate\n");


	printf("test case 1:\n");



	if (getCardExpiryDate(&cardData) == CARD_OK) {
		printf("input data:\t%s\n", cardData.cardExpirationDate);
		printf("expected output :\tcard ok\n");

	}
	else {
		printf("input data:\t%s\n", cardData.cardExpirationDate);
		printf("expected output :\twrong Expiration Date\n");
	}
}

void getCardPANTest(void) {
	ST_cardData_t cardData;



	printf("tester name : Osama Hatem \n");
	printf("function name : getCardPAN\n");


	printf("test case 1:\n");



	if (getCardPAN(&cardData) == CARD_OK) {
		printf("input data:\t%s\n", cardData.primaryAccountNumber);
		printf("expected output :\tcard ok\n");

	}
	else {
		printf("input data:\t%s\n", cardData.primaryAccountNumber);
		printf("expected output :\twrong pan\n");
	}
}




/*	ST_cardData_t* cardptr;
	uint8_t cardHolderName[25];
	printf("please enter card holder name\n");
	gets(&cardHolderName);
	int i, x, y;
	bool counter;
	bool alphbitic;



	for (i = 0; i < 30; i++) {
		x = strlen(cardHolderName);
		if (cardHolderName[i] == ' ') {
			y = 1;
		}
		else
		{
			y = isalpha(cardHolderName[i]);
		}




		if ((x > 19 && x < 25)) {


			counter = 1;


		}
		else {
			counter = 0;

		}

		if (counter && cardHolderName[i] == '\0') {
			break;
		}






		if (counter && (y != 0)) {

			return CARD_OK;
			printf("correct1 \tlast:%d\n", i);
			return CARD_H;
			printf("card-ok");

		}
		else {
			printf("try num %d \t %d \n", i, isalpha(cardHolderName[i]));
			return	WRONG_NAME;
			while (1) {
				printf("please enter card holder name\n");
				gets(&cardHolderName);
				x = strlen(cardHolderName);
				if (cardHolderName[i] == ' ') {
					y = 1;
				}
				else
				{
					y = isalpha(cardHolderName[i]);
				}

				if ((x > 19 && x < 25)) {


					counter = 1;


				}
				else {
					counter = 0;

				}


				if (counter && cardHolderName[i] == '\0') {
					break;
				}




				if (counter && (y != 0)) {

					printf("correct2 \tlast:%d\n", i);
					return CARD_OK;
					printf("card-ok");
					break;


				}

			}

		}
	}



	cardptr = &cardHolderName;*/