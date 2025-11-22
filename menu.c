#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#include<unistd.h>
#include"header.h"

extern void clrscr();
extern struct pnode *root;

void menu(){
    int opt;
    do{
        printf("====================== MENU ======================\n");
        printf("1. ADD PATIENT\n");
        printf("2. SEARCH PATIENT\n");
        printf("3. DISPLAY PATIENTS\n");
        printf("4. DISPALY TRIAGE LIST\n");
        printf("5. DISCHARE PATIENT\n");
        printf("6. LOG OUT\n");
        printf("7. EXIT\n");
        printf("ENTER YOUR CHOICE:");
        scanf("%d",&opt);
        switch(opt){
            case 1:
            clrscr();       
            add_patient();
            break;
            case 2:
            clrscr();
            search_patient();
            break;
            case 3:
            clrscr();
            display_patient();
            break;
            case 4:
            clrscr();
            // atriage();
            break;
            case 5:
            clrscr();
            discharge_patient();
            break;
            case 6:
            printf("Logging Out\n");
            sleep(3);
            clrscr();
            return;
            break;
            case 7:
            printf("Exiting...............\n");
            exit(0);
            break;
            default:
            printf("INVALID INPUT!RETRY\n");
            sleep(3);
            clrscr();
            break;
        }
    }while(opt!=7);
}