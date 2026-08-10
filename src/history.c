#include <stdio.h>
#include "history.h"

void print_history(char *list[], int count)
{
    if (count == 0)
    {
        printf("history is empty.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        printf("%2d %s\n", i + 1, list[i]);
    }
}
