/*************************************************************************
 MIT License

 Copyright(c) 2019 Joker2770

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files(the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions :

 The above copyright notice and this permission notice shall be included in all
	 copies or substantial portions of the Software.

	 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
	 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	 SOFTWARE.

    > File Name: StudentsManageSystem.cpp
    > Author: Joker2770
    > Mail: 18608842770@163.com 
    > Created Time: Sun 04 Mar 2018 10:10:30 AM DST
 ************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#if defined __GNUC__

const char *clear = "clear";

#elif defined _MSC_VER

const char *clear = "cls";

#endif

#include<string.h>
#include"StudentsManageSystem.h"
#include "extra/sqlite3.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int main()
{
	while(1)
	{
		printf(">>>>>>>>>>>>>>>>>>>>>>Welcome To Use Students Grades Manage System<<<<<<<<<<<<<<<<<<<<<<<\n");
		printf(">___________________________Please chose the list function______________________________<\n");
		printf(">\t\t\t\t1)Record students information\t\t\t\t<\n");
		printf(">\t\t\t\t2)Print students information\t\t\t\t<\n");
		printf(">\t\t\t\t3)Save students information\t\t\t\t<\n");
		printf(">\t\t\t\t4)Read students information\t\t\t\t<\n");
		printf(">\t\t\t\t5)Count students amount\t\t\t\t\t<\n");
		printf(">\t\t\t\t6)Search students information\t\t\t\t<\n");
		printf(">\t\t\t\t7)Modify students information\t\t\t\t<\n");
		printf(">\t\t\t\t8)Delete students information\t\t\t\t<\n");
		printf(">\t\t\t\t0)Exit system\t\t\t\t\t\t<\n");
		printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>VERSION 1.0<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
		
		//pause
		int n;
		int iNumber = 0;

		scanf("%d",&n);
		//judge
		switch(n)
		{
			case 1:
				InputStudent();	
				break;
			case 2:
				PrintStudent();
				break;
			case 3:
				SaveStudent();
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				PrintStudent();
				printf("Please input the ID which you want to delete:\n");
				scanf("%d", &iNumber);
				DeleteStudent(iNumber);
				break;
			case 0:
				printf("Welcome to use again!\n");
				return 0;
				break;
			default:
				//system(clear);
				//printf("Input error,please input again!\n");
				break;
			
		}
	}
	exit(0);
}

void InputStudent()
{
	printf("Please input students' information:Name Number Age Grades\n");
	Node *p = g_pHead;	//present node
	
	//find tail node
	while(g_pHead != NULL && p->pNext != NULL)
	{
		p = p->pNext;

	}

	Node *pNewNode = (Node*)malloc(sizeof(Node));
	pNewNode->pNext = NULL;

	if(g_pHead == NULL)
	{
		g_pHead = pNewNode;
	}
	else
	{
		p->pNext=pNewNode;
	}

	scanf("%s %d %d %d",pNewNode->stu.szName,&pNewNode->stu.nStuNum,&pNewNode->stu.nAge,&pNewNode->stu.nScore);

	//clear
	system(clear);

	printf("Insert data successful!\n");

}
void PrintStudent()
{
	
	system(clear);
	printf("***************Students information list***************\n");

	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	const char* data = "Callback function called";
	char sql[1024] = "";
	memset(sql, 0, sizeof(sql));

	/* Open database */
	rc = sqlite3_open("test.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}

	/* Create SQL statement */
	strcpy(sql, "SELECT * from STUDENT");

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Operation done successfully\n");
	}

	sqlite3_close(db);

	printf("*******************************************************\n");
}
void SaveStudent()
{
	system(clear);

	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	const char* data = "Callback function called";
	char sql[1024] = "";
	memset(sql, 0, sizeof(sql));

	/* Open database */
	rc = sqlite3_open("test.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}

	/* Create SQL statement */
	strcpy(sql, "CREATE TABLE STUDENT("  \
		"ID INT PRIMARY KEY     NOT NULL," \
		"NAME           TEXT    NOT NULL," \
		"AGE            INT     NOT NULL," \
		"SCORE			REAL	NOT NULL);");

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Table created successfully\n");
	}

	//Write data
	Node* p = g_pHead;	//present node
	while(p != NULL)
	{
		/* Create SQL statement */
		sprintf(sql, "INSERT INTO STUDENT (ID,NAME,AGE,SCORE) "  \
			"VALUES (%d, '%s', %d, %d); ", p->stu.nStuNum, p->stu.szName, p->stu.nAge, p->stu.nScore);

		/* Execute SQL statement */
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else {
			fprintf(stdout, "Records created successfully\n");
		}
		
		p = p->pNext;
	}

	/* Create SQL statement */
	strcpy(sql, "SELECT * from STUDENT");

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Operation done successfully\n");
	}

	sqlite3_close(db);

	printf("Save data successful!\n");
}

void DeleteStudent(int iNum)
{
	system(clear);

	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char sql[1024] = "";
	memset(sql, 0, sizeof(sql));
	const char* data = "Callback function called";

	/* Open database */
	rc = sqlite3_open("test.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}

	/* Create merged SQL statement */
	sprintf(sql, "DELETE from STUDENT where ID=%d; " \
		"SELECT * from STUDENT", iNum);

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Operation done successfully\n");
	}
	sqlite3_close(db);
}
