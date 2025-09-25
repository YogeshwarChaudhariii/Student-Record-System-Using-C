#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////
//
// Structure : student
// Use : Holds information about student 
//
///////////////////////////////////////////////////////////////
struct student 
{
    char first_name[20];
    char last_name[20];
    char address[20];
    int roll_no;
    char Class[10];
    float per;
};

///////////////////////////////////////////////////////////////
//
// Functions Declaration 
//
///////////////////////////////////////////////////////////////
void AddStudent();
void StudentRecord();
void SearchStudent();
void DeleteStudent();

///////////////////////////////////////////////////////////////
//
// Function : AddStudent
// Use : Add information about student 
//
///////////////////////////////////////////////////////////////
void AddStudent() 
{
    char another;
    FILE *fp;
    struct student info;

    do {
        fp = fopen("student_info.txt", "ab"); // append binary mode

        if (fp == NULL) 
        {
            printf("Error opening file!\n");

            return;
        }

        printf("\n===== Add Student Information =====\n");

        printf("Enter First Name    : ");
        scanf("%s", info.first_name);
        printf("Enter Last Name     : ");
        scanf("%s", info.last_name);
        printf("Enter Roll Number   : ");
        scanf("%d", &info.roll_no);
        printf("Enter Class         : ");
        scanf("%s", info.Class);
        printf("Enter Address       : ");
        scanf("%s", info.address);
        printf("Enter Percentage    : ");
        scanf("%f", &info.per);

        fwrite(&info, sizeof(struct student), 1, fp);
        fclose(fp);

        printf("\nRecord Stored Successfully!\n");
        printf("Do You Want To Add Another Record? (y/n): ");
        fflush(stdin);
        scanf(" %c", &another);

    } while (another == 'y' || another == 'Y');
}

///////////////////////////////////////////////////////////////
//
// Function : StudentRecord
// Use : Add records about student 
//
///////////////////////////////////////////////////////////////
void StudentRecord() 
{
    FILE *fp;
    struct student info;

    fp = fopen("student_info.txt", "rb");   // Reading binary mode

    if (fp == NULL) 
    {
        printf("Error opening file!\n");
        return;
    }

    printf("\n===== Student Records =====\n");

    while (fread(&info, sizeof(struct student), 1, fp)) 
    {
        printf("\nName       : %s %s", info.first_name, info.last_name);
        printf("\nRoll No    : %d", info.roll_no);
        printf("\nClass      : %s", info.Class);
        printf("\nAddress    : %s", info.address);
        printf("\nPercentage : %.2f", info.per);
        printf("\n-----------------------------\n");
    }

    fclose(fp);
    getch();
}

///////////////////////////////////////////////////////////////
//
// Function : SearchStudent
// Use : Search records about student 
//
///////////////////////////////////////////////////////////////
void SearchStudent() 
{
    FILE *fp;
    struct student info;
    int roll_no, found = 0;

    fp = fopen("student_info.txt", "rb");

    if (fp == NULL) 
    {
        printf("Error opening file!\n");
        return;
    }

    printf("\n===== Search Student Record =====\n");

    printf("Enter Roll Number: ");
    scanf("%d", &roll_no);

    while (fread(&info, sizeof(struct student), 1, fp)) 
    {
        if (info.roll_no == roll_no) 
        {
            printf("\nName       : %s %s", info.first_name, info.last_name);
            printf("\nRoll No    : %d", info.roll_no);
            printf("\nClass      : %s", info.Class);
            printf("\nAddress    : %s", info.address);
            printf("\nPercentage : %.2f", info.per);
            printf("\n-----------------------------\n");

            found = 1;
            break;
        }
    }

    if (!found) 
    {
        printf("\nRecord Not Found!\n");
    }
    fclose(fp);
    getch();
}

///////////////////////////////////////////////////////////////
//
// Function : DeleteStudent
// Use : delete records of student 
//
///////////////////////////////////////////////////////////////
void DeleteStudent() 
{
    FILE *fp, *ftemp;
    struct student info;
    int roll_no, found = 0;

    fp = fopen("student_info.txt", "rb");
    ftemp = fopen("temp.txt", "wb");

    if (fp == NULL || ftemp == NULL) 
    {
        printf("Error opening file!\n");
        return;
    }

    printf("\n===== Delete Student =====\n");
    printf("Enter Roll Number: ");
    scanf("%d", &roll_no);

    while (fread(&info, sizeof(struct student), 1, fp)) 
    {
        if (info.roll_no == roll_no) 
        {
            found = 1;
            printf("\nRecord with Roll No %d Deleted Successfully!\n", roll_no);
        } 
        
        else 
        {
            fwrite(&info, sizeof(struct student), 1, ftemp);
        }
    }

    fclose(fp);
    fclose(ftemp);

    remove("student_info.txt");
    rename("temp.txt", "student_info.txt");

    if (!found) 
    {
        printf("\nRecord Not Found!\n");
    }
    getch();
}

///////////////////////////////////////////////////////////////
//
// Entry Point Function (main)
//
///////////////////////////////////////////////////////////////
int main() 
{
    int choice = 0;

    while (choice != 5) 
    {
        printf("\n===== STUDENT DATABASE MANAGEMENT SYSTEM =====\n");

        printf("1. Add Student Record\n");
        printf("2. Student Record\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1: AddStudent(); break;
            case 2: StudentRecord(); break;
            case 3: SearchStudent(); break;
            case 4: DeleteStudent(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid Choice!\n");
        }
    }
    return 0;
}
