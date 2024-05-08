/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_flag_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:43:26 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 16:03:21 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static int	ft_strdup_flag_count(char *str)
{
	int		i;
	int		flag;
	int		cnt;

	i = 0;
	flag = 0;
	cnt = 0;
	while (str[i])
	{
		if (flag == 0 && (str[i] == '\'' || str[i] == '\"'))
			flag = str[i];
		else if (flag == str[i])
			flag = 0;
		else if (flag != str[i])
		{
			cnt++;
		}
		++i;
	}
	return (cnt);
}

char	*ft_strdup_flag(char *str)
{
	char	*ret;
	int		i;
	int		j;
	int		flag;

	ret = malloc(ft_strdup_flag_count(str) + 1);
	i = 0;
	flag = 0;
	j = 0;
	while (str[i])
	{
		if (flag == 0 && (str[i] == '\'' || str[i] == '\"'))
			flag = str[i];
		else if (flag == str[i])
			flag = 0;
		else if (flag != str[i])
		{
			ret[j] = str[i];
			++j;
		}
		++i;
	}
	ret[j] = 0;
	return (ret);
}
