#include <stdio.h>
#include <string.h>
struct user
{
    char user_name[21];
    char password[21];
    char security_answer[20];
   
};
struct User_node
{
    struct user u;
    struct User_node *Next; 

};

//funtions on list
struct User_node * create_user();
int user_search(struct User_node *Head,struct User_node *Tail,char user[]);
int add_user(struct User_node **Head,struct User_node **Tail);

//functions on user
struct user fill_user(void);
int user_search(struct User_node *Head,struct User_node *Tail,char user[]);


//create user
struct User_node * create_user()
{
    struct User_node *ptr;
    ptr=(struct User_node *)malloc(sizeof(struct User_node));
    if(ptr)
    {
        ptr-> u=fill_user();
        ptr-> Next =NULL;
    }
    return ptr;
}

int add_user(struct User_node **Head,struct User_node **Tail)
{
    int isExist=0,retval=0;
    struct User_node *ptr= create_user();

    if(ptr)
    {
        if(!*Head) //no list
        {
            *Head=*Tail=ptr;
        }
        else //there is a list
        {   
            //search for the same user is exist or not
            isExist=user_search(*Head,*Tail,ptr->u.user_name);
            while(isExist)
            {
                printf("sorry user name already exist try again..");
                free(ptr);
                ptr=create_user();
				isExist=user_search(*Head,*Tail,ptr->u.user_name);
            }

			if(Head==Tail)//1 user only
			{
				(*Head)->Next=ptr; //error is here
				*Tail=ptr;

			}
			else // more than 1 user
			{
				 (*Tail)->Next=ptr;
				 *Tail=ptr;
			}

		}
        retval=1;
    }
    return retval;
}

//fill user
struct user fill_user(void)
{
    
    struct user u;
	char c,pass[21];
	int l,done=0;
	strcpy(pass,"");
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


//search for user
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