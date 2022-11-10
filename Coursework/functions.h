#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

// структурата на един елемент/запис
typedef struct NODE {
    int ID;
    char name[50];
    int sides;
    float volume;
    float area;

    // указател към следващия елемент
    struct NODE* next;
} NODE;

// прототипите на функциите, съдържащи се в functions.c
NODE* create_list(void);
NODE* create_node(NODE* root,NODE temp);
void printList(NODE* root);
void printEntry(NODE* temp);
NODE* change_entry(NODE* root);
NODE * add_new(NODE* root);
void viewByVolume(NODE* root);
void viewBySides(NODE* root);
void exitProgramm(NODE* root);

#endif // FUNCTIONS_H_INCLUDED
