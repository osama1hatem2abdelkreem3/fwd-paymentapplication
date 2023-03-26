#define _CRT_SECURE_NO_WARNINGS
#include"server.h"
#include<stdio.h>
#include <string.h>
//from 2k to 11k (10 accounts)
//toggle blocked and running
//shift numbers 0123456789123456 (16 num)
uint32_t index, accountRef;

ST_accountsDB_t accountsDB[255] = 
{ 
	{2000,RUNNING,"0123456789123456"},
	{3000,BLOCKED,"1234567891234567"},
	{4000,RUNNING,"2345678912345678"},
	{5000,BLOCKED,"3456789123456789"},
	{6000,RUNNING,"4567891234567890"},
	{7000,BLOCKED,"5678912345678901"},
	{8000,RUNNING,"6789123456789012"},
	{9000,BLOCKED,"7891234567890123"},
	{10000,RUNNING,"8912345678901234"},
	{11000,BLOCKED,"9123456789012345"} 
};

ST_transaction_t transaction[255];
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) {
	
	
	for ( index = 0; index < 255; index++)
	{
		//(*accountRefrence).primaryAccountNumber == accountsDB[i].primaryAccountNumber;

		if (strcmp((*cardData).primaryAccountNumber, accountRefrence[index].primaryAccountNumber) != 0) {
			if (index==254)
			{
				return ACCOUNT_NOT_FOUND;
			}
			else
			{
				continue;
			}
			
			//printf("try num \n");
		}
		else {
			return SERVER_OK;
			break;
			
			
			//printf("here it is \n");

		}

	}
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
	/*printf("pleasae enter the number\n");
	scanf_s("%d", &index);*/
	if ((accountRefrence[index].state == RUNNING)) {



		return SERVER_OK;

	}
	else
	{
		return BLOCKED_ACCOUNT;
			
	}



}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) {
	
	
	
	if (accountsDB->balance >= (termData->transAmount)) {

		return SERVER_OK;
			
	}
	else {
		return LOW_BALANCE;
			
	}

	
	
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	
	if (index >= 255) {
		return SAVING_FAILED;
	}
	else
	{
		//card
		strcpy(transaction->cardHolderData.cardHolderName, transData->cardHolderData.cardHolderName);
		strcpy(transaction->cardHolderData.cardExpirationDate, transData->cardHolderData.cardExpirationDate);
		strcpy(transaction->cardHolderData.primaryAccountNumber, transData->cardHolderData.primaryAccountNumber);
		//terminal
		transaction->terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
		transaction->terminalData.transAmount = transData->terminalData.transAmount;
		strcpy(transaction->terminalData.transactionDate , transData->terminalData.transactionDate);
		transaction->transState = transData->transState;
		transaction->transactionSequenceNumber = transData->transactionSequenceNumber;
		//transaction[transData->transactionSequenceNumber].cardHolderData = transData->cardHolderData;
		//transaction[transData->transactionSequenceNumber].terminalData = transData->terminalData;
		//transaction[transData->transactionSequenceNumber].transState = transData->transState;
		//transaction[transData->transactionSequenceNumber].transactionSequenceNumber = transData->transactionSequenceNumber;
		transData->transactionSequenceNumber = ++index;

		
		return SERVER_OK;
	}
	
}




EN_transState_t recieveTransactionData(ST_transaction_t* transData) {

	if (isValidAccount(&transData->cardHolderData, accountsDB) == ACCOUNT_NOT_FOUND) return FRAUD_CARD;
	else if (isBlockedAccount(accountsDB) == BLOCKED_ACCOUNT) return DECLINED_STOLEN_CARD;
	else if (isAmountAvailable(&transData->terminalData, accountsDB) == LOW_BALANCE) return DECLINED_INSUFFECIENT_FUND;
	else if (saveTransaction(&transData) == SAVING_FAILED) return INTERNAL_SERVER_ERROR;
	else
	{
		accountsDB[index].balance -= (*transData).terminalData.transAmount;
		printf("\nYour new balance now is: %f\n", accountsDB[index].balance);
		return APPROVED;
	}
}

void isValidAccountTest(void) {
	ST_cardData_t cardData;

	printf("tester name : Osama Hatem \n");
	printf("function name is valid account \n");


	printf("test case 1:\n");
	getCardPAN(&cardData);

	//isValidAccount(&cardData, &accountRefrence) ;

	if (isValidAccount(&cardData,accountsDB) == SERVER_OK) {
		printf("input data:\t%s\n", cardData.primaryAccountNumber);
		printf("expected output :\server OK\n");
	}
	else {
		printf("input data:\t%s\n", cardData.primaryAccountNumber);
		printf("expected output :\t account not found \n");
		

	}
	//printf("the accout data %s\n", accountsDB[1].primaryAccountNumber);
}

void isBlockedAccountTest(void) {
	ST_accountsDB_t accountRefrence;


	printf("tester name : Osama Hatem \n");
	printf("function name is blocked  \n");

	


	//(*accountRefrence).state = accountsDB[i].state;
	//isValidAccount(&cardData, &accountRefrence) ;

	if (isBlockedAccount(&accountRefrence) == SERVER_OK) {
		printf("input data:\tRUNNING\n" );
		printf("expected output :\server OK\n");
	}
	else {
		printf("input data:\tBLOCKED\n");
		//printf("expected output :\t account not found \n");


	}
}

void isAmountAvailableTest(void) {
	ST_terminalData_t termData;
	
	printf("tester name : Osama Hatem \n");
	printf("function name is valid amount \n");

	printf("test case 1:\n");
	
	while(getTransactionAmount(&termData)!=0) printf("Wrong input please enter another one\n");
	
	if (isAmountAvailable(&termData, &accountsDB[0]) == SERVER_OK) {
		printf("input data:\%.2f\n", termData.transAmount);
		printf("expected output :\server OK\n");
	}
	else {
		printf("input data:\t%.2f\n", termData.transAmount);
		printf("expected output :\t low balance \n");


	}
}

void saveTransactionTest(void) {

	ST_transaction_t transData;

	printf("Tester Name: Osama Hatem\n");
	printf("Function Name: saveTransaction\n");
	//transData.cardHolderData = (ST_cardData_t){ .cardHolderName = "osama",
	//											.primaryAccountNumber = "1234567890123456",
	//											.cardExpirationDate = "05/20" };
	//transData.terminalData = (ST_terminalData_t){ .transAmount = 2000,
	//											.maxTransAmount = 20000,
	//											.transactionDate = "31/12/2022" };
	printf("\nTest Case 1:\n");
	getCardHolderName(&transData.cardHolderData);
	getCardExpiryDate(&transData.cardHolderData);
	getCardPAN(&transData.cardHolderData);
	getTransactionAmount(&transData.terminalData);
	isBelowMaxAmount(&transData.terminalData);
	getTransactionDate(&transData.terminalData);
	isCardExpired(&transData.cardHolderData, &transData.terminalData);

	//transData.transState = FRAUD_CARD;
	transData.transactionSequenceNumber = 1;
	
	printf("Input Data:\ncard holder name: %s\nccv: %s\npan: %s\nTrans amount %f\nmax trans amount %f\nexpiey date %s\n", transData.cardHolderData.cardHolderName,
		transData.cardHolderData.cardExpirationDate,
		transData.cardHolderData.primaryAccountNumber
		, transData.terminalData.transAmount
		, transData.terminalData.maxTransAmount
		, transData.terminalData.transactionDate);
	//printf("Expected Result: %d \n", SERVER_OK);
	printf("Actual Result: %d \n", saveTransaction(&transData));
	printf("SequenceNumber: %d \n", transData.transactionSequenceNumber);
	
	
}



void recieveTransactionDataTest(void) {

	ST_transaction_t transData;

	printf("Tester Name: Osama Hatem\n");
	printf("Function Name: recieveTransactionData\n");
	//transData.cardHolderData = (ST_cardData_t){ .cardHolderName = "osama",
	//											.primaryAccountNumber = "1234567890123456",
	//											.cardExpirationDate = "05/20" };
	//transData.terminalData = (ST_terminalData_t){ .transAmount = 2000,
	//											.maxTransAmount = 20000,
	//											.transactionDate = "31/12/2022" };
	printf("\nTest Case 1:\n");
	getCardHolderName(&transData.cardHolderData);
	getCardExpiryDate(&transData.cardHolderData);
	getCardPAN(&transData.cardHolderData);
	getTransactionAmount(&transData.terminalData);
	isBelowMaxAmount(&transData.terminalData);
	getTransactionDate(&transData.terminalData);
	fflush(stdin);
	isCardExpired(&transData.cardHolderData, &transData.terminalData);

	//transData.transState = FRAUD_CARD;
	transData.transactionSequenceNumber = 1;

	printf("Input Data:\ncard holder name: %s\nccv: %s\npan: %s\nTrans amount %f\nmax trans amount %f\nexpiey date %s\n",
		transData.cardHolderData.cardHolderName,
		transData.cardHolderData.cardExpirationDate,
		transData.cardHolderData.primaryAccountNumber
		, transData.terminalData.transAmount
		, transData.terminalData.maxTransAmount
		, transData.terminalData.transactionDate);
	//printf("Expected Result: %d \n", SERVER_OK);
	printf("Actual Result: %d \n", recieveTransactionData(&transData));
	
}


void listSavedTransactions(void) {
	ST_cardData_t cardData;
	ST_terminalData_t termData;
	ST_transaction_t transData;
	ST_accountsDB_t accountRefrence;
	
	EN_transState_t transState;
	getCardHolderName(&transData.cardHolderData);
	getCardExpiryDate(&transData.cardHolderData);
	getCardPAN(&transData.cardHolderData);
	getTransactionAmount(&transData.terminalData);

	isBelowMaxAmount(&transData.terminalData);

	//getTransactionDate(&transData.terminalData);

	getTransactionDate(&transData.terminalData);
	//isCardExpired(&transData.cardHolderData, &transData.terminalData);

	printf("#########################################################\n");
	printf("Transaction Sequence Number: %d\n", index);
	printf("Transaction Date: %s\n",transData.terminalData.transactionDate);
	printf("Transaction Amount: %f\n",transData.terminalData.transAmount);
	printf("Transaction State: %d\n", accountsDB->state);
	printf("Terminal Max Amount: %f\n",transData.terminalData.maxTransAmount);
	printf("Cardholder Name: %s\n",transData.cardHolderData.cardHolderName);
	printf("PAN: %s\n",transData.cardHolderData.primaryAccountNumber);
	printf("Card Expiration Date: %s\n",transData.cardHolderData.cardExpirationDate);
	printf("#########################################################");
}



/*
}*//*fflush(stdin);
	getCardHolderName(&transData.cardHolderData);*/
	//getCardExpiryDate(&transData.cardHolderData);
	//getCardPAN(&transData.cardHolderData);
	//getTransactionAmount(&transData.terminalData);
	//isBelowMaxAmount(&transData.terminalData);
	//getTransactionDate(&transData.terminalData);
	//isCardExpired(&transData.cardHolderData, &transData.terminalData);

	////transData.transState = FRAUD_CARD;
	////transData.transactionSequenceNumber = 1;

	//printf("Input Data:\ncard holder name: %s\nccv: %s\npan: %s\nTrans amount %f\nmax trans amount %f\nexpiey date %s\n", transData.cardHolderData.cardHolderName,
	//	transData.cardHolderData.cardExpirationDate,
	//	transData.cardHolderData.primaryAccountNumber
	//	, transData.terminalData.transAmount
	//	, transData.terminalData.maxTransAmount
	//	, transData.terminalData.transactionDate);
	////printf("Expected Result: %d \n", SERVER_OK);
	//printf("Actual Result: %d \n", saveTransaction(&transData));
	//printf("SequenceNumber: %d \n", transData.transactionSequenceNumber);

	//printf("SequenceNumber: %d \n", transData.transactionSequenceNumber);
	//printf("\nTest Case 2:\n");
	//getCardHolderName(&transData.cardHolderData);
	//getCardExpiryDate(&transData.cardHolderData);
	//getCardPAN(&transData.cardHolderData);
	//getTransactionAmount(&transData.terminalData);
	//isBelowMaxAmount(&transData.terminalData);
	//getTransactionDate(&transData.terminalData);
	//isCardExpired(&transData.cardHolderData, &transData.terminalData);

	////transData.transState = FRAUD_CARD;
	////transData.transactionSequenceNumber = 1;

	//printf("Input Data:\ncard holder name: %s\nccv: %s\npan: %s\nTrans amount %f\nmax trans amount %f\nexpiey date %s\n", transData.cardHolderData.cardHolderName,
	//	transData.cardHolderData.cardExpirationDate,
	//	transData.cardHolderData.primaryAccountNumber
	//	, transData.terminalData.transAmount
	//	, transData.terminalData.maxTransAmount
	//	, transData.terminalData.transactionDate);
	////printf("Expected Result: %d \n", SERVER_OK);
	//printf("Actual Result: %d \n", recieveTransactionData(&transData));
	//printf("SequenceNumber: %d \n", transData.transactionSequenceNumber);

