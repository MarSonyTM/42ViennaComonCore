#include <stdio.h>
#include "ft_printf.h"

int main(int ac, char **av)
{
    char input[256];

    while (1)
    {
        printf("Enter a string: ");
        fgets(input, sizeof(input), stdin);

        printf("ft_printf output: ");
        ft_printf("%s", input);


        printf("printf output: ");
        printf("%s", input);
    }
    return 0;
}