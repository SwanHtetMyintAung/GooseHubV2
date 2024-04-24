
//libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "library/User.h"


int g_user_count = -1;
int g_login_id = -1;
int *ptr = &g_login_id;
struct AVL_node* current_user = NULL;
int main(){
    struct AVL_node* root = NULL;
    while(true){
        int l_option = -1;
        clear_screen();
        print_main_menu();
        scanf("%d",&l_option);
        /**************Options******************/
        //the user cann't be in login state
        if((l_option == 1) && (g_login_id == -1)){
            clear_screen();
            User temp_user;
            //registeration state
            bool r_state = registeration(&temp_user,g_user_count++,&root);
            if(!r_state) printf("Something Went Wrong In Registeration\n");
        }else if(l_option == 2){
            printf("Login Screen!\n");
            
        }else if(l_option == 3){
            printf("Logout!\n");
        }else if(l_option == 4){
            exit(0);
        }
    }



    return 0;
}