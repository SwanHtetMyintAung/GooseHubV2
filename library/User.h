#ifndef USER_C
#define USER_C

struct AVL_node;
//libraries
#include "AVLtree.h"
#include "utilities.h"

//symbolic constants

#define PAS_LEN 20
#define MAX_USER 7
#define MAX_RECORD 10
#define DEFAULT_TOKEN 500


//definition for structures
typedef struct Transition_Record{
    int record_id;
    char date[100];
    char record[100];
}Transition_Record;

typedef struct User{
    int suspend;
    int id;
    int token;
    char name[STR_LEN];
    char email[STR_LEN];
    char password[PAS_LEN];
    struct Transition_Record transition_db[MAX_RECORD];
}User;


//declarations
bool registeration(User *user,int totalUser,struct AVL_node** root);
struct AVL_node* AVL_tree_insert(struct AVL_node *root,User *entity);
struct AVL_node* AVL_tree_search_by_email(struct AVL_node* root,char* email);
bool login(struct AVL_node* root,int *g_id);


//definitions

//takes in adress of user object where you want the data to be saved
bool registeration(User *user,int totalUser,struct AVL_node** root){
    // if(user != NULL){
    //     printf("This user already has data or faulty initialization!\n");
    //     return false;
    // }
    //not suspended
    user->suspend = 0;
    user->id = totalUser+1;
    //default token
    user->token = DEFAULT_TOKEN;
    //name
    printf("Enter Your Name:");
    scanf("%s",user->name);
    //email
    bool isEmail = false;
    while(!isEmail){
        printf("Enter Your Email:");
        scanf("%s",user->email);
        isEmail = validate_email(user->email);
        //if the input email wasn't valid , it will ask user to input again
        if(!isEmail){
            continue;
        }
        struct AVL_node* existingUser = AVL_tree_search_by_email((*root),user->email);
        if(existingUser != NULL){
            printf("The Email Already Exist\n");
            isEmail = false;
            continue;
        }
    }
    //password
    bool isPassword = false;
    while(!isPassword){
        printf("Enter Your Password:");
        scanf("%s",user->password);
        isPassword = validate_password(user->password);
        //if the function returns false , this will restart the loop
        if(!isPassword) continue;
    }
    (*root) = AVL_tree_insert(*root,user);

    return true;
}

bool login(struct AVL_node* root,int *g_id){
    char *l_email , *l_password;
    struct AVL_node* existingUser = (struct AVL_node*)malloc(sizeof(struct AVL_node));
    //email handling
    bool isEmailValid = false;
    while(!isEmailValid){
        printf("Enter Your Email:");
        scanf("%s",l_email);
        //check the format of email
        isEmailValid = validate_email(l_email);
        //if the input email wasn't valid , it will ask user to input again
        if(!isEmailValid) continue;
        existingUser = AVL_tree_search_by_email(root,l_email);
        if(existingUser == NULL){
            printf("The Email Doesn't Exist\n");
            isEmailValid = false;
            continue;
        }
        printf("%s",existingUser->user.email);
    }
    //password handling
    bool isPasswordValid = false;
    while((existingUser) && (!isPasswordValid)){
        printf("Enter Your PassworValidd:");
        scanf("%s",l_password);
        isPasswordValid = validate_password(l_password);
        //if the function returns false , this will restart the loop
        if(!isPasswordValid) continue;
        char *passwordInDb = existingUser->user.email;
        bool passwordIsCorrect = strings_are_equal(l_password,passwordInDb);
        //if the password didn't match
        if(!passwordIsCorrect) continue;
        //pass the user object and global id variable to the dashboard function
    }
    
    return true;
}

// void dashboard(struct AVL_node* node , int *g_id){
//     // while(true){
//     //     //ask prompt

//     //     /*********Options*********/
//     //     //1. to check account status
//     //     //2. transfer point to other account
//     //     //3.
//     // }
// }



#endif