/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:55:54 by pjang             #+#    #+#             */
/*   Updated: 2022/12/27 15:26:32 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	swap2(char **str1, char **str2)
{
	char	*tmp;

	tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
}

void	sort_2d(char **ret, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < i)
		{
			if (ft_strcmp(ret[i], ret[j]) < 0)
				swap2(&ret[i], &ret[j]);
			j++;
		}
		i++;
	}
	i = 0;
}

void	print_sort_env(void)
{
	char	**ret;
	int		i;
	int		len;

	i = 0;
	len = lst_size(g_mini.env);
	ret = convert_lst_2d(g_mini.env);
	sort_2d(ret, len);
	while (i < len)
	{
		printf("declare -x %s\n", ret[i]);
		free(ret[i]);
		ret[i] = NULL;
		i++;
	}
	free(ret);
}

void	ft_export(char *str)
{
	if (str == NULL || *str == 0)
	{
		print_sort_env();
		return ;
	}
	replace_lst(&(g_mini.env), make_env(str));
}
