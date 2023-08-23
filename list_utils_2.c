#include "shell.h"

/**
 * add_node_start - Adds a new node to the start of a linked list
 * @head: Double pointer to the head of the list
 * @str: String for new node
 * @num: Number for new node
 * 
 * Description: Allocates and initializes new node. Sets
 * next pointer and updates head pointer.
 * 
 * Returns: Pointer to new node or NULL on failure
 */
list_s *add_node_start(list_s **head, const char *str, int num)
{
	list_s *new_node;

	if (!head)
		return (NULL);

	new_node = malloc(sizeof(list_s));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_s));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	new_node->next = *head;
	*head = new_node;
	return (new_node);
}

/**
 * add_node_end - Adds a new node to the end of a linked list
 * @head: Pointer to pointer of head node
 * @str: String for new node
 * @num: Number for new node
 * 
 * Description: Allocates and initializes new node. Traverses
 * list to find tail and links new node, updating tail.
 * 
 * Returns: Pointer to new node or NULL
 */
list_s *add_node_end(list_s **head, const char *str, int num)
{
	list_s *new_tail, *head_copy;

	if (!head)
		return (NULL);

	head_copy = *head;
	new_tail = malloc(sizeof(list_s));

	if (!new_tail)
		return (NULL);

	_memset((void *)new_tail, 0, sizeof(list_s));
	new_tail->num = num;

	if (str)
	{
		new_tail->str = _strdup(str);

		if (!new_tail->str)
		{
			free(new_tail);
			return (NULL);
		}
	}

	if (head_copy)
	{
		while (head_copy->next)
		{
			head_copy = head_copy->next;
		}
		head_copy->next = new_tail;
	}
	else
	{
		*head = new_tail;
	}
	return (new_tail);
}

/**
 * print_list_str - Prints the strings of nodes in a linked list
 * @head: Pointer to head of linked list
 * 
 * Description: Traverses the list iterating the next pointer.
 * Prints the string field of each node, or "(nil)" if null.
 * 
 * Return: Number of nodes printed
 */
size_t print_list_str(const list_s *head)
{
	size_t i = 0;

	while (head)
	{
		if (head->str)
		{
			_puts(head->str);
		}
		else
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
 * delete_node_at_index - Deletes a node at a given index in a linked list
 * @head: Pointer to head of the linked list
 * @index: Index of the node to delete
 * 
 * Description: Traverses list to find node at index. Handles
 * edge case of head node. Unlinks and frees target node.
 * 
 * Returns: 1 if node deleted, 0 otherwise
 */
int delete_node_at_index(list_s **head, unsigned int index)
{
	unsigned int i = 0;
	list_s *current_node, *prev_node;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		current_node = *head;
		*head = (*head)->next;
		free(current_node->str);
		free(current_node);
		return (1);
	}
	current_node = *head;
	while (current_node)
	{
		if (i == index)
		{
			prev_node->next = current_node->next;
			free(current_node->str);
			free(current_node);
			return (1);
		}
		i++;
		prev_node = current_node;
		current_node = current_node->next;
	}
	return (0);
}

/**
 * free_list - Frees the memory of a linked list
 * @head: Double pointer to the head of the list
 * 
 * Description:
 * Traverses the list and frees the string and node memory
 * for each node. Sets the head to NULL after freeing all nodes.
 * 
 * Return: Nothing.
 */
void free_list(list_s **head)
{
	list_s *node, *next_node, *head_copy;

	if (!head || !*head)
		return;

	head_copy = *head;
	node = head_copy;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head = NULL;
}
