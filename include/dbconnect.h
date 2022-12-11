#ifndef RPG2_DBCONNECT_H
#define RPG2_DBCONNECT_H

#include <mysql/mysql.h>
#define USERNAME "root"
#define SERVER "localhost"
#define PASS "52468592kK@#"
#define DB "RPG"


int CreateDB(MYSQL *);
int Select();
void FinishWithErrors(MYSQL *);
#endif //RPG2_DBCONNECT_H
