#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "menu.h"
#include "main.h"

int error_Checking(int word_length)
{
    float integer_ERROR_CHECKING;

    if (scanf("%f", &integer_ERROR_CHECKING) != 1)
    {

        fprintf(stderr,"ERROR: Invalid word size\n");
        scanf("%*[^\n]");
        return -1;
    }
    else
    {
        word_length = integer_ERROR_CHECKING;
        if ((word_length != integer_ERROR_CHECKING) || (word_length < 0))
        {
            fprintf(stderr,"ERROR: Invalid word size\n");
            scanf("%*[^\n]");
            return -1;
        }
        else
        {
            scanf("%*[^\n]");
            return word_length;
        }
    }
    return -1;
}

/*Algoritm based on code found @ https://www.geeksforgeeks.org/c-program-bubble-sort-linked-list/ */
void swap(List *a, List *b)
{
    char *tempWord;
    int temp_num_of_references;
    int temp_order;

    tempWord = a->word;
    temp_num_of_references = a->num_of_references;
    temp_order = a->order;

    a->word = b->word;
    a->num_of_references = b->num_of_references;
    a->order = b->order;

    b->word = tempWord;
    b->num_of_references = temp_num_of_references;
    b->order = temp_order;
}

/*Algoritm based on code found @ https://www.geeksforgeeks.org/c-program-bubble-sort-linked-list/ */
void sortListAscending(List *head)
{
    int swapped;
    List *ptr1;
    List *lptr = NULL;

    if (head == NULL)
    {
        return;
    }

    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next_node != lptr)
        {
            if (strcmp(ptr1->word, ptr1->next_node->word) > 0)
            {
                swap(ptr1, ptr1->next_node);
                swapped = 1;
            }
            ptr1 = ptr1->next_node;
        }
        lptr = ptr1;
    } while (swapped);
}
/*Algoritm based on code found @ https://www.geeksforgeeks.org/c-program-bubble-sort-linked-list/ */
void sortListdescending(List *head)
{
    int swapped;
    List *ptr1;
    List *lptr = NULL;

    if (head == NULL)
    {
        return;
    }

    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next_node != lptr)
        {
            if (strcmp(ptr1->word, ptr1->next_node->word) < 0)
            {
                swap(ptr1, ptr1->next_node);
                swapped = 1;
            }
            ptr1 = ptr1->next_node;
        }
        lptr = ptr1;
    } while (swapped);
}
/*Algoritm based on code found @ https://www.geeksforgeeks.org/c-program-bubble-sort-linked-list/ */
void sortListDefault(List *head)
{
    int swapped;
    List *ptr1;
    List *lptr = NULL;

    if (head == NULL)
    {
        return;
    }

    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next_node != lptr)
        {
            if (ptr1->order > ptr1->next_node->order)
            {
                swap(ptr1, ptr1->next_node);
                swapped = 1;
            }
            ptr1 = ptr1->next_node;
        }
        lptr = ptr1;
    } while (swapped);
}

void printWordsMoreThan(List *head)
{
    List *temp = head;
    int word_Length = 0;
    printf("Enter the minimum word length: ");

    word_Length = error_Checking(word_Length);

    printf("\n");
    while ((temp != NULL) && (word_Length != -1))
    {
        if ((signed int)strlen(temp->word) > word_Length)
        {
            printf("%s (%d)\n", temp->word, temp->num_of_references);
        }
        temp = temp->next_node;
    }
    printf("\n");
}

void printWordsEqualTo(List *head)
{
    List *temp = head;
    int word_Length = 0;
    printf("Enter the word length: ");

    word_Length = error_Checking(word_Length);

    printf("\n");
    while ((temp != NULL) && (word_Length != -1))
    {
        if ((signed int)strlen(temp->word) == word_Length)
        {
            printf("%s (%d)\n", temp->word, temp->num_of_references);
        }
        temp = temp->next_node;
    }
    printf("\n");
}

void printWordsLessThan(List *head)
{
    List *temp = head;
    int word_Length = 0;
    printf("Enter the maximum word length: ");

    word_Length = error_Checking(word_Length);

    printf("\n");
    while ((temp != NULL) && (word_Length != -1))
    {
        if ((signed int)strlen(temp->word) < word_Length)
        {
            printf("%s (%d)\n", temp->word, temp->num_of_references);
        }
        temp = temp->next_node;
    }
    printf("\n");
}

void printLinkedList(List *head)
{
    List *temp;
    temp = head;

    while(temp != NULL)
    {
        printf("%s (%d)\n",temp->word,temp->num_of_references);
        temp = temp->next_node;
    }
    printf("\n");
}

/*Menu Display and  user selection */
int menu()
{
    int picked_Number;
    char ESC = 27;
    /*Menu */
    printf("%c[1m",ESC); printf("1."); printf("%c[0m",ESC); printf(" Display "); printf("%c[1m",ESC); printf("statistics"); printf("%c[0m",ESC); printf(" about the processed words.\n");
    printf("%c[1m",ESC); printf("2."); printf("%c[0m",ESC); printf(" Change "); printf("%c[1m",ESC); printf("sort"); printf("%c[0m",ESC); printf(" order.\n");
    printf("%c[1m",ESC); printf("3."); printf("%c[0m",ESC); printf(" List all the words by "); printf("%c[1m",ESC); printf("length"); printf("%c[0m",ESC);printf("\n");
    printf("%c[1m",ESC); printf("4."); printf("%c[0m",ESC); printf(" Write all the words found to a "); printf("%c[1m",ESC); printf("file"); printf("%c[0m",ESC); printf(".\n");
    printf("%c[1m",ESC); printf("9."); printf(" Exit"); printf("%c[0m",ESC); printf(" the program.\n");
    /*User selection */
    scanf("%d", &picked_Number);
    if ((picked_Number < 1) || (picked_Number > 9))
    {
        scanf("%*[^\n]");
        return 7; /*using 7 cause it is an invalid picked_Number */
    }
    else
    {
        return picked_Number;
    }
} /*End of menu  */

void menu_Options(int command, char *file_Name, int processed_Lines, int processed_Words, int words_Stored, int num_duplicate_words, List *List_head, FILE *fp)
{

    char ESC = 27;
    List *List_cursor = List_head;
    int word_Length = 0;
    char output_File_Name[32];
    char over_Write_Option[32];
    char *input;

    while (command != 9)
    {

        switch (command)
        {
        case 1:
        {
            printf("                       Input filename: %s\n", file_Name);
            printf("                      Lines processed: %4d\n", processed_Lines);
            printf("                      Words processed: %4d\n", processed_Words);
            printf("                      Duplicate words: %4d\n", num_duplicate_words);
            printf("          Words stored in linked list: %4d\n", words_Stored);
            printf("\n");
            break;
        }

        break;
        case 2:
            

            printf("%c[1m",ESC); printf("2a -"); printf("%c[0m",ESC); printf(" Sort ascending.\n");
            printf("%c[1m",ESC); printf("2b -"); printf("%c[0m",ESC); printf(" Sort descending.\n");
            printf("%c[1m",ESC); printf("2c -"); printf("%c[0m",ESC); printf(" Display in origonal file order (default).\n");
            
            input = malloc(16);       
            
            scanf("%s", input);
            scanf("%*[^\n]");
            
            if(!strcmp(input,"2a") || !strcmp(input,"a") )
            {
                sortListAscending(List_head);
                printLinkedList(List_head);
            }
            else if(!strcmp(input, "2b") || !strcmp(input, "b") )
            {
                sortListdescending(List_head);
                printLinkedList(List_head);
            }
            else if((!strcmp(input,"2c")) || (!strcmp(input, "c")) )
            {
                sortListDefault(List_head);
                printLinkedList(List_head);
            }
            else
            {
                fprintf(stderr,"invalid input\n");
            }
        
            free(input);
            break;
        case 3: /*word length sub menu*/

            printf("%c[1m",ESC); printf("3a -"); printf("%c[0m",ESC); printf(" List all the words found greater than a certain length.\n");
            printf("%c[1m",ESC); printf("3b -"); printf("%c[0m",ESC); printf(" List all of the words found less than a certain length.\n");
            printf("%c[1m",ESC); printf("3c -"); printf("%c[0m",ESC); printf(" List all the words found equal to a certain length.\n");
            
            
            input = malloc(16);       
            
            scanf("%s", input);
            scanf("%*[^\n]");
            if(!strcmp(input,"3a") || !strcmp(input,"a") )
            {
                printWordsMoreThan(List_head);
            }
            else if(!strcmp(input, "3b") || !strcmp(input, "b") )
            {
                printWordsLessThan(List_head);
            }
            else if((!strcmp(input,"3c")) || (!strcmp(input, "c")) )
            {
                printWordsEqualTo(List_head);
            }
            else
            {
                fprintf(stderr,"invalid input\n");
            }
            free(input);
            break;

        case 4:
            printf("Enter the filename: ");
            scanf("%s", output_File_Name);
            if (access(output_File_Name, F_OK) != -1)
            {
                /*file exists*/
                fprintf(stderr,"File Exists\n");
                printf("Do you wish to overwrite %s?", output_File_Name); printf("%c[1m",ESC); printf(" (y/n)"); printf("%c[0m",ESC); printf("\n");
                if ((scanf("%s", over_Write_Option) != 1) || ((tolower(over_Write_Option[0]) != 'n') && (tolower(over_Write_Option[0]) != 'y')))
                {
                    fprintf(stderr,"ERROR: Invalid input\n");
                    scanf("%*[^\n]");
                    break;
                }
                else if (tolower(over_Write_Option[0]) == 'n')
                {
                    break;
                }
            }

            fp = fopen(output_File_Name, "w");

            if (fp == NULL)
            {

                if (errno == 13)
                {
                    fprintf(stderr,"File %s cannot be opened. \n", output_File_Name);
                    break;
                }
                else
                {
                    perror("");
                    break;
                }
            }
            else
            {
                printf("Do you want to include the reference count?"); printf("%c[1m",ESC); printf(" (y/n)"); printf("%c[0m",ESC); printf("\n");

                input = malloc(16);

                scanf("%s", input);
                scanf("%*[^\n]");

                if ((!strcmp(input, "Y")) || (!strcmp(input, "y")))
                {
                    while (List_cursor != NULL)
                    {
                        if ((signed int)strlen(List_cursor->word) > word_Length)
                        {
                            fprintf(fp, "%s (%d)\n", List_cursor->word, List_cursor->num_of_references);
                        }
                        List_cursor = List_cursor->next_node;
                    }
                    List_cursor = List_head;
                    printf("%4d words written to %s\n", words_Stored, output_File_Name);
                }
                else if ((!strcmp(input, "N")) || (!strcmp(input, "n")))
                {
                    while (List_cursor != NULL)
                    {
                        fprintf(fp, "%s\n", List_cursor->word);
                        List_cursor = List_cursor->next_node;
                    }
                    List_cursor = List_head;
                    printf("%4d words written to %s\n", words_Stored, output_File_Name);
                }
                else
                {
                    fprintf(stderr,"ERROR: Invalid input\n");
                }

                fclose(fp);
                free(input);
            }
            break;

        case 9:
            break;

        default:
            fprintf(stderr,"ERROR: Invalid input\n");
            break;

        } /*End of swtich */
        command = menu();
    } /*End of while */
    printf("Goodbye. \n");
    /*free memory allocated */
    while (List_head != NULL)
    {
        List_cursor = List_head;
        List_head = List_head->next_node;
        free(List_cursor->word); /*frees word */
        free(List_cursor);       /*frees node */
    }
}