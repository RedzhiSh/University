#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

// прототип на функция
void navigate_user(NODE* root);

int main()
{
    // тази функция създава листа, като прочита информацията от бинарен файл и я зарежда в динамична структура
    NODE* root = create_list();

    // тази функция подпомага т.нар. user experience
    navigate_user(root);

    // връщаме 0 за успех
    return 0;
}

void navigate_user(NODE* root)
{
    printf("Welcome!\n");

    int option;
    // безкраен цикъл
    for(;;)
    {
        printf("\nMenu:\n");
        printf("Option 1: view the list\n");
        printf("Option 2: add figure\n");
        printf("Option 3: edit/delete figure\n");
        printf("Option 4: show list of figures by volume\n");
        printf("Option 5: show list of figures by number of sides\n");
        printf("Option 0: save changes and exit the program\n");
        printf("Enter your option: ");

        scanf("%d",&option);

        if(option==1)
        {
            // тази функция принтира на екрана целия лист
            printList(root);
        }
        else if(option == 2)
        {
            // чрез тази функция, потребителят може да добави нов елемент в листа
            root = add_new(root);
        }
        else if(option==3)
        {
            // чрез тази функция, потребителят може да промени/изтрие елемент в листа
            root = change_entry(root);
        }
        else if(option==4)
        {
            // тази функция принтира елементи от листа базирано на някакъв избор на потребиеля (обем на тяло)
            viewByVolume(root);
        }
        else if(option==5)
        {
            // тази функция принтира телата с най много стени
            viewBySides(root);
        }
        else if(option==0)
        {
            // тази функция запазва на ново файла, като презаписва информацията ако има някакви промени
            exitProgramm(root);
        }
        else
        {
            printf("Incorrect input! Try again!\n");
        }
    }
}
