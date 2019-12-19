#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"


// global identifier variable used for auto increment book id
long int identifier =1l;

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
int addnode(struct node** phead,struct node** ptail,  struct Book book);

int readFileIntoList(struct node* * phead , struct node** ptail,char path[]);
int writeIntoFile(struct Book* book ,char path[]  );

void printList(struct node* phead);
int getSize(struct node* phead);

struct Book * search(struct node* phead,char name[]);

// sorting 
void swap(struct node* a , struct node* b);
void bubbleSort(struct node* head);

int removeBook(struct node ** phead,struct node** ptail,int id,char path[]);


/**
 * @Fill book details from user input
 * @param void
 * @return book : struct Book
 */
struct Book  fillBookData(){
   struct Book book;
    book.id = identifier;
    printf("Enter the book name : ");
    scanf("%s",book.name);
    printf("Enter book Author : ");
    scanf("%s",book.author);
    printf("Enter the book price : ");
    scanf("%d",&book.price);
    return book;
}


/**
 * @print the details of a single book
 * @param book : struct Book
 * @return  void
 */
void printBook(struct Book book){
    printf("\n");
    printf("book's id :   %d \n",book.id);
    printf("book's name:   %s \n",book.name);
    printf("book's author:  %s \n",book.author);
    printf("book's price:   %d  \n",book.price);
    printf("\n");
}


// list functions

/**
 * @brief  createnode function return a pointer to node 
 * @param book : struct Book
 * @return  ptr :  struct node* 
 */
 
struct node * createnode( struct Book book){
            struct node * ptr = (struct node *) malloc(sizeof(struct node));
            if(ptr){
                ptr->book = book;
                ptr->next = NULL;
                ptr->prev = NULL;
            }
            
            return ptr;
}

/**
 * @brief   append a node to the list  
 * @param phead : struct node**  ( pointer to the head pointer of the list )
 * @param ptail : struct node** ( pointer to the tail pointer of the list)
 * @param book : struct Book
 * @return  retval : int (check if addition was successful)
 */
 
int addnode(struct node** phead,struct node** ptail, struct Book book){
   
    int retval =0;
    struct node* ptr = createnode(book);
    if(ptr){
        if(!*phead){
            *phead =*ptail = ptr;
        }
        else{
            ptr->prev = *ptail;
            (*ptail)->next = ptr;
            *ptail = ptr;
        }
        identifier++;
    retval =1;
    }
    return retval;
}


/**
 * @brief   write data  into the .dat file 
 * @param book : struct Book*
 * @param path : char []  ( the file path to write into)
 * @return  retval : int (check if writing was successful)
 */
 
int writeIntoFile(struct Book*  book ,char path[]  ){
    int retval =0;
     FILE * outfile ;
      outfile = fopen (path, "a"); 
        
        // check if the file is opened 
        if (outfile == NULL) 
            { 
                fprintf(stderr, "\nError opening the file .. data may not be saved \n"); 
       
            } 
        else{
                        // writing the content of book struct into the file 
        
                        fwrite (book,sizeof(struct Book),1,outfile);
        
                        printf("book added and contents to file written successfully !\n"); 
                        fclose (outfile);
                        retval =1;
        }
        return retval;
}


int readFileIntoList(struct node** phead , struct node** ptail, char path[]  ){
    int retval =0;
    struct Book input;
    FILE * infile ;
    infile = fopen(path, "r");
     if(infile != NULL){
        while(fread(&input, sizeof(struct Book), 1, infile)) {
            // add each struct into the list
               struct node* ptr = createnode(input);
                if(ptr){
                if(!*phead){
                    *phead =*ptail = ptr;
                }
            else{
                ptr->prev = *ptail;
                (*ptail)->next = ptr;
                *ptail = ptr;
            }
         identifier=input.id;
        }
      
   
    }
     // close file 
    fclose (infile); 
    retval =1;
    identifier++;
     }
    return retval;

}


// print the whole list of books

void printList(struct node* phead){
    struct node * temp = phead;
    if(!temp){
        printf("\nLibrary is empty.\n");
    }
    else{
        printf("\n[[\n");
        
           while(temp){
                printBook(temp->book);
                temp= temp->next;
                printf("\n***********************************************\n");
            }
            
            printf("\n]]\n");
    }
 
}


// get list size
int getSize(struct node* phead){
    int size =0;
    struct node* temp = phead;
    while(temp){
        size ++;
        temp = temp->next;
    }
    return size;
    
}

// search function

struct Book * search(struct node* phead,char name[]){
    struct node* temp = phead;
    struct Book* ptr = NULL;
    char tempName[40];
    // convert to lower case for ignore case comparison
    tolowercase(name);
    while (temp){
    	strcpy(tempName,temp->book.name);
    	tolowercase(tempName);
        if(strcmp(tempName,name) == 0){
            ptr =& (temp->book);
            temp = NULL;
        }
        else{
            temp = temp->next;
        }
    }
    
    return ptr;
}

// sort according to book names 
void bubbleSort(struct node *head) 
{ 
    int swapped, i; 
    struct node *ptr1; 
    struct node *lptr = NULL; 
  
    /* Checking for empty list */
    if (head == NULL) 
        return; 
  
    do
    { 
        swapped = 0; 
        ptr1 = head; 
  
        while (ptr1->next != lptr) 
        { 
            if (strcmp(ptr1->book.name, ptr1->next->book.name ) >0)
            {  
                swap(ptr1, ptr1->next); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    } 
    while (swapped); 
} 
  

/* function to swap data of two nodes a and b*/
void swap(struct node *a, struct node *b) 
{ 
    struct Book temp = a->book; 
    a->book = b->book; 
    b->book= temp; 
} 


/**
 * @brief Delete a book
 * @param &phead
 *  @param &ptail
 * @param id
 */
 
 int removeBook(struct node** phead ,struct node** ptail, int id,char path[]){
     int found =0 , deleted =0;
    
     struct node * temp = *phead;
    
// if the list isn't empty 
 if(temp){
    // still in the list boundary and didn't find the record yet 
     while(temp && !found){
         if(temp->book.id == id){
             // check if the found record is the only record 
            if(temp == *phead && temp == *ptail){
                *phead = *ptail = NULL;
                identifier = 1;
            }    
            // if not the only record but the first record 
            else if(temp == *phead){
                ( *phead)->next->prev = NULL;
               (*phead) = (*phead)->next;
               free(temp);
            }
             // if not the only record but the last record 
            else if(temp == *ptail){
               (*ptail)->prev->next = NULL;
               *ptail = (*ptail)->prev;
               free(temp);
                 identifier = id;
            }
            // a record in between any other 2 records 
            else{
                temp->next->prev = temp->prev;
                temp->prev->next = temp->next;
                free(temp);
            }
            found =1;
            deleted =1;
         }
         temp = temp->next;
     }
     }
     if(deleted){
         remove(path);
     
        temp = *phead;
    
        
        while(temp){
            writeIntoFile(&(temp->book) , path);
            temp = temp->next;
        }
     }
     
     
     return deleted ;
     
 }


