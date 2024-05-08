/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:33:09 by pjang             #+#    #+#             */
/*   Updated: 2023/01/05 13:23:16 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\r')
		return (32);
	return (c);
}

char	*valid_token_list2(t_prs *prs, int flag)
{
	char	*value;
	char	*str1;
	char	*str2;
	t_list	*temp;

	temp = prs->redirect;
	while (temp)
	{
		value = (char *)temp->content;
		if (!flag && is_seq2(value))
			flag = 1;
		else if (flag && is_seq2(value))
		{
			str1 = ft_strjoin("\'", value);
			str2 = ft_strjoin(str1, "\'");
			safety_free((void **)&str1);
			return (str2);
		}
		else
			flag = 0;
		if (flag && !temp->next)
			return (ft_strdup("\'newline\'"));
		temp = temp->next;
	}
	return (NULL);
}

int	valid_token_list(t_prs *prs)
{
	char	*valid;

	valid = valid_token_list2(prs, 0);
	if (valid)
	{
		g_mini.continue_flag = 1;
		put_error2("syntax error near unexpected token", valid);
		safety_free((void **)&valid);
		return (1);
	}
	return (0);
}

int	get_max_redirection_count(void)
{
	int		res;
	t_tkn	*tkn;
	t_list	*temp;

	temp = g_mini.token;
	res = 0;
	while (temp)
	{
		tkn = (t_tkn *)temp->content;
		if (tkn->idx == STD_IN || tkn->idx == STD_OUTT || \
			tkn->idx == HEREDOC || tkn->idx == STD_OUTA)
			res++;
		temp = temp->next;
	}
	return (res);
}

int	get_max_command_count(void)
{
	int		res;
	t_tkn	*tkn;
	t_list	*temp;

	temp = g_mini.token;
	res = 0;
	while (temp)
	{
		tkn = (t_tkn *)temp->content;
		if (tkn->idx == COMMAND)
			res++;
		temp = temp->next;
	}
	return (res);
}
