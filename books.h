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
    printf(KGRN);
    printf("Enter the book name : ");
    scanf("%s",book.name);
    printf("Enter book Author : ");
    scanf("%s",book.author);
    printf("Enter the book price : ");
    scanf("%d",&book.price);
    printf(KNRM);
    return book;
}

/**
 * @print the details of a single book
 * @param book : struct Book
 * @return  void
 */
void printBook(struct Book book){
    printf("\n");
    printf("-------------------------\n");
    printf(KYEL "book's id    :  ");   
    printf(KWHT"%d \n",book.id);
    printf(KYEL "book's name  :  ");   
    printf(KWHT"%s \n",book.name);
    printf(KYEL "book's author:  ");   
    printf(KWHT"%s \n",book.author);
    printf(KYEL "book's price :  ");   
    printf(KWHT"%d  \n",book.price);
    printf("-------------------------\n");
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
                        fclose (outfile);
                        retval =1;
        }
        return retval;
}

/**
 * @brief   load the data from file into list
 * @param phead : struct node**
 * @param ptail : struct node**
 * @param path : char []  ( the file path to read from)
 * @return  retval : int (check if reading was successful)
 */

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
        printf(KRED"\nLibrary is empty.\n\n");
        printf(KWHT);
    }
    else{
        printf("\n\n[[\n\n");
        
           while(temp){
             
                printf(KRED "-------------------\n");
                printf(KRED "-------------------\n");
                printf(KYEL "Id   ")  ;
                printf(KWHT ":  %d\n",temp->book.id);
                printf(KYEL "Name ");
                printf(KWHT ":  %s\n",temp->book.name);
                printf(KRED "-------------------\n");
                printf(KRED "-------------------\n");
                temp= temp->next;
                printf( KWHT ",\n");
            }
            
            printf("\n]]\n\n");
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

/**
 * @brief   search for a book using its name
 * @param phead : struct node*
 * @param name : char []  ( the book name )
 * @return ptr : struct Book * ( pointer to the found book " NULL if not found")
 */
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
    char tmp1 [40] ;
    char tmp2[40];
  
    /* Checking for empty list */
    if (head == NULL) 
        return; 
  
    do
    { 
        swapped = 0; 
        ptr1 = head; 
  
        while (ptr1->next != lptr) 
        { 
            strcpy(tmp1 , ptr1->book.name);
            strcpy(tmp2,ptr1->next->book.name);
            // for non case sensitive comparison
            tolowercase(tmp1);
            tolowercase(tmp2);
            
            if (strcmp(tmp1, tmp2 ) >0)
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


