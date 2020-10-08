
#include "header.h"
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <cstring>
#include <mysql.h>
#include "database-detail.h"


#define SERVER "localhost"
#define USER "root"
#define PASSWORD "yarin1414"
#define DATABASE "book_managment"


#include <iostream>
#include <mysql.h>


using namespace std;

class MySQL
{
    protected:
        /** MySQL connectivity Variables */
        MYSQL *connect;
        MYSQL_RES *res_set;
        MYSQL_ROW row;

        unsigned int i;

    public:
        /** MySQL Constructor */
        MySQL();
		char* stringToChar(string str);
		void query1();
		void query2();
		void query3();
		void query4();
		void query5();
		void query6();
		void query7();
		void query8();
		void query9();
		void query10();
		void query11();
		void query12();
		void query13();
		void query14();
		void query15();
		void query16();
		void query17();
		//void query18();
		void query19();
		void query20();
		void query21();
		void query22();
		void query23();
		void query24();
		void query25();
		void query26();

        /** MySQL Destructor */
        ~MySQL();
};
