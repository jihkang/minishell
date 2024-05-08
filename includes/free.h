/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:53:45 by pjang             #+#    #+#             */
/*   Updated: 2022/11/24 14:53:45 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "global.h"
# include "env.h"

void	free_env(t_env *env);
void	free_node(t_list **cur);
void	clear_envlst(t_list **lst);

#endif
