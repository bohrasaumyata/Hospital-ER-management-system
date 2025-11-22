
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#include<unistd.h>
#include"header.h"

struct dnode *dhead=NULL;

void clrscr(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void clrbfr() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void trnl(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

void login();
void signup();
void id(char type,char *ids);
void adminlog();
void admin();
void dprintfunc(struct dnode *node);
void search_staff();
void display_staff();
void update_staff();
void remove_staff();

int main()
{
    srand(time(NULL));
    clrscr();
    int choice;
    do{
        printf("======================= MENU =======================\n");
        printf("1. Login\n");
        printf("2. Signup\n");
        printf("3. Admin Mode\n");
        printf("4. Exit\n");
        printf("Enter your choice:");
        scanf("%d",&choice);
        switch(choice){
            case 1:
            login();
            break;    
            case 2:
            signup();
            break;
            case 3:
            adminlog();
            break;
            case 4:
            printf("Exiting.............!\n");
            exit(0);
            default:
            printf("YOU INPUTED INCORRECT OPTION! PLEASE INPUT CORRECT OPTIONS!\n");
            clrscr();
            break;
        }
    }while(choice!=4);
    return 0;
}

void login(){
    char id[11],password[30],ch;
    int flag=0;
    renter:
    clrscr();
    printf("================ LOGIN MENU ================\n");
    clrbfr();
    printf("Enter Your User ID:");
    fgets(id,sizeof(id),stdin);
    trnl(id);
    if(strncmp(id,"DOC-",4)==0){
        clrbfr();
        printf("Enter Your Password:");
        fgets(password,sizeof(password),stdin);
        trnl(password);
        if(dhead==NULL){
            printf("NO DOCTORS ARE REGISTERED YET!\n");
            return;
        }
        struct dnode *search=dhead;
        do{
            if(strcmp(search->data.doctorid,id)==0 && strcmp(search->data.password,password)==0){
                printf("DOCTOR %s LOGGED IN SUCESSFULLY\n",search->data.name);
                menu();
                flag=1;
                break;
            }
            search=search->next;
        }while(search!=dhead);
        if(flag==0){
            rei:
            printf("YOU HAVE INPUTTED INCORRECT USERNAME OR PASSWORD!\n");
            printf("Press r to RETRY or y to RETURN to MAINMENU\n");
            ch=tolower(getchar());
            if(ch=='r'){
                goto renter;
            }else if(ch=='y'){
                clrscr();
                return;
            }else{
                goto rei;
            } 
        }      
    }
    else{
        rep:
        printf("YOU HAVE INPUTTED INCORRECT USERNAME OR PASSWORD!\n");
        printf("Press r to RETRY or y to RETURN to MAINMENU\n");
        ch=tolower(getchar());
        if(ch=='r'){
            goto renter;
        }else if(ch=='y'){
            clrscr();
            return;
        }else{
            goto rep;
        } 
    }
}


void signup(){
    clrscr();
    char ids[11];
    char gender;
    char password[20],cpassword[20],name[20],email[30];
    int age,experience,phone,opt;
    struct dnode *node=(struct dnode*)malloc(sizeof(struct dnode));
    clrbfr();
    printf("================ SIGNUP MENU ================\n");
    printf("ENTER NAME:");
    fgets(name,sizeof(name),stdin);
    trnl(name);
    strcpy(node->data.name,name);
    dgen:
    printf("ENTER GENDER (f for FEMALE or m for MALE):");
    scanf("%c",&gender);
    gender=tolower(gender);
    if(gender=='f' || gender=='m'){
        node->data.gender=gender;
    }else{
        printf("You have inputed incorrect gender!Input again\n");
        clrbfr();
        goto dgen;
    }
    printf("ENETR AGE:");
    scanf("%d",&age);
    node->data.age=age;
    clrbfr();
    do{
        printf("ENTER YOUR SPECIALIZATION:\n");
        printf("1 - Cardiac\n");
        printf("2 - Pulmonary\n");
        printf("3 - Maternity\n");
        printf("4 - Infection\n");
        printf("5 - Gut\n");
        printf("6 - Injury\n");
        printf("7 - Diabetes\n");
        printf("8 - psychiatric\n");
        printf("CHOOSE YOUR SPECIALIZATION (1-8):");
        scanf("%d",&opt);
        switch(opt){
            case 1:strcpy(node->data.specialization,"Cardiac");break;
            case 2:strcpy(node->data.specialization,"Pulmonary");break;
            case 3:strcpy(node->data.specialization,"Maternity");break;
            case 4:strcpy(node->data.specialization,"Infection");break;
            case 5:strcpy(node->data.specialization,"Gut");break;
            case 6:strcpy(node->data.specialization,"Injury");break;
            case 7:strcpy(node->data.specialization,"Diabetes");break;
            case 8:strcpy(node->data.specialization,"Psychiatric");break;
            default:printf("INVALID OPTION!Please Choose Again b/w 1 to 8");break;        
        }
    }while(opt<1 || opt>8);
    printf("ENTER YEARS OF EXPERIENCE ON FIELD:");
    scanf("%d",&experience);
    node->data.experience=experience;
    clrbfr();
    printf("ENTER EMAIL:");
    fgets(email,sizeof(email),stdin);
    trnl(email);
    strcpy(node->data.email,email);
    printf("ENTER PHONE NO.:");
    scanf("%d",&phone);
    node->data.phone=phone;
    clrbfr();
    dpass:
    printf("CREATE A PASSWORD:");
    fgets(password,sizeof(password),stdin);
    trnl(password);
    printf("CONFIRM PASSWORD:");  
    fgets(cpassword,sizeof(cpassword),stdin); 
    trnl(cpassword);
    if(strcmp(password,cpassword)==0){
        strcpy(node->data.password,password);
        id('d',ids);
        printf("Your ID : %s\n",ids);
        printf("Returning to Menu\n");
        strcpy(node->data.doctorid,ids);
        sleep(5);
        clrscr();
        printf("Your ID : %s\n",ids);
    }else{
        printf("Password Not Matched!Please Re-Enter The Password\n");
        goto dpass;
    }
    if(dhead==NULL){
        node->next=node;
        node->prev=node;
        dhead=node;
    }else{
        node->next=dhead;
        node->prev=dhead->prev;
        dhead->prev->next=node;
        dhead->prev=node;
    } 
}


void id(char type,char *ids){
    int randid;
    int min=100000,max =999999;
    randid=(rand()%(max-min+1))+min;
    if(type=='d'){
        sprintf(ids,"DOC-%06d",randid);
    }
}


void adminlog(){
    char id[10],password[20];
    retq:
    clrscr();
    printf("========================== ADMIN LOGIN ==========================\n");
    printf("ENTER ADMIN ID:");
    clrbfr();
    fgets(id,sizeof(id),stdin);
    trnl(id);
    printf("PASSWORD:");
    fgets(password,sizeof(password),stdin);
    trnl(password);
    if(strcmp(adminid,id)==0 && strcmp(adminpass,password)==0){
        admin();
    }else{
        char opt;
        tyagainn:
        printf("ADMIN ID OR PASSWORD IS INCORRECT!\n");
        printf("PRESS r TO RETRY OR y TO GOBACK\n");
        opt=tolower(getchar());
        clrbfr();
        if(opt=='r'){
            clrbfr();
            goto retq;
        }else if(opt=='y'){
            clrscr();
            return;
        }else{
            printf("INVALID INPUT!\n");
            goto tyagainn;
        }
    }

}

void admin(){
    clrscr();
    int choice;
    do{
        printf("======================= ADMIN MENU =======================\n");
        printf("1. SEARCH STAFF\n");
        printf("2. DISPLAY\n");
        printf("3. UPDATE STAFF DETAILS\n");
        printf("4. REMOVE STAFF\n");
        printf("5. GOBACK TO MAIN MENU\n");
        printf("6. EXIT\n");
        printf("ENTER YOUR CHOICE:");
        scanf("%d",&choice);
        switch(choice){
            case 1:
            clrscr();
            search_staff();
            break;
            case 2:
            clrscr();
            display_staff();
            break;
            case 3:
            clrscr();
            update_staff();
            break;
            case 4:
            clrscr();
            remove_staff();
            break;
            case 5:
            clrscr();
            return;
            break;
            case 6:
            printf("Exiting.................\n");
            exit(0);
            default:
            printf("YOU INPUTED INCORRECT OPTION! PLEASE INPUT CORRECT OPTIONS!\n");
            sleep(3);
            clrscr();
            break;
        }
    }while(choice!=6);
}

void dprintfunc(struct dnode *node){
    printf("ID: %s\n", node->data.doctorid);
    printf("Name: %s\n", node->data.name);
    printf("Gender: %c\n", node->data.gender);
    printf("Age: %d\n", node->data.age);
    printf("Specialization: %s\n", node->data.specialization);
    printf("Experience: %d years\n", node->data.experience);
    printf("Email: %s\n", node->data.email);
    printf("Phone: %d\n", node->data.phone);
}

void search_staff(){
    char id[11];
    retype:
    clrscr();
    printf("====================== SEARCH MENU ======================\n");
    printf("ENTER STAFF ID:");
    clrbfr();
    fgets(id,sizeof(id),stdin);
    trnl(id);

    if(strncmp(id, "DOC-", 4) == 0){
        if(dhead==NULL){
            printf("NO DOCTORS ARE REGISTERED YET!\n");
            sleep(3);
            return;
        }
        struct dnode *node=dhead;
        int found=0;

        do{
            if(strcmp(node->data.doctorid,id)==0){
                printf("\n--- Staff Found ---\n");
                dprintfunc(node);
                found=1;
                break;
            }
            node=node->next;
        }while(node!=dhead);

        if(!found){
            printf("\nDoctor with ID %s not found!\n", id);
        }
        printf("\nPress any key to return...");
        clrbfr();
        getchar();
        return;
    }
    else{
        char opt;
        tyagain:
        printf("INPUTTED INVALID ID!\n");
        printf("PRESS r TO RETRY OR y TO GOBACK\n");
        opt=tolower(getchar());
        if(opt=='r'){
            goto retype;
        }else if(opt=='y'){
            clrscr();
            return;
        }else{
            printf("INVALID INPUT!\n");
            goto tyagain;
        }
    }
}


void display_staff(){
    int choice;
    char opt;
    again:
    clrscr();
    do{
        printf("===================== STAFF DETAILS =====================\n");
        printf("1. SHOW ALL DOCTORS\n");
        printf("2. GO BACK\n");
        printf("3. EXIT\n");
        printf("ENTER YOUR CHOICE:");
        scanf("%d",&choice);
        switch(choice){
            case 1:  
            if(dhead==NULL){
                printf("NO DOCTORS ARE REGISTERED YET!\n");
                sleep(3);
                goto again;
            }
            struct dnode *dnode=dhead;
            printf("=================== Doctors List ===================\n");
            do {
                dprintfunc(dnode);
                printf("------------------------------------------------\n");
                dnode = dnode->next;
            } while (dnode != dhead);
            printf("PRESS y TO GO BACK\n");
            clrbfr();
            opt=tolower(getchar());
            if(opt=='y'){
                clrscr();
                return;
            }else{
                sleep(7);
                clrscr();
                return;
            }
            break;
            case 2:
            clrscr();
            return;
            break;
            case 3:
            printf("Exiting...................\n");
            exit(0);
            default:
            printf("YOU HAVE INPUTED INVALID INPUT!\n");
            sleep(3);
            clrscr();
            break;
        }
    }while(choice!=3);
}

void update_staff(){
    int choice,phone;
    char id[11],email[30],pass[30];
    mains:
    clrscr();
    do{
        printf("===================== UPDATE MENU =====================\n");
        printf("1. UPDATE STAFF EMAIL\n");
        printf("2. UPDATE STAFF PHONE NO.\n");
        printf("3. UPDATE STAFF PASSWORD\n");
        printf("4. GO BACK\n");
        printf("5. EXIT\n");
        printf("ENTER YOUR CHOICE:");
        scanf("%d",&choice);
        switch(choice){
            case 1:
            tryone:
            clrscr();
            printf("===================== UPDATE STAFF ID =====================\n");
            printf("ENTER STAFF ID:");
            clrbfr();
            fgets(id,sizeof(id),stdin);
            trnl(id);
            if(strncmp(id, "DOC-", 4) == 0){
                int found=0;
                struct dnode *node=dhead;
                do{
                    if(strcmp(node->data.doctorid,id)==0){
                        clrbfr();
                        printf("ENTER NEW EMAIL:");
                        fgets(email,sizeof(email),stdin);
                        trnl(email);
                        printf("EMAIL UPDATED SUCESSFULLY\n");
                        strcpy(node->data.email,email);
                        found=1;
                        clrscr();
                        break;
                    }
                    node=node->next;
                }while(node!=dhead);       
                if(!found)
                    printf("DOCTOR WITH %s ID NOT FOUND!\n",id);         
            }
            else{
                tryme:
                printf("YOU HAVE INPUTTED INCORRECT USERID\n");
                printf("PRESS r TO RETRY OR y TO GA BACK\n");
                char ch=tolower(getchar());
                if(ch=='r'){
                    goto tryone;
                }else if(ch=='y'){
                    goto mains;
                }else{
                    clrscr();
                    printf("INVALID INPUT!RETRY......\n");
                    goto tryme;
                }
            }
            break;
            case 2:
            trytwo:
            clrscr();
            printf("===================== UPDATE STAFF PHONE NUMBER =====================\n");
            printf("ENTER STAFF ID:");
            clrbfr();
            fgets(id,sizeof(id),stdin);
            trnl(id);
            if(strncmp(id, "DOC-", 4) == 0){
                int found=0;
                struct dnode *node=dhead;
                do{
                    if(strcmp(node->data.doctorid,id)==0){
                        printf("ENTER NEW PHONE NO.:");
                        scanf("%d",&phone);
                        printf("PHONE NO. UPDATED SUCESSFULLY\n");
                        node->data.phone=phone;
                        found=1;
                        clrscr();
                        break;
                    }   
                }while(node!=dhead);
                if(!found)
                    printf("DOCTOR WITH %s ID NOT FOUND!\n",id);                
            }
            else{
                tryin:
                printf("YOU HAVE INPUTTED INCORRECT USERID\n");
                printf("PRESS r TO RETRY OR y TO GO BACK\n");
                char ch=tolower(getchar());
                if(ch=='r'){
                    goto trytwo;
                }else if(ch=='y'){
                    goto mains;
                }else{
                    clrscr();
                    printf("INVALID INPUT!RETRY......\n");
                    goto tryin;
                }
            }
            break;
            case 3:
            trythree:
            clrscr();
            printf("===================== UPDATE STAFF PASSWORD =====================\n");
            printf("ENTER STAFF ID:");
            clrbfr();
            fgets(id,sizeof(id),stdin);
            trnl(id);
            if(strncmp(id, "DOC-", 4) == 0){
                int found=0;
                struct dnode *node=dhead;
                do{
                    if(strcmp(node->data.doctorid,id)==0){
                        clrbfr();
                        printf("ENTER NEW PASSWORD:");
                        fgets(pass,sizeof(pass),stdin);
                        trnl(pass);
                        printf("PASSWORD UPDATED SUCESSFULLY\n");
                        strcpy(node->data.password,pass);
                        clrscr();
                        break;
                    }
                }while(node!=dhead);
                if(!found)
                    printf("DOCTOR WITH %s ID NOT FOUND!\n",id);   
            }
            else{
                trynw:
                printf("YOU HAVE INPUTTED INCORRECT USERID\n");
                printf("PRESS r TO RETRY OR y TO GO BACK\n");
                char ch=tolower(getchar());
                if(ch=='r'){
                    goto trythree;
                }else if(ch=='y'){
                    goto mains;
                }else{
                    clrscr();
                    printf("INVALID INPUT!RETRY......\n");
                    goto trynw;
                }
            }
            break;
            case 4:
            clrscr();
            return;
            break;
            case 5:
            printf("Exiting...................\n");
            exit(0);
            default:
            printf("YOU HAVE INPUTTED INVALID INPUT\n");
            sleep(3);
            clrscr();
            break;
        }
    }while(choice!=5);
}

void remove_staff() {
    char id[11], choice;
    remty:
    clrscr();
    printf("========================== STAFF DELETION MENU ==========================\n");
    printf("ENTER STAFF ID TO REMOVE:");
    clrbfr();
    fgets(id,sizeof(id),stdin);
    trnl(id);
    if(strncmp(id, "DOC-", 4) == 0){
        if(dhead==NULL){
            printf("Doctor list is empty!\n");
            sleep(2);
            goto remty;
        }
        struct dnode *node=dhead;
        int found=0;
        do{
            if(strcmp(node->data.doctorid,id)==0){
                found=1;
                if(node->prev==node && node->next==node){
                    printf("STAFF FOUND SUCESSFULLY\n\n");
                    dprintfunc(node);
                    prvi:
                    printf("PRESS Y TO DELETE OR N TO GO BACK\n");
                    clrbfr();
                    choice=tolower(getchar());
                    if(choice=='y'){
                        free(node);
                        dhead=NULL;
                    }else if(choice=='n'){
                        clrscr();
                        return;
                    }else{
                        printf("INVALID INPUT!TRY AGAIN......\n");
                        goto prvi;
                    }
                }else if(node==dhead){
                    printf("STAFF FOUND SUCESSFULLY\n\n");
                    dprintfunc(node);
                    pry:
                    printf("PRESS Y TO DELETE OR N TO GO BACK\n");
                    clrbfr();
                    choice=tolower(getchar());
                    if(choice=='y'){
                        dhead->prev->next=dhead->next;
                        dhead->next->prev=dhead->prev;
                        dhead=dhead->next;
                        free(node);
                    }else if(choice=='n'){
                        clrscr();
                        return;
                    }else{
                        printf("INVALID INPUT!TRY AGAIN......\n");
                        goto pry;
                    }
                }else{
                    printf("STAFF FOUND SUCESSFULLY\n\n");
                    dprintfunc(node);
                    prp:
                    printf("PRESS Y TO DELETE OR N TO GO BACK\n");
                    clrbfr();
                    choice=tolower(getchar());
                    if(choice=='y'){
                        node->prev->next=node->next;
                        node->next->prev=node->prev;
                        free(node);
                    }else if(choice=='n'){
                        clrscr();
                        return;
                    }else{
                        clrscr();
                        printf("INVALID INPUT!TRY AGAIN......\n");
                        goto prp;
                    }
                }
                break;
            }
            node=node->next;
        }while(node!=dhead);
        if(!found){
            printf("Doctor with ID %s not found!\n",id);
            sleep(2);
        }
    }
    else{
        trynr:
        printf("YOU HAVE INPUTTED INCORRECT USERID\n");
        printf("PRESS r TO RETRY OR y TO GO BACK\n");
        char ch=tolower(getchar());
        if(ch=='r'){
            goto remty;
        }else if(ch=='y'){
            clrscr();
            return;
        }else{
            printf("INVALID INPUT!RETRY......\n");
            goto trynr;
        }
    }
}
