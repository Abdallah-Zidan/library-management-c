#include <stdio.h>
#include <stdlib.h>


struct Book{
        int id;
        char name[40];
        char author[30];
        int price ;
} ;


 struct node {
        struct Book book;
        struct node* next;
       struct node* prev;    
} ;

// Book details functions //
struct Book fillBookData();
void printBook(struct Book book);


// list functions //
struct node * createnode(struct Book book);
int addnode(struct Book book);
int removeBook(int id);





int main(int argc, char **argv)
{
	
    struct Book book = fillBookData();
    printBook(book);
    
	return 0;
}


// book functions 
struct Book  fillBookData(){
   struct Book book;
    printf("Enter the book id: ");
    scanf("%d",&book.id);
    printf("Enter the book name : ");
    scanf("%s",book.name);
    printf("Enter book Author : ");
    scanf("%s",book.author);
    printf("Enter the book price : ");
    scanf("%d",&book.price);
    
    return book;
}

void printBook(struct Book book){
    printf("\n");
    // printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("book's id :   %d \n",book.id);
    printf("book's name:   %s \n",book.name);
    printf("book's author:  %s \n",book.author);
    printf("book's price:   %d  \n",book.price);
  //  printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\n");
}