# library-management-c

### A simple console program to manage library

=================================================================

#### Linked list is used in order to save books data.

#### Data is then saved into a file for permanent storage.

## features

##### 1. add new book to the library.

##### 2. search for a book using name.

##### 3. get the count of books in the library.

##### 4. print the whole list of books.

##### 5. sort the books alphabetically.

##### 6. remove a book using its id.

##### 7. exit the program.

### Books Functions

```c
        // Book details functions //
        struct Book fillBookData();
        void printBook(struct Book book);

        // list functions //
        struct node * createnode(struct Book book);
        int addnode(struct node** phead,struct node** ptail,  struct Book book);
        int removeBook(struct node ** phead,struct node** ptail,int id,char path[]);

        int readFileIntoList(struct node* * phead , struct node** ptail,char path[]);
        int writeIntoFile(struct Book* book ,char path[]  );

        void printList(struct node* phead);
        int getSize(struct node* phead);

        struct Book * search(struct node* phead,char name[]);

        // sorting
        void swap(struct node* a , struct node* b);
        void bubbleSort(struct node* head);

```
