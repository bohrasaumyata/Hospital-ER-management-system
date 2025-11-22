#include"header.h"

extern void clrscr();
extern void clrbfr();
extern void trnl(char *str);
extern void printpatient(struct pnode *node);
struct pnode *root=NULL;
extern struct dnode *dhead;
struct triage *thead=NULL; 

int alot(){
    static int pid = 100000;
    return pid++;
}

void add_patient(){
    char name[20],gender,ephone[15];
    int age,opt;
    int minpat=9999;
    clrscr();
    printf("====================== PATIENT MENU ======================\n");
    struct dnode *docnode,*mini;
    docnode=dhead; 
    mini=NULL;
    struct pnode *node=(struct pnode*)malloc(sizeof(struct pnode));
    printf("Patient Name:");
    clrbfr();
    fgets(name,sizeof(name),stdin);
    trnl(name);
    strcpy(node->data.name,name);
    printf("Patient Gender(f for FEMALE or m for MALE):");
    scanf(" %c",&gender); 
    node->data.gender=gender;
    printf("Patient Age:");
    scanf("%d",&age); 
    node->data.age=age;
    printf("Patient Emergency Contact No.:");
    clrbfr();
    fgets(ephone,sizeof(ephone),stdin);
    trnl(ephone);
    strcpy(node->data.ephone,ephone);
    do{
        printf("Select the patient's Admit Category:\n");
        printf("1 - Cardiac\n");
        printf("2 - Pulmonary\n");
        printf("3 - Maternity\n");
        printf("4 - Infection\n");
        printf("5 - Gut\n");
        printf("6 - Injury\n");
        printf("7 - Diabetes\n");
        printf("8 - psychiatric\n");
        printf("Enter Category (1-8):");
        scanf("%d",&opt);
        switch(opt){
            case 1:strcpy(node->data.category,"Cardiac");break;
            case 2:strcpy(node->data.category,"Pulmonary");break;
            case 3:strcpy(node->data.category,"Maternity");break;
            case 4:strcpy(node->data.category,"Infection");break;
            case 5:strcpy(node->data.category,"Gut");break;
            case 6:strcpy(node->data.category,"Injury");break;
            case 7:strcpy(node->data.category,"Diabetes");break;
            case 8:strcpy(node->data.category,"Psychiatric");break;
            default:printf("INVALID OPTION!Please Choose Again b/w 1 to 8");break;        
        }
    }while(opt<1 || opt>8);
    do{
        printf("Select the patient's triage level:\n");
        printf("1 - Critical (Immediate life-threatening)\n");
        printf("2 - Urgent\n");
        printf("3 - Semi-urgent\n");
        printf("4 - Non-urgent\n");
        printf("5 - Normal\n");
        printf("Enter level (1-5):");
        scanf("%d",&opt);
        switch(opt){
            case 1:node->data.tlevel=1;break;
            case 2:node->data.tlevel=2;break;
            case 3:node->data.tlevel=3;break;
            case 4:node->data.tlevel=4;break;
            case 5:node->data.tlevel=5;break;
            default:printf("INVALID OPTION!Please Choose Again b/w 1 to 5");break;        
        }
    }while(opt<1 || opt>5);
    node->data.patientid=alot();
    if(dhead!=NULL){
        docnode=dhead;
        do{
            if(strcmp(docnode->data.specialization,node->data.category)==0){
                if(docnode->data.patients<minpat){ 
                    minpat=docnode->data.patients; 
                    mini=docnode;
                }
            }
            docnode=docnode->next;
        }while(docnode!=dhead);
    }  
    if(mini!=NULL){
        strcpy(node->data.docid, mini->data.doctorid);
        mini->data.patients++;          
        printf("\nPatient assigned to doctor %s.\n",mini->data.name);
        strcpy(node->data.status,"Admitted");
    }else{
        printf("\nWarning: No doctor found for category '%s'.\n",node->data.category);
        strcpy(node->data.status,"Pending Assignment");
        strcpy(node->data.docid, "0");
    }  
    
    struct triage *tnode=(struct triage*)malloc(sizeof(struct triage));
    tnode->data=node->data;
    if(thead==NULL){
        tnode->next=tnode;
        tnode->prev=tnode;
        thead=tnode;  
    }else{
        tnode->next=thead;
        tnode->prev=thead->prev;
        thead->prev->next=tnode;    
        thead->prev=tnode;
        thead=tnode;
    }

    node->left=NULL;
    node->right=NULL;
    if(root==NULL){
        root=node;
    }else{
        struct pnode *current=root;
        struct pnode *parent=NULL;
        while(current!=NULL){
            parent=current;
            if(node->data.patientid<current->data.patientid){
                current=current->left;
            }else if(node->data.patientid>current->data.patientid){
                current=current->right;
            }else{
                printf("Error: Duplicate Patient ID %d! BST insertion failed.\n",node->data.patientid);
                free(node);
                return;
            }
        }
        if(node->data.patientid<parent->data.patientid){
            parent->left=node;
        }else{
            parent->right=node;
        }
    }
    printf("\n--- Patient Admission Details ---\n");
    printpatient(node);
    printf("\nPatient admission complete. Press Enter to continue...");
    clrbfr();
    getchar();
    clrscr();
}