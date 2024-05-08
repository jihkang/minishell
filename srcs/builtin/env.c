/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:55:35 by pjang             #+#    #+#             */
/*   Updated: 2022/12/04 20:25:55 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*make_env(char *str)
{
	t_env				*env;
	unsigned int		i;

	i = ft_strichr(str, '=');
	env = malloc(sizeof(t_env));
	env->key = ft_substr(str, 0, i);
	if (str[i] && i < ft_strlen(str))
		env->value = ft_substr(str, i + 1, ft_strlen(str));
	else
		env->value = ft_strdup("");
	return (env);
}

void	init_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		push_back_lst(&(g_mini.env), make_env(env[i]));
		i++;
	}
}

void	ft_env(void)
{
	t_list	*cur;
	t_env	*env;

	cur = g_mini.env;
	while (cur)
	{
		env = cur->content;
		if (env->value[0])
		{
			printf("%s", env->key);
			printf("=%s\n", env->value);
		}
		cur = cur->next;
	}
}
