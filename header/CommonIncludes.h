#pragma once
#define STR_LEN 50
#define PAS_LEN 20
#define MAX_RECORD 10

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