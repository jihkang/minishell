/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_seq_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:32:54 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 16:05:01 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

int	is_seq(char *c)
{
	if (*c == '\"' || *c == '\'')
		return (*c);
	return (0);
}

int	is_seq1(char *c)
{
	if (*c == '(' || *c == ')')
		return (*c);
	return (0);
}

int	is_seq2(char *c)
{
	if (*c == '&' && *c && *(c + 1) == '&')
		return (*c);
	if (*c == '|')
	{
		if (*c && *(c + 1) == '|')
			return (OR);
		return (*c);
	}
	return (0);
}

int	is_seq3(char *c)
{
	if (*c == '<')
	{
		if (*c && *(c + 1) == '<')
			return (HEREDOC);
		return (STD_IN);
	}
	if (*c == '>')
	{
		if (*c && *(c + 1) == '>')
			return (STD_OUTA);
		return (STD_OUTT);
	}
	return (0);
}
