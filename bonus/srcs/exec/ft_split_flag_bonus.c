/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_flag_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:39:07 by pjang             #+#    #+#             */
/*   Updated: 2023/01/05 14:39:17 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	set_flags(int *chk, int *cnt)
{
	*chk = 1;
	*cnt = 0;
}

static int	word_count(char *str, char c, int flag)
{
	int	chk;
	int	cnt;

	set_flags(&chk, &cnt);
	while (ft_isspace(*str) == c)
		++str;
	while (*str)
	{
		if (flag == 0 && (*str == '\'' || *str == '\"'))
		{
			flag = *str;
			cnt++;
		}
		else if (flag != 0 && flag == *str)
			flag = 0;
		else if (flag == 0 && chk == 1 && ft_isspace(*str) != c)
		{
			cnt++;
			chk = 0;
		}
		else if (flag == 0 && ft_isspace(*str) == c)
			chk = 1;
		++str;
	}
	return (cnt);
}

static int	ft_strichr_flag(char *str, char c)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (flag == 0 && (str[i] == '\'' || str[i] == '\"'))
			flag = str[i];
		else if (flag != 0 && str[i] == flag)
			flag = 0;
		if (flag == 0 && ft_isspace(str[i]) == c)
			return (i);
		++i;
	}
	return (i);
}

int	ft_split_flag_op(char **str, int j)
{
	if (j == 0)
	{
		*str = NULL;
		return (1);
	}
	return (0);
}

char	**ft_split_flag(char *str, char c)
{
	char	**spt;
	int		cnt;
	int		i;
	int		j;

	cnt = word_count(str, c, 0);
	spt = (char **)malloc(sizeof(char *) * (cnt + 2));
	i = 0;
	while (ft_isspace(*str) == c)
		++str;
	while (i < cnt)
	{
		j = ft_strichr_flag(str, c);
		if (ft_split_flag_op(&spt[i], j))
			break ;
		spt[i] = ft_substr(str, 0, j);
		while (ft_isspace(str[j]) == c)
			++j;
		str += j;
		++i;
	}
	spt[cnt] = NULL;
	return (spt);
}
