/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:34:46 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 15:42:24 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_to_value(t_list **list, int i)
{
	int		start;
	char	*news;
	t_env	*res;
	t_tkn	*tkn;
	t_list	*temp;

	temp = *list;
	tkn = (t_tkn *)temp->content;
	if (i < 0 || tkn->value[i] == '\0')
		return ;
	if (tkn->value[i + 1] == '?')
	{
		news = change_env_exit_code(tkn, i);
		safety_free((void **)&tkn->value);
		tkn->value = news;
		return ;
	}
	start = i + 1;
	res = get_env_value(g_mini.env, tkn, start, i);
	if (!res)
		return ;
	news = get_new_value(&res, tkn, i);
	safety_free((void **)&tkn->value);
	tkn->value = news;
}

int	get_total_count_dalar(void)
{
	int		i;
	int		res;
	t_tkn	*tkn;
	t_list	*temp;

	i = 0;
	res = 0;
	temp = g_mini.token;
	while (temp)
	{
		tkn = (t_tkn *)temp->content;
		while (tkn->value[i])
		{
			if (tkn->value[i] == '$')
				res++;
			i++;
		}
		temp = temp->next;
	}
	return (res);
}

int	get_count_dalar(t_tkn *tkn)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	while (tkn->value[i])
	{
		if (tkn->value[i] == '$')
			res++;
		i++;
	}
	return (res);
}

char	*change_env_exit_code(t_tkn *tkn, int i)
{
	char	*str1;
	char	*str2;
	char	*str3;
	char	*str4;
	char	*new;

	str1 = ft_substr(tkn->value, 0, i);
	str2 = ft_substr(tkn->value, i + 2, ft_strlen(tkn->value));
	if (g_mini.exit_code >= 512)
		str4 = ft_itoa(g_mini.exit_code / 256);
	else
		str4 = ft_itoa(g_mini.exit_code);
	str3 = ft_strjoin(str1, str4);
	new = ft_strjoin(str3, str2);
	safety_free((void **)&str1);
	safety_free((void **)&str2);
	safety_free((void **)&str3);
	safety_free((void **)&str4);
	return (new);
}
