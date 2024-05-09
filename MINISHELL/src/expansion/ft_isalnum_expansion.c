/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum_expansion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:55:51 by marianfurni       #+#    #+#             */
/*   Updated: 2024/04/24 11:29:26 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isalnum_expansion(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z' )
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

void	handle_normal_char(t_expansion *exp)
{
	char	append[2];

	append[0] = **exp->cursor;
	append[1] = '\0';
	*exp->result = append_to_string(*exp->result, append);
	(*exp->cursor)++;
}
