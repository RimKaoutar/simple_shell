#include "shell.h"

/**
 * _listlen - Returns the length of a singly linked list
 * @node: The head node of the list
 * 
 * Description: Traverses the list by iterating the next pointer
 * and counting the nodes until reaching the tail (null next).
 * 
 * Return: The number of nodes in the list
*/
size_t _listlen(const list_t *node)
{
	size_t i = 0;

	while (node)
	{
		node = node->next;
		i++;
	}
	return (i);
}

/**
 * list_to_vector - Converts a singly linked list to a vector of strings
 * @head: Head node of linked list
 * 
 * Description: Counts list length to determine vector size.
 * Loops through list copying string data into new vectors.
 * 
 * Return: Pointer to new vector or NULL on failure
 */

char **list_to_vector(list_t *head)
{
	list_t *node = head;
	char **str_list, *str;
	size_t i = _listlen(head), j = 0;

	if (!head || !i)
		return (NULL);

	str_list = malloc(sizeof(char *) * (i + 1));

	if (!str_list)
		return (NULL);
	i = 0;
	while (node)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			while (j < i)
			{
				free(str_list[j++]);
			}
			free(str_list);
			return (NULL);
		}
		str = _strcpy(str, node->str);
		str_list[i] = str;
		node = node->next;
		i++;
	}
	str_list[i] = NULL;
	return (str_list);
}

/**
 * print_list - Prints the elements of a linked list
 * @head: Pointer to the head of the linked list
 * 
 * Description: Traverses list iterating next pointer.
 * Prints node number and string value using helper functions.
 * 
 * Return: The number of nodes printed
 */

size_t print_list(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		_puts(change_base(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		if (head->str)
		{
			_puts(head->str);
		} else
		{
			_puts("(nil)");

		}
		_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * node_str_start - Finds the first node in a linked list that matches
 * prefix and character criteria
 * @head: Pointer to head of linked list
 * @prefix: String prefix to match
 * @c: Character to match or -1 to ignore
 *
 * Description: Traverses list iterating next pointer. Checks
 * each node string using starts_with() against prefix. Returns
 * first match that also passes character check.
 * 
 * Return: Pointer to matching node or NULL
 */

list_t *node_str_start(list_t *head, char *prefix, char c)
{
	char *ptr = NULL;

	while (head)
	{
		ptr = starts_with(head->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
		{
			return (head);
		}
		head = head->next;
	}
	return (NULL);
}

/**
 * get_node_index - Gets the index of a node in a linked list
 * @head: Pointer to head of linked list
 * @node: Node to find index of
 * 
 * Description: Traverses list iterating next pointer.
 * Returns index of first match with given node.
 * 
 * Return: Index of node or -1 if not found
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
		{
			return (i);
		}
		head = head->next;
		i++;
	}
	return (-1);
}
