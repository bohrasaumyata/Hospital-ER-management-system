#include"header.h"

extern void clrscr();
extern void clrbfr();
extern void printpatient(struct pnode *node);
extern struct pnode *root;

void search_patient(){
    int patientid;
    clrscr();
    printf("====================== PATIENT SEARCH MENU ======================\n");
    if(root==NULL){
        printf("NO PATIENTS ARE ADMITTED YET!\n");
        sleep(3);
        return;
    }else{
        printf("ENTER PATIENT ID TO SEARCH:");
        scanf("%d",&patientid);
        struct pnode *current=root;
        int found=0;
        while(current!=NULL){
            if(patientid==current->data.patientid){
                printpatient(current);
                found=1;
                break;
            }else if(patientid<current->data.patientid){
                current=current->left;
            }else{
                current=current->right;
            }
        }
        if(!found){
            printf("\nPatient with ID %d not found.\n",patientid);
        }
    }
    printf("\nPress any key to return to the previous menu...");
    clrbfr();
    getchar();
}