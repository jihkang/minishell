/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:56:41 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 21:40:06 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_char(char *str, char *str2, char c)
{
	char	*ret;
	int		i;
	int		j;

	if (!str)
		return (ft_strdup(str2));
	ret = malloc(ft_strlen(str) + ft_strlen(str2) + 2);
	i = 0;
	while (*(str + i))
	{
		ret[i] = str[i];
		i++;
	}
	ret[i++] = c;
	j = 0;
	while (*(str2 + j))
	{
		ret[i + j] = str2[j];
		j++;
	}
	ret[i + j] = 0;
	return (ret);
}

int	lst_size(t_list	*lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	**convert_lst_2d(t_list *lst)
{
	char	**ret;
	t_env	*env;
	int		i;
	int		j;

	j = lst_size(lst);
	i = 0;
	ret = malloc(sizeof(char *) * (j + 1));
	while (i < j)
	{
		env = lst->content;
		lst = lst->next;
		ret[i] = ft_strjoin_char(env->key, env->value, '=');
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
