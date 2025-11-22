#include"header.h"

extern void clrscr();
extern void printpatient(struct pnode *node);
extern struct pnode *root;
extern struct dnode *dhead;

void discharge_patient(){
    int choice,patientid;
    printf("====================== PATIENT DISCHARGE MENU ======================\n");
    if(root==NULL){
        printf("NO PATIENTS ARE ADMITTED YET!\n");
        sleep(3);
        return;
    }else{
        printf("ENTER PATIENT ID TO DISCHARGE:");
        scanf("%d",&patientid);
        struct pnode *current=root;
        int found=0;
        while(current!=NULL){
            if(patientid==current->data.patientid){
                printpatient(current);
                found=1;
                printf("\nDO YOU WANT TO DISCAHRGE %s PATIENT.\n",current->data.name);
                printf("1. YES\n");
                printf("2. GO BACK\n");
                printf("ENTER YOUR CHOICE:");
                scanf("%d",&choice);
                if(choice==1){
                    strcpy(current->data.status,"Discharged");
                    current->data.tlevel=0;                     
                    printf("Patient %s with ID %d has been discharged successfully.\n",current->data.name,patientid);
                    struct dnode *doctor=dhead;
                    do{
                        if(strcmp(doctor->data.doctorid,current->data.docid)==0){
                            doctor->data.patients--;
                            break;
                        }
                        doctor=doctor->next;
                    }while(doctor!=dhead);
                    printf("GOING BACK TO MAIN MENU\n");
                    sleep(5);
                    clrscr();
                    return;
                }else{
                    printf("DISCHARGE OPERATION CANCELLED.\n");
                    printf("GOING BACK TO MAIN MENU\n");
                    sleep(3);
                    clrscr();
                    return;
                }
                break;
            }else if(patientid<current->data.patientid){
                current=current->left;
            }else{
                current=current->right;
            }
        }
        if(!found){
            printf("\nPatient with ID %d not found.\n",patientid);
            printf("GOING BACK TO MAIN MENU\n");
            sleep(3);
            clrscr();
            return;
        }
    }
}