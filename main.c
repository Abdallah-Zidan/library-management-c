#include <stdio.h>
#include "books.h"  // everything related to books is in that file
#include "user.h"  //verything related to users is in that file


/*
 * A console program to manage a library of books 
 * you can add new books providing the book details as  book id , book name , book author and  book price
 * you can search for a book using name or id 
 * you can edit book's details 
 * you can remove a book using it's id
 * books are saved in a dat file
 * */
 
 
void menu(struct node ** phead , struct node ** ptail,char path[] );
void user_menu(struct User_node ** Head , struct User_node ** Tail,char U_Path[] ,struct node ** phead , struct node ** ptail,char path[] );
char getch(void);
int traverseList(int initY,int limit,struct node* walker);





int main(int argc, char **argv)
{

    char path[] = "books.dat";
    char U_path[]="users.dat";
    struct node* phead = NULL;
    struct node* ptail = NULL;
    struct User_node *Head =NULL;
    struct User_node *Tail =NULL;
    readFileIntoList(&phead,&ptail,path);
    user_menu(&Head,&Tail,U_path,&phead,&ptail,path);
	return 0;
}

/**
 * @brief   move over the list of books and view the details any chosen book
 * @param  initY : int (initial y position for the cursor)
 * @param  limit : int (the maximum y position for cursor to go)
 * @param  walker  : node * ( a pointer to move over the list)
 * @return retval : int (check if enter or q was pressed)
 */
 int traverseList(int initY,int limit,struct node* walker){
     char ch ;
     int done =0,retval=50;
      // retval is to check if the user clicked on enter to view the book or q to leave the list
     // the value will be returned to the menu in order to take the right action.
     
     if(walker){
        gotoxy(1,initY);
        printf(KYEL "*");
        printf(KNRM );
        gotoxy(1,initY);
     do{
        ch =getch();
        switch (tolower(ch))
        {
        case 's':
        if (initY < limit-7)
        {
            walker = walker->next;
            initY+=7;
            printf("  ");
            gotoxy(1,initY);
            
            printf(KYEL"*");
            printf(KNRM);
            gotoxy(1,initY);
        }
        
        break;
        case 'w':
            if(initY >7){
                walker = walker->prev;
                initY-=7;
                printf("  ");
                gotoxy(1,initY);
                printf(KYEL "*");
                printf(KNRM);
                gotoxy(1,initY);
            }
            break;
        case 'q':
            done =1;
            retval =50;
            gotoxy(1,limit+7);
            break;

        case 10:
            system("clear");
            printBook(walker->book);
            printf("press any key to return to the list");
            getch();
            retval =4;
            done =1;
            break;
  
          }
         }while (!done);
     }
     
      
         return retval;
     
 }





// Menu 

void menu(struct node ** phead , struct node ** ptail,char path[] ){
	struct node* ptr , *walker ;
	struct Book* bookPtr , book;
    int choice , done =0 , removeId , retval , printllistSize  , check=0;
    char searchName[40];
   // char s[2];
    printf("Library management system using c language.\n\n");
   
do {
    system("clear");
    printf("choose from the following : \n");
    printf("1- add a new book.\n2- search for a book.\n3- get the books count.\n4- print the books in the library.\n5- sort the book alphabetically.\n6- remove book by id.\n7- exit.\n");
    printf("your choice : ");
    if(!check){
        scanf("%d",&choice);
    }
 
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
                gotoxy(1,1);
                
                printf("                                                      ");
                printList(*phead);
                if(*phead){
                     printf("Use w and s to move up and down\n");
                     printf("\nPress enter to view the full book details or q to return to main menu");
                }
                printllistSize=getSize(*phead)*6+7;
                walker = *phead;
                choice = traverseList(7,printllistSize,walker);
                if(choice ==4){
                   check =1;
                }
                else{
                   check =0;
                }
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
            gotoxy(1,1);
            break;
    }
    if(!check){
        if(choice!=7 )//don't print this when exit the program
        {
        
         printf("press any key to continue...");
         getch();
         }
    }
     
    
}while(!done);
}

void user_menu(struct User_node **Head , struct User_node **Tail,char U_Path[] ,struct node **phead , struct node **ptail,char path[] )
{
    int choice,done=0,root=0;
    struct User_node *ptr;
    if(readUsersFileIntoList(Head ,Tail,U_Path))
    do
    {
         
        if(choice!=4)//to exit the program when exit the functions menu
        {
          system("reset");
          printf("choose from the following : \n");
          printf("1- login.\n2- create a new user.\n3- printall.\n4- exit.\n");
          printf("your choice : ");
          scanf("%d",&choice);
          system("clear");
        }
        switch(choice)
        {
        case 1:
        {
            if(login(*Head,*Tail))//access granted
            {
                menu(phead,ptail,path);
                system("clear");
                choice=4;//mark exit after exit the functions menu
               
            }
            else//access denied
            {
                printf("username or password is wrong..!\n");
            }
            break;
        }
        
        case 2:
        {
            // if(root)//only root user can add new users
            ptr=add_user(Head,Tail);
            if(ptr)
            {
               
                if(writeUserIntoFile(&(ptr->u), U_Path  ))
                {
                     printf("\nuser created succesfully..!");
                }


            }
            else
            {
                printf("\nsorry user creation failed ..try again \n");
            }
            break;
                
        }
        case 3:
        {
             struct User_node *ptr;
   
            ptr=*Head;
            while(ptr)
             {
               print_user(ptr->u);
                ptr=ptr->Next;
             }
            break;
        }
        case 4:
        {
            done=1;
            break;
        }
        
    }
    if(choice!=4)//don't print this when exit the program
         {
         printf("\npress any key to continue...\n");
         getch();
         }
    }while(!done);
}



