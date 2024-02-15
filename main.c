#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include "main.h"

/*
Student: Jason Waid & Muhammadu Ahmadu
Student #:040912687 & 040776232
Program: Computer Engineering Technology
Course: CST8234 - Assign2
Date: August 9th 2019
Updates: 
            All words are added to the list by default
            Implemented sub-Menu for sorting the Linked List
            Implemented sub-menu for printing words of a certain length
            Implemented code for printing number of duplicates in statistics
            Implemented code for printing number of duplicates per word
*/

/************************************************************************************************** 
 * Code creates a node, returns a pointer to the node
*/

List *create_Node(char *word_buffer, int num_accepted_words)
{
    List *node = malloc(sizeof(List));
    node->word = malloc(sizeof(word_buffer));
    node->num_of_references = 1;
    node->order = num_accepted_words;
    strcpy(node->word, word_buffer);
    return node;
}
/************************************************************************************************** 
 * Code searches the list for duplicates, returns true or false
*/
int search_List(char *word_buffer, List *List_head)
{
    List *temp = List_head;
    while (temp != NULL)
    {
        if ((strcmp(word_buffer, temp->word)) == 0)
        {
            temp->num_of_references++;
            return 1; /* true */
        }
        if (temp->next_node == NULL)
        {
            return 0;
        }
        else
        {
            temp = temp->next_node;
        }
    }
    return 0; /* false */
}
/************************************************************************************************** 
 * Code Inserts Nodes at the correct location, using insertion sort
 * updates the pointer of the neighboring node
*/

int main(int argc, char **argv)
{

    char file_buffer[256];
    char *input_buffer = file_buffer;
    char word_buffer[64];

    List *List_head = NULL;
    List *List_cursor = List_head;

    int word_length_MAX = 0;
    int i;
    char *wordlength_ERRORCHECKING = argv[2];
    float wordlength_INT_ERROR_CHECK;
    int word_size;
    int num_accepted_words = 0;
    int num_words_processed = 0;
    int num_spaces = 0;
    int num_lines_processed = 0;
    int num_duplicate_words = 0;
    FILE *fp;

    if (argc >= 2)
    {
        if (argc == 3)
        {

            for (i = 0; wordlength_ERRORCHECKING[i]; i++)
            {
                if (isalpha(wordlength_ERRORCHECKING[i]))
                {
                    fprintf(stderr, "ERROR: %s is not a valid word size\n", wordlength_ERRORCHECKING);
                    return 0;
                }
            }

            sscanf(argv[2], "%f", &wordlength_INT_ERROR_CHECK);
            word_length_MAX = wordlength_INT_ERROR_CHECK;

            if ((wordlength_INT_ERROR_CHECK != word_length_MAX) || (wordlength_INT_ERROR_CHECK < 0))
            {
                fprintf(stderr, "ERROR: %s is not a valid word size\n", wordlength_ERRORCHECKING);
                return 0;
            }
        }

        else if (argc > 3)
        {
            fprintf(stderr, "Too many Arguments. Max is 3\n");
            return 0;
        }

        fp = fopen(argv[1], "r");

        if (fp == NULL)
        {
            if (errno == 2)
            {
                fprintf(stderr, "File %s not found. Terminating.\n", argv[1]);
                return 0;
            }
            else if (errno == 13)
            {
                fprintf(stderr, "File %s cannot be opened. Terminating\n", argv[1]);
                return 0;
            }
            else
            {
                perror("");
                return 0;
            }
        }
    }
    else
    {
        fprintf(stderr, "<filename> missing.");
        fprintf(stderr, "\nUsage: ./assign2 <filename>\n");
        return 0;
    }

    while (!feof(fp))
    {
        fgets(file_buffer, 255, fp);
        word_size = 0;
        num_lines_processed++;
        input_buffer = file_buffer;

        /*converts to lower case*/
        for (i = 0; input_buffer[i]; i++)
        {
            if ((isalpha(input_buffer[i]) && (isupper(input_buffer[i]))))
            {
                input_buffer[i] = tolower(input_buffer[i]);
            }
        }

        while (sscanf(input_buffer, "%s", word_buffer) != EOF)
        {
            num_spaces = 0;
            word_size = 0;

            /*Logic for counting spaces before word*/
            for (i = 0; isspace(input_buffer[i]); i++)
            {
                num_spaces++;
            }

            /*determines # of bytes used by word*/
            for (i = 0; word_buffer[i]; i++)
            {
                word_size++;
            }
            if (word_size >= word_length_MAX)
            {
                if (List_cursor == NULL)
                {
                    num_accepted_words++;
                    List_cursor = create_Node(word_buffer, num_accepted_words);
                    List_head = List_cursor;
                }
                else if (search_List(word_buffer, List_head) == 0)
                {
                    num_accepted_words++;
                    List_cursor->next_node = create_Node(word_buffer, num_accepted_words);
                    List_cursor = List_cursor->next_node;
                }
                else
                {
                    num_duplicate_words++;
                }
            }
            num_words_processed++;
            input_buffer = input_buffer + word_size + num_spaces; /*makes up for spaces and word size when incrementing buffer*/
        }
    }
    printf("\n");
    fclose(fp);
    menu_Options(menu(), argv[1], num_lines_processed, num_words_processed, num_accepted_words, num_duplicate_words, List_head, fp);
    return 0;
}