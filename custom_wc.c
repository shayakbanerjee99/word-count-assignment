#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LSIZ 128 
#define RSIZ 10 

/* Author: Shayak Banerjee
 * Date: 16th September 2020
 *
 * This program implements a word count function which finds the number of lines, words
 * and characters in one or more files
 *
 * The following arguments are supported
 * -l : display the number of lines used
 * -w : display the number of words used
 * -c : display the number of characters used
 *
 * The arguments can be used in combination with each other, or separately.
 *
 * Usage:-
 * suppose file hello.txt contains the following data
 * +----------+
 * | what is  |
 * | going on |
 * +----------+
 *
 * $ custom_wc hello.txt
 * filename: hello.txt
 * lines: 2
 * words: 3
 * chars: 16
 */

// linked list node used to store the filenames
struct Node{
    char *value;
    struct Node* next;
};

void addNode(struct Node *head, char *value);
void word_count(char* fname, int *lines, int *words, int *bytes);

// adds a note to the linked list
void addNode(struct Node *head, char *value){
    if(head->value == NULL){
        head->value = value;
    } else {
        struct Node *current = head;
        while(current->next != NULL)
            current = current->next;

        struct Node *temp = (struct Node*)malloc(sizeof(struct Node*));
        temp->value = value;
        current->next = temp;
    }
}

/*
 * @param fname   name of the file
 * @param lines   pointer to the location where number of lines have to be stored
 * @param words   pointer to the location where number of words have to be stored
 * @param bytes   pointer to the location where number of characters have to be stored
 */
void word_count(char* fname, int *lines, int *words, int *bytes){

    char line[RSIZ][LSIZ];
    FILE *fptr = NULL;
    int tot=0, i=0;

    // read the file data
    fptr = fopen(fname, "r");
    while(fgets(line[i], LSIZ, fptr)){
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }

    tot = i;
    int ch_count = 0, w_count = 0;
    for(i = 0; i < tot; i++){
        for(int j = 0; line[i][j] != '\0'; j++){
            if(line[i][j] == ' ')
                w_count++;
            ch_count++;
        }

        // newline
        w_count++;
        ch_count++;
    }

    w_count--;

    *lines = tot;
    *words = w_count;
    *bytes = ch_count;
}

// driver function
int main(int argc, char *argv[]){

    int l_flag = 0, w_flag = 0, c_flag = 0;

    struct Node* args = (struct Node*)malloc(sizeof(struct Node*));

    if(argc >= 2){
        // arguments are stored in flags
        // filenames are stored in the linked list with head 'args'
        for(int i = 1; i < argc; i++){
            if(strcmp(argv[i], "-l") == 0){
                l_flag = 1;
            } else if(strcmp(argv[i], "-w") == 0){
                w_flag = 1;
            } else if(strcmp(argv[i], "-c") == 0){
                c_flag = 1;
            } else if(argv[i][0] == '-'){
                if(argv[i][1] != 'w' || argv[i][1] != 'c' || argv[i][1] != 'l'){
                    printf("error: invalid argument -%c\n", argv[i][1]);
                    return 0;
                }
            } else {
                addNode(args, argv[i]);
            }
        }
    } else {
        printf("error: no arguments provided\n");
        return 0;
    }

    // if no argument was provided, then all are true
    if(l_flag == 0 && w_flag == 0 && c_flag == 0){
        l_flag = 1;
        w_flag = 1;
        c_flag = 1;
    }

    struct Node* current = args;
    while(current != NULL){
        
        int *lines = (int*)malloc(sizeof(int));
        int *words = (int*)malloc(sizeof(int));
        int *bytes = (int*)malloc(sizeof(int));
        word_count(current->value, lines, words, bytes);
        
        printf("filename: %s", current->value);

        if(l_flag == 1)
            printf("\nlines: %d", *lines);
        if(w_flag == 1)
            printf("\nwords: %d", *words);
        if(c_flag == 1)
            printf("\nchars: %d", *bytes);
        
        printf("\n\n");
        
        current = current->next;
    }

    return 0;
}
