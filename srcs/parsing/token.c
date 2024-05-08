/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 09:35:43 by pjang             #+#    #+#             */
/*   Updated: 2023/01/05 14:12:06 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_mini	g_mini;

void	set_token(t_tkn *token, int idx, char *value)
{
	token[0].idx = idx;
	token[0].value = value;
}

int	set_logical_pipe_token(char *buf, int i)
{
	if (is_seq2(buf) == AND)
	{
		set_token(&g_mini.tkn[i], AND, ft_strdup(buf));
		return (1);
	}
	else if (is_seq2(buf) == OR)
	{
		set_token(&g_mini.tkn[i], OR, ft_strdup(buf));
		return (1);
	}
	else if (is_seq2(buf) == PIPE)
	{
		set_token(&g_mini.tkn[i], PIPE, ft_strdup(buf));
		return (1);
	}
	return (0);
}

char	*get_token_value(t_list *temp, char *buf, int i)
{
	char	*res;
	char	*str;
	char	*str2;
	char	**split;

	res = NULL;
	str = ft_strjoin(buf, " ");
	str2 = (char *)temp->next->content;
	split = ft_split_token(str2, ' ');
	res = ft_strjoin(str, split[0]);
	if (split[1])
	{
		set_token(&g_mini.tkn[i + 1], COMMAND, ft_substr(str2, \
			ft_strlen(split[0]) + 1, ft_strlen(str2) - ft_strlen(split[0])));
	}
	safety_dimention_free(split);
	safety_free((void **)&str);
	return (res);
}

int	set_redirection_token(t_list *temp, char *buf, int i)
{
	char	*str;

	if (temp->next)
		str = get_token_value(temp, buf, i);
	else
		str = ft_strdup(buf);
	if (is_seq3(buf) == STD_IN || is_seq3(buf) == STD_OUTT)
	{
		set_token(&g_mini.tkn[i], is_seq3(buf), str);
		return (1);
	}
	else if (is_seq3(buf) == HEREDOC || is_seq3(buf) == STD_OUTA)
	{
		set_token(&g_mini.tkn[i], is_seq3(buf), str);
		return (2);
	}
	safety_free((void **)&str);
	return (0);
}

void	set_command_token(t_list **temp, char *buf, int *i)
{
	char	*next;
	char	*str;
	t_list	*lst;

	lst = *temp;
	if (lst->next)
	{
		next = (char *)lst->next->content;
		if (is_quote(next))
			str = get_token_value(lst, buf, 0);
		else
			str = buf;
	}
	else
		str = buf;
	set_token(&g_mini.tkn[*i], COMMAND, ft_strdup(str));
	if (ft_strlen(str) != ft_strlen(buf))
	{
		*i += 1;
		temp[0] = temp[0]->next;
		safety_free((void **)&str);
	}
}
