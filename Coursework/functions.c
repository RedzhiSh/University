#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"


// тази функция създава листа, като прочита информацията от бинарен файл и я зарежда в динамична структура
// връща указател към "корена"(върха) на листа, и не приема параметри
NODE* create_list(void)
{
    // отваряме файла с информацията в режим четене на бинарен файл
    FILE* fp = fopen("data.bin","rb");

    // проверяваме за проблем
    if(fp == NULL)
    {
        printf("Unable to open file!\n");
        return NULL;
    }

    // заделяме памет за един елемент структура
    NODE* root = (NODE*)malloc(sizeof(NODE));

    // проверяваме за проблем
    if(root == NULL)
    {
        printf("Memory allocation problem!\n");
        exit(2);
    }

    // временна променлива, в която ще запазваме прочетеното
    NODE temp;

    // прочитаме от бинарния файл информацията
    if(fread(&temp,sizeof(NODE),1,fp)!=1)
    {
        printf("File does not have entries!\n");
        return NULL;
    }

    // записваме прочетената информация в структурата, която е динамично заделене
    *root = temp;
    root->next = NULL;

    // с безкраен цикъл четем информация от бинарния файл, докато fread не даде стойност показваща достигането на края на файла
    for(;;)
    {
        if(fread(&temp,sizeof(NODE),1,fp)!=1)
        {
            printf("File loaded!\n");
            break;
        }

        // извикваме функцията за създаване на нова структура, която връща указател към нов "корен" (връх) на листа
        // приема като параметри: старият "корен", и информацията за структурата
        root = create_node(root,temp);
    }

    // след като сме прочели информацията от файла, го затваряме
    fclose(fp);

    // връщаме указател към "корена" (връха) на листа
    return root;
}

// тази функция създава нова структура и я добавя на върха на листа
// връща указател към "корена"(върха) на листа
// приема като параметри: старият "корен", и информацията за структурата
NODE* create_node(NODE* root,NODE temp)
{
    // заделяме памет за един елемент структура
    NODE* new_node = (NODE*)malloc(sizeof(NODE));

    // проверяваме за грешка
    if(new_node==NULL)
    {
        printf("Memory allocation problem!\n");
        exit(2);
    }

    // записваме подадената информация като параметри в структурата
    *new_node = temp;

    // правим този елемент да е новият връх
    new_node->next = root;

    // връщаме указател към новия връх
    return new_node;
}

// тази функция принтира на екрана целия лист
// приема като параметър указателя към корена на листа
void printList(NODE* root)
{
    if(root==NULL)
    {
        printf("List is empty!\n");
        return;
    }

    NODE* temp;
    printf("All entries:\n");

    // обхождаме целия лист
    for(temp=root;temp!=NULL;temp=temp->next)
    {
        printEntry(temp);
    }
}

// принтира елемент от листа
void printEntry(NODE* temp)
{
    printf("ID: %d; 3D form: %s; sides: %d; volume: %.2f; area of the base: %.2f;\n",temp->ID,temp->name,temp->sides,temp->volume,temp->area);
}


// чрез тази функция, потребителят може да промени/изтрие елемент в листа
// приема като параметър указателя към корена на листа
// връща указател към "корена"(върха) на листа
NODE* change_entry(NODE* root)
{
    if(root==NULL)
    {
        printf("List is empty!\n");
        return NULL;
    }

    // прочитаме от потребителя, кой елемент иска да промени/изтрие
    int id;
    printf("Enter the ID for a 3D form, which you want to edit/remove.\n");
    scanf("%d",&id);

    NODE* temp;
    NODE* pre;
    int flag = 1;

    // обхождаме целия лист, като запазваме кой е и предишния елемент
    for(temp=root,pre=root;temp!=NULL;pre=temp,temp=temp->next)
    {
        // ако намерим конкретния елемент
        if(temp->ID==id)
        {
            flag = 0;
            printf("Chosen entry:\n");
            printEntry(temp);
            break;
        }
    }
    // ако не сме намерили такъв елемент
    if(flag==1)
    {
        printf("There is no entries matching your input\n");
        // прекратяваме функцията
        return root;
    }

    // питаме потребителя дали иска да промени/изтрие
    printf("If you want to remove this entry, enter 0\n");
    printf("If you want to edit, enter another number: ");
    int choise;
    scanf("%d",&choise);

    // ако иска да изтрие
    if(choise==0)
    {
        // проверяваме дали иска да изтрие върха, само тогава предишният елемент и текущият ще съвпадат
        if(temp==root)
        {
            // запазваме елемента след върха
            root=root->next;

            // освобождаваме върха
            free(temp);

            // връщаме новия връх (функ. се прекратява тук)
            return root;
        }

        // свързваме елементите, които са от двете страни на елемента, който искаме да махнем
        pre->next=temp->next;

        // освобождаме елемента
        free(temp);

        // връщаме връха (функ. се прекратява тук)
        return root;
    }

    // ако потребителят иска да промени елемент, функцията няма да се е прекратила

    char name[50];
    int sides;
    float area, volume;

    // сканираме новата информация за елемента
    printf("If you do not want to change something, enter invalid input (non-positive for numbers or non-alpha for strings)\n");
    printf("Enter a new name: ");
    fflush(stdin);
    gets(name);
    printf("Enter number of sides: ");
    scanf("%d",&sides);
    printf("Enter volume: ");
    scanf("%f",&volume);
    printf("Enter area of the base: ");
    scanf("%f",&area);

    // променяме само валидно въведените стойности, които потребителят е въвел
    if(sides>0)
    {
        temp->sides = sides;
    }
    if(volume>0)
    {
        temp->volume = volume;
    }
    if(area>0)
    {
        temp->area = area;
    }

    // поверяваме дали символният низ съдържа само главни букви
    int i;
    flag = 1;
    for(i=0;i<strlen(name);i++)
    {
        if(!isupper(name[i]) && name[i] != ' ')
        {
            flag = 0;
            break;
        }
    }
    // ако е валиден, го запазваме
    if(flag==1)
    {
        strcpy(temp->name,name);
    }

    // връщаме връха
    return root;
}

// чрез тази функция, потребителят може да добави нов елемент в листа
// приема като параметър указателя към корена на листа
// връща указател към "корена"(върха) на листа
NODE * add_new(NODE* root)
{
    NODE new_node;

    printf("Enter unique ID: ");
    scanf("%d",&new_node.ID);

    // обхождаме целия лист за да проверим дали няма вече такав елемент
    NODE* temp;
    for(temp=root;temp!=NULL;temp=temp->next)
    {
        // ако има, прекратяваме функ. и връщаме върха на листа
        if(temp->ID==new_node.ID)
        {
            printf("There is the same number already!\n");
            return root;
        }
    }

    // прочитаме информацията за новия елемент
    printf("Enter a name: ");
    fflush(stdin);
    gets(new_node.name);
    printf("Enter number of sides: ");
    scanf("%d",&new_node.sides);
    printf("Enter volume: ");
    scanf("%f",&new_node.volume);
    printf("Enter area of the base: ");
    scanf("%f",&new_node.area);

    // проверяме дали е валидна информацията
    if(new_node.sides<=0 || new_node.volume<=0 || new_node.area<=0)
    {
        printf("Invalid input!\n");
        return root;
    }

    // поверяваме дали символните низове са валидни, като ги обхождаме
    int i;
    for(i=0;i<strlen(new_node.name);i++)
    {
        if(!isupper(new_node.name[i]) && new_node.name[i] != ' ')
        {
            printf("Invalid input!\n");
            return root;
        }
    }

    // извикваме функцията за създаване на нова структура, която връща указател към нов "корен" (връх) на листа
    // приема като параметри: старият "корен", и информацията за структурата
    root = create_node(root,new_node);
    return root;
}

// тази функция принтира елементи от листа базирано на някакъв избор на потребиеля (минимален обем на тяло)
// приема като параметър указателя към корена на листа
/*
    идеята на тази функ. е да разбере колко тела има с по-голям обем от посочения,
    да задели масив от съответния брой елементи (структури),
    да ги сортира според лицето на основата и принтира на екрана
*/
void viewByVolume(NODE* root)
{
    if(root==NULL)
    {
        printf("List is empty!\n");
        return;
    }

    float volume;
    printf("Enter a minimum volume: ");
    scanf("%f",&volume);

    NODE* temp;
    int counter = 0;
    // обхождаме целия лист и проверяме колко елемента има отговарящи на критерия
    for(temp=root;temp!=NULL;temp=temp->next)
    {
        if(temp->volume>volume)
        {
            counter++;
        }
    }
    if(counter==0)
    {
        printf("There are no entries matching!\n");
        return;
    }

    // заделяме динамичен масив
    NODE* arr = (NODE*)malloc(counter*sizeof(NODE));

    // проверяваме за проблем
    if(arr==NULL)
    {
        printf("Memory allocation error.\n");
        exit(3);
    }

    int i = 0;
    // запълваме масивът със съответните елементи
    for(temp=root;temp!=NULL;temp=temp->next)
    {
        if(temp->volume>volume)
        {
            arr[i++] = *temp;
        }
    }

    // помощна структура, която ще ни помогне за сортирането
    NODE change;
    int j;

    // сортираме масива според лицето на оновата (бъбъл сорт)
    for(i=0;i<counter;i++)
    {
        for(j=0;j<counter-1;j++)
        {
            if(arr[j].area < arr[j+1].area)
            {
                change = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = change;
            }
        }
    }
    // принтираме елементите
    for(i=0;i<counter;i++)
    {
        printEntry(&arr[i]);
    }

    // освобождаваме заделената памет
    free(arr);
}

// тази функция принтира тялото с най-много стени
// приема като параметър указателя към корена на листа
void viewBySides(NODE* root)
{
    if(root==NULL)
    {
        printf("List is empty!\n");
        return;
    }

    int sides = 0;

    NODE* temp;

    // обхождаме целия лист и търсим елемент с по-много стени
    for(temp=root;temp!=NULL;temp=temp->next)
    {
        // ако намерим ново по-голямо, го запазваме
        if(temp->sides > sides)
        {
            sides = temp->sides;
        }
    }

    // обхождаме целия лист и принтираме елементите с най-много стени
    printf("Forms with the most sides:\n");
    for(temp=root;temp!=NULL;temp=temp->next)
    {
        if(temp->sides == sides)
        {
            printEntry(temp);
        }
    }
}


// тази функция запазва на ново файла, като презаписва информацията ако има някакви промени
// приема като параметър указателя към корена на листа
void exitProgramm(NODE* root)
{
    // отваряме файла с информацията в режим записване на бинарен файл
    FILE* fp = fopen("data.bin","wb");

    // проверяваме за проблеми
    if(fp == NULL)
    {
        printf("Unable to open file!\n");
        exit(1);
    }

    NODE* temp;
    // обхождаме целия лист и записваме информацията му в бинарния файл
    while(root!=NULL)
    {
        temp= root;
        root=root->next;
        temp->next=NULL;
        fwrite(temp,sizeof(NODE),1,fp);
        free(temp);
    }

    // успех
    exit(0);
}
