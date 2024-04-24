#ifndef UTILITIES_H
#define UTILITIES_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STR_LEN 50

//declaration
int size_of_array(char *array);
bool validate_email(char *email);
bool validate_password(char *password);
void print_main_menu();
void clear_screen();
bool strings_are_equal(char *destination,char *target);

//get the actual length of the array
int size_of_array(char *array){
    int size =0;
    //loop through the array until it see "\0"
    for(int i=0;i<STR_LEN;i++){
        if(array[i]=='\0') break;
        size++;
    }
    return size;
}

//to validate email
bool validate_email(char *email){
    //get the total length of the array
    int size = size_of_array(email);
    //temp variable for conditions
    int at_sign = 0;
    int dot_sign = 0;
    for(int i=0;i<=size;i++){
        if(email[i] == '@'){
            //at sign can't be at last or near it "example@google.com"
            if(i < size - 3){
                at_sign = i;
            }
        }else if(email[i] == '.'){
            //dot can't be at the last place and can't be next to at sign
            if(i != size && at_sign < i && !(i == at_sign+1)){
                dot_sign = i;
            }
        }
    }
    if(at_sign && dot_sign){
        return true;
    }else{
        printf("The Email Format Is NOT Correct!\n");
        return false;
    }
}
bool validate_password(char *password){
    //small letter-> 97-122 , capital letter -> 65-90
    //special character -> 33-46 ,58-64 , 91-96 , 123 ,126

    //variable to check EACH requirements for validation
    bool is_valid = false;
    int has_small_letter =0;
    int has_capital_letter =0;
    int has_number =0;
    int has_special_character =0;

    //get the length of the array
    int length_of_pass = size_of_array(password);
    // if it's less than six , the passsword is weak
    if(length_of_pass >= 6){
        //loop through every element in array
        for(int i=0;i<length_of_pass;i++){
            //check their respective ascii value
            if(password[i] > 96 && password[i] < 123){
                has_small_letter = 1;
            }else if(password[i] > 64 && password[i] < 91){
                has_capital_letter = 1;
            }else if(password[i] > 47 && password[i] < 58){
                has_number = 1;
            }else{
                has_special_character =1;
            }
        }
    }else{
        printf("Password Must Be At Least 6 characters Long\n");
    }
    //if only all requirements are fulfilled , this code will work
    if(has_capital_letter && has_small_letter && has_number && has_capital_letter && has_special_character){
        printf("your password is strong!\n");
        //printf("%d ; %d ; %d ; %d \n", has_capital_letter ,has_small_letter , has_number, has_special_character);
        is_valid=true;
    //if the requirements aren't fulfilled , the warning message and requirements to strong password will show up
    }else{
        is_valid = false;
        printf("Password Must Be Have At Least 1 small letter , 1 CAPITAL LETTER , 1 Number And 1 Special Character Such As : !@#$%%^&*\n");
    }
    return is_valid;
}
//this is a function to print option as main menu
void print_main_menu(){
    printf("****WELCOME TO MY SYSTEM****\n");
    printf("Enter 1 to Register.\n");
    printf("Enter 2 to Login.\n");
    printf("Enter 3 to Logout.\n");
    printf("Enter 4 to Exit.\n");
    printf("Enter an Option:");
}
//to clear the screen via terminal
void clear_screen(){
    int x = system("clear");
    if(x == -1){
        system("cls");
    }
}
//return true if the two inputs are the same string
bool strings_are_equal(char *destination,char *target){
    //get the length of the two strings
    int first = size_of_array(destination);
    int second = size_of_array(target);

    if(first != second) return false;
    //loop through every chracter . the counter for first OR second dones't matter since they'll be the same
    for(int i=0;i<first;i++){
        if(destination[i] != target[i]) return false;
    }
    //this will trigger only if the above "return" were not triggered
    return true;
}


#endif