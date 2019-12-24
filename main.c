#include <stdio.h>
#include "books.h"  // everything related to books is in that file


/*
 * A console program to manage a library of books 
 * you can add new books providing the book details as  book id , book name , book author and  book price
 * you can search for a book using name or id 
 * you can edit book's details 
 * you can remove a book using it's id
 * books are saved in a dat file
 * */
 
 
void menu(struct node ** phead , struct node ** ptail,char path[] );
char getch(void);
void moveCursor(int initY);





int main(int argc, char **argv)
{

    char path[] = "books.dat";
    struct node* phead = NULL;
    struct node* ptail = NULL;

  readFileIntoList(&phead,&ptail,path);

  menu(&phead,&ptail,path);
    
	return 0;
}


 void moveCursor(int initY){
     char ch ;
     ch =getch();
    switch (tolower(ch))
    {
    case 'w':
        initY++;
        gotoxy(1,initY);
        printf("*");
        break;
    case 's':
        initY--;
         printf("*");
        gotoxy(1,initY);
        break;
  
    }
 }





// Menu 

void menu(struct node ** phead , struct node ** ptail,char path[] ){
	struct node* ptr;
	struct Book* bookPtr , book;
    int choice , done =0 , removeId , retval ;
    char searchName[40];
   // char s[2];
    printf("Library management system using c language.\n\n");
   
do {
    system("clear");
 printf("choose from the following : \n");
    printf("1- add a new book.\n2- search for a book.\n3- get the books count.\n4- print the books in the library.\n5- sort the book alphabetically.\n6- remove book by id.\n7- exit.\n");
    printf("your choice : ");
    scanf("%d",&choice);
    system("clear");
    switch(choice){
        case 1:
            book = fillBookData();
            ptr = createnode(book);
            addnode(phead , ptail , book);
            writeIntoFile(&book , path);
            break;
        case 2:
            printf(KBLU);
        	printf("Enter the book name you want to search for : ");
        	scanf("%s",searchName);
        	bookPtr = search(*phead , searchName);
            printf(KNRM);
        	if(bookPtr){
        		printBook(*bookPtr);
        	}else{
                printf(KRED);
        		printf("sorry book not found.\n\n");
                
        	}
            printf(KNRM);
            break;
        case 3:
                printf(KGRN);
                printf("you have %d book in the library \n\n",getSize(*phead));
                printf(KNRM);
                break;
            case 4:
                printList(*phead);
               // moveCursor(16);
               // fflush(stdin);
                break;
            case 5:
                bubbleSort(*phead);
                break;
            case 6:
            printf(KRED);
                printf("the id of the book you want to delete ? : ");
                scanf("%d",&removeId);
                retval = removeBook(phead ,ptail , removeId,path);
                if(retval ){
                    printf(KGRN);
                    printf("successfully deleted book of id : %d\n\n",removeId);
                }else{
                    printf(KRED);
                    printf("sorry .. maybe that book doesn't exist\n\n");
                }
                printf(KNRM);
                break;
        case 7:
            done =1;
            break;
    }
     if(choice!=7)//don't print this when exit the program
     {
        
         printf("press any key to continue...");
         getch();
     }
    
}while(!done);
    

}













