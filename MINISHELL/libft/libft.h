/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:28:03 by mafurnic          #+#    #+#             */
/*   Updated: 2024/04/16 14:24:16 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>
# include <termios.h>
# include <sys/ioctl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1042
# endif

typedef struct s_list
{
	int				content;
	int				index;
	struct s_list	*next;
}	t_list;

t_list			*ft_lstnew(int content);
int				ft_lstsize(t_list *head);
void			ft_lstadd_front(t_list **stack, t_list *newnode);
void			ft_lstadd_back(t_list	**stack, t_list *newnode);
t_list			*ft_lstlast(t_list *head);
char			*ft_itoa_base(int n, int base);
int				ft_atoi_base(const char *str, int base);
int				ft_isspace(int c);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
unsigned long	ft_strlen(const char *s);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
void			ft_bzero(void *s, size_t n);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			*ft_memset(void *s, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_atoi(const char *nptr);
char			*ft_strdup(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(const char *s1, const char *set);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_uitoa(unsigned int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(const char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
int				ft_putnbr_base_fd(unsigned long long n, int base,
					int fd, int uppercase);
void			ft_putnbr_unsigned_fd(unsigned int n, int fd);
int				ft_printf(const char *str, ...);
void			handle_specifier(char specifier, va_list args, int *char_count);
void			handle_char(va_list args, int *char_count);
void			handle_string(va_list args, int *char_count);
void			handle_pointer(va_list args, int *char_count);
void			handle_int(va_list args, int *char_count);
void			handle_uint(va_list args, int *char_count);
void			handle_hex_lower(va_list args, int *char_count);
void			handle_hex_upper(va_list args, int *char_count);
void			handle_percent(int *char_count);
char			*ft_substr(char const *s, unsigned int start, size_t len);
unsigned long	ft_strlen(const char *s);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_isnum(const char *str);
int				ft_atoi_overflow(const char *str, int *error);
long			ft_atoi_long(const char *nptr);
char			*ft_strtok(char *str, const char *delim);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strndup(const char *s, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
size_t			ft_strcspn(const char *s, const char *reject);
size_t			ft_strnlen(const char *s, size_t maxlen);

#endif