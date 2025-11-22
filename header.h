#ifndef HEADER_H
#define HEADER_H

typedef struct doctorcred{
    char name[20];
    char gender;
    int age;
    char specialization[20];
    int experience;
    char email[30];
    int phone; 
    char password[20];
    char doctorid[11];
    int patients;
}dcred;

typedef struct patients{
    char name[20];
    int age;
    char gender;
    char ephone[15];
    int tlevel;
    int patientid;
    char category[20];
    char docid[11];
    char status[20];
}pcred;

struct dnode{
    struct dnode *prev;
    dcred data;
    struct dnode *next;
};

struct pnode{
    pcred data;
    struct pnode *left;
    struct pnode *right;
};

struct triage{
    struct triage *prev;
    pcred data;
    struct triage *next;
};

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#include<unistd.h>
#include<stdbool.h>

#define adminid "DSIII252"
#define adminpass "110099"

void clrscr();
void clrbfr();
void trnl(char *str);

void menu();
void add_patient();
void discharge_patient();
void search_patient();
void display_patient();

#endif 