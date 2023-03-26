#include<stdio.h>

#include<string.h>
#include<ctype.h>
#include "terminal.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	char DDMMYYYY[11];
	int i;
	printf("please enter DD/MM/YYYY\n");
	fflush(stdin);
	scanf("%s", &DDMMYYYY);
	//gets(DDMMYYYY);
	
	//fgets(DDMMYYYY, 11, stdin);
	//DDMMYYYY[strlen(DDMMYYYY) - 1] = '\0';
	//fflush(stdin);
	i = strlen(DDMMYYYY);
	strcpy((*termData).transactionDate, DDMMYYYY);
	if ((i < 10)|| (DDMMYYYY[2] != '/' || DDMMYYYY[5] != '/'))
	{
		return WRONG_DATE;
	}
	else {
		return TERMINAL_OK;
	}
	
}
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {
	/*ST_terminalData_t termData;
	getTransactionDate(&termData);*/

	if (((*cardData).cardExpirationDate[3] > (*termData).transactionDate[8])) {
	//	if (((*cardData).cardExpirationDate[3] >= (*termData).transactionDate[8]))
	//	{
	//		
	//		/*if((*cardData).cardExpirationDate[1] >= (*termData).transactionDate[4]){
	//			if ((*cardData).cardExpirationDate[0] >= (*termData).transactionDate[3]) {
	//				return TERMINAL_OK;
	//			}
	//			else
	//			{
	//				return EXPIRED_CARD;
	//			}
	//		}
	//		else
	//		{
	//			return EXPIRED_CARD;
	//		}*/
	//	}
	//	else
	//	{
	//		return EXPIRED_CARD;
	//	}
		return TERMINAL_OK;
	}
	else if(((*cardData).cardExpirationDate[3] == (*termData).transactionDate[8]))
	{
		if (((*cardData).cardExpirationDate[4] > (*termData).transactionDate[9]))
		{
			return TERMINAL_OK;
		}
		else if(((*cardData).cardExpirationDate[4] == (*termData).transactionDate[9]))
		{
			if ((*cardData).cardExpirationDate[0] > (*termData).transactionDate[3]) {
				return TERMINAL_OK;
			}
			else if((*cardData).cardExpirationDate[0] == (*termData).transactionDate[3])
			{
				if ((*cardData).cardExpirationDate[1] >= (*termData).transactionDate[4]) {
					return TERMINAL_OK;
				}
				else
				{
					return EXPIRED_CARD;
				}
			}
			else
			{
				return EXPIRED_CARD;
			}
		}
		else
		{
			return EXPIRED_CARD;
		}

		
	}
	else
	{
		return EXPIRED_CARD;
	}
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	
	float buff;
	printf("transaction amount\n");
	fflush(stdin);
	scanf_s("%f", &buff);
	if (buff >= 0) {
		(*termData).transAmount = buff;
		return TERMINAL_OK;
	}
	return INVALID_AMOUNT;

}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	printf("please enter max transaction amount\n");
	scanf("%f", &(*termData).maxTransAmount);

	
	if ((*termData).transAmount <= (*termData).maxTransAmount) {
		return TERMINAL_OK;
	}
	else {
		return EXCEED_MAX_AMOUNT;
	}
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount) {

	

	if ((maxAmount <= 0)) {
		return INVALID_MAX_AMOUNT;
	}
	else {
		return TERMINAL_OK;
	}
}
void getTransactionDateTest(void) {
	ST_terminalData_t termData;



	printf("tester name : Osama Hatem \n");
	printf("function name : getTransactionDate\n");


	printf("test case 1:\n");



	if (getTransactionDate(&termData) != TERMINAL_OK) {
		printf("input data:\t%s\n", termData.transactionDate);
		printf("expected output :\tWRONG DATE\n");
	}
	else {
		
		printf("input data:\t%s\n", termData.transactionDate);
		printf("expected output :\TERMINAL OK\n");

	}
}
void isCardExpiredTest(void) {
	ST_terminalData_t termData;
	ST_cardData_t cardData;
	
	printf("tester name : Osama Hatem \n");
	printf("function name : isCardExpired\n");


	printf("test case 1:\n");
	getCardExpiryDate(&cardData);
	getTransactionDate(&termData);
	/**/

	if (isCardExpired(&cardData,&termData) == TERMINAL_OK) {
		
		printf("input data:\t%s\n", termData.transactionDate);
		printf("input data card:\t%s\n", cardData.cardExpirationDate);
		printf("expected output :\TERMINAL OK\n");
	}
	else {

		printf("input data:\t%s\n", termData.transactionDate);
		printf("input data card:\t%s\n", cardData.cardExpirationDate);
		printf("expected output :\tExpired\n");

	}
}
void getTransactionAmountTest(void) {
	ST_terminalData_t termData;



	printf("tester name : Osama Hatem \n");
	printf("function name :getTransactionAmount \n");


	printf("test case 1:\n");



	if (getTransactionAmount(&termData) != TERMINAL_OK) {
		printf("input data:\t%f\n", termData.transAmount);
		printf("expected output :\tWRONG Amount\n");
	}
	else {

		printf("input data:\t%f\n", termData.transAmount);
		printf("expected output :\TERMINAL OK\n");

	}
}
void isBelowMaxAmountTest(void) {
	ST_terminalData_t termData;

		

	printf("tester name : Osama Hatem \n");
	printf("function name :isBelowMaxAmount \n");


	printf("test case 1:\n");
	getTransactionAmount(&termData);


	if (isBelowMaxAmount(&termData) != TERMINAL_OK) {
		printf("input data:\t%f\n", termData.transAmount);
		printf("expected output :\tWRONG Amount\n");
	}
	else {

		printf("input data:\t%f\n", termData.transAmount);
		printf("expected output :\TERMINAL OK\n");

	}
}
void setMaxAmountTest(void) {

	ST_terminalData_t termData;
	float max;



	printf("tester name : Osama Hatem \n");
	printf("function name :set max amount \n");


	printf("test case 1:\n");

	printf("please enter max amount\n");
	scanf("%f", &max);

	
	if ( setMaxAmount(&termData, max)  != TERMINAL_OK) {
		printf("input data:\t%f\n", max);
		printf("expected output :\tINVALID MAX AMOUNT\n");
	}
	else {

		printf("input data:\t%f\n", max);
		printf("expected output :\TERMINAL OK\n");

	}
}