#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#include<unistd.h>
#include"header.h"

extern void clrscr();
extern struct pnode *root;
void dispatient(struct pnode *node,int flag);
void printpatient(struct pnode *node);

void display_patient() {
    int choice;
    int patients_found; 

    do {
        printf("====================== DISPLAY MENU ======================\n");
        printf("1. DISPLAY ADMITTED PATIENTS\n");
        printf("2. DISPLAY DISCHARED PATIENTS\n");
        printf("3. DISPLAY ALL PATIENTS\n");
        printf("4. GO BACK TO MAIN MENU\n");
        printf("ENTER YOUR CHOICE:");
        scanf("%d", &choice);

        if (root == NULL && choice >= 1 && choice <= 3) {
            clrscr();
            printf("NO PATIENTS IN THE SYSTEM YET!\n");
            sleep(3);
            clrscr();
            continue;
        }

        patients_found = 0; 
        clrscr();           

        switch (choice) {
            case 1:
                printf("--- Admitted Patients ---\n");
                dispatient(root, 1);
                if (patients_found == 0) {
                    printf("NO ADMITTED PATIENTS FOUND.\n");
                }
                printf("\nPress any key to continue...");
                clrbfr();
                getchar();
                clrscr();
                break;
            case 2:
                printf("--- Discharged Patients ---\n");
                dispatient(root, 2);
                if (patients_found == 0) {
                    printf("NO DISCHARGED PATIENTS FOUND.\n");
                }
                printf("\nPress any key to continue...");
                clrbfr();
                getchar();
                clrscr();
                break;
            case 3:
                printf("--- All Patients ---\n");
                dispatient(root, 0);
                if (patients_found == 0) {
                    printf("NO PATIENTS IN THE SYSTEM YET!\n");
                }
                printf("\nPress any key to continue...");
                clrbfr();
                getchar();
                clrscr();
                break;
            case 4:
                printf("Going Back to Main Menu\n");
                sleep(3);
                clrscr();
                return; 
                break;
            default:
                printf("INVALID INPUT!RETRY\n");
                sleep(3);
                clrscr();
                break;
        }
    } while (choice != 4);
}

void printpatient(struct pnode *node){
    printf("------------------------------------------------\n");
    printf("ID:            %d\n", node->data.patientid);
    printf("Name:          %s\n", node->data.name);
    printf("Status:        %s\n", node->data.status); 
    printf("Age:           %d\n", node->data.age);
    printf("Gender:        %c\n", node->data.gender);
    printf("Category:      %s\n", node->data.category);
    printf("Triage Level:  %d\n", node->data.tlevel);
    printf("Assigned Doc:  %s\n", node->data.docid);
    printf("Emergency Ph:  %s\n", node->data.ephone);
    printf("------------------------------------------------\n");
}

void dispatient(struct pnode *node,int flag){
    if(node==NULL){
        return;
    }
    dispatient(node->left,flag);
    if(flag==1){ 
        if(strcmp(node->data.status,"Admitted")==0){
            printpatient(node);
        }
    }else if(flag==2){ 
        if(strcmp(node->data.status,"Discharged")==0){
            printpatient(node);
        }
    }else{ 
        printpatient(node);
    }
    dispatient(node->right,flag);
}