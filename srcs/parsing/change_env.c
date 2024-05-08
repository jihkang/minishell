/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:51:18 by pjang             #+#    #+#             */
/*   Updated: 2023/01/03 19:30:48 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*get_env_value(t_list *list, t_tkn *tkn, int start, int i)
{
	char	*key;
	t_env	*env;
	t_list	*find;
	t_list	*res;

	res = NULL;
	while (tkn->value[++i])
	{
		key = ft_substr(tkn->value, start, i - start + 1);
		find = find_lst(list, key);
		if (!find)
		{
			safety_free((void **)&key);
			continue ;
		}
		env = (t_env *)find->content;
		push_back_lst(&res, new_env(key, env->value));
		safety_free((void **)&key);
	}
	if (!last_lst(res))
		return (NULL);
	env = (t_env *)last_lst(res)->content;
	env = new_env(env->key, env->value);
	clear_envlst(&res);
	return (env);
}

char	*get_new_value(t_env **env, t_tkn *tkn, int i)
{
	char	*temp;
	char	*part1;
	char	*part2;
	char	*res;
	t_env	*env1;

	env1 = *env;
	part1 = ft_substr(tkn->value, 0, i);
	part2 = ft_substr(tkn->value, i + ft_strlen(env1->key) + 1, \
					ft_strlen(tkn->value));
	temp = ft_strjoin(part1, env1->value);
	res = ft_strjoin(temp, part2);
	safety_free((void **)&part1);
	safety_free((void **)&part2);
	safety_free((void **)&temp);
	free_env(*env);
	return (res);
}

void	get_flag(int *flag, char c)
{
	if (c == '\"')
	{
		if (*flag == 1)
			*flag = 0;
		else if (*flag == 0)
			*flag = 1;
	}
	if (c == '\'')
	{
		if (*flag == 2)
			*flag = 0;
		else if (*flag == 0)
			*flag = 2;
	}
}

int	*is_env(t_tkn *tkn)
{
	int	i;
	int	j;
	int	flag;
	int	*res;

	res = NULL;
	if (get_count_dalar(tkn))
	{
		flag = 0;
		i = 0;
		j = 0;
		res = (int *)malloc(sizeof(int) * (get_count_dalar(tkn) + 1));
		ft_memset(res, -1, sizeof(int) * (get_count_dalar(tkn) + 1));
		while (tkn->value[i])
		{
			get_flag(&flag, tkn->value[i]);
			if (flag < 2 && tkn->value[i] == '$' && tkn->value[i + 1] != '$')
				res[j++] = i;
			i++;
		}
		res[j] = -1;
	}
	return (res);
}

void	change_env(void)
{
	int		i;
	int		j;
	int		*idx;
	t_tkn	*tkn;
	t_list	*temp;

	temp = g_mini.token;
	while (temp)
	{
		tkn = (t_tkn *)temp->content;
		while (42)
		{
			j = -1;
			idx = is_env(tkn);
			i = get_count_dalar(tkn);
			while (++j < get_count_dalar(tkn) && idx)
				change_to_value(&temp, idx[j]);
			safety_free((void **)&idx);
			if (get_count_dalar(tkn) == i)
				break ;
		}
		temp = temp->next;
	}
}
