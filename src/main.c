#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "history.h"
#include "token.h"
#include "lexer.h"

int main(void)
{
    printf("=====================================\n");
    printf("          Shellforge\n");
    printf("   A Unix Style Shell written in C\n");
    printf("=====================================\n");

    token_list_t tokens;

    using_history();

    char *line;

    while (1)
    {
        line = readline("shellforge$ ");

        /* Ctrl+D */
        if (line == NULL)
        {
            printf("\nGoodbye!\n");
            break;
        }

        /* Exit command */
        if (strcmp(line, "exit") == 0)
        {
            free(line);
            printf("Exiting...\n");
            break;
        }

        /* Empty input */
        if (strlen(line) == 0)
        {
            free(line);
            continue;
        }

        /* History command */
        if (strcmp(line, "history") == 0)
        {
            HIST_ENTRY **hist = history_list();

            if (hist == NULL)
            {
                printf("history is empty.\n");
            }
            else
            {
                int count = 0;

                while (hist[count] != NULL)
                {
                    count++;
                }

                char *list[count];

                for (int i = 0; i < count; i++)
                {
                    list[i] = hist[i]->line;
                }

                print_history(list, count);
            }

            free(line);
            continue;
        }

        /* Add command to history */
        add_history(line);

        /* Lex the command */
        lexer(line, &tokens);

        /* Display tokens */
        token_print(&tokens);

        free(line);
    }

    return 0;
}
