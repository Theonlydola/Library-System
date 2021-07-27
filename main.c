#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
typedef struct
{
    int building;
    char street[25];
    char city[25];

} address;
typedef struct
{
    char firstname[50];
    char lastname[50];
    int ID;
    char phone[25];
    char mail[25];
    address uaddress;
    int age;
} user;
typedef struct
{
    int day;
    int month;
    int year;
} date;

typedef struct
{
    char name[100];
    char author[100];
    char publisher[100];
    char category[100];
    char isbn[50];
    int ncopies;
    int ncopiesa;
    date published;
} book;

typedef struct
{
    char isbn[50];
    int id;
    date borrowed;
    date due;
    date returned;
} borrow;

user userarray[100];
int ucount=0;

void addnew() //Add New User
{
    int x,valid;
    char integer[25],r[2];
    x= ucount;
    printf("New User:\n");
    getchar();
    do
    {
        printf("First Name: ");
        gets(userarray[x].firstname);
        valid=atoi(userarray[x].firstname);
        if (valid!=0) printf("Please Enter correct Name!\n");
    }
    while (valid!=0);//Validating its a string
    do
    {
        printf("Last Name: ");
        gets(userarray[x].lastname);
        valid=atoi(userarray[x].lastname);
        if (valid!=0) printf("Please Enter correct Name!\n");
    }
    while (valid!=0);
    do
    {
        printf("Age: ");
        gets(integer);
        valid=atoi(integer);
        if (valid<=0) printf("Please Enter correct Age!\n");
    }
    while (valid<=0); //validate its an integer
    userarray[x].age=valid;
    printf("Address:\n");
    do
    {
        printf("\tBuilding number: ");
        gets(integer);
        valid=atoi(integer);
        if (valid<=0) printf("Please Enter correct number!\n");
    }
    while (valid<=0); //validate its an integer
    userarray[x].uaddress.building=valid;
    do
    {
        printf("\tStreet Name: ");
        gets(userarray[x].uaddress.street);
        valid=atoi(userarray[x].uaddress.street);
        if (valid!=0) printf("Please Enter correct street!\n");
    }
    while (valid!=0);
    do
    {
        printf("\tCity: ");
        gets(userarray[x].uaddress.city);
        valid=atoi(userarray[x].uaddress.city);
        if (valid!=0) printf("Please Enter correct City!\n");
    }
    while (valid!=0);
    do
    {
        printf("Phone Number: ");
        gets(userarray[x].phone);
        valid=atoi(userarray[x].phone);
        if (valid==0) printf("Please Enter correct Number!\n");
    }
    while (valid==0);
    do
    {
        printf("E-mail address: ");
        gets(userarray[x].mail);
        valid=atoi(userarray[x].mail);
        if (!strstr(userarray[x].mail,"@")||!strstr(userarray[x].mail,".")) valid=1;
        if (valid!=0) printf("Please Enter E-mail with correct format (example@domain.ext)\n");
    }
    while (valid!=0);
    userarray[x].ID=userarray[x-1].ID+1;
    printf("User Added successfully!\n");
    printf("User ID: %d\n",userarray[x].ID);
    ucount++;
    printf("Press 9 to go back to Main Menu\n");
    gets(r);
    if (!strcmp(r,"9"))
    {
        system("cls");
        return;
    }
}

void deleteuser2() //Delete User
{
    system("cls");
    int i,del;
    char r[2];
    char save[2];
    do
    {
        printf("Enter User ID: ");
        del=searchID();
        if (del==-1) printf("Member NOT Found\n");
    }
    while (del==-1);

    int v;
    v=checkborrowed(del);
    if(v>0)
    {
        printf("This user can't be deleted!\nhasn't returned all the books he has borrowed yet\n");
        printf("\nPress 9 to go back to Main Menu\n");
        gets(r);
        if (!strcmp(r,"9"))
        {
            system("cls");
            return;
        }
    }
    printf("Are You Sure?\n1) Delete\t2) Discard\n");
    gets(save);
    int z;
    z=ucount-1;
    if (!strcmp(save,"1"))
    {
        for(i=del; i<z; i++)
        {
            userarray[i]=userarray[i+1];
        }
        ucount--;
        printf("\nBook Deleted Successfully!\nPress 9 to go back\n");
        gets(r);
        if (!strcmp(r,"9"))
        {
            system("cls");
            return;
        }
        else return;
    }
    else if (!strcmp(save,"2"))
    {
        del=-1;
        printf("\nPress 9 to go back to Main Menu\n");
        gets(r);
        if (!strcmp(r,"9"))
        {
            system("cls");
            return;
        }
    }
    else return;
}

int searchID()//Search ID Returns index
{
    int i=0;
    char x[2];
    int T=-1,valid=-1;
    do
    {
        gets(x);
        valid=atoi(x);
    }
    while (valid==0);

    for (i=0; i<ucount; i++)
    {
        if(userarray[i].ID==valid)
        {
            T=i;
            break;
        }
    }

    return T;
}


void usermenu() //MENU
{
    system("cls");
    char ds[2];
    printf("USER MANAGEMENT \n1) Register \n2) Delete User\n9) Go back\n");
    scanf("%s",ds);
    if (!strcmp(ds,"1"))
    {
        system("cls");
        addnew();
    }
    else if (!strcmp(ds,"2"))
    {
        system("cls");
        deleteuser2();
    }
    else return;
}

book booksarray[100];
borrow borrowedarray[100];
int count=0,bcount=0;

date scandate() //Validate The date
{
    int v=0;
    date issued;
    char vday[10],vmon[10],vyear[10];
    scanf("%[^/]%*c%[^/]%*c%s",vday,vmon,vyear);
    issued.day=atoi(vday);
    issued.month=atoi(vmon);
    issued.year=atoi(vyear);
    if (issued.day>31||issued.day<1||issued.month>12||issued.month<1||issued.year>9999||issued.year<1000)
    {
        v=1;
        while (v==1)
        {
            v=0;
            printf("Please Enter correct date format as in dd/mm/yy: ");
            scandate();
        }
    }
    return issued;
}


book addnewbook() //Adds New book
{
    int i,dup=0,valid;
    book a;
    char integer[5];
    printf("New Book\n");
    do                                                      //do while to validate atoi 0 when string 1 when number
    {
        printf("Book Title: ");
        gets(a.name);
        valid=atoi(a.name);
        if (valid!=0) printf("Please Enter correct Title!\n");
    }
    while (valid!=0);
    do
    {
        dup=0;
        printf("\nISBN: ");
        gets(a.isbn);
        //fgets(a.isbn,sizeof(a.isbn),stdin);
        //a.isbn[strlen(a.isbn)-1]='\0';
        for (i=0; i<count; i++)
        {
            if (!strcmp(a.isbn,booksarray[i].isbn))
            {
                dup=1;
                printf("\nThis ISBN ALREADY EXISTS!\nPLEASE ENTER A UNIQUE ISBN: ");
                break;
            }
        }

    }
    while (dup==1);

    do
    {
        printf("\nAuthor: ");
        gets(a.author);
        valid=atoi(a.author);
        if (valid!=0) printf("Please Enter correct Name!\n");
    }
    while (valid!=0);

    do
    {
        printf("\nPublisher: ");
        gets(a.publisher);
        valid=atoi(a.publisher);
        if (valid!=0) printf("Please Enter correct Name!\n");
    }
    while (valid!=0);


    do
    {
        printf("\nCategory: ");
        gets(a.category);
        valid=atoi(a.category);
        if (valid!=0) printf("Please Enter correct Name!\n");
    }
    while (valid!=0);

    do
    {
        printf("\nNumber of copies: ");
        gets(integer);
        valid=atoi(integer);
        if (valid<=0) printf("Please Enter correct Number!\n");
    }
    while (valid<=0); //validate its an integer
    a.ncopies=valid;

    do
    {
        printf("\nNumber of Available copies: ");
        gets(integer);
        valid=atoi(integer);
        if (valid<=0) printf("Please Enter correct Number!\n");
    }
    while (valid<=0); //validate its an integer
    a.ncopiesa=valid;
    printf("\nDate issued:");
    a.published = scandate();
    return a;
}

int searchisbn(char * a) //searches for book isbn and return its index and prints book data
{
    int f=0,i;
    for (i=0; i<count; i++)
    {
        if (!strcmp(a,booksarray[i].isbn))
        {
            system("cls");
            printf("Book title: %s\nAuthor: %s\nPublisher: %s\nCategory: %s\nNumber of copies: %d\nNumber of copies available: %d\nDate issued: %d/%d/%d\n",booksarray[i].name,booksarray[i].author,booksarray[i].publisher,booksarray[i].category,booksarray[i].ncopies,booksarray[i].ncopiesa,booksarray[i].published.day,booksarray[i].published.month,booksarray[i].published.year);
            f=1;
            return i;
        }
    }
    if (f!=1) return -1;
}

int isbnindex(char * a) //searches for book isbn and return its index only
{
    int f=0,i;
    for (i=0; i<count; i++)
    {
        if (!strcmp(a,booksarray[i].isbn))
        {
            f=1;
            return i;
        }
    }
    if (f!=1) return -1;
}

void editbook(int g) //Edits All book Entries
{

    char newname[100],isb[50];
    int newint;
    int save,i,dup=0;
    char td[2],r[2];
    printf("\n\nChoose which Entry you want to edit:\n1)Book Title\n2)Author\n3)Publisher\n4)Category\n5)ISBN\n6)Number of copies\n7)Number of Available copies\n8)Date\n9)Go Back to main menu\n");
    gets(td);
    if (!strcmp(td,"1"))
    {
        system("cls");
        printf("Edit book name: %s\n",booksarray[g].name);
        printf("Enter New Name: ");
        gets(booksarray[g].name);
        printf("%s",booksarray[g].name);
        printf("Done! press 9 to Go back");
        getchar();
        gets(r);
        if (!strcmp(r,"9"))
            editbook(g);
    }
    else if (!strcmp(td,"2"))
    {
        system("cls");
        printf("Edit Author: %s\n",booksarray[g].author);
        printf("Enter New Author: ");
        gets(newname);
        strcpy(booksarray[g].author,newname);
        printf("\nDone! press 9 to Go back");
        getchar();
        gets(r);
        if (!strcmp(r,"9"))
            editbook(g);
    }
    else if (!strcmp(td,"3"))
    {
        system("cls");
        printf("Edit publisher: %s\n",booksarray[g].author);
        printf("Enter New publisher: ");
        gets(newname);
        strcpy(booksarray[g].publisher,newname);
        printf("\nDone! press 9 to Go back");
        getchar();
        gets(r);
        if (!strcmp(r,"9"))
            editbook(g);
    }
    else if (!strcmp(td,"4"))
    {
        system("cls");
        printf("Edit Category: %s",booksarray[g].author);
        printf("Enter New Category: ");
        gets(newname);
        strcpy(booksarray[g].category,newname);
        printf("\nDone! press 9 to Go back");
        getchar();
        gets(r);
        if (!strcmp(r,"9"))
            editbook(g);
    }
    else if (!strcmp(td,"5"))
    {
        system("cls");
        char isb[50];
        printf("Edit ISBN: %s",booksarray[g].isbn);
        do
        {
            dup=0;
            printf("\nISBN: ");
            gets(isb);
            for (i=0; i<count; i++)
            {
                if (strcmp(isb,booksarray[i].isbn)==0)
                {
                    dup=1;
                    printf("\nThis ISBN ALREADY EXISTS!\nPLEASE ENTER A UNIQUE ISBN: ");
                }
            }

        }
        while (dup==1);
        strcpy(booksarray[g].isbn,isb);
        printf("\nDone! press 9 to Go back");
        getchar();
        gets(r);
        if (!strcmp(r,"9"))
            editbook(g);
    }
    else if (!strcmp(td,"6"))
    {
        system("cls");
        printf("Edit Number of copies: %d",booksarray[g].ncopies);
        do
        {
            printf("Enter New Number of copies: ");
            scanf("%d",&newint);
        }
        while (newint<0);
        booksarray[g].ncopies=newint;
        printf("\nDone! press 9 to Go back");
        getchar();
        gets(r);
        if (!strcmp(r,"9"))
            editbook(g);
    }
    else  if (!strcmp(td,"7"))
    {
        system("cls");
        printf("Edit Number of available copies: %d",booksarray[g].ncopiesa);
        do
        {
            printf("Enter New Number of available copies: ");
            scanf("%d",&newint);
        }
        while (newint<0);
        booksarray[g].ncopiesa=newint;
        printf("\nDone!\n press 9 to Go back");
        getchar();
        gets(r);
        if (!strcmp(r,"9"))
            editbook(g);
    }
    else  if (!strcmp(td,"9"))
    {
        system("cls");
        bookmenu();
    }

}
void searchmenu() //MENU
{
    system("cls");
    char td[2],r[2];
    printf("Search for a book\nChoose Entry:\n1) Book title\n2) Author\n3) ISBN\n4) Category\n5) ALL\n9) Go back\n");
    gets(td);
    system("cls");
    if (!strcmp(td,"1"))
    {
        char searchtitle[100];
        char searchstr[100];
        printf("Search for book title: ");
        getchar();
        gets(searchtitle);
        int f=0,i;
        for (i=0; i<count; i++)
        {
            strcpy(searchstr,booksarray[i].name); //use temporary string
            strlwr(searchstr); //lower cases of the string to use strstr
            strlwr(searchtitle);
            if(strstr(searchstr, searchtitle) != NULL)
            {
                f=1;
                printf("\n%s\n\tAuthor: %s\n\tPublisher: %s\n\tCategory: %s\n\tISBN: %s\n\tNumber of copies: %d\n\tNumber of copies available: %d\n\tDate issued: %d/%d/%d\n",booksarray[i].name,booksarray[i].author,booksarray[i].publisher,booksarray[i].category,booksarray[i].isbn,booksarray[i].ncopies,booksarray[i].ncopiesa,booksarray[i].published.day,booksarray[i].published.month,booksarray[i].published.year);
            }
        }
        if (f!=1) printf("Book not found!\n");
        printf("\nPress 1 to search for another Book\nPress 9 to go back\n");
        gets(r);
        if (!strcmp(r,"9"))
        {
            system("cls");
            return;
        }

        if (!strcmp(r,"1"))
            searchmenu();
    }
    else if (!strcmp(td,"2"))
    {
        char searchauthor[100],searchstr[100];
        printf("Search for Author's books: ");
        getchar();
        gets(searchauthor);
        int f=0,i;
        for (i=0; i<count; i++)
        {
            strcpy(searchstr,booksarray[i].author); //use temporary string
            strlwr(searchstr); //lower cases of the string to use strstr
            strlwr(searchauthor);
            if(strstr(searchstr,searchauthor) != NULL)
            {
                f=1;
                printf("\n%s\n\tAuthor: %s\n\tPublisher: %s\n\tCategory: %s\n\tISBN: %s\n\tNumber of copies: %d\n\tNumber of copies available: %d\n\tDate issued: %d/%d/%d\n",booksarray[i].name,booksarray[i].author,booksarray[i].publisher,booksarray[i].category,booksarray[i].isbn,booksarray[i].ncopies,booksarray[i].ncopiesa,booksarray[i].published.day,booksarray[i].published.month,booksarray[i].published.year);
            }
        }
        if (f!=1) printf("Author not found!\n");
        printf("\nPress 1 to search for another Book\nPress 9 to go back to Main Menu\n");
        gets(r);
        if (!strcmp(r,"9"))
        {
            system("cls");
            return;
        }

        else if (!strcmp(r,"1"))
        {
            system("cls");
            searchmenu();
        }
    }
    else if (!strcmp(td,"3"))
    {
        int f=0,i;
        char searchisbn[50];
        printf("Search for ISBN: ");
        getchar();
        gets(searchisbn);
        for (i=0; i<count; i++)
        {
            if (strcmp(searchisbn,booksarray[i].isbn)==0)
            {
                printf("\nBook title: %s\nAuthor: %s\nPublisher: %s\nCategory: %s\nNumber of copies: %d\nNumber of copies available: %d\nDate issued: %d/%d/%d\n",booksarray[i].name,booksarray[i].author,booksarray[i].publisher,booksarray[i].category,booksarray[i].ncopies,booksarray[i].ncopiesa,booksarray[i].published.day,booksarray[i].published.month,booksarray[i].published.year);
                f=1;
            }
        }
        if (f!=1) printf("ISBN not found!");
        printf("\nPress 1 to search for another Book\nPress 9 to go back to Main Menu\n");
        gets(r);
        if (!strcmp(r,"9"))
        {
            system("cls");
            return;
        }

        if (!strcmp(r,"1"))
        {
            system("cls");
            searchmenu();
        }
    }
    else if (!strcmp(td,"4"))
    {
        char searchcategory[100],searchstr[100];
        printf("Search for Book Category: ");
        getchar();
        gets(searchcategory);
        int f=0,i;
        for (i=0; i<count; i++)
        {
            strcpy(searchstr,booksarray[i].category); //use temporary string
            strlwr(searchstr); //lower cases of the string to use strstr
            strlwr(searchcategory);
            if(strstr(searchstr,searchcategory) != NULL)
            {
                f=1;
                printf("Category: %s\nTitle: %s\n\tAuthor: %s\n\tPublisher: %s\n\tISBN: %s\n\tNumber of copies: %d\n\tNumber of copies available: %d\n\tDate issued: %d/%d/%d\n",booksarray[i].category,booksarray[i].name,booksarray[i].author,booksarray[i].publisher,booksarray[i].isbn,booksarray[i].ncopies,booksarray[i].ncopiesa,booksarray[i].published.day,booksarray[i].published.month,booksarray[i].published.year);
            }
        }
        if (f!=1) printf("Category not found!");
        printf("\nPress 1 to search for another Book\nPress 9 to go back to Main Menu\n");
        gets(r);
        if (!strcmp(r,"9"))
        {
            system("cls");
            return;
        }

        if (!strcmp(r,"1"))
        {
            system("cls");
            searchmenu();
        }

    }
    else if (!strcmp(td,"5"))
    {
        char search[100],searchstr[100];
        printf("Search ALL:\n");
        getchar();
        gets(search);
        int f=0,i;
        for (i=0; i<count; i++) //Category
        {
            strcpy(searchstr,booksarray[i].category); //use temporary string
            strlwr(searchstr); //lower cases of the string to use strstr
            strlwr(search);
            if(strstr(searchstr,search) != NULL)
            {
                f=1;
                printf("Category: %s\nTitle: %s\n\tAuthor: %s\n\tPublisher: %s\n\tISBN: %s\n\tNumber of copies: %d\n\tNumber of copies available: %d\n\tDate issued: %d/%d/%d\n",booksarray[i].category,booksarray[i].name,booksarray[i].author,booksarray[i].publisher,booksarray[i].isbn,booksarray[i].ncopies,booksarray[i].ncopiesa,booksarray[i].published.day,booksarray[i].published.month,booksarray[i].published.year);
            }
        }
        for (i=0; i<count; i++) //ISBN
        {
            if (strcmp(search,booksarray[i].isbn)==0)
            {
                printf("\nBook title: %s\nAuthor: %s\nPublisher: %s\nCategory: %s\nNumber of copies: %d\nNumber of copies available: %d\nDate issued: %d/%d/%d\n",booksarray[i].name,booksarray[i].author,booksarray[i].publisher,booksarray[i].category,booksarray[i].ncopies,booksarray[i].ncopiesa,booksarray[i].published.day,booksarray[i].published.month,booksarray[i].published.year);
                f=1;
            }
        }
        for (i=0; i<count; i++) //AUTHOR
        {
            strcpy(searchstr,booksarray[i].author); //use temporary string
            strlwr(searchstr); //lower cases of the string to use strstr
            strlwr(search);
            if(strstr(searchstr,search) != NULL)
            {
                f=1;
                printf("\nAuthor: %s\n\tName: %s\n\tPublisher: %s\n\tCategory: %s\n\tISBN: %s\n\tNumber of copies: %d\n\tNumber of copies available: %d\n\tDate issued: %d/%d/%d\n",booksarray[i].author,booksarray[i].name,booksarray[i].publisher,booksarray[i].category,booksarray[i].isbn,booksarray[i].ncopies,booksarray[i].ncopiesa,booksarray[i].published.day,booksarray[i].published.month,booksarray[i].published.year);
            }
        }
        for (i=0; i<count; i++) //Book Title
        {
            strcpy(searchstr,booksarray[i].name); //use temporary string
            strlwr(searchstr); //lower cases of the string to use strstr
            strlwr(search);
            if(strstr(searchstr,search) != NULL)
            {
                f=1;
                printf("\nName: %s\n\tAuthor: %s\n\tPublisher: %s\n\tCategory: %s\n\tISBN: %s\n\tNumber of copies: %d\n\tNumber of copies available: %d\n\tDate issued: %d/%d/%d\n",booksarray[i].name,booksarray[i].author,booksarray[i].publisher,booksarray[i].category,booksarray[i].isbn,booksarray[i].ncopies,booksarray[i].ncopiesa,booksarray[i].published.day,booksarray[i].published.month,booksarray[i].published.year);
            }
        }
        if (f!=1) printf("NO matches!");
        printf("\nPress 1 to search for another Book\nPress 9 to go back to Main Menu\n");
        getchar();
        gets(r);
        if (!strcmp(r,"9"))
        {
            system("cls");
            return;
        }

        if (!strcmp(r,"1"))
        {
            system("cls");
            searchmenu();
        }

    }
    else if (!strcmp(td,"9")) return;
}

void deletebook()
{
    system("cls");
    int i,del;
    char r[2],save[2];
    char searchisb[50];
    printf("Delete A book\n");
    do
    {
        printf("Enter ISBN: ");
        gets(searchisb);
        del=searchisbn(searchisb);
        if (del==-1)
        {
            printf("ISBN NOT FOUND!\n");
        }
    }
    while (del==-1);

    printf("Are You Sure?\n1) Delete\t2) Discard\n");
    gets(save);
    if (!strcmp(save,"1"))
    {
        for(i=del; i<count-1; i++)
        {
            booksarray[i]=booksarray[i+1];
        }
        count--;
        printf("\nBook Deleted Successfully!\nPress 9 to go back\n");
        getchar();
        gets(r);
        if (!strcmp(r,"9"))
        {
            system("cls");
            bookmenu();
        }
        else return;
    }
    else if (!strcmp(save,"2"))
    {
        del=-1;
        printf("\nPress 9 to go back to Main Menu\n");
        getchar();
        gets(r);
        if (!strcmp(r,"9"))
        {
            system("cls");
            bookmenu();
        }
    }
    else return;
}

void addnewcopy()
{
    system("cls");
    int g,valid;
    char newcopies[2],save[2];
    printf("Add new copy\n");
    do
    {
        g=0;
        printf("Enter ISBN: ");
        char isb[50];
        gets(isb);
        g=searchisbn(isb);
        if (g==-1) printf("\nISBN NOT FOUND!\n");
    }
    while (g==-1);

    do
    {
        do
        {
            printf("Add new number of copies:  ");
            scanf("%s",newcopies);
            valid=atoi(newcopies);
        }
        while (valid==0);
    }
    while (valid<0);
    booksarray[g].ncopies+=valid;
    booksarray[g].ncopiesa+=valid;
    char r[2];
    printf("\nBook Added Successfully!\nPress 9 to go back\n");
    getchar();
    gets(r);
    if (!strcmp(r,"9"))
    {
        system("cls");
        bookmenu();
    }
}


void bookmenu() //MENU
{
    system("cls");
    int x;
    char sd[2],r[2];
    printf("1) Insert New Book\n2) Search\n3) Add New copies\n4) Delete\n5) Edit\n9) Go back to Main Menu\n");
    getchar();
    gets(sd);
    if (!strcmp(sd,"1"))
    {
        system("cls");
        x=count++;
        booksarray[x]=addnewbook();
        printf("\nBook Added Successfully!\nPress 9 to go back to Main Menu\n");
        getchar();
        gets(sd);
        if (!strcmp(sd,"9"))
        {
            system("cls");
            bookmenu();
        }
    }
    else if (!strcmp(sd,"2"))
    {
        searchmenu();
    }

    else if (!strcmp(sd,"3"))
    {
        addnewcopy();
    }
    else if (!strcmp(sd,"4"))
    {
        deletebook();
    }

    else if (!strcmp(sd,"5"))
    {
        system("cls");
        int g;
        int newint;
        char isb[50];
        printf("Edit A book\n");
        do
        {
            printf("Enter ISBN: ");
            gets(isb);
            g=searchisbn(isb);
            if (g==-1) printf("ISBN NOT FOUND!\n");
        }
        while (g==-1);
        editbook(g);

    }
    else if (!strcmp(sd,"9"))
    {
        system("cls");
        return;
    }
}

int checkborrowed(int u) //check if this user has borrowed a book and hasn't retruned it yet
{
    int t=0,j;
    for (j=0; j<bcount; j++)
    {
        if (userarray[u].ID==borrowedarray[j].id&&borrowedarray[j].returned.day==0)
        {
            t++;
        }
    }
    return t;
}

void borrowbook()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int u,g,i;
    char isb[50],r[2];
    system("cls");
    printf("Borrow a book:\n");
    do
    {
        printf("Enter Book ISBN: ");
        gets(isb);
        g=searchisbn(isb);
        if (g==-1)
        {
            printf("ISBN NOT Found\n1) Retry\n9) go back\n");
            gets(r);
            if (!strcmp(r,"1"))
            {
                continue;
            }
            else return;
        }
    }
    while (g==-1);
    do
    {
        printf("Enter User ID: ");
        u=searchID();
        if (u==-1) printf("Member NOT Found\n");
    }
    while (u==-1);

    if (checkborrowed(u)==3) //check if the user limit allows him
    {
        printf("This User has already reached his borrowing limit!\nPress 9 to go back\n");
        gets(r);
        return;
    }
    for(i=0; i<bcount; i++) //check if he has the book already
    {

        if (userarray[u].ID==borrowedarray[i].id&&!strcmp(booksarray[g].isbn,borrowedarray[i].isbn)&&borrowedarray[i].returned.day==0)
        {
            printf("This User is already borrowing that book\nPress 9 to go back\n");
            gets(r);
                return;
        }
    }
    if (booksarray[g].ncopiesa==0) //check if the book is available
    {
        printf("This book is not currently available\nPress 9 to go back\n");
        gets(r);
        return;
    }
    strcpy(borrowedarray[bcount].isbn,booksarray[g].isbn);
    borrowedarray[bcount].id=userarray[u].ID;
    borrowedarray[bcount].borrowed.day=tm.tm_mday;
    borrowedarray[bcount].borrowed.month=tm.tm_mon + 1;
    borrowedarray[bcount].borrowed.year=tm.tm_year + 1900;
    int flag=0;
    do
    {
        flag=0;
        printf("Enter Date Due Returning: ");
        borrowedarray[bcount].due=scandate();
        if (borrowedarray[bcount].due.day<=borrowedarray[bcount].borrowed.day||borrowedarray[bcount].due.month<borrowedarray[bcount].borrowed.month||borrowedarray[bcount].due.year<borrowedarray[bcount].borrowed.year)
            flag = 1;
        if (flag==1)
        {
            printf("\nWrong Date\n");
        }
    }
    while(borrowedarray[bcount].due.day<=borrowedarray[bcount].borrowed.day||borrowedarray[bcount].due.month<borrowedarray[bcount].borrowed.month||borrowedarray[bcount].due.year<borrowedarray[bcount].borrowed.year);
    bcount++;

    booksarray[g].ncopiesa--;
    printf("Book borrowed successfully!\nPress 9 to go back");
    getchar();
    gets(r);
    if (!strcmp(r,"9")) return;
}
void retrunbook()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int num=0,u,i;
    char r[2];
    printf("Return Book:\n");
    do
    {
        printf("Enter User ID: ");
        u=searchID();
        if (u==-1) printf("Member NOT Found\n");
    }
    while (u==-1);
    printf("\n");
    for (i=0; i<bcount; i++) //check if this user has books under his name
    {
        if (userarray[u].ID==borrowedarray[i].id&&borrowedarray[i].returned.day==0)
        {
            printf("%d:\n",num+1);
            num++;
            printf("%s\n",borrowedarray[i].isbn);
        }
    }
    if (num!=0)
    {
        char is[50];
        int flag=0,g,found=0;
        do
        {
            printf("Enter book isbn to return\n");
            gets(is);
            g=isbnindex(is);
            if (g==-1) printf("ISBN NOT FOUND!\n");
        }
        while(g==-1);

        for (i=0; i<bcount; i++)
        {
            if ((strcmp(is,borrowedarray[i].isbn)==0)&&(userarray[u].ID==borrowedarray[i].id)&&(borrowedarray[i].returned.day==0))
            {
             do
                {
                    found=1;
                    flag=0;
                    printf("Enter Date Returned: ");
                    borrowedarray[i].returned=scandate();
                    if (borrowedarray[i].returned.year<borrowedarray[i].borrowed.year||borrowedarray[i].returned.year>tm.tm_year+1900)
                    {
                        flag=1;
                    }
                    else if (borrowedarray[i].returned.month<borrowedarray[i].borrowed.month||borrowedarray[i].returned.month>tm.tm_mon+1)
                    {
                        flag=1;
                    }
                    else if (borrowedarray[i].returned.day<borrowedarray[i].borrowed.day||borrowedarray[i].returned.day>tm.tm_mday)
                    {
                        flag=1;
                    }

                    if (flag==1)
                    {
                        printf("\nWrong Date\n");
                    }
                }
                while(flag==1);
                break;
            }
           else continue;
        }
        if (found==0){
                printf("This book is not borrowed by this user\npress 9 go back\n");
                getchar();
                gets(r);
                if (!strcmp(r,"9")) return;
        }
        else {
                booksarray[g].ncopiesa++;
                printf("Book Returned successfully\npress 9 to go back\n");
                getchar();
                gets(r);
                if (!strcmp(r,"9")) return;
        }
    }
    else if (num==0)
    {
        printf("This User has no current borrowed books\npress 9 to go back");
        getchar();
        gets(r);
        if (!strcmp(r,"9")) borrowmenu();
    }

}
void borrowmenu()//MENU
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t); //struct storing current time
    char sd[2];
    system("cls");
    printf("Borrow Management:\n1) Borrow a book\n2) Return a book\n3) Search for a book\n9) Go back\n");
    //do {
    getchar();
    gets(sd);
    //}while(sd!=1||sd!=2||sd!=9);

    if (!strcmp(sd,"1"))
    {
        system("cls");
        borrowbook();
    }
    else if (!strcmp(sd,"2"))
    {
        system("cls");
        retrunbook();

    }
    else if (!strcmp(sd,"3"))
    {
        searchmenu();
    }
    else if (!strcmp(sd,"9")) return;
}
void overdue()
{
    system("cls");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("Overdue Books:\n");
    int g,i;
    char r[2];
    for (i=0; i<bcount; i++)
    {

        if (borrowedarray[i].due.year<tm.tm_year+1900&&borrowedarray[i].returned.year==0)
        {
            g=isbnindex(borrowedarray[i].isbn);
            printf("Book ISBN: %s\n\tBook Name: %s\n\tID: %d\n\tDate Due Returning: %d/%d/%d\n",borrowedarray[i].isbn,booksarray[g].name,borrowedarray[i].id,borrowedarray[i].due.day,borrowedarray[i].due.month,borrowedarray[i].due.year);
        }
        else if (borrowedarray[i].due.month<tm.tm_mon+1&&borrowedarray[i].returned.year==0)
        {
            g=isbnindex(borrowedarray[i].isbn);
            printf("Book ISBN: %s\n\tBook Name: %s\n\tID: %d\n\tDate Due Returning: %d/%d/%d\n",borrowedarray[i].isbn,booksarray[g].name,borrowedarray[i].id,borrowedarray[i].due.day,borrowedarray[i].due.month,borrowedarray[i].due.year);
        }
        else if (borrowedarray[i].due.day<tm.tm_mday&&borrowedarray[i].returned.year==0)
        {
            g=isbnindex(borrowedarray[i].isbn);
            printf("Book ISBN: %s\n\tBook Name: %s\n\tID: %d\n\tDate Due Returning: %d/%d/%d\n",borrowedarray[i].isbn,booksarray[g].name,borrowedarray[i].id,borrowedarray[i].due.day,borrowedarray[i].due.month,borrowedarray[i].due.year);
        }
    }
    printf("Press 9 to go back\n");
    gets(r);
    if (!strcmp(r,"9")) return;
}
void popular()
{
    system("cls");
    int i,j,k=0,max=0,index=-1;
    int num[count];
    int pop[count];
    char r[2];
    for (i=0; i<count; i++)
    {
        num[i]=0;
        pop[i]=0;
    }
    printf("Popular Books:\n");
    for (i=0; i<count; i++)
    {
        for(j=0; j<bcount; j++)
        {
            if (!strcmp(booksarray[i].isbn,borrowedarray[j].isbn))
            {
                num[i]++;
            }
        }
    }

    for(i=0; i<count; i++)
    {
        max=0;
        for(j=0; j<count; j++)
        {
            if ((num[j]>=max))
            {

                index=j;
                max=num[j];
            }
        }

        if (k<5) printf("%s\n\tAuthor: %s\n\tisbn: %s\n",booksarray[index].name,booksarray[index].author,booksarray[index].isbn);
        k++;
        num[index]=-1;
    }
    printf("Press 9 to go back\n");
    getchar();
    gets(r);
    if (!strcmp(r,"9")) return;
}

void administrative() //administrative actions Overdue and popular
{
    system("cls");
    int i;
    char sd[2],r[2];
    printf("Administrative Actions:\n1)Overdue Books\n2)Popular books\n3)Show All Books\n4)Show All Users\n5)Show All Borrowed books\nPress 9 to go back\n");
    getchar();
    gets(sd);
    if (!strcmp(sd,"1"))
    {
        overdue();
    }
    else if (!strcmp(sd,"2"))
    {
        popular();
    }
    else if (!strcmp(sd,"3"))
    {
        system("cls");
        printf("ALL BOOKS:\n");
        for (i=0; i<count; i++)
        {
            printf("Book %d:\nName: %s\n\tAuthor: %s\n\tPublisher: %s\n\tCategory: %s\n\tISBN: %s\n\tNumber of copies: %d\n\tNumber of copies available: %d\n\tDate issued: %d/%d/%d\n",i+1,booksarray[i].name,booksarray[i].author,booksarray[i].publisher,booksarray[i].category,booksarray[i].isbn,booksarray[i].ncopies,booksarray[i].ncopiesa,booksarray[i].published.day,booksarray[i].published.month,booksarray[i].published.year);
        }
        printf("Press 9 to go back");
        gets(r);
        if (!strcmp(r,"9")) return;
    }
    else if (!strcmp(sd,"4"))
    {
        system("cls");
        printf("ALL USERS:\n");
        for (i=0; i<ucount; i++)
        {
            printf("User %d:\nName: %s, %s\nID: %d\nAddress: %d,%s,%s\nPhone Number: %s\nAge: %d\nE-mail: %s\n\n",i+1,userarray[i].lastname,userarray[i].firstname,userarray[i].ID,userarray[i].uaddress.building,userarray[i].uaddress.street,userarray[i].uaddress.city,userarray[i].phone,userarray[i].age,userarray[i].mail);
        }
        printf("Press 9 to go back");
        gets(r);
        if (!strcmp(r,"9")) return;
    }
    else if (!strcmp(sd,"5"))
    {
        system("cls");
        printf("ALL Borrowed Books:\n");
        for (i=0; i<ucount; i++)
        {
            if(borrowedarray[i].returned.day!=0)
                printf("Book %d:\nISBN: %s\nUSER ID: %d\nDate Borrowed: %d/%d/%d\nDate Due: %d/%d/%d\nDate Returned: %d/%d/%d\n\n",i+1,borrowedarray[i].isbn,borrowedarray[i].id,borrowedarray[i].borrowed.day,borrowedarray[i].borrowed.month,borrowedarray[i].borrowed.year,borrowedarray[i].due.day,borrowedarray[i].due.month,borrowedarray[i].due.year,borrowedarray[i].returned.day,borrowedarray[i].returned.month,borrowedarray[i].returned.year);
            else
                printf("Book %d:\nISBN: %s\nUSER ID: %d\nDate Borrowed: %d/%d/%d\nDate Due: %d/%d/%d\nDate Returned: NOT Returned yet\n\n",i+1,borrowedarray[i].isbn,borrowedarray[i].id,borrowedarray[i].borrowed.day,borrowedarray[i].borrowed.month,borrowedarray[i].borrowed.year,borrowedarray[i].due.day,borrowedarray[i].due.month,borrowedarray[i].due.year);
        }
        printf("Press 9 to go back\n");
        gets(r);
        if (!strcmp(r,"9")) return;
    }
    else return;

}
void savechanges(FILE *fu,FILE *books, FILE *borrowed)
{
    system("cls");
    int i;
    books = fopen("books.txt","w");
    for(i=0; i<count; i++)
    {
        fprintf(books,"%s,%s,%s,%s,%s,%d,%d,%d/%d/%d\n",booksarray[i].name,booksarray[i].author,booksarray[i].publisher,booksarray[i].category,booksarray[i].isbn,booksarray[i].ncopies,booksarray[i].ncopiesa,booksarray[i].published.day,booksarray[i].published.month,booksarray[i].published.year);
    }
    fclose(books);

    fu = fopen("userx.txt","w");
    for(i=0; i<ucount; i++)
    {
        fprintf(fu,"%s,%s,%d,%d,%s,%s,%s,%d,%s\n",userarray[i].lastname,userarray[i].firstname,userarray[i].ID,userarray[i].uaddress.building,userarray[i].uaddress.street,userarray[i].uaddress.city,userarray[i].phone,userarray[i].age,userarray[i].mail);
    }
    fclose(fu);

    borrowed=fopen("borrowed.txt","w");
    for (i=0; i<bcount; i++)
    {
        fprintf(borrowed,"%s,%d,%d/%d/%d,%d/%d/%d,%d/%d/%d\n",borrowedarray[i].isbn,borrowedarray[i].id,borrowedarray[i].borrowed.day,borrowedarray[i].borrowed.month,borrowedarray[i].borrowed.year,borrowedarray[i].due.day,borrowedarray[i].due.month,borrowedarray[i].due.year,borrowedarray[i].returned.day,borrowedarray[i].returned.month,borrowedarray[i].returned.year);
    }
    fclose(borrowed);
}
int main()
{
    FILE * fu;
    FILE * books;
    FILE * borrowed;
    books=fopen("books.txt","r");
    //user userarray[100];
    while (!feof(books))
    {
        fscanf(books,"%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%d,%d,%d/%d/%d\n",booksarray[count].name, booksarray[count].author, booksarray[count].publisher,booksarray[count].category,booksarray[count].isbn,&booksarray[count].ncopies,&booksarray[count].ncopiesa,&booksarray[count].published.day,&booksarray[count].published.month,&booksarray[count].published.year);
        count++;
    }

    //int ucount;
    fu=fopen("userx.txt","r");
    while(!feof(fu))        //reading the file
    {

        fscanf(fu,"%[^,]%*c%[^,]%*c%d,%d,%[^,]%*c%[^,]%*c%[^,]%*c%d,%s\n",userarray[ucount].lastname,userarray[ucount].firstname,&userarray[ucount].ID,&userarray[ucount].uaddress.building,userarray[ucount].uaddress.street,userarray[ucount].uaddress.city,userarray[ucount].phone,&userarray[ucount].age,userarray[ucount].mail);
        ucount++;
    }
    fclose(fu);

    borrowed=fopen("borrowed.txt","r");
    while(!feof(borrowed))
    {
        fscanf(borrowed,"%[^,]%*c%d,%d/%d/%d,%d/%d/%d,%d/%d/%d\n",borrowedarray[bcount].isbn,&borrowedarray[bcount].id,&borrowedarray[bcount].borrowed.day,&borrowedarray[bcount].borrowed.month,&borrowedarray[bcount].borrowed.year,&borrowedarray[bcount].due.day,&borrowedarray[bcount].due.month,&borrowedarray[bcount].due.year,&borrowedarray[bcount].returned.day,&borrowedarray[bcount].returned.month,&borrowedarray[bcount].returned.year);
        bcount++;
    }
    fclose(borrowed);
    int saved=1;
    char d[2];
    char sd[2];
    int mainmenu=9;
    while (mainmenu==9)
    {
        do
        {
            system("cls");
            printf("o Book Management (1)\n\t=>Insert, search, add new copies, delete, edit\no Member Management (2)\n\t=> Register, remove\no Borrow Management (3)\n\t=> Borrow, return\no Administrative actions (4)\n\t=> Overdue, popular\no Save changes (5)\no Exit (6)\n\t=> Save and exit, exit without saving\n");
            fgets(d,2,stdin);
        }
        while((strcmp(d,"1"))&&(strcmp(d,"2"))&&(strcmp(d,"3"))&&(strcmp(d,"4"))&&(strcmp(d,"5"))&&(strcmp(d,"6"))) ;

        if (!strcmp(d,"1"))
        {
            bookmenu();
            saved=0;
        }

        if(!strcmp(d,"2"))
        {
            usermenu();
            saved=0;
        }
        if (!strcmp(d,"3"))
        {
            borrowmenu();
            saved=0;
        }
        if (!strcmp(d,"4"))
        {
            administrative();
            saved=0;
        }
        if (!strcmp(d,"5"))
        {
            savechanges(fu,books,borrowed);
            saved=1;
            printf("Changes Saved\n");
            printf("press any key to go back\n");
            getchar();
            gets(sd);
        }
        if (!strcmp(d,"6"))
        {
            system("cls");
            if (saved==1) mainmenu=0;
            else
            {
                printf("If you don't save before exiting all your changes will be lost!\n1) save and exit\n2) exit without saving\n3) Cancel\n");
                getchar();
                gets(sd);
                if(!strcmp(sd,"1"))
                {
                    savechanges(fu,books,borrowed);
                    mainmenu=0;
                }
                else if (!strcmp(sd,"2")) mainmenu=0;
                else if (!strcmp(sd,"3")) continue;
            }
        }
    }
    return 0;
}
