/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:01:49 by mafurnic          #+#    #+#             */
/*   Updated: 2023/09/15 13:20:58 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*#include <stdio.h>
#include <fcntl.h>   // For open
#include <unistd.h>  // For close

// Assuming you've included or declared ft_putchar_fd above

int main(void) {
    // Test 1: Write to standard output
    printf("Standard Output: ");
    ft_putchar_fd('A', 1);
    printf("\n");

    // Test 2: Write to standard error
    fprintf(stderr, "Standard Error: ");
    ft_putchar_fd('B', 2);
    fprintf(stderr, "\n");

    // Test 3: Write to a file
    int fd = open("testfile.txt", O_WRONLY | O_CREAT, 0644);
    if (fd != -1) {
        ft_putchar_fd('C', fd);
        close(fd);
        printf("Character written to testfile.txt\n");
    } else {
        perror("Error opening testfile.txt");
    }

    // (Optional) Test 4: Write to an invalid file descriptor
    // ft_putchar_fd('D', 9999); // Note: This may produce unwanted behaviors

    return 0;
}
*/
