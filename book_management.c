/*
*   File name: book_management.c
*   Author: Phan Minh Thong
*   Date: --/--/--
*   Desciption: **************Service to manage Books in a Library***********************
                I/ The book records are kept in the Singly Linked List as nodes, 
                with each node linking to the next node.

                II/ Using two different linked lists to create the dataset of the books. 
                Each linked list stores the data of the books in three fields:
                    1/name of book
                    2/name of author 
                    3/id of the book.

                III/ One of the linked lists stores the books that are AVAILABLE in he library 
                and the second list stores the books which are LOANED to students. 
                    Studemts can loan books from the available books. This book will given by admin. 
                The loaned book gets deleted from the available books list and is added to 
                the loaned books list.

                IV/ The Admin can save two lists in file after update Books to Library database.
                    File Available.bin contains all available books. And Loaned.bin contains all
                    loaned Books.
                **************************************************************************
*/

#include "book_management.h"

/*
* Function name: PrintMessage
* Description: Print out the Welcome Title.
* Input: None
* Output: None
*/
void PrintMessage(void){
    printf("\n  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("                    WELCOME TO BOOK MANAGEMENT SYSTEM                   ");
    printf("\n  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
}

/*
* Function name: Create_Available
* Description:  Create a linked list of available books by 
				taking input from the user about the first book. 
* Input: None
* Output: 
	Return: Book* - Pointer to the List.
*/
Book* Create_Available_List(void){
    Book *head;
    head = (Book*)malloc(sizeof(Book));
    char Name[30] , Author[30];
        // Enter the ID of book.
    printf("\nPlease Enter Data for the Book!\n");
    printf("\n>>\tEnter ID of the Book : ");
    scanf("%d",&head->id);
    	// Enter the Name of book.
    printf("\n>>\tEnter the Book's Name : ");
    scanf("%s",Name);
    strcpy(head->Name , Name);
        // Enter the Author of book.
    printf("\n>>\tEnter Book's Author: ");
    scanf("%s",Author);
    strcpy(head->Author , Author);
    
	head->next = NULL;
    return head;
}

/*
* Function name: Add_Available_Book
* Description: 	Add books in the linked list of available books 
				by taking input from the user.
* Input: 
	m - Number of Book(Node) will be add to List.
	*head - Pointer to List of Books.
* Output: 
	Return: None.
*/
void Add_Available_Book(int m , Book *head){
    Book* temp;
    char Name[30],Author[30];
    //Goto the last Node
    while(head->next != NULL)
    {
        head = head->next;
    }
    //Create m Node and add to the list
    for(int i=0; i<m ; i++)
    {
        temp = (struct Book*)malloc(sizeof(Book));
        printf("\nPlease Enter Data for the Book!\n");
        printf("\n>>\tEnter ID of the Book : ");
        scanf("%d",&temp->id);

        printf("\n>>\tEnter the Book's Name : ");
        scanf("%s",Name);
        strcpy(temp->Name,Name);

        printf("\n>>\tEnter Book's Author: ");
        scanf("%s",Author);
        strcpy(temp->Author , Author);
        //Last Node point to NULL
        temp->next=NULL;
        //Add node to head
        head->next = temp;
        head = head->next;

    }
}

/*
* Function name: Delete_Book_ByID
* Description: Delete a Specific Book Node in linked list by using the ID gived by User.
* Input: 
	*head - Pointer to List of Books.
	id - The ID of Book will be deleted.
* Output: 
	Return the pointer to the list.
*/
Book* Delete_Book_ByID(Book *head, int id){
    Book *temp = head;
    Book *prev;
    if(temp != NULL && temp->id == id)
    {
        head = temp->next;
        free(temp);
        return head;
    }

    while(temp != NULL && temp->id != id)
    {
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL)
        return head;
    
    prev->next = temp->next;

    free(temp);
    
    return head;
}

/*
* Function name: Create_List_From_Data
* Description: 	create a linked list while reading the data from previously available
				dataset stored in binary files.
* Input: 
	*data - Pointer to List.
* Output: 
	Return: pointer to the list after create.
*/
Book* Create_List_From_Data(Book *data){
    Book *head;
    head = (Book*)malloc(sizeof(Book));

    head->id = data->id;
    strcpy(head->Name, data->Name);
    strcpy(head->Author,data->Author);
    head->next = NULL;

    printf("Created List Successfully!\n");
    return head;
}

/*
* Function name: Add_Book_To_List
* Description: Add books to a specific list after issuing or returning the book.
* Input: 
	*data - Pointer to data to be added.
	*head - Pointer to Book list.
* Output: 
	Return: None.
*/
void Add_Book_To_List(Book *data, Book *head){
     while(head->next != NULL)
    {
        head = head->next;
    }

    Book *temp;
    temp = (Book*)malloc(sizeof(Book));
    head->next = temp;

    temp->id = data->id;
    strcpy(temp->Name, data->Name);
    strcpy(temp->Author,data->Author);
    temp->next = NULL;
}

/*
* Function name: Search_Book_In_List
* Description: Check if a specific list contains the given book or not.
* Input: 
	*head - Pointer to Book list.
	id - ID of Book being searched.
* Output: 
	Return: Pointer to the Node of Book.
*/
Book* Search_Book_In_List(Book *head, int id){
    Book *temp,*p;
    int book_found = 0;

    temp = (Book *)malloc(sizeof(Book));

    p = head;
    while(p != NULL)
    {
        if(p->id == id)
        {
            book_found = 1;
            temp->id = p->id;
            strcpy(temp->Name, p->Name);
            strcpy(temp->Author ,p->Author);
        }
        p = p->next;
    }

    printf("Search Completed!\n");
    if(book_found == 1)
        return temp;
    else
        return NULL;   
}

/*
* Function name: Display
* Description: Display all the books in the list of choice.
* Input: 
	*head - Pointer to Book list.
* Output: 
	Return: None.
*/
void Display(Book *head){
    printf("\t-----------------------------------------");
    printf("\n\tID\t\tName\t\tAuthor\n");
    printf("\t-----------------------------------------");
    while(head!=NULL)
    {
        printf("\n\t%d\t\t%s\t\t%s\n",head->id,head->Name,head->Author);
        head = head->next;
    }
}

/*
* Function name: Write_To_File
* Description: Write whole list of Book to a Binary File.
* Input: 
	*available - Pointer to Available Book list.
	*issued - Pointer to Loaned Book list
* Output: 
	Return: None.
*/
void Write_To_File(Book *available, Book *issued){
    FILE *pFile;
    pFile = fopen("Available.bin","wb");

    if(pFile != NULL)
    {
        Book *current = available;
        Book *hold = NULL;

        while(current != NULL)
        {
            hold = current->next;

            current->next = NULL;

            fseek(pFile,0,SEEK_END);
            fwrite(current, sizeof(Book),1,pFile);

            printf("Writing: %s to file!\n",current->Name);

            current->next = hold;
            hold = NULL;
            current = current->next;
        }
        fclose(pFile);
        pFile = NULL;
    }
    else
    {
        printf("*\tFILE OPEN ERROR\n");
    }

    pFile = fopen("Loaned.bin","wb");
    if(pFile != NULL)
    {
        Book *current = issued;
        Book *hold = NULL;

        while(current != NULL)
        {
            hold = current->next;

            current->next = NULL;

            fseek(pFile,0,SEEK_END);
            fwrite(current, sizeof(Book),1,pFile);

            printf("Writing:%s to file\n",current->Name);

            current->next = hold;
            hold = NULL;
            current = current->next;
        }
        fclose(pFile);
        pFile = NULL;
    }
    else
    {
        printf("*\tFILE OPEN ERROR\n");
    }
}

/*
* Function name: Read_Next_From_File
* Description: Read the next Book from binary file.
* Input: 
	*start - Pointer to Book Node to save data.
	*pFile - Pointer to file.
* Output: 
	Return: Pointer to Book Node after reading data.
*/
Book* Read_Next_From_File(Book *start, FILE *pFile){
    size_t returnValue;
    if(start == NULL)
    {
        start = malloc(sizeof(Book));
        returnValue = fread(start, sizeof(Book),1,pFile);
        start->next = NULL;
    }
    else
    {
        Book *indexBook = start;
        Book *newBook = malloc(sizeof(Book));
        while(indexBook->next != NULL)
        {
            indexBook = indexBook->next;
        }
        returnValue = fread(newBook, sizeof(Book),1,pFile);
        indexBook->next = newBook;
        newBook->next = NULL; 
    }
    return start;
}

/*
* Function name: Read_Available_List
* Description: Read all data saved in Available.bin file.
* Input: 
	*start - Pointer to the fisrt Node to be read.
* Output: 
	Return: Pointer to Book Node after reading data.
*/
Book* Read_Available_List(Book *start){
    FILE *pFile;
    pFile = fopen("Available.bin","rb");
    if(pFile != NULL)
    {
        start = NULL;

        fseek(pFile, 0, SEEK_END);
        long fileSize = ftell(pFile);
        rewind(pFile);

        int numEntries = (int)(fileSize / (sizeof(Book)));
        printf("Number of Available Entries: %d\n",numEntries);

        int loop = 0;
        for(loop = 0;loop < numEntries; loop++)
        {
            fseek(pFile,(sizeof(Book) * loop), SEEK_SET);
            start = Read_Next_From_File(start,pFile);
        }
    }
    else
    {
        printf("*\tFILE OPEN ERROR IN READ\n");
    }
    return start;
}

/*
* Function name: Read_Loaned_List
* Description: Read all data saved in Loaned.bin file.
* Input: 
	*start - Pointer to the fisrt Node to be read.
* Output: 
	Return: Pointer to Book Node after reading data.
*/
Book* Read_Loaned_List(Book *start){
    FILE *pFile;
    pFile = fopen("Loaned.bin","rb");
    if(pFile != NULL)
    {
        start = NULL;

        fseek(pFile, 0, SEEK_END);
        long fileSize = ftell(pFile);
        rewind(pFile);

        int numEntries = (int)(fileSize / (sizeof(Book)));
        printf("Number of Loaned Entries: %d\n",numEntries);

        int loop = 0;
        for(loop = 0;loop < numEntries; loop++)
        {
            fseek(pFile,(sizeof(Book) * loop), SEEK_SET);
            start = Read_Next_From_File(start,pFile);
        }
    }
    else
    {
        printf("*\tFILE OPEN ERROR IN READ\n");
    }
    return start;
}

/*
* Function name: login
* Description: Service to check password and user id.
* Input: none.
* Output: 
	Return: 1 if login information's incorrrect. 0 if it's correct.
*/
int Admin_Login_Authen(){

    char acc[50];
    int attempts = 0;
    User:
    printf("\n>>\tEnter your Admin Account: ");
    scanf("%s", acc);

    if (strcmp(acc,"adminaccount")==0)
    {
        printf("Id is correct!!\n");
        attempts = 0;
    }

    else
    {
        printf("\n*\tYou have enetred an invalid Account!!!\n");
        attempts++;
        if(attempts<3)
        {
            printf("You have %d times reamining to try! Please enter again!\n",(3-attempts));
            goto User;
        }
        else
            return 1;
    }

    char pass[50];

    pass:
    printf(">>\tEnter your password: ");
    scanf("%s", pass);

    if(strcmp(pass,"12345")==0)
    {
        printf("You have successly loged in!!\n");
    }

    else
    {
        printf("*\tYou have entered a wrong password!!!\n");
        attempts++;
        if(attempts<3)
        {
            printf("You have %d time to try! Enter your password again!\n",(3-attempts));
            goto pass;
        }
        else
            return 1;
    }

    return 0;
}

