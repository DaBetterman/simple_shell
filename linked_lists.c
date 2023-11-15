#include "shell.h"

/**
 * add_sep_node_end - Adds a separator found at the end of
 *						a linked list of type sep_list.
 * @head: A pointer to the head of the linked list.
 * @sep: The separator to be added (`;`, `|`, or `&`).
 * Return: A pointer to the updated head of the linked list.
 */
sep_list *add_sep_node_end(sep_list **head, char sep)
{
	sep_list *new, *temp;

	/*Allocate memory for the new separator node*/
	new = malloc(sizeof(sep_list));
	if (new == NULL)
		return (NULL);

	/*Set the separator for the new node*/
	new->separator = sep;
	new->next = NULL;
	temp = *head;

	/*If the linked list is empty*/
	if (temp == NULL)
	{
		/*Update the head to point to the new node*/
		*head = new;
	}
	else
	{
		/*Traverse the linked list to find the last node*/
		while (temp->next != NULL)
			temp = temp->next;

		/*Add the new node at the end of the linked list*/
		temp->next = new;
	}

	/*Return the updated head of the linked list*/
	return (*head);
}

/**
 * free_sep_list - Frees a linked list of type sep_list.
 * @head: A pointer to the head of the linked list.
 * Return: No return.
 */
void free_sep_list(sep_list **head)
{
	sep_list *temp;
	sep_list *curr;

	/*Check if the input pointer 'head' is not NULL*/
	if (head != NULL)
	{
		/*Initialize 'curr' with the head of the linked list*/
		curr = *head;

		/*Traverse the linked list and free each node*/
		while ((temp = curr) != NULL)
		{
			/*Move to the next node*/
			curr = curr->next;

			/*Free the current node*/
			free(temp);
		}
		/*Set 'head' to NULL to indicate that the linked list is empty*/
		*head = NULL;
	}
}

/**
 * add_line_node_end - Adds a command line at
 *						the end of a linked list of type line_list.
 * @head: A pointer to the head of the linked list.
 * @line: The command line to be added.
 * Return: A pointer to the updated head of the linked list.
 */
line_list *add_line_node_end(line_list **head, char *line)
{
	line_list *new, *temp;

	/*Allocate memory for the new command line node*/
	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);

	/*Set the command line for the new node*/
	new->line = line;
	new->next = NULL;
	temp = *head;

	/*If the linked list is empty*/
	if (temp == NULL)
	{
		/*Update the head to point to the new node*/
		*head = new;
	}
	else
	{
		/*Traverse the linked list to find the last node*/
		while (temp->next != NULL)

			/*Add the new node at the end of the linked list*/
			temp = temp->next;
		temp->next = new;
	}

	/*Return the updated head of the linked list*/
	return (*head);
}

/**
 * free_line_list - Frees a linked list of type line_list.
 * @head: A pointer to the head of the linked list.
 * Return: No return.
 */
void free_line_list(line_list **head)
{
	line_list *temp;
	line_list *curr;

	/*Check if the input pointer 'head' is not NULL*/
	if (head != NULL)
	{

		/*Initialize 'curr' with the head of the linked list*/
		curr = *head;

		/*Traverse the linked list and free each node*/
		while ((temp = curr) != NULL)
		{
			/*Move to the next node*/
			curr = curr->next;
			/*Free the current node*/
			free(temp);
		}
		/*Set 'head' to NULL to indicate that the linked list is empty*/
		*head = NULL;
	}
}
