#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>

#define CNN 15  // for name
#define CBN 4   // for code
COORD coordinates= {0,0};
void gotocoordinate(int x,int y)   //gotoxy function
{
    coordinates.X=x;
    coordinates.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinates);
}

void checking_code(char[]);
int checking(char[]);


typedef struct
{
    char name[CNN],code[CBN];
    float rate;
    int quantity;
} record;
record stocks;


void cur(int);  // cursur function 
void departmentbill();  // bill function
void department_menu(); // main menu function
void view(record *,int,int);   // display function
void window_screen(int,int,int,int); // box function
void view_concern(); 
void department_search();  // search function
void h_light(int,int);


void cal_bill() ;  // calculation bill function
void modify();   // update function
void add_stocks();  // add stock function
void delete_stocks();  // delete function
void exit();  // exit function

void depart_name();
void depart_code();
void depart_rate();
void depart_qty();
void depart_all();


int main() // main function
{
    department_menu();
    return 0;
}

void department_menu()  // main menu 1st box
{
    int a;
    char st;
    const char *menu[]= {"   Calculate Bill","   Add Goods","   Edit Goods","   Display All ","   Search", "   Delete Goods","   Exit"};
    system("cls");
    window_screen(25,50,20,32);
    gotocoordinate(33,18);
    printf("MAIN MENU");
    for (a=0; a<=6; a++)
    {
        gotocoordinate(30,22+a+1);
        printf("%s\n\n\n",menu[a]);
    }
    cur(7);
}

void department_search()  // search box
{
    char st;
    int a;
    const char *menu[]= {"	BY Name","   By Code","   By Rate","   By Quantity","   Back to main menu"};
    system("cls");

    window_screen(25,50,20,32);    // box
    gotocoordinate(33,18);
    printf("SEARCH MENU");
    for (a=0; a<=3; a++)
    {
        gotocoordinate(30,22+a+1);
        printf("%s\n\n\n",menu[a]);
    }
    cur(4);
}


void cur(int no)  // for cursur
{
    int counting=1;
    char st='0';
    gotocoordinate(30,22);  //* 23
    while(1)
    {
        switch(st)
        {
        case 80:       // code value of up and down
            counting++;
            if (counting==no+1)
            counting=1;
            break;
        case 72:
            counting--;
            if(counting==0) counting=no;
            break;
        }
        h_light(no,counting);
        st=getch();
        if(st=='\r')
        {
            if(no==7)
            {
                if (counting==1) cal_bill() ;
                else if(counting==2) add_stocks();
                else if(counting==3) modify();
                else if (counting==4) depart_all();
                else if (counting==5) department_search();
                else if (counting==6) delete_stocks();
                else   exit(0);
            }
            if(no==4)
            {
                if (counting==1) depart_code();
                else if (counting==2)depart_rate();
                else if (counting==3) depart_qty();
                else department_menu();
            }
        }
    }
}

void h_light(int no,int count)  // after search box search by name,code,etc
{
    if (no==4)
    {
        gotocoordinate(30,22);
        printf("   By Name			");
        gotocoordinate(30,23);
        printf("   By Code          ");
        gotocoordinate(30,24);
        printf("   By Rate          ");
        gotocoordinate(30,25);
        printf("   By Quantity      ");
        gotocoordinate(30,26);
        printf("   Back to main menu");

        switch (count)
        {
        case 1:
        	gotocoordinate(30,22);
        	printf(" - By Name 			");
        case 2:
            gotocoordinate(30,23);
            printf(" - By Code          ");
            break;
        case 3:
            gotocoordinate(30,24);
            printf(" - By Rate          ");
            break;
        case 4:
            gotocoordinate(30,25);
            printf(" - By Quantity      ");
            break;
        case 5:
            gotocoordinate(30,26);
            printf(" - Back to main menu");
            break;
        }
    }

    if(no==7)
    {

        gotocoordinate (30,23);
        printf("   Calculate Bill ");
        gotocoordinate (30,24);
        printf("   Add Goods      ");
        gotocoordinate (30,25);
        printf("   Edit Goods     ");
        gotocoordinate (30,26);
        printf("   Display All    ");
        gotocoordinate (30,27);
        printf("   Search         ");
        gotocoordinate (30,28);
        printf("   Delete Goods   ");
        gotocoordinate (30,29);
        printf("   Exit           ");

        switch(count)
        {
        case 1:
            gotocoordinate (30,23);
            printf(" - Calculate Bill ");
            break;
        case 2:
            gotocoordinate (30,24);
            printf(" - Add Goods      ");
            break;
        case 3:
            gotocoordinate (30,25);
            printf(" - Edit Goods     ");
            break;
        case 4:
            gotocoordinate (30,26);
            printf(" - Display All    ");
            break;
        case 5:
            gotocoordinate (30,27);
            printf(" - Search         ");
            break;
        case 6:
            gotocoordinate (30,28);
            printf(" - Delete Goods   ");
            break;
        case 7:
            gotocoordinate (30,29);
            printf(" - Exit           ");
            break;
        }
    }
}

void cal_bill()  // calculation of bill
{
    char c[4]= {0};
    int d=29,e=0,size=0,f=1;
    float d_tot=0,gross_tot=0;
    FILE *openfile;
    openfile=fopen("record.txt","r+b");
    rewind(openfile);
    system("cls");
    departmentbill();
    gotocoordinate(26,15);
    printf("enter  \"end\" to finish input");
    while(1)
    {
        gotocoordinate(25,18);
        printf("                    ");
        gotocoordinate(25,19);
        printf("                    ");
        gotocoordinate(25,18);
        printf("enter item code:");   // bill by code
        scanf("%s",c);
        if(strcmp(c,"end")==0)
        break;
        gotocoordinate(25,19);
        printf("enter quantity:");
        scanf("%d",&e);
        rewind(openfile);
        while(fread(&stocks,sizeof(stocks),1,openfile))
        {
            if((strcmp(stocks.code,c)==0))
            {
                d_tot=stocks.rate*e;
                gotocoordinate(11,d);
                printf("%4d",f);
                printf("%9s",stocks.name);
                printf("%13d",e);
                printf("%15.2f",stocks.rate);
                printf("%13.2f",d_tot);
                gross_tot=gross_tot+d_tot;
                size=sizeof(stocks);
                stocks.quantity=stocks.quantity-e;
                d+=2;
                f++;
                fseek(openfile,-size,SEEK_CUR);
                fwrite(&stocks,sizeof(stocks),1,openfile);
                break;
            }
        }
    }
    if(gross_tot!=0)
    {
        gotocoordinate(30,d+5);
        printf("TOTAL AMOUNT = %6.2f",gross_tot);
    }
    fclose(openfile);
    getch();
    department_menu();
}

void departmentbill()  // last bill
{
    int a;
    gotocoordinate(20,10);
//;
    for (a=1; a<=10; a++)
        printf("*");
    printf(" * Big Bazaar * ");
    for (a=1; a<=10; a++)
        printf("*");
    printf("\n\n");
    gotocoordinate(30,11);
    printf("Departmental Store");
//textcolor(1);
    gotocoordinate(32,25);
    printf("CUSTOMER'S BILL") ;
//textcolor(8);
    gotocoordinate(13,27);
    printf("SN.   Item Name     Quantity     Rate        Total");

}

void add_stocks ()  // for add stock or add new record
{
    FILE *openfile;
    char l[CBN],m[12];
    system("cls");
//textbackground(11);
//textcolor(0);
    gotocoordinate(25,25);
    printf("Enter new record(Y/N)?");
    while(toupper(getche())=='Y')
    {
        system("cls");
        openfile=fopen("record.txt","ab");
        checking_code(l);
        strcpy(stocks.code,l);
        gotocoordinate(22,28);
        printf("Enter rate of the item:");
        scanf("%f",&stocks.rate);
        gotocoordinate(22,30);
        printf("Enter quantity of the item:");
        scanf("%d",&stocks.quantity);
        gotocoordinate(22,32);
        printf("Enter name of the item:");
        scanf("%s",stocks.name);
        fseek(openfile,0,SEEK_END);
        fwrite(&stocks,sizeof(stocks),1,openfile);
        fclose(openfile);
        gotocoordinate(22,34);
        printf("Enter new record(Y/N)?");

    }
    department_menu();  // 1st box main menu
}


void checking_code(char y[])  // for update
{
    int flagerized;
    FILE *openfile;
    openfile=fopen("record.txt","rb");
    while(1)
    {
        system("cls");
        window_screen(20,58,23,36);
        gotocoordinate(32,18);
        printf(" ADD ARTICLES ")  ;    
        flagerized=1;
        rewind(openfile);
        gotocoordinate(22,25);
        printf("Enter new code of the article:");  // update by code
        scanf(" %[^\n]",y);
        while(fread(&stocks,sizeof(stocks),1,openfile)==1)
        {
            if (strcmp(y,stocks.code)==0)
            {
                flagerized=0;
                gotocoordinate(26,30);
                printf("code already exists");  // id already exists
                gotocoordinate(29,32);
                printf("enter again");
                getch();
                break;
            }
        }
        if (flagerized==1)
            break;
    }
}


void modify()  // for edit record
{
    int flagerized=0,options;
    char r[CBN],s[CBN];
    FILE *openfile;
    int sze;
    system("cls");
//textcolor(0);
//textbackground(11);
    window_screen(20,63,20,46);
    gotocoordinate(35,18);
    printf("EDIT RECORDS");
    ;
    gotocoordinate(25,23);
    printf("enter item code: ");
    scanf("%s",r);
    flagerized=checking(r);
    if(flagerized==0)
    {
        openfile=fopen("record.txt","r+b");
        rewind(openfile);
        while (fread(&stocks,sizeof (stocks),1,openfile))
        {
            if(strcmp(stocks.code,r)==0)
            {
                //textcolor(0);
                gotocoordinate(25,27);
                printf("name       = %s",stocks.name);
                gotocoordinate(25,28);
                printf("code       = %s",stocks.code);
                gotocoordinate(25,29);
                printf("rate       = %g",stocks.rate);
                gotocoordinate(25,30);
                printf("quantity   = %d",stocks.quantity);
                gotocoordinate(25,32);;
                printf("Do you want to edit this record?(y/n):");
                fflush(openfile);
                if(toupper(getche())=='Y')
                {
                    //textcolor(0);
                    gotocoordinate(25,34);
                    printf("1- edit name ");  // what we want to edit name,code,etc
                    gotocoordinate(25,35);
                    printf("2- edit code ");
                    gotocoordinate(25,36);
                    printf("3- edit rate ");
                    gotocoordinate(25,37);
                    printf("4- edit quantity ");
                    gotocoordinate(25,39);  ;
                    printf(" enter your choice(1, 2, 3, 4) ");
                    scanf("%d",&options);
                    switch(options)
                    {
                    case 1:        //case 1 for edit name
                        system("cls");
                        window_screen(23,48,20,40);
                        gotocoordinate(35,18);
                        printf("EDIT RECORDS");
                        gotocoordinate(25,24);
                        printf(" enter new name: ");
                        scanf("%s",stocks.name);
                        sze=sizeof(stocks);
                        fseek(openfile,-sze,SEEK_CUR);
                        fwrite(&stocks,sizeof(stocks),1,openfile);
                        break;
                    case 2:
                        system("cls");
                        window_screen(23,65,20,40);
                        gotocoordinate(35,18);
                        printf("EDIT RECORDS");
                        gotocoordinate(25,24);
                        checking_code(s);
                        strcpy(stocks.code,s);
                        sze=sizeof(stocks);
                        fseek(openfile,-sze,SEEK_CUR);
                        fwrite(&stocks,sizeof(stocks),1,openfile);
                        break;
                    case 3:
                        system("cls");
                        window_screen(23,65,20,40);
                        gotocoordinate(35,18);
                        printf("EDIT RECORDS");
                        gotocoordinate(25,24);
                        printf(" enter new rate: ");
                        scanf("%f",&stocks.rate);
                        sze=sizeof(stocks);
                        fseek(openfile,-sze,SEEK_CUR);
                        fwrite(&stocks,sizeof(stocks),1,openfile);
                        break;
                    case 4:
                        system("cls");
                        window_screen(23,65,20,40);
                        gotocoordinate(35,18);
                        printf("EDIT RECORDS");
                        gotocoordinate(25,24);
                        printf(" enter new quantity: ");
                        scanf("%d",&stocks.quantity);
                        sze=sizeof(stocks);
                        fseek(openfile,-sze,1);
                        fwrite(&stocks,sizeof(stocks),1,openfile);
                        break;
                    }
                    gotocoordinate(27,30);
                    printf("--- item edited---");
                    break;
                }
            }
        }
    }
    if (flagerized==1)
    {
        gotocoordinate(32,30);
        printf("Item does not exist.");
        gotocoordinate(36,32);
        printf("TRY ABGAIN");
    }
    getch();
    fclose(openfile);
    department_menu();   // main menu
}


void depart_all()
{
    int a,d=1;
    FILE *openfile;
    view_concern();
    openfile=fopen("record.txt","rb");
    rewind(openfile);
    a=26;
    fflush(openfile);
    while(fread(&stocks,sizeof(stocks),1,openfile))
    {
        view(&stocks,a,d);
        a++;
        d++;
        if ((d%20)==0)
        {
            gotocoordinate(27,47);/*textcolor(0)*/;
            printf("Press any key to see more...........");
            getch();
            system("cls");
            view_concern();
            a=26;
            continue;
        }
    }
    getch();
    if (a==26)
    {
        gotocoordinate(24,30);
        printf("-- no articles found --");
    }
    getch();
    fclose(openfile);
    department_menu();
}

/*function to display by quantity*/
void depart_qty()   //search by quantity
{
    int s,t=1;
    int p,q;
    FILE *openfile;
    view_concern();
    openfile=fopen("record.txt","rb");
    rewind(openfile);
    s=26;
    gotocoordinate(16,20);;
    printf("Enter lower range: ");
    scanf("%d",&p);
    gotocoordinate(16,21);
    printf("Enter upper range:");
    scanf("%d",&q);
    fflush(openfile);
    while(fread(&stocks,sizeof(stocks),1,openfile))
    {
        if((stocks.quantity>=p)&&(stocks.quantity<=q))
        {
            view(&stocks,s,t);
            s++;
            t++;
            if ((t%20)==0)
            {
                gotocoordinate(27,47);
                printf("Press any key to see more...........");
                getch();
                system("cls");
                view_concern();
                s=26;
                continue;
            }
        }
    }
    getch();
    if (s==26)
    {
        gotocoordinate(28,30);
        printf(" No items found.");
    }
    getch();
    department_search();
    fclose(openfile);
}


void depart_rate()  // search by rate
{
    int s,t=1;
    float p,q;
    FILE *openfile;
    view_concern();
    openfile=fopen("record.txt","rb");
    rewind(openfile);
    s=26;
    gotocoordinate(16,20);;
    printf("enter lower range: ");
    scanf("%f",&p);
    gotocoordinate(16,21);
    printf("enter upper range: ");
    scanf("%f",&q);
    fflush(openfile);
    while(fread(&stocks,sizeof(stocks),1,openfile))
    {
        if((stocks.rate>=p)&&(stocks.rate<=q))
        {
            view(&stocks,s,t);
            s++;
            t++;
            if ((t%20)==0)
            {
                gotocoordinate(27,47);
                printf("press any key to see more...........");
                getch();
                system("cls");
                view_concern();
                s=26;
                continue;
            }
        }
    }
    getch();
    if (s==26)
    {
        gotocoordinate(28,30);
        printf(" no item found ");
    }
    getch();
    fclose(openfile);
    department_search();
}


void depart_code()   // search by code
{
    int s,t=1;
    char d[4]= {0};
    FILE *openfile;
    view_concern();
    openfile=fopen("record.txt","rb");
    rewind(openfile);
    s=26;
    gotocoordinate(16,20);;
    printf("enter item code: ");
    scanf("%s",d);
    fflush(openfile);
    while(fread(&stocks,sizeof(stocks),1,openfile))
    {
        if((strcmp(stocks.code,d)==0))
        {
            view(&stocks,s,t);
            s++;
            t++;
            break;
        }
    }
    if (s==26)
    {
        gotocoordinate(28,30);
        printf("no item found");
    }
    getch();
    fclose(openfile);
    department_search();
}


void depart_name()   // search by code
{
    int s,t=1;
    char d[15]= {0};
    FILE *openfile;
    view_concern();
    openfile=fopen("record.txt","rb");
    rewind(openfile);
    s=26;
    gotocoordinate(16,20);;
    printf("enter item Name: ");
    scanf("%s",d);
    fflush(openfile);
    while(fread(&stocks,sizeof(stocks),1,openfile))
    {
        if((strcmp(stocks.code,d)==0))
        {
            view(&stocks,s,t);
            s++;
            t++;
            break;
        }
    }
    if (s==26)
    {
        gotocoordinate(28,30);
        printf("no item found");
    }
    getch();
    fclose(openfile);
    department_search();
}

void view_concern()
{
    int a;
    system("cls");
    gotocoordinate(20,10);
    ;
    for (a=1; a<=10; a++)
        printf("*");
    printf(" * Big Bazaar * ");
    for (a=1; a<=10; a++)
        printf("*");
    printf("\n\n");
    gotocoordinate(30,11);
    printf("Departmental Store");
//textcolor(1);
    gotocoordinate(32,17);
    printf("RECORDS") ;
//textcolor(8);
    gotocoordinate(18,23);
    printf ("SN   Item Name   Item Code      Rate     Quantity");
}


void view(record *stocks,int i,int j)
{
    gotocoordinate(20,i);
    printf("%-3d",j);
    printf("%-6s",stocks->name);
    printf("%12s",stocks->code);
    printf("%14.2f",stocks->rate);
    printf("%11d",stocks->quantity);
}


void delete_stocks()
{
    int flagerized;
    char d[CNN];
    FILE *openfile,*openfile1;
    system("cls");
//textbackground(11);
//textcolor(0);
    window_screen(23,51,25,34);
    gotocoordinate(29,18);
    printf("DELETE ARTICLES");
    gotocoordinate(27,27);
    printf("enter item code: ");
    scanf("%s",d);
    flagerized=checking(d);
    if(flagerized==0)
    {
        openfile1=fopen("record1.txt","wb");
        openfile=fopen("record.txt","rb");
        rewind(openfile);
        while (fread(&stocks,sizeof (stocks),1,openfile)==1)
        {
            if(strcmp(stocks.code,d)!=0)
                fwrite(&stocks,sizeof(stocks),1,openfile1);
        }
        gotocoordinate(27,29);
        printf("---item deleted---");
        fclose(openfile1);
        fclose(openfile);
        remove("record.txt");
        rename("record1.txt","record.txt");
    }
    if (flagerized==1)
    {
        gotocoordinate(25,29);
        printf("---item does not exist---");
        gotocoordinate(30,31);
        printf("TRY AGAIN");
    }
    fclose(openfile1);
    fclose(openfile);
    getch();
    department_menu();
}


int checking(char x[CNN])
{
    FILE *openfile;
    int flagerized=1;
    openfile=fopen("record.txt","rb");
    rewind(openfile);
    while (fread(&stocks,sizeof (stocks),1,openfile))
    {
        if(strcmp(stocks.code,x)==0)
        {
            flagerized=0;
            break;
        }
    }
    fclose(openfile);
    return flagerized;
}


void window_screen(int a,int b,int c,int d)
{
    int v;
    system("cls");
    gotocoordinate(20,10);
//textcolor(1);
    for (v=1; v<=10; v++)
        printf("*");
    printf(" * Big Bazaar * ");
    for (v=1; v<=10; v++)
        printf("*");
    printf("\n\n");
    gotocoordinate(30,11);
    printf("Department Store");
//textcolor(4);
    for (v=a; v<=b; v++)
    {
        gotocoordinate(v,17);
        printf("\xcd");
        gotocoordinate(v,19);
        printf("\xcd");
        gotocoordinate(v,c);
        printf("\xcd");
        gotocoordinate(v,d);
        printf("\xcd");
    }

    gotocoordinate(a,17);
    printf("\xc9");
    gotocoordinate(a,18);
    printf("\xba");
    gotocoordinate(a,19);
    printf("\xc8");
    gotocoordinate(b,17);
    printf("\xbb");
    gotocoordinate(b,18);
    printf("\xba");
    gotocoordinate(b,19);
    printf("\xbc");

    for(v=c; v<=d; v++)
    {
        gotocoordinate(a,v);
        printf("\xba");
        gotocoordinate(b,v);
        printf("\xba");
    }
    gotocoordinate(a,c);
    printf("\xc9");
    gotocoordinate(a,d);
    printf("\xc8");
    gotocoordinate(b,c);
    printf("\xbb");
    gotocoordinate(b,d);
    printf("\xbc");
}

       


