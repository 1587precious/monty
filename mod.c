#include "monty.h"

/**
 * compute_modulus - Computes the rest of the division of the second
 * top element of the stack by the top element of the stack.
 * @stack_head: Pointer to the stack head
 * @line_number: Line number in the Monty bytecode file
 * Return: No return value
 */
void compute_modulus(stack_t **stack_head, unsigned int line_number)
{
    stack_t *current;
    int stack_size = 0, result;

    current = *stack_head;

    while (current)
    {
        current = current->next;
        stack_size++;
    }

    if (stack_size < 2)
    {
        fprintf(stderr, "L%d: can't mod, stack too short\n", line_number);
        perform_cleanup_and_exit();
    }

    current = *stack_head;

    if (current->n == 0)
    {
        fprintf(stderr, "L%d: division by zero\n", line_number);
        perform_cleanup_and_exit();
    }

    result = current->next->n % current->n;
    current->next->n = result;
    *stack_head = current->next;
    free(current);
}

/**
 * perform_cleanup_and_exit - Closes file, frees memory, and exits with failure status
 */
void perform_cleanup_and_exit()
{
    fclose(bus.file);
    free(bus.content);
    free_stack(*stack_head);
    exit(EXIT_FAILURE);
}
