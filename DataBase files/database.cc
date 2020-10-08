#include <string>
#include "database.h"
using namespace std;


MySQL :: MySQL()
{
    connect = mysql_init(NULL);
    if ( !connect )
    {
        cout << "MySQL Initialization Failed";
    }   

    connect = mysql_real_connect(connect, SERVER, USER, PASSWORD, DATABASE, 0,NULL,0);
    
    if ( connect )
    {
        cout << "Connection Succeeded\n";
    }
    
    else
    {
        cout << "Connection Failed\n";
    }
}

MySQL :: ~MySQL()
{
    mysql_close (connect);
}
char* MySQL::stringToChar(string str)
{
	int n = str.length();
	char* cstr = new char[n + 1];
	copy(str.begin(), str.end(), cstr);
	cstr[n] = '\0';
	return cstr;
}
void MySQL::query1()
{
	string part1 = "select store_amount + storage_amount as 'Total'\
		from inventory i\
		join All_Books al\
		where i.bookID = al.bookID and al.bookID\
		=";
	string part2 = ";";
	string user;

	cout << "Enter book ID:" << endl;
	cin.ignore();
	getline(cin, user);

	part1 = part1 + user + part2;
	char* final_query = stringToChar(part1);

	/** Add MySQL Query */
	mysql_query(connect, final_query);
	delete final_query;

	res_set = mysql_store_result(connect);

	if (res_set != nullptr && res_set->row_count != 0)
	{
		row = mysql_fetch_row(res_set);
		cout << "The book is in stock! amount[" << row[0] << "]" << endl;
	}
	else
		cout << "Sorry, can't find '" << user << "' book" << endl;
	system("pause");
}
void MySQL::query2()
{
	string part1 = "select fname, lname , join_date\
		from  Customers\
	where join_date = (select min(join_date) from Customers);";
	char* final_query = stringToChar(part1);

	/** Add MySQL Query */
	mysql_query(connect, final_query);
	delete final_query;

	res_set = mysql_store_result(connect);

	if (res_set != nullptr && res_set->row_count != 0)
	{
		row = mysql_fetch_row(res_set);
		cout << "The oldest customer is " << row[0] << " " << row[1] << endl;
	}
	system("pause");
}
void MySQL::query3() {
	string part1 = "SELECT al.title\
		FROM inventory i\
		join all_books al\
		INNER JOIN\
		store_purchase s ON i.bookID = s.bookID\
		WHERE\
		i.store_amount > 0\
		OR i.storage_amount > 0\
		ORDER BY s.purchase_date\
		LIMIT 1\
		";

	char* final_query = stringToChar(part1);

	/** Add MySQL Query */
	mysql_query(connect, final_query);
	delete final_query;

	res_set = mysql_store_result(connect);

	if (res_set != nullptr && res_set->row_count != 0)
	{
		row = mysql_fetch_row(res_set);
		cout << "The oldest book in the store and storage is : " << row[0] << endl;
	}
	system("pause");
}
void MySQL::query4()
{
	string part1 = "select * from reservation r\
	where res_status != 0\
		order by r.res_date;";

	char* final_query = stringToChar(part1);

	/** Add MySQL Query */
	mysql_query(connect, final_query);
	delete final_query;

	res_set = mysql_store_result(connect);

	if (res_set != nullptr && res_set->row_count != 0)
	{
		cout << "Current reservation list order by dates: " << endl;
		cout << "reservationID\t" << "customerID\t" << "bookID\t" << "res_status\t" << "res_date" << "last_contact\t" << endl;
		while ((row = mysql_fetch_row(res_set)) != NULL)
			cout << "\t" << row[0] << "\t\t" << row[1] << "\t" << row[2] << "\t\t" << row[3] << "\t" << row[4] << "\t\t" << row[5] << endl;
	}
	else
		cout << "No reservation right now!"<< endl;
	system("pause");
}
void MySQL::query5()
{
	string part1 = "select al.bookID, al.title,  count(p.bookID) as Sold\
		from all_books al\
		join purchase_details p\
	where p.bookID = al.bookID and p.bookID =";
	string part2 = ";";
	string user;

	cout << "Enter book ID:" << endl;
	cin.ignore();
	getline(cin, user);

	part1 = part1 + user + part2;
	char* final_query = stringToChar(part1);
	/** Add MySQL Query */
	mysql_query(connect, final_query);
	delete final_query;

	res_set = mysql_store_result(connect);

	if (res_set != nullptr && res_set->row_count != 0)
	{
		row = mysql_fetch_row(res_set);
		cout << "Store has been sold " << row[2] << " copies of " << row[1] << endl;
	}
	else
		cout << "Sorry, can't find '" << user << "' book" << endl;
	system("pause");
}
void MySQL::query6()
{
	string part1 = "select author.fname, author.lname\
		from author\
		inner join author_book on author.authorID = author_book.authorID\
		inner join All_Books on All_Books.bookID = author_book.bookID\
		inner join purchase_details on purchase_details.bookID = All_Books.bookID\
		inner join customer_purchase on customer_purchase.purchaseID = purchase_details.purchaseID\
		where purchase_date between '"; 
		
	string and = "' and '";
	string part4 = "' group by author.authorID\
			order by count(author_book.bookID) desc\
			limit 1;";	
		string date1,date2;
		cout << "Enter start date: YYYY/MM/DD " << endl;
		cin >> date1;
		
		cout << "Enter end date:  YYYY/MM/DD" << endl;
		cin >> date2;

		part1 = part1 + date1 + and + date2+ part4;
		char* final_query = stringToChar(part1);
		/** Add MySQL Query */
		mysql_query(connect, final_query);
		delete final_query;

		res_set = mysql_store_result(connect);

		if (res_set != nullptr && res_set->row_count != 0)
		{
			row = mysql_fetch_row(res_set);
			cout << "The most read author between dates :" << date1 << " - " << date2 << row[0] << row[1] << endl;
		}
		else
			cout << "Not found the most read author" << endl;
	
		system("pause");
}
void MySQL::query7() {
	string part1 = "select c.fname, c.lname , count(pd.customerID) as 'bought' from purchase_details pd\
		join Customers c\
	where c.customerID = pd.customerID\
	group by pd.customerID\
		order by bought desc\
		limit 3";
	char* final_query = stringToChar(part1);

	/** Add MySQL Query */
	mysql_query(connect, final_query);
	delete final_query;

	res_set = mysql_store_result(connect);

	if (res_set != nullptr && res_set->row_count != 0)
	{
		cout << "3 customers that bought the most books -  " << endl;
		cout << "first name " << "last name " << "how much book they bought: "<< endl;
		while ((row = mysql_fetch_row(res_set)) != NULL)
			cout << row[0] << "   " << row[1] << "   " << row[2] <<  endl;
	}

	system("pause");

}
void MySQL::query8()
{
	string part1 = "select distinct aa.title, count(aa.translator) as 'amount of tranlations'\
		from inventory i\
		inner join\
		All_Books aa on aa.bookID = i.bookID and (i.store_amount > 0 or i.storage_amount > 0)\
		inner join\
		All_Books ab on aa.title = ab.title\
	where aa.translator < ab.translator\
	group by aa.title\
		order by count(ab.translator) desc\
		limit 1;";
	char* final_query = stringToChar(part1);

	/** Add MySQL Query */
	mysql_query(connect, final_query);
	delete final_query;

	res_set = mysql_store_result(connect);

	

	if (res_set != nullptr && res_set->row_count != 0)
	{
		row = mysql_fetch_row(res_set);
		cout <<"The book with the most interpreters is:" << row[0] << "and he have " <<  row[1] << " interpreters"<< endl;
	}
	else
		cout << "Not found the most read author" << endl;

	system("pause");
}
void MySQL::query9()
{	string part1=" SELECT c.fname, c.lname, cp.purchase_date\
	FROM purchase_details pd\
	INNER JOIN\
	customers c ON pd.customerID = c.customerID\
	INNER JOIN\
	customer_purchase cp ON pd.purchaseID = cp.purchaseID\
	WHERE pd.customerID = ";
	string part2 = " ORDER BY purchase_date;";

	string user;
	cout << "Enter customer ID:" << endl;
	cin >> user;

	part1 = part1 + user + part2;
	
	char* final_query = stringToChar(part1);

	/** Add MySQL Query */
	mysql_query(connect, final_query);
	delete final_query;

	res_set = mysql_store_result(connect);

	if (res_set != nullptr && res_set->row_count != 0)
	{
		cout << "History purchase of customer ID: "<<user  << endl;
		while ((row = mysql_fetch_row(res_set)) != NULL)
			cout << row[0] << "\t\t" << row[1] << "\t" << row[2] << "\t\t" << row[3] <<  endl;
	}
	else
		cout << "No purchase for this customer!" << endl;
	system("pause");
}
void MySQL::query10()
{
	string part1 = "select  distinct c.fname,c.lname,r.bookID,r.res_date as 'reservation date',r.res_status as 'reservation status' from reservation r\
		inner join customers c on  c.customerID = r.customerID and r.customerID =";
	string part2 = " order by res_date desc;";

		string user;
	cout << "Enter customer ID:" << endl;
	cin >> user;

	part1 = part1 + user + part2;

	char* final_query = stringToChar(part1);

	/** Add MySQL Query */
	mysql_query(connect, final_query);
	delete final_query;

	res_set = mysql_store_result(connect);

	if (res_set != nullptr && res_set->row_count != 0)
	{
		cout << "History reservatin of customer ID: " << user <<" (if the customer allready bought the book it will be wrote in the status)" << endl;
		while ((row = mysql_fetch_row(res_set)) != NULL)
			cout << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] <<"\t" << row[4] << endl;
	}
	else
		cout << "No reservation right now for custmer ID" << " user" << endl;
	system("pause");
}
void MySQL::query11()
{
	string part1 = "SELECT purchaseID,bookID,sum((weight * cost_per_kilo)) AS 'shipment taarif'\
		FROM (SELECT al.bookID, pd.purchaseID, al.weight, di.cost_per_kilo\
			FROM All_books al\
			INNER JOIN purchase_details pd USING(bookID)\
			INNER JOIN customer_purchase cp USING(purchaseID)\
			INNER JOIN deliveries d ON cp.purchaseID = d.deliveryID\
			INNER JOIN delivery_info di USING(delivery_info_id)) AS temp\
		group by purchaseID\
		ORDER BY purchaseID;";
	char* final_query = stringToChar(part1);

	/** Add MySQL Query */
	mysql_query(connect, final_query);
	delete final_query;

	res_set = mysql_store_result(connect);

	if (res_set != nullptr && res_set->row_count != 0)
	{
		cout << "Shiping cost:" << endl;
		cout << "purchaseID\t" << "bookID\t" << "shipment_taarif\t" << endl;
		while((row = mysql_fetch_row(res_set)) != NULL)
			cout << row[0] << "\t\t" << row[1] << "\t"<<row[2] << endl;
	}
	system("pause");
}
void MySQL::query12() {
	string part1 = "SELECT \
		c.customerID, c.fname, c.lname, d.address, cp.payment_method\
		FROM\
		customer_purchase cp,\
		customer_purchase cp1\
		INNER JOIN\
		customers c ON cp1.customerID = c.customerID\
		INNER JOIN\
		deliveries d ON cp1.purchaseID = d.deliveryID\
		WHERE\
		c.fname = '";
	string part2 = "'AND c.lname = '";

	string part3 = "' AND cp.customerID = cp1.customerID\
	AND cp.purchase_date = cp1.purchase_date\
	AND cp.purchaseID != cp1.purchaseID; ";
		
	string fname, lname;
	cout << "Enter first name" << endl;
	cin >> fname;
	cout << "Enter last name" << endl;
	cin >> lname;
	
	part1 = part1 + fname + part2 + lname + part3;

	char* final_query = stringToChar(part1);

	/** Add MySQL Query */
	mysql_query(connect, final_query);
	delete final_query;

	res_set = mysql_store_result(connect);

	if (res_set != nullptr && res_set->row_count != 0)
	{
		cout << "if customer splitted his order:" << endl;
		cout << "customerID\t\t" << "first name\t" << "last name\t" << "address\t" << "payment method\t" << endl;
		while ((row = mysql_fetch_row(res_set)) != NULL) {
			cout << row[0] << "\t\t" << row[1] << "\t\t" << row[2] << "\t\t" << row[3] <<"\t"<< endl;
		}
	}
	else
		cout << "there is no customer who split hes deliveries" << endl;
	system("pause");

	
}
void MySQL::query13() {
	string part1 = "select d.tracking_num,d.status from deliveries d\
	where d.tracking_num = '";
	string part2 = "';";
	string user;

	cout << "Enter tracking number: by the format AA123" << endl;
	cin.ignore();
	getline(cin, user);

	part1 = part1 + user + part2;
	char* final_query = stringToChar(part1);

	/** Add MySQL Query */
	mysql_query(connect, final_query);
	delete final_query;

	res_set = mysql_store_result(connect);

	if (res_set != nullptr && res_set->row_count != 0)
	{	
		row = mysql_fetch_row(res_set);
		cout << "tracking_num\t" << "status\t" << endl;
		cout <<  row[0] << "\t\t" << row[1] << endl;
	}
	else
		cout << "Sorry, can't find this tracking numer" << endl;
	system("pause");

}
void MySQL::query14() {
	string part1 = "SELECT DISTINCT di.company, COUNT(d.delivery_info_id) AS 'delivery amount'\
		FROM deliveries d\
		INNER JOIN\
		delivery_info di USING(delivery_info_id)\
		INNER JOIN\
		customer_purchase cp ON cp.purchaseID = d.deliveryID\
		WHERE\
		YEAR(cp.purchase_date) = '";
	string year, month;
		
	string and = "' and '";
	string part2 = " MONTH(cp.purchase_date) = '";
	string part3 = "AND di.delivery_info_id BETWEEN '4' AND '5'";
		
		
		cout << "Enter year please:YYYY" << endl;
		cin.ignore();
		getline(cin, year);
		cout << "Enter month please: M" << endl;
		cin.ignore();
		getline(cin, month);
		part1 = part1 + year + part2 + month + part3;
		char* final_query = stringToChar(part1);

		/** Add MySQL Query */
		mysql_query(connect, final_query);
		delete final_query;

		res_set = mysql_store_result(connect);

		if (res_set != nullptr && res_set->row_count != 0)
		{
			row = mysql_fetch_row(res_set);
			cout << "company\t" << "delivery amount\t" << endl;
			cout << row[0] << "\t\t\t" << row[1] << endl;
		}
		else
			cout << "Sorry,there is no delivery for Xpress this month" << endl;
		system("pause");
}
void MySQL::query15() {
	string part1 = "SELECT \
		payment_method AS 'Payment method',\
		SUM(al.price) AS 'total from Bit'\
		FROM\
		customer_purchase cp\
		INNER JOIN\
		purchase_details pd USING(purchaseID)\
		INNER JOIN\
		All_Books al USING(bookID)\
		WHERE\
		payment_method = 'Bit app'\
		AND MONTH(purchase_date) =";

	string part2 = " AND YEAR(purchase_date) = ";
	string part3 = ";";

	


	string month, year;
	cout << "Enter year please:YYYY" << endl;
	cin >> year;

	cout << "Enter month please: M" << endl;
	cin >> month;

	part1 = part1 + month + part2 + year + part3;
	char* final_query = stringToChar(part1);

	/** Add MySQL Query */
	mysql_query(connect, final_query);
	delete final_query;

	res_set = mysql_store_result(connect);

	if (res_set != nullptr && res_set->row_count != 0)
	{
		row = mysql_fetch_row(res_set);
		cout << "payment_method\t" << "total from bit\t" << endl;
		cout << row[0] << "\t\t" << row[1] << endl;
	}
	else
		cout << "Sorry,there is no BIT payments this month" << endl;

	system("pause");
}
void MySQL::query16() {
	string part1 = "SELECT \
		cp.purchase_date,\
		cp.purchaseID,\
		(al.price - sp.book_price) AS income\
		FROM\
		store_purchase sp\
		INNER JOIN\
		All_Books al USING(bookID)\
		INNER JOIN\
		purchase_details pd USING(bookID)\
		INNER JOIN\
		customer_purchase cp USING(purchaseID)\
		WHERE\
		(al.price - sp.book_price) > (SELECT\
			AVG((al.price - sp.book_price)) AS average\
			FROM\
			store_purchase sp\
			INNER JOIN\
			All_Books al USING(bookID)\
			INNER JOIN\
			purchase_details pd USING(bookID)\
			INNER JOIN\
			customer_purchase cp\
			WHERE\
			cp.purchase_date BETWEEN DATE_SUB(CURRENT_DATE(),\
				INTERVAL 1 YEAR) AND CURRENT_DATE())\
		AND(cp.purchase_date BETWEEN DATE_SUB(CURRENT_DATE(),\
			INTERVAL 1 YEAR) AND CURRENT_DATE());";
	char* final_query = stringToChar(part1);

	/** Add MySQL Query */
	mysql_query(connect, final_query);
	delete final_query;

	res_set = mysql_store_result(connect);

	if (res_set != nullptr && res_set->row_count != 0)
	{
		cout << "Transactions with profit above the average in last year:" << endl;
		cout << "purchase date\t\t" << "purchase ID\t" << "income" << endl;
		while ((row = mysql_fetch_row(res_set)) != NULL) {
			cout << row[0] << "\t" << row[1] << "\t" << row[2] << endl;
		}
	}
	system("pause");
}
void MySQL::query17() {
	string part1 = "SELECT \
		di.company, COUNT(d.delivery_info_id) AS 'num of deliveries'\
		FROM\
		deliveries d\
		INNER JOIN\
		delivery_info di USING(delivery_info_id)\
		INNER JOIN\
		customer_purchase cp\
		on cp.purchaseID = d.deliveryID\
	where cp.purchase_date between date_sub(current_date(), interval 1 year) and current_date() and di.company != 'store'\
		group by company;";
	char* final_query = stringToChar(part1);

	/** Add MySQL Query */
	mysql_query(connect, final_query);
	delete final_query;

	res_set = mysql_store_result(connect);

	if (res_set != nullptr && res_set->row_count != 0)
	{
		cout << "Amount of shippings made by Xpress and Israel post last year:" << endl;
		cout << "company\t" << "number of deliveries\t" << endl;
		while ((row = mysql_fetch_row(res_set)) != NULL) {
			cout << row[0] << "\t\t" << row[1] << endl;
		}
	}
	system("pause");
}
void MySQL::query19() {
	string part1 = "SELECT \
		c.customerID, c.fname, c.lname, cp.purchase_date\
		FROM\
		customer_purchase cp\
		INNER JOIN\
		customers c USING(customerID)\
		WHERE customerID not in\
		(select customerid\
			from customer_purchase\
			where\
			cp.purchase_date  BETWEEN DATE_SUB(CURRENT_DATE(),\
				INTERVAL 2 YEAR) AND CURRENT_DATE());";
	char* final_query = stringToChar(part1);

	/** Add MySQL Query */
	mysql_query(connect, final_query);
	delete final_query;

	res_set = mysql_store_result(connect);

	if (res_set != nullptr && res_set->row_count != 0)
	{
		cout <<"Customers that haven't purchased at the last 24 months:" << endl;
		cout << "customerID\t" << "first name\t"<< "last name\t"<< "purchase date" << endl;
		while ((row = mysql_fetch_row(res_set)) != NULL) {
			cout << row[0] << "\t" << row[1]<<"\t"<<row[2]<<"\t"<<row[3]<< endl;
		}
	}
	system("pause");
}
void MySQL::query20() {
	string part1 = "select r.reservationID ,c.fname, c.lname , r.last_contacted , r.res_status\
		from reservation r\
		inner join customers c\
		using(customerID)\
	where current_date() > last_contacted + 14 and res_status != 'item purchased';";
	
	char* final_query = stringToChar(part1);

	/** Add MySQL Query */
	mysql_query(connect, final_query);
	delete final_query;

	res_set = mysql_store_result(connect);

	if (res_set != nullptr && res_set->row_count != 0)
	{
		cout << "All customers that order and didn't arrive to take their books at least 14 days:" << endl;
		cout << "reservationID\t" << "first name\t" << "last name\t" << "last contacted\t" << "reservation status\t" << endl;
		while ((row = mysql_fetch_row(res_set)) != NULL)
			cout << row[0] << "\t\t" << row[1] << "\t\t" << row[2] << "\t\t" << row[3] << "\t\t" << row[4] << endl;
	}
	else
		cout << "There is  no customers that  didnt arrive to take their books" << endl;
	system("pause");
}
void MySQL::query21() {
	string part1 = "SELECT YEAR(purchase_date), MONTH(purchase_date), SUM(i.storage_amount)\
                FROM store_purchase sp\
                INNER JOIN inventory i USING (bookID)\
    GROUP BY purchase_date";
	char* final_query = stringToChar(part1);

	/** Add MySQL Query */
	mysql_query(connect, final_query);
	delete final_query;

	res_set = mysql_store_result(connect);

	if (res_set != nullptr && res_set->row_count != 0)
	{
		cout << "Number of books in the storage in number of monthly incision:" << endl;
		cout << "year\t" << "month\t" << "sum\t" << endl;
		while ((row = mysql_fetch_row(res_set)) != NULL)
			cout << row[0] << "\t" << row[1] << "\t" << row[2] << endl;
	}
	system("pause");
}
void MySQL::query22() {
	string part1 = "SELECT \
		SUM(i.store_amount + storage_amount) AS 'amount of books',\
		SUM(sp.book_price * (i.store_amount + i.storage_amount)) AS 'total amount'\
		FROM\
		store_purchase sp\
		INNER JOIN\
		inventory i USING(bookID)\
		WHERE\
		purchase_date BETWEEN '";
	
	string date1, date2;
	string and = "' AND '";
	cout << "Enter start date:YYYY-MM-DD" << endl;
	cin >> date1;
	cout << "Enter end date:YYYY-MM-DD" << endl;
	cin >> date2;
	string part2 = "';";
	part1 = part1 + date1 + and +date2 + part2;
	char* final_query = stringToChar(part1);

	/** Add MySQL Query */
	mysql_query(connect, final_query);
	delete final_query;

	res_set = mysql_store_result(connect);

		cout << "Number of books the store purchased and the total price paid between " << date1 << " to " << date2 << endl;
		cout << "amount of books\t" << "total amount" << "sum\t" << endl;
		if (res_set != nullptr && res_set->row_count != 0)
		{
				row = mysql_fetch_row(res_set);
				cout << row[0] << "\t\t" << row[1] << "\t" << endl;
		}
		else
			cout << "The store didnt bought books this month" << endl;
	
	system("pause");
}
void MySQL::query23() {
	string part1 = "SELECT \
		(SUM(al.price) - (SELECT\
			SUM(sp.book_price * (i.store_amount + i.storage_amount)) AS 'total prof'\
			FROM\
			store_purchase sp\
			INNER JOIN\
			inventory i USING(bookID)\
			WHERE\
			YEAR(sp.purchase_date) = "; 
		string part2 = " AND MONTH(sp.purchase_date) = "; 
		string part3 = " )) AS 'profit'\
		FROM\
		All_Books al\
		INNER JOIN\
		purchase_details ps USING(bookID)\
		INNER JOIN\
		customer_purchase cp USING(purchaseID)\
		WHERE\
		YEAR(cp.purchase_date) = ";
	string part4 = " AND MONTH(cp.purchase_date)  =";
	string part5 = ";";

	string month, year;
	cout << "enter year:YYYY" << endl;
	cin >> year;
	cout << "enter month:M" << endl;
	cin >> month;

	part1 = part1 + year + part2 + month + part3 + year + part4 + month + part5;
	char* final_query = stringToChar(part1);

	/** Add MySQL Query */
	mysql_query(connect, final_query);
	delete final_query;

	res_set = mysql_store_result(connect);
	cout << "profit in a given month"<< endl;
	cout << "profit" << endl;
	if (res_set != nullptr && res_set->row_count != 0)
	{
		row = mysql_fetch_row(res_set);
		cout << row[0] << endl;
	}


	system("pause");



}
void MySQL::query24() {
	string part1 = "SELECT YEAR(cp.purchase_date) AS year, SUM(al.price) / 12 AS 'average income'\
    FROM customer_purchase cp\
            INNER JOIN purchase_details pd USING (purchaseID)\
            INNER JOIN All_Books al USING (bookID)\
    WHERE YEAR(purchase_date)\
    GROUP BY YEAR(purchase_date)\
    ORDER BY YEAR(purchase_date) DESC;";
	char* final_query = stringToChar(part1);

	/** Add MySQL Query */
	mysql_query(connect, final_query);
	delete final_query;

	res_set = mysql_store_result(connect);

	if (res_set != nullptr && res_set->row_count != 0)
	{
		cout << "The annual average in monthly transactions " << endl;
		cout << "Year" << "Avrage income" << "sum\t" << endl;
		row = mysql_fetch_row(res_set);
			cout << row[0] << "\t\t" << row[1] << endl;
	}
	system("pause");
}
void MySQL::query25() {
	string part1 = "select wt.year , wt.month , e.fname , e.lname , wt.salary_for_month\
		from Employee e\
		inner join work_time wt\
		using(employeeID)\
	where wt.year =";
		string year, month,employee;
	cout<<"Enter a year:YYYY"<<endl;
	cin >> year;
	cout << "Enter a month:M" << endl;
	cin >> month;
	cout << "Enter employee ID" << endl;
	cin >> employee;
	string part2 = " and wt.month =";
	string part3 = " and e.employeeID =";
	string part4 = ";";
		
	part1 = part1 + year + part2 + month + part3 + employee + part4;
	char* final_query = stringToChar(part1);

	/** Add MySQL Query */
	mysql_query(connect, final_query);
	delete final_query;

	res_set = mysql_store_result(connect);


	cout << "Employee's " <<employee<<" in month " << month << " and year " << year << endl;
	cout << "year\t" << "month\t" << "first name\t" <<"last name\t"<<"Salary for month"<< endl;
	if (res_set != nullptr && res_set->row_count != 0)
	{

		row = mysql_fetch_row(res_set);
		cout << row[0] << "\t" << row[1] << "\t\t" << row[2]<< "\t" << row[3]<< "\t\t" << row[4]<< endl;
	}
	else
		cout << "The store didnt bought books this month" << endl;

	system("pause");
}
void MySQL::query26() {
	string part1 = "select e.fname, e.lname, count(employeeID)\
		from employee e\
		inner join customer_purchase cp\
		using (employeeID)\
	where year(purchase_date) =";
	
		string part2 = " and month(purchase_date) =";
	
		string part3=" group by employeeID\
		order by employeeID desc\
		limit 1;";

		string month, year;
		cout << "Enter year" << endl;
		cin >> year;
		cout << "Enter month" << endl;
		cin >> month;
		part1 = part1 + year + part2 + month + part3;
	
	
		char* final_query = stringToChar(part1);

		/** Add MySQL Query */
		mysql_query(connect, final_query);
		delete final_query;

		res_set = mysql_store_result(connect);


		cout << "Employee with the most transactions per month " << month <<  endl;
		cout << "first name\t" << "last name\t" << "sales\t" << endl;
		if (res_set != nullptr && res_set->row_count != 0)
		{

			row = mysql_fetch_row(res_set);
			cout << row[0] <<"\t"  << row[1] << "\t\t" << row[2]<<"\t"<< endl;
		}
		else
			cout << "The store didnt bought books this month" << endl;

		system("pause");

}