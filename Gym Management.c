#include<stdio.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include<stdlib.h>
#define size 30


void addrecords();
void modifyrecords();
void deleterecords();
void searchrecords();

struct client
{
 char id[20];
 char name[50];
 char trainer[10];
 char place[10];
 char amount[10];
 char membersince[20];
};

typedef  struct client sub;
char buf[size],u[11][11];
int pos,rrn[10],flag ,count,add[10];
FILE *fp;


void pack(sub s)
{
    strcpy(buf,s.id);
    strcat(buf,"|");
    strcat(buf,s.name);
    strcat(buf,"|");
    strcat(buf,s.trainer);
    strcat(buf,"|");
    strcat(buf,s.place);
    strcat(buf,"|");
    strcat(buf,s.amount);
    strcat(buf,"|");
    strcat(buf,s.membersince);
    strcat(buf,"|");
    strcat(buf,"#");
}


void write()
{
    int i;
    fp=fopen("gym.txt","a+");
    if(fp)
    {
        fwrite(buf,strlen(buf),1,fp);
    }
    fclose(fp);
    }

void addrecords()
{
    sub s;
    printf("enter the following fields:Id, Name, Trainer, Place, Amount, Membersince for New Member\n");
    scanf("%s%s%s%s%s%s",s.id,s.name,s.trainer,s.place,s.amount,s.membersince);
    pack(s);
    write();
}

sub unpack()
{

    sub y;
    char *ptr=buf;
    while(*ptr!='#')
    {
        if(*ptr=='|')
            *ptr='\0';
        ptr++;
    }
    ptr=buf;
    strcpy(y.id,ptr);
    ptr=ptr+strlen(ptr)+1;
    strcpy(y.name,ptr);
    ptr=ptr+strlen(ptr)+1;
    strcpy(y.trainer,ptr);
    ptr=ptr+strlen(ptr)+1;
    strcpy(y.place,ptr);
    ptr=ptr+strlen(ptr)+1;
    strcpy(y.amount,ptr);
    ptr=ptr+strlen(ptr)+1;
    strcpy(y.membersince,ptr);
    ptr=ptr+strlen(ptr);
    return y;
  }

void searchrecord()
{
  sub x;
  char u[12];
  printf("enter id to be searches:\n");
  scanf("%s",u);
  FILE *fp;
  fp=fopen("gym.txt","r");
  flag=0;
  while(!feof(fp) && !flag)
  {
      int i=0;
      while((buf[i]=fgetc(fp))!='#' && buf[i]!=EOF)
      {
          i++;
          continue;
      }
      x=unpack();
      if(strcmp(x.id,u)==0)
      {
          printf("record found\n");
          printf("****************************************************************************************************\n");
          printf("ID\t|\t NAME\t|\t TRAINER\t| PLACE\t\t| AMOUNT\t|\t MEMBERSINCE\n");
          printf("****************************************************************************************************\n");
          printf("%s\t|\t %s\t|\t %s\t\t| %s\t| %s\t\t| \t%s\t\t\n",x.id,x.name,x.trainer,x.place,x.amount,x.membersince);
          printf("----------------------------------------------------------------------------------------------------\n");
          flag=1;
      }
  }
  if(!flag)
  {
      printf("record not found\n");
  }
  fclose(fp);
}

void modify()
{
sub x;
int ch,len;
char u[12];
printf("enter a id to be searched \n");
scanf("%s",u);
FILE *fp;
flag=0;
fp=fopen("gym.txt","r+");
while(!feof(fp)&& !flag)
{
 int i=0;
while((buf[i]=fgetc(fp))!='#' && buf[i]!=EOF)
{
i++;
continue;
}
len=strlen(buf);
x=unpack();
if(strcmp(x.id,u)==0)
{
printf("Trainee found!!!!\n");
printf("**********************************************************\n");
printf("NAME\t|\t TRAINER\t| PLACE\n");
printf("**********************************************************\n");
printf("%s\t|\t %s\t|\t %s\t\t\n",x.name,x.trainer,x.place);
printf("----------------------------------------------------------\n");
pos=ftell(fp);
pos=pos-len;
fseek(fp,pos,SEEK_SET);
fwrite("*",1,1,fp);
fclose(fp);
printf("\nChoose a Content to Modify \n  1.NAME\n 2.TRAINER\n 3.PLACE\n \n");
scanf("%d",&ch);
switch(ch)
{
case 1:printf("Enter Name:");
scanf("%s",x.name);
break;
case 2:printf("Enter Trainer:");
scanf("%s",x.trainer);
break;
case 3:printf("Enter Place:");
scanf("%s",x.place);
break;

default:printf("Can't Modify \n");
break;
}
flag=1;
pack(x);
write();
}
}
if(!flag)
{
printf("Record details are not available\n");
}
}

void sort()
{
 int i,j,addlist ;
 char temp[20];
 for(i=0;i<=count;i++)
 {
  for(j=i+1;j<=count;j++)
  {
  if(strcmp(u[i],u[j])>0)
   {
   strcpy(temp,u[i]);
   strcpy(u[i],u[j]);
   strcpy(u[j],temp);
   addlist=add[i];
   add[i]=add[j];
   add[j]=addlist;
   }
  }
 }
}

void createindex()
{
 int pos;
 count=-1;
 FILE *fp;
 fp=fopen("gym.txt","r");
 while(fp)
 {
  pos=ftell(fp);
  int i=0;
  while((buf[i]=fgetc(fp))!='#' && buf[i]!=EOF)
    {
     i++;
     continue;
    }
    if(*buf=='@')
      continue;
    if(feof(fp))
      break;
    char *ptr=buf;
    while(*ptr!='|')
      ptr++;
    *ptr='\0';
    strcpy(u[++count],buf);
    add[count]=pos;
   }
   fclose(fp);
   sort();
}

int searchid(char key[12])
{
 int low =0,high=count,mid,pos,flag=0;
 while(low<=high)
 {
  mid=(low+high)/2;
  if(strcmp(u[mid],key)==0)
  {
   flag=1;
   break;
  }
  if(strcmp(u[mid],key)>0)
  high=mid-1;
  else low=mid+1;
 }
 if(flag)
 return mid;
 else
 return -1;
}

void eliminate()
{
 char key[12];
 int pos;
 FILE *fp;
 printf(" enter the id to be searched\n");
 scanf("%s",key);
 pos=searchid(key);
 if(pos>=0)
 {
  fp=fopen("gym.txt","r+");
  int add1=add[pos];
  fseek(fp,add1,SEEK_SET);
  fwrite("*",1,1,fp);
  printf("Record Removed Successfully!!!\n");
  fclose(fp);
  count--;
 }
 else
   {
    printf("Record Not Found!!!\n");
   }
 }

void display()
{
    char buf[50],temp;
    printf("****************************************************************************************************\n");
    printf("ID\t|\t NAME\t|\t TRAINER\t| PLACE\t\t| AMOUNT\t|\t MEMBERSINCE\n");
    printf("****************************************************************************************************\n");
    fp=fopen("gym.txt","r");
    if(fp==NULL)
    {
        printf("Error in File\n");
    }
    else
    {
        do
        {

            temp = fgetc(fp);
            if(temp == '*')
            {
                while(temp != '#')
                    {
                    temp = fgetc(fp);
                }
            }
            else
            {
                if(temp == '|')
                    {
                    printf("\t\t");
                }
                else if(temp == '#')
                    {
                    printf("\n");
                }
                else
                    {
                    printf("%c", temp);
             }
            }

        }while(!feof(fp));


printf("---------------------------------------------------------------------------------------------------\n");
       fclose(fp);
    }
    getch();
}

void discount()
{
 char n[]="Rainy";
 char o[]="Summer";
 char m[]="Christmas";
 char c[]="no discount";

 char answer[50];
 float price;
 float discount_percentage;
 float discount_amount;
 float discounted_price;

 sub x;
 int ch,len;
 char u[12];
 printf("enter a id for discount \n");
 scanf("%s",u);

 FILE *fp;
 flag=0;

 fp=fopen("gym.txt","r+");
 while(!feof(fp)&& !flag)
 {
  int i=0;
  while((buf[i]=fgetc(fp))!='#' && buf[i]!=EOF)
  {
   i++;
   continue;
  }
  len=strlen(buf);
  x=unpack();

  if(strcmp(x.id,u)==0)
  {
   printf("Trainee found!!!!\n\n");
   printf("***********\n");
   printf("Amount\n");
   printf("***********\n");
   printf("%s",x.amount);
   printf("\n-----------\n\n");

  printf("Select a Season for Discount - Summer | Rainy | Christmas | No discount\n\n");
  printf("enter the choice for discount\n");
  scanf("%s",answer);
  if(strcmp(answer,m)==0)
  {
  printf("enter price: ");
  scanf("%f",&price);
  discount_amount=(20 * price)/100;
  discounted_price = price - discount_amount;
  printf("discount amount=%f\n",discount_amount);
  printf("discount price=%f\n",discounted_price);

  }
  else if(strcmp(answer,n)==0)
  {
   printf("enter price: ");
   scanf("%f",&price);
   discount_amount=(30 * price)/100;
   discounted_price = price - discount_amount;
   printf("discount amount=%f\n",discount_amount);
   printf("discount price=%f\n",discounted_price);

  }
  else if(strcmp(answer,o)==0)
  {
   printf("enter price: ");
   scanf("%f",&price);
   discount_amount=(10 * price)/100;
   discounted_price = price - discount_amount;
   printf("discount amount=%f\n",discount_amount);
   printf("discount price=%f\n",discounted_price);

  }

 else if(strcmp(answer,c)==0)
 {
  printf("enter price of item:");
  scanf("%f",&price);

  printf("enter discount percentage\n");
  scanf("%f", &discount_percentage);

  discount_amount = (discount_percentage * price)/100;

  discounted_price = price - discount_amount;


  printf("Discount Amount: %f \n\n ", discount_amount);
  printf("Discounted_price: %f \n\n", discounted_price);
    break;
    fclose(fp);
    printf("Confirm Amount amount");
    scanf("%s",x.amount);
 }
}
    char dp[10];
    snprintf(dp, sizeof(dp), "%f", discounted_price);

    strcpy(x.amount, dp);

    pos=ftell(fp);
    pos=pos-len;
    fseek(fp,pos,SEEK_SET);
    fwrite("*",1,1,fp);
    fclose(fp);
    flag=1;
    pack(x);
    write();
}
if(!flag)
{
printf("Record details are not available\n");
}
}

void main()
{
 int choice;
 char username[15];
 char password[12];


 printf("Enter your Username:\n");
 scanf("%s",username);

 printf("Enter your Password:\n");
 scanf("%s",password);

 if(strcmp(username,"lehan")==0)
    {
    if(strcmp(password,"max")==0)
    {

      printf("\nWelcome Login Success!");
      printf("\n\t\t****************************************************************");
      printf("\n\t\t\t------WELCOME TO GYM MANAGEMENT SYSTEM------");
      printf("\n\t\t****************************************************************");

	  while (1)
      {

		printf("\n Enter\n 1: For adding new records.\n 2: For searching in existing records records ");
		printf("\n 3: For modifying existing record\n 4: For deleting existing record\n 5: For displaying the records\n 6. Discount\n");
		printf(" 7: For exit\n");
		printf("Enter the Choice\n");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:addrecords();
                   break;
            case 2:searchrecord();
                   break;
            case 3:modify();
                   break;
			case 4:createindex();
                   eliminate();
				   break;
            case 5:display();
                   break;
            case 6:discount();

                   break;
            case 7:exit(0);
            default:printf("Invalid Choice!!!!!\n");
		   }
         }
        }
        else
            {
    printf("\nwrong password!! \n \nPlease, Try Again\n");
   }
  }
  else
     {
      printf("\nUser doesn't exist");
     }
   }
