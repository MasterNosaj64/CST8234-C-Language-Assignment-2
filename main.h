#ifndef HEADER_FILE
#define HEADER_FILE

#define MAX_SIZE 64

typedef struct ListNode
{
    char *word;
    int num_of_references;
    struct ListNode *next_node;
    int order;

} List;

int menu();
void menu_Options(int command, char *filename, int processedLines, int processedWords, int wordStored, int num_duplicate_words, List *List_head, FILE *fp);

#endif