#include <stdio.h>
#include <string.h>
struct user
{
    char user_name[21];
    char password[21];
   
};
struct User_node
{
    struct user u;
    struct User_node *Next; 

};
//funtions on list
struct User_node * create_user(struct User_node *Head,struct User_node *Tail);
int user_search(struct User_node *Head,struct User_node *Tail,char user[]);
int add_user(struct User_node *Head,struct User_node *Tail);

//functions on users
struct user fill_user(void);

//create user
int add_user(struct User_node **Head,struct User_node **Tail)
{
    struct User_node *ptr;
    int retval=0,done=0;
     ptr=create_user(*Head,*Tail);
        if(!*Head) //there is no users
        {
            *Head=*Tail=ptr;
            
            printf("%s sttt\t\t",*Head->u.user_name);
            

        }
        else //there is a user or more
        {
            do
        {
           
            // printf("%s\n",us.user_name);
             if(!user_search(*Head,*Tail,ptr->u.user_name))
                 {
                     *Tail->Next=ptr;
                     *Tail=ptr;
                     retval=1;
                     done=1;
                    //  printf("%s\n",ptr->u.user_name);
                 }
             else
                 {
                     printf("user already exists\n..try again !");
                     ptr=create_user(*Head,*Tail);
                  }
        }while(!done);
            
        
       
        
        
        
        
    }
    return retval;

}

//create user
struct User_node * create_user(struct User_node *Head,struct User_node *Tail)
{
    struct User_node *ptr;
    // struct user us;
    ptr=(struct User_node* ) malloc(sizeof(struct User_node));
    if(ptr)
    {
        ptr->Next=NULL;
        ptr->u=fill_user();
    }
    return ptr;
}

//fill user
struct user fill_user(void)
{
    struct user u;
    char c,pass[21]={};
    int l,done=0;
    printf("please enter user name: ");
    scanf("%s",u.user_name);
    printf("please enter password (max 20 chars): ");
    // while(!done)
    // {
    //     l=0;
    //     do
    //     {
    //         c=getch();
    //         l++;
    //         printf("%d",c);
    //     }while(c!=10&&l<=20);
    //      if(l>20)
    //     {
    //         printf("sorry password is 20 chars max...\n enter your pass word again");
    //     }
    //     else
    //     {
    //           //printf("user created !");
    //           done=1;
    //     }

    // }
    scanf("%s",u.password);
    return u;
}

//user_search for user
int user_search(struct User_node *Head,struct User_node *Tail,char user[])
{
    int retval=0;
    struct User_node *ptr;
    ptr=Head;
    while(ptr->Next)
    {
        if(!strcmp(ptr->u.user_name,user))
        {
            retval=1;
        }
    }
    return retval;
}
