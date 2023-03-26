#define _CRT_SECURE_NO_WARNINGS
#include"app.h"
#include<stdio.h>
#include <string.h>
float max;
void appStart(void) {
	//card
	while (getCardHolderName(&transData.cardHolderData) != CARD_OK) { printf("please enter the name again\n"); }

	while (getCardExpiryDate(&transData.cardHolderData) != CARD_OK) { printf("please enter the date again\n"); }
	while (getCardPAN(&transData.cardHolderData) != CARD_OK) {
		printf("please enter the pan again\n");
	}
	
	//termnal
	while (getTransactionDate(&transData.terminalData) != TERMINAL_OK) printf("please enter the date again\n");
	while (isCardExpired(&transData.cardHolderData, &transData.terminalData) != TERMINAL_OK)
	{
		
		//return 1;
		break;
	}
	if (isCardExpired(&transData.cardHolderData, &transData.terminalData) != TERMINAL_OK)
	{
		printf("card Expired\n");
	}
	else
	{
		while (getTransactionAmount(&transData.terminalData) != TERMINAL_OK) { printf("please enter the number again\n"); }
		/*while (isBelowMaxAmount(&termData)) {

			
			break;
		}*/
		if (isBelowMaxAmount(&transData.terminalData) != TERMINAL_OK)
		{
			printf("Exceded max amount \n");
		}
		else
		{
			//printf("please enter max amount\n");
			//scanf_s("%f", &max);
			while (setMaxAmount(&transData.terminalData,accountsDB->balance) != TERMINAL_OK) printf("please enter the number again\n");

			//srver
			while (isValidAccount(&transData.cardHolderData, &accountRefrence) != SERVER_OK) {
				
				break;
			}
			if (isValidAccount(&transData.cardHolderData, accountsDB) != SERVER_OK)
			{
				printf("Invalid acount\n");
			}
			else
			{
				while (isAmountAvailable(&transData.terminalData, &accountRefrence) != SERVER_OK) {
					
					break;
				}
				if (isAmountAvailable(&transData.terminalData, &accountRefrence) != SERVER_OK)
				{
					printf("fund problem\n");
				}
				else
				{
					/*saveTransaction(&transData);
					*/
					if (recieveTransactionData(&transData)!= APPROVED)
					{
						printf("error in revew number  %d\n", recieveTransactionData(&transData));
					}
					else
					{
						saveTransaction(&transData);
						printf("saved!!");
					}
					
				}
			}

			
		}
		
	}
	

}
//getCardExpiryDate(&cardData);
	//getCardPAN(&cardData);
