#include "shell.h"

/**
 * check_env - checks if the typed variable is an env variable
 *
 * @h: head of linked list
 * @in: input string
 * @var_env: var_env structure
 * Return: no return
 */
void check_env(r_var **h, char *in, data *var_env)
{
    int row, chr, j, lval;
    char **_envr;

	/* Get the environment variables from the var_env structure */
    _envr = var_env->_environ;
    for (row = 0; _envr[row]; row++)
    {
        for (j = 1, chr = 0; _envr[row][chr]; chr++)
        {
            if (_envr[row][chr] == '=')
            {
                /* Calculate the length of the environment variable's value */
                lval = _strlen(_envr[row] + chr + 1);
                /* Add the environment variable's value to the linked list */
                add_rvar_node(h, j, _envr[row] + chr + 1, lval);
                return;
            }

            if (in[j] == _envr[row][chr])
                j++;
            else
                break;
        }
    }

    for (j = 0; in[j]; j++)
    {
        /* If the character is a space, tab, semicolon, or newline, stop checking */
        if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
            break;
    }

    /* Add an empty node to the linked list */
    add_rvar_node(h, j, NULL, 0);
}


/**
 * check_vars - check if the typed variable is $$ or $?
 *
 * @h: head of the linked list
 * @in: input string
 * @st: last status of the Shell
 * @var_env: var_env structure
 * Return: the number of characters processed
 */
int check_vars(r_var **h, char *in, char *st, data *var_env)
{
    int i, lst, lpd;

    /* Calculate the length of the last status string and the process ID string */
    lst = _strlen(st);
    lpd = _strlen(var_env->pid);

    for (i = 0; in[i]; i++)
    {
        /* Check if the current character is '$' */
        if (in[i] == '$')
        {
            if (in[i + 1] == '?')
            {
                /* If it's "$?", add the last status to the linked list */
                add_rvar_node(h, 2, st, lst);
                i++;
            }
            else if (in[i + 1] == '$')
            {
                /* If it's "$$", add the process ID to the linked list */
                add_rvar_node(h, 2, var_env->pid, lpd);
                i++;
            }
            else if (in[i + 1] == '\n' || in[i + 1] == '\0' || in[i + 1] == ' ' || in[i + 1] == '\t' || in[i + 1] == ';')
            {
                /* If it's followed by certain characters, add an empty node to the linked list */
                add_rvar_node(h, 0, NULL, 0);
            }
            else
            {
                /* Otherwise, check if it's an environment variable and add it to the linked list */
                check_env(h, in + i, var_env);
            }
        }
    }

    /* Return the number of characters processed */
    return (i);
}


/**
 * replaced_input - replaces string into variables
 *
 * @head: head of the linked list
 * @input: input string
 * @new_input: new input string (replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
    r_var *indx;
    int i, j, k;

	/* Initialize the index to the head of the linked list */
    indx = *head;
    for (j = i = 0; i < nlen; i++)
    {
		/* Check if the current character is a variable */
        if (input[j] == '$')
        {
			/* If variable length and value length are both zero */
            if (!(indx->len_var) && !(indx->len_val))
            {
				/* Copy the character as is */
                new_input[i] = input[j];
                j++;
            }
			/* If variable length is not zero and value length is zero */
            else if (indx->len_var && !(indx->len_val))
            {
				/* Skip the variable in the original input */
                for (k = 0; k < indx->len_var; k++)
                    j++;
					/* Decrement the index to overwrite the '$' in the new input */
                	i--;
            }
            else
            {
				/* If variable length and value length are both non-zero */
                for (k = 0; k < indx->len_val; k++)
                {
					/* Copy the variable value into the new input */
                    new_input[i] = indx->val[k];
                    i++;
                }
				/* Skip the variable in the original input */
                j += (indx->len_var);
                i--;
            }
			/* Move to the next variable in the linked list */
            indx = indx->next;
        }
        else
        {
			/* Copy the character as is */
            new_input[i] = input[j];
            j++;
        }
    }

    return (new_input);
}


/**
 * rep_var - calls functions to replace string into vars
 *
 * @input: input string
 * @var_envbase: var_env structure
 * Return: replaced string
 */
char *rep_var(char *input, data *var_envbase)
{
    r_var *head, *indx;
    char *status, *new_input;
    int olen, nlen;

    /* Convert the status into a string */
    status = aux_itoa(var_envbase->status);

    /* Initialize a linked list to store variable replacements */
    head = NULL;

    /* Check and store variable replacements */
    olen = check_vars(&head, input, status, var_envbase);

    /* If no variable replacements, return the original input */
    if (head == NULL)
    {
        free(status);
        return (input);
    }

    indx = head;
    nlen = 0;

    while (indx != NULL)
    {
        /* Calculate the new length of the input after replacements */
        nlen += (indx->len_val - indx->len_var);
        indx = indx->next;
    }

    nlen += olen;

    /* Allocate memory for the new input */
    new_input = malloc(sizeof(char) * (nlen + 1));

    /* Null-terminate the new input string */
    new_input[nlen] = '\0';

    /* Replace variables in the input and store it in new_input */
    new_input = replaced_input(&head, input, new_input, nlen);

    /* Free the original input */
    free(input);

    /* Free the status string */
    free(status);

    /* Free the linked list of variable replacements */
    free_rvar_list(&head);

    return (new_input);
}
