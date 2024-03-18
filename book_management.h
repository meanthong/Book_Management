/*
*   File name: book_management.c
*   Author: Phan Minh Thong
*   Date: --/--/--
*   Desciption: **************Service to manage Books in a Library***********************
*/
#ifndef BOOK_MANAGEMENT_H
#define BOOK_MANAGEMENT_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

	/*
	* The struct include data of a book in database.(A Node in list)
	* id - The ID of the book.
	* Name - Name of the book.
	* Author - Author of the book.
	* *next - The pointer to the next Node in the linked list.
*/
typedef struct
{
    int id;
    char Name[30];
    char Author[30];
    struct Book *next;
} Book;

void PrintMessage(void);
Book* Create_Available_List(void);
void Add_Available_Book(int m , Book *head);
Book* Delete_Book_ByID(Book *head, int id);
Book* Create_List_From_Data(Book *data);
void Add_Book_To_List(Book *data, Book *head);
Book* Search_Book_In_List(Book *head, int id);
void Display(Book *head);
void Write_To_File(Book *available, Book *issued);
Book* Read_Next_From_File(Book *start, FILE *pFile);
Book* Read_Available_List(Book *start);
Book* Read_Loaned_List(Book *start);
int Admin_Login_Authen();

#endif