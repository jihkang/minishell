/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:53:36 by pjang             #+#    #+#             */
/*   Updated: 2022/11/30 21:44:22 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "global.h"

typedef struct s_env
{
	char	*key;
	char	*value;
}				t_env;

t_env	*new_env(char *key, char *value);
char	*get_value(t_env *env);
void	init_env(char **env);
char	*get_key(t_env *env);
t_env	*make_env(char *str);
void	ft_env(void);

#endif
