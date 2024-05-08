/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_astric_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:17:13 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 16:03:05 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

int	count_new_cmd(char **cmd, char	**astric)
{
	int		count_1;
	int		count_2;

	count_1 = 0;
	count_2 = 0;
	while (cmd[count_1])
		count_1++;
	while (astric[count_2])
		count_2++;
	return (count_1 + count_2 - 1);
}

char	**get_new_cmd(char **cmd, char	**aster_tok, int idx, int count)
{
	int		i;
	int		j;
	int		k;
	char	**new_cmd;

	i = -1;
	j = 0;
	k = 1;
	new_cmd = (char **)malloc(sizeof(char *) * (count + 1));
	while (++i < count)
	{
		if (i < idx)
			new_cmd[i] = ft_strdup(cmd[i]);
		else if (i >= idx && aster_tok[j])
			new_cmd[i] = ft_strdup(aster_tok[j++]);
		else if (cmd[idx + k])
			new_cmd[i] = ft_strdup(cmd[idx + k++]);
	}
	new_cmd[i] = NULL;
	return (new_cmd);
}

void	exec_asterisk(char **cmd, int idx)
{
	char	*tmp;
	char	**aster_tok;
	char	**new_cmd;
	int		count;

	tmp = ft_astric(cmd[idx]);
	aster_tok = ft_split_flag(tmp, ' ');
	free(tmp);
	tmp = NULL;
	count = count_new_cmd(cmd, aster_tok);
	new_cmd = get_new_cmd(cmd, aster_tok, idx, count);
	safety_dimention_free(aster_tok);
	exec_cmd(new_cmd);
	safety_dimention_free(new_cmd);
}

int	is_asterisk(char **cmd)
{
	int		i;
	char	*ret;

	i = 0;
	if (cmd == NULL)
		return (-1);
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '*'))
		{
			ret = ft_astric(cmd[i]);
			if (ret != NULL)
			{
				safety_free((void **)&ret);
				return (i);
			}
		}
		i++;
	}
	return (-1);
}
