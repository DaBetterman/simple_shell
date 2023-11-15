#include "shell.h"

/**
 * add_rvar_node - Adds a variable node at the end of a linked
 *					list of type r_var.
 * @head: A pointer to the head of the linked list.
 * @lvar: Length of the variable.
 * @val: Value of the variable.
 * @lval: Length of the value.
 * Return: A pointer to the updated head of the linked list.
 */
r_var *add_rvar_node(r_var **head, int lvar, char *val, int lval)
{
	r_var *new, *temp;

	/*Allocate memory for the new variable node*/
	new = malloc(sizeof(r_var));
	if (new == NULL)
		return (NULL);

	/*Set the values for the new node*/
	new->len_var = lvar;
	new->val = val;
	new->len_val = lval;

	/*Initialize the next pointer of the new node to NULL*/
	new->next = NULL;

	/*Set 'temp' to the head of the linked list*/
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
 * free_rvar_list - Frees a linked list of type r_var.
 * @head: A pointer to the head of the linked list.
 * Return: No return.
 */
void free_rvar_list(r_var **head)
{
	r_var *temp;
	r_var *curr;

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
