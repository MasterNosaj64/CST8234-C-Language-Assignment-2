#ifndef MENU_HEADER_FILE
#define MENU_HEADER_FILE
#include "main.h"
int menu();
void menu_Options(int command, char *filename, int processedLines, int processedWords, int wordStored, int num_duplicate_words, List *list_head, FILE *fp);

#endif