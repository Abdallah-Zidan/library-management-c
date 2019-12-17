#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * A console program to manage a library of books 
 * you can add new books providing the book details as  book id , book name , book author and  book price
 * you can search for a book using name or id 
 * you can edit book's details 
 * you can remove a book using it's id
 * books are saved in a dat file
 * */
 
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

int removeBook(int id);




// main functions 
void menu();


int main(int argc, char **argv)
{

    char path[] = "books.dat";
    char val[] = "Alchemist";
    struct node* phead = NULL;
    struct node* ptail = NULL;

    readFileIntoList(&phead,&ptail,path);
    struct Book book = fillBookData();
   addnode(&phead ,&ptail,book ) ;
   writeIntoFile(&book , path);
   bubbleSort(phead);
    printList(phead);
    
    struct Book* retval = search(phead,val);
    if(retval){
        printf("found ..... ");
        printBook(*retval);
    }
    
    
    printf("\n\nsize : %d\n",getSize(phead));
    
	return 0;
}




/**
 * @Fill book details from user input
 * @param void
 * @return  struct Book
 */
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


/**
 * @print the details of a single book
 * @param struct Book
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
 * @param struct Book
 * @return  struct node* 
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
 * @param pointer to the head pointer of the list
 * @param pointer to the tail pointer of the list
 * @param struct Book
 * @return  int
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
    retval =1;
    }
    return retval;
}


/*
 * write a node to the .dat file
 * shall be called after addnode function
 * */
 
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
    infile = fopen("books.dat", "r");
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
        }
      
   
    }
     // close file 
    fclose (infile); 
    retval =1;
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
    while (temp){
        if(strcmp(temp->book.name,name) == 0){
            ptr =& (temp->book);
            temp = NULL;
        }
        else{
            temp = temp->next;
        }
    }
    
    return ptr;
}



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
            if (ptr1->book.id> ptr1->next->book.id) 
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









