/*************************************************************************
    > File Name: StudentsManageSystem.h
    > Author: YangJintao
    > Mail: 18608842770@163.com 
    > Created Time: Sun 04 Mar 2018 10:10:59 AM DST
 ************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>


typedef struct tagStudent
{
	char szName[20];
	int	nStuNum;
	int nAge;
	int nScore;
}Student;

typedef struct tagNode
{
	Student stu;
	struct tagNode* pNext;//point to next student
}Node;

Node *g_pHead = NULL;	//head node

//insert students information
void InputStudent();
void PrintStudent();
void SaveStudent();
