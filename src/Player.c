#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_MUSIC_SIZE 100
#define MAX_NAME_SIZE 20

void add(int *top, char **Music_names);
void list(int const *top, char **Music_names);
void clear(int *top, char **Music_names);
void del(int *top, char **Music_names);
void quit(int *top, char *Music_names);
void move(int *current_Music, char **Music_names);
void play(int const *current_Music, char **Music_names);
void next(int *current_Music);
void prev(int const *top, int *current_Music);
void load(int *top, char **Music_names);
void save(int const (*top), char const **Music_names);

int main() {
    int N; scanf("%d",&N);
    int top=-1;
    int current_Music = -1;
    char *Music_names[MAX_MUSIC_SIZE];

    for(int i=0; i<N; i++) add(&top,(char **)Music_names);
    current_Music = top;
    int N1; scanf("%d",&N1);
    for(int i=0; i<N1; i++) {
        char *command = malloc(sizeof(char) * 5);
        scanf(" %s",command);
        if(strcmp(command,"add") == 0) add(&top, (char **) &Music_names);
        else if(strcmp(command,"list") == 0) list(&top,(char **)&Music_names);
        else if(strcmp(command,"clear") == 0) clear(&top,(char **)Music_names);
        else if(strcmp(command,"quit") == 0) quit(&top, (char *)Music_names);
        else if(strcmp(command,"del") == 0) del(&top, (char **)Music_names);
        else if(strcmp(command,"move") == 0) move(&current_Music, (char **)Music_names);
        else if(strcmp(command,"play") == 0) play(&current_Music, (char **)Music_names);
        else if(strcmp(command,"next") == 0) next(&current_Music);
        else if(strcmp(command,"prev") == 0) prev(&top, &current_Music);
        else if(strcmp(command,"load") == 0) load(&top, (char **)Music_names);
//        else if(strcmp(command,"save") == 0) save(&list_index,&top, (char **) &Music_list, (char **)Music_names);  // *
        else if(strcmp(command,"save") == 0) save(&top, (char const **)Music_names);
        free(command);

    }
//    for(int i=0; i<top; i++) printf("%c ",Music_list[0][i]);

    return 0;
}

void add(int *top, char **Music_names) {
    (*top)++;
    char tmp[100];
    scanf(" %s",tmp);
    Music_names[*top] = (char *)malloc(strlen(tmp)+1);
    strcpy(Music_names[*top],tmp);
}

void list(int const *top, char **Music_names) {
    printf("LinkedList [ ");
    for(int i=(*top); i>=0; i--) printf("%s ",Music_names[i]);
    printf("]\n");
}

void clear(int *top, char **Music_names) {
    while((*top) > -1) free(Music_names[(*top)--]);       //(*top)--;  //*top--; --> Warning | Expression result unused |
    printf("LinkedList is cleared!\n");
}

void del(int *top, char **Music_names) {
    char tmp[100];
    int del_point=0;
    char *Music_stack[(*top)+1];
    scanf(" %s", tmp);
    for(int i=0; i<=(*top); i++) {
        if(strcmp(Music_names[i], tmp) == 0) {
            del_point = i;
        }
    }
    int k = 0;
    for(int i=0; i<=(*top); i++) {
        if(i == del_point) continue;
        else {
            Music_stack[k] = Music_names[i];
            k++;
        }
    }
    (*top)--;
    for(int i=0; i<=(*top); i++) {
        Music_names[i] = (char *)malloc(sizeof(char) * strlen(Music_stack[i]));         //*
        strcpy(Music_names[i],Music_stack[i]);
    }
}

void quit(int *top, char *Music_names) {
    clear(top, (char **)Music_names);
    printf("quit!\n");
}

void move(int *current_Music, char **Music_names) {
    int move_index;
    char *temp;
    scanf("%d",&move_index);
    temp = Music_names[move_index-1];
    Music_names[move_index-1] = Music_names[*current_Music];
    Music_names[*current_Music] = temp;
    *current_Music = (move_index-1);
}

void play(int const *current_Music, char **Music_names) {
    printf("%s is now playing!\n", Music_names[*current_Music]);
}

void next(int *current_Music) {
    if(*current_Music > 0) (*current_Music)--;
}

void prev(int const *top, int *current_Music) {
    if(*current_Music < (*top)) (*current_Music)++;
}

void load(int *top, char **Music_names) {
    char *name;
    int i=0;
    char *file_name = (char *)malloc(sizeof(char) * 10);
    scanf("%s", file_name);
    FILE* fp = fopen(file_name,"r");
    do {
        name = (char *)malloc(sizeof(char) * MAX_NAME_SIZE);
        fgets(name,MAX_NAME_SIZE,fp);
        (i)++;
    } while(strcmp(name,"\0") != 0);
    (*top) = i-2;
    printf("%d\n",(*top));
    fclose(fp);
    FILE* fp1 = fopen(file_name,"r");
    for(int k=0; k<=(*top); k++) {
        name = (char *)malloc(sizeof(char) * MAX_NAME_SIZE);
        fgets(name,MAX_NAME_SIZE,fp1);
        name[strlen(name)-1] = '\0';
        Music_names[k] = name;
        printf("%s\n",Music_names[k]);
    }
    fclose(fp1);
}

void save(int const (*top), char const **Music_names) {
    char *file_name = (char *)malloc(sizeof(char) * 10);
    scanf("%s", file_name);
    FILE* fp = fopen(file_name,"w");
    for(int i=0; i<=(*top); i++) {
        fputs(Music_names[i], fp);
        fputs("\n", fp);
    }
    free(file_name);
    fclose(fp);
}


