/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:39:01 by pjang             #+#    #+#             */
/*   Updated: 2022/12/27 15:26:27 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

t_env	*new_env(char *key, char *value)
{
	t_env	*env;

	if (!key || !value)
		return (NULL);
	env = malloc(sizeof(t_env));
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	return (env);
}

char	*get_value(t_env *env)
{
	return (env->value);
}

char	*get_key(t_env *env)
{
	return (env->key);
}
