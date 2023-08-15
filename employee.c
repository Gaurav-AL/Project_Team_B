#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
/*
    This function is to get the current date according to your system.
*/
struct tm getsysdate(){
    time_t sysdate;
    sysdate = time(NULL);
    return *localtime(&sysdate);
}

/*
    This Function is to add the Employee Details.
*/
void addEmployee(FILE *ptr){
    int emp_code,age,dob_day,dob_month,dob_year;
    char first_name[50],middle_name[50],last_name[50],address[50],emp_dept[50],emp_unit[50], gender[50],final_buffer[1200];
    printf("Enter Employee Code :");
    scanf("%d", &emp_code);
    printf("Enter Employee's First name :");
    scanf(" %[^\n]s",first_name);
    printf("Enter Employee's Middle name :");
    scanf(" %[^\n]s", middle_name);
    printf("Enter Employee's Last name :");
    scanf(" %[^\n]s", last_name);
    printf("Enter Employee's gender :");
    scanf(" %[^\n]s", gender);
    printf("Enter Employee's address :");
    scanf(" %[^\n]s", address);
    printf("Enter Employee's Department name :");
    scanf(" %[^\n]s", emp_dept);
    printf("Enter Employee's Unit name :");
    scanf(" %[^\n]s", emp_unit);
    printf("Enter Employee's Date of Birth day :");
    scanf("%d", &dob_day);
    printf("Enter Employee's Date of Birth month :");
    scanf("%d", &dob_month);
    printf("Enter Employee's Date of Birth year :");
    scanf("%d", &dob_year);
    int year_diff = getsysdate().tm_year+1900 - dob_year;
    if(dob_month > getsysdate().tm_mon+1 ) year_diff -= 1;
    age = year_diff;
    // Formatting the user input.
    sprintf(final_buffer , "%d | %s | %s | %s | %s | %s | %d/%d/%d | %d | %s | %s\n",emp_code,first_name,middle_name,last_name,gender,address,dob_day,dob_month,dob_year,age,emp_dept,emp_unit);
    ptr = fopen("file.txt","a");
    fputs(final_buffer, ptr);
    fclose(ptr);
}
/*
    Validating Whether Employee is in File or no
*/
bool isEmployeePresent(FILE *ptr, int emp_code){
    int emp_no_f;
    char *str_tok;
    ptr = fopen("file.txt","r");
    char getmessage[1000];
    while(fgets(getmessage, 1000, ptr) != NULL){
        str_tok = strtok(strdup(getmessage), " | ");
        emp_no_f = atoi(str_tok);
        if(emp_no_f == emp_code) {
            return true;
        }
    }
    fclose(ptr);
    return false;
}
/*
    This function is for deleting employee's record.
*/
void deleteEmployee(FILE *ptr, int emp_code){
    int emp_no_f, del_ren;
    char getmessage[1000];
    char *str_tok;
    ptr = fopen("file.txt" , "r");
    FILE *del_ptr = fopen("delete.txt", "w+");
    while(fgets(getmessage, 1000, ptr) != NULL){
        str_tok = strtok(strdup(getmessage), " | ");
        emp_no_f = atoi(str_tok);
        if(emp_no_f != emp_code) fputs(getmessage, del_ptr);
    }
    fclose(del_ptr);
    fclose(ptr);
    // This Message is for debugging 
    if (remove("file.txt") == 0) printf("Deleted successfully\n");
    del_ren = rename("delete.txt","file.txt");
    if(!del_ren) printf("successfully renamed delete.txt to file.txt\n");
}
/*
    This Function is for updating Employee's Data.
*/
void updateEmployee(FILE *ptr, int emp_code){
    if(!isEmployeePresent(ptr, emp_code)){
        printf("Employee Id is wrong or not present in the Database :(");
        return;
    }
    int age,dob_day,dob_month,dob_year;
    char first_name[50],middle_name[50],last_name[50],address[50],emp_dept[50],emp_unit[50],gender[50],final_buffer[1200];
    printf("Enter Employee's First name :");
    scanf(" %[^\n]s",first_name);
    printf("Enter Employee's Middle name :");
    scanf(" %[^\n]s", middle_name);
    printf("Enter Employee's Last name :");
    scanf(" %[^\n]s", last_name);
    printf("Enter Employee's gender :");
    scanf(" %[^\n]s", gender);
    printf("Enter Employee's address :");
    scanf(" %[^\n]s", address);
    printf("Enter Employee's Department name :");
    scanf(" %[^\n]s", emp_dept);
    printf("Enter Employee's Unit name :");
    scanf(" %[^\n]s", emp_unit);
    printf("Enter Employee's Date of Birth day :");
    scanf("%d", &dob_day);
    printf("Enter Employee's Date of Birth month :");
    scanf("%d", &dob_month);
    printf("Enter Employee's Date of Birth year :");
    scanf("%d", &dob_year);

    int year_diff = getsysdate().tm_year+1900 - dob_year;
    if(dob_month > getsysdate().tm_mon+1 ) year_diff -= 1;
    age = year_diff;
    
    sprintf(final_buffer , "%d | %s | %s | %s | %s | %s | %d/%d/%d | %d | %s | %s\n",emp_code,first_name,middle_name,last_name,gender,address,dob_day,dob_month,dob_year,age,emp_dept,emp_unit);
    deleteEmployee(ptr, emp_code);
    ptr = fopen("file.txt","a");
    fputs(final_buffer, ptr);
    fclose(ptr);
}
/*
    This Function is for displaying all employee's details.
*/
void displayAllEmployee(FILE *ptr){
    char getmessage[1000];
    ptr = fopen("file.txt","r");
    while(fgets(getmessage, 1000, ptr) !=  NULL){
        printf("%s", getmessage);
    }
    fclose(ptr);
}
/*
    This function is for displaying employee's data according to the employee code.
*/
void displayEmployeeInfo(FILE *ptr, int emp_code){
    int emp_no_f,flag = 0;
    char *str_tok;
    ptr = fopen("file.txt","r");
    char getmessage[1000];
    while(fgets(getmessage, 1000, ptr) != NULL){
        str_tok = strtok(strdup(getmessage), " | ");
        emp_no_f = atoi(str_tok);
        if(emp_no_f == emp_code) {
            flag = 1;
            printf("%s", getmessage);
            break;
        }
    }
    if(flag == 0) printf("No such Employee Found :(");
    fclose(ptr);
}

/*
    return true if the file specified by the filename exists
*/
bool file_exists(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    bool is_exist = false;
    if (fp != NULL)
    {
        is_exist = true;
        fclose(fp); // close the file
    }
    return is_exist;
}
/*
    This is main function.
*/
int main(){
    int choice,emp_code;
    char *filename = "file.txt";
    FILE *ptr;
    char file_header[1200] = "S.no | First Name | Middle Name | Last Name | Gender | Address | Date of Birth | Age | Emp. Dept | Emp. Unit\n";
    printf("Press \n1. Add a Employee\n2. Delete a Employee\n3. Update a Employee\n4. Display all Employee\n5. Display an Employee Info\n6. Exit");
    if(!file_exists(filename)){
        ptr = fopen(filename,"w+");
        fputs(file_header , ptr);
    }
    else{
        ptr = fopen(filename,"a");
    } 
    fclose(ptr);
    if(choice == 6) goto exit;
    do{
        printf("\nEnter Your choice : ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                addEmployee(ptr);
                break;
            case 2:
                printf("Enter Employee Code to be deleted :");
                scanf("%d",&emp_code);
                deleteEmployee(ptr, emp_code);
                break;
            case 3:
                printf("Enter Employee Code to be updated :");
                scanf("%d",&emp_code);
                updateEmployee(ptr, emp_code);
                break;
            case 4:
                displayAllEmployee(ptr);
                break;
            case 5:
                int emp_code;
                printf("Enter Employee Code to be displayed :");
                scanf("%d",&emp_code);
                displayEmployeeInfo(ptr, emp_code);
                break;
            default:
                printf("Wrong choice ! :(");
                break;
        }
    }while(choice != 6);
    exit:
}