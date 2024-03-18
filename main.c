/*
*   File name: main.c
*   Author: Phan Minh Thong
*   Date: --/--/--
*   Desciption: Service to manage Books in a Library.
                Application file.
*/
#include "book_management.h"

int main()
{
    Book *available_head = NULL ,*issued_head = NULL, *p;
    int menu_check=1,choice;
    int Search_ID,x;

    PrintMessage();
    
    x = Admin_Login_Authen();

    if(x==0)
    {
        do
        {   printf("\n>>Welcome! Give a choice:");
            printf("\n\t\t(1) Add Books to Library");
            printf("\n\t\t(2) Loan New Book");
            printf("\n\t\t(3) Return Loaned Book");
            printf("\n\t\t(4) Display Available Books");
            printf("\n\t\t(5) Display Loaned Books");
            printf("\n\t\t(6) Write in file");
            printf("\n\t\t(7) Read Data");
            printf("\n\t\t(8) Exit");
            printf("\n>>\tEnter your choice here: ");
            scanf("%d",&choice);

            switch (choice)
            {
                case 1: printf("\n>>\tEnter number of Books you want to add : ");
                int m;
                scanf("%d",&m);
                if(available_head == NULL)
                {
                    available_head = Create_Available_List();
                    Add_Available_Book(m-1,available_head);
                }
                else
                    Add_Available_Book(m,available_head); 
                break;

                case 2: printf("\n>>\tEnter the Id of the Book you want to loan : ");
                scanf("%d",&Search_ID);
                p = Search_Book_In_List(available_head, Search_ID);
                if(p != NULL && issued_head == NULL)
                {
                    issued_head = Create_List_From_Data(p);
                    available_head = Delete_Book_ByID(available_head, Search_ID);
                    printf("\tDelete Done!\n");
                }
                else if(p != NULL && issued_head != NULL)
                {
                    Add_Book_To_List(p, issued_head);
                    available_head = Delete_Book_ByID(available_head, Search_ID);
                    printf("\tDelete Done!\n");
                }
                else if( p == NULL)
                {
                    printf("*\tBook not found!!\n");
                }
                break;

                case 3: printf("\n>>\tEnter the Id of the Book you want to return : ");
                scanf("%d",&Search_ID);
                p = Search_Book_In_List(issued_head, Search_ID);
                if(p != NULL && available_head == NULL)
                {
                    printf("Book found!\n");
                    available_head = Create_List_From_Data(p);
                    issued_head = Delete_Book_ByID(issued_head, Search_ID);
                    printf("Delete Done!\n");
                }
                else if(p != NULL && issued_head != NULL)
                {
                    Add_Book_To_List(p, available_head);
                    issued_head = Delete_Book_ByID(issued_head, Search_ID);
                    printf("Delete Done!\n");
                }
                else if( p == NULL)
                {
                    printf("*\tBook not found!\n");
                }
                break;

                case 4: 
                if(available_head!=NULL)
                    Display(available_head);
                else
                    printf("\n***\tThis Category is EMPTY, try again by reading the data fist!\n");
                break;

                case 5: 
                if(issued_head!=NULL)
                    Display(issued_head);
                else
                    printf("\n***\tThis Category is EMPTY, try again by reading the data fist!\n");
                break;

                case 6: Write_To_File(available_head, issued_head);
                break;

                case 7: available_head = Read_Available_List(available_head);
                issued_head = Read_Loaned_List(issued_head);
                break;

                case 8: printf("\nExit from the service! All files will be saved and updated.!\n");
                Write_To_File(available_head, issued_head);
                printf("Files updated and saved! You are out now!\n Exit!");
                exit(1);
                break;

                default:printf("\n***\tYou have entered an Invalid Choice, please try again.!");
                break;
            }

        }
        while(menu_check==1);
    }
    else
    {
        printf("***\tMaximum attempts reached! \n");
    }
    return 0;
}