#include "shell.h"

/**
 * set_zeros - Sets all elements of an array to zero
 * @array: The target array
 * @size: Number of elements in the array
 * 
 * Description: Iterates through the array and sets each
 * element to zero.
 * 
 * Return: Nothing
*/
void set_zeros(unsigned int *array, size_t size)
{
	size_t i = 0;

	while (i < size)
	{
		array[i] = 0;
		i++;
	}
}

/**
 * set_nulls - Sets all elements of a string array to null terminators
 * @array: The target string array
 * @size: Number of elements in the array
 * 
 * Description: Iterates through the array and sets each
 * element to the null terminator character.
 *
 * Return: Nothing
 */

void set_nulls(char *array, size_t size)
{
	size_t i = 0;

	while (i < size)
	{
		array[i] = '\0';
		i++;
	}
}
