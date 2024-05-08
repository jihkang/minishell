/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:53:19 by pjang             #+#    #+#             */
/*   Updated: 2022/11/24 16:41:46 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "global.h"

t_list	*add_node(void *data);
t_list	*last_lst(t_list *lst);
void	push_back_lst(t_list **lst, void *content);
t_list	*find_lst(t_list *lst, char *key);
void	replace_lst(t_list **lst, void *content);
char	*ft_strjoin_char(char *str, char *str2, char c);
int		lst_size(t_list *lst);
char	**convert_lst_2d(t_list *lst);

#endif
