/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:55:40 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 15:45:55 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

int	sub_match(char *str, char *spt, char *ptn)
{
	if (str[0] == 0 && spt != NULL)
		return (0);
	else if (str[0] == 0 && spt == NULL)
		return (1);
	else if (str[0] != 0 && ptn[ft_strlen(ptn) - 1] == '*')
		return (1);
	return (0);
}

void	ft_match2(char *str, char **spt, int *i, int *j)
{
	while (str[(*j)] && spt[*i])
	{
		if (str[*j] == spt[*i][0] && \
			ft_strncmp(str + *j, spt[*i], ft_strlen(spt[*i])) == 0)
		{
			*j += ft_strlen(spt[*i]) - 1;
			*i += 1;
		}
		(*j)++;
	}
}

int	ft_match(char *str, char *ptn)
{
	char	**spt;
	int		i;
	int		j;

	spt = ft_split(ptn, '*');
	i = 0;
	j = 0;
	if (*ptn != '*')
	{
		if (ft_strncmp(str, spt[i], ft_strlen(spt[i])) != 0)
		{
			safety_dimention_free(spt);
			return (0);
		}
		j = ft_strlen(spt[i]) - 1;
		++i;
	}
	ft_match2(str, spt, &i, &j);
	i = sub_match(str + j, *(spt + i), ptn);
	safety_dimention_free(spt);
	return (i);
}
