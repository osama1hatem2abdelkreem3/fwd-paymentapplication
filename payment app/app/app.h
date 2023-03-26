#ifndef APP_H
#define APP_H
#include"../server/server.h"
ST_cardData_t cardData;
ST_terminalData_t termData;
ST_transaction_t transData;
ST_accountsDB_t accountRefrence;
extern ST_accountsDB_t accountsDB[];
void appStart(void);
#endif