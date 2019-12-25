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
struct User_node * create_user(void);
int add_user(struct User_node **Head,struct User_node **Tail);
struct user fill_user(void);
struct User_node * user_search(struct User_node *Head,struct User_node *Tail,char user[]);
void print_user(struct user u);
int login(struct User_node *Head,struct User_node *Tail);



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
    int retval=0;
    struct User_node *ptr= create_user();
    struct User_node *isExist;

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
            puts("s");
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
	char c,pass[21],*ptr;
	int l,done=0;
	strcpy(pass,"");
    printf("please enter user name: ");
    scanf("%s",u.user_name);
    printf("please enter password (max 20 chars): ");
    ptr=&c;
    while(!done)
    {
        l=0;
        do
        {
            c=getch();
            pass[l]=c;
            l++;
            // printf("%s\n",pass);
        }while(c!=10&&l<=20);
         if(l>20)
        {
            printf("\nsorry password is 20 chars max...\n enter your pass word again\n");
            strcpy(pass,"");
        }
        else
        {
              strcpy(u.password,pass);
              u.password[l]=0;
              done=1;
        }

    }
    // scanf("%s",u.password);
    return u;
}


//search for user
struct User_node * user_search(struct User_node *Head,struct User_node *Tail,char user[])
{
    struct User_node *ptr, *retval;
    ptr=Head;
    while(ptr)
    {
        if(!strcmp(ptr->u.user_name,user))
        {
            retval=ptr;
        }
        ptr=ptr->Next;
    }
    return retval;
}

//print user
void print_user(struct user u)
{
    printf("user: %s \t pass: %s\n",u.user_name,u.password);
}

int login(struct User_node *Head,struct User_node *Tail)
{
    char user[21],pass[21];
    struct User_node *isExist;
    int retval=0;
    printf("user name: ");
    scanf("%s",user);
    printf("\npassword: ");
    scanf("%s",pass);
    isExist=user_search(Head,Tail,user);
    if(isExist)
    {
        if(!strcmp(pass,isExist->u.password))
        {
            printf("%s\t%s",isExist->u.password,pass);
            retval=1;
        }
    }
    else
    {
        printf("\nusername or password is wrong\n");
    }
    return retval;
}