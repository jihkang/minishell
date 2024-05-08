/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjang <pjang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:34:24 by pjang             #+#    #+#             */
/*   Updated: 2023/01/05 13:25:31 by pjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	get_flag_match(int *flag, char c, char **str, int *i)
{
	char	*buf;

	if (str)
		buf = *str;
	if (c == '\"' || c == '\'')
	{
		if (*flag)
		{
			*flag = 0;
			if (str)
			{
				*buf = c;
				*str += 1;
			}
			*i += 1;
		}
		else
			*flag = 1;
	}
}

int	get_len_token(const char *s, char c)
{
	int	len;
	int	flag;

	len = 0;
	flag = 0;
	while (s[len] && (ft_isspace(s[len]) != c || flag))
	{
		if ((s[len] == '\"' || s[len] == '\'') && len == 0)
			flag = 1;
		len++;
		get_flag_match(&flag, s[len], NULL, &len);
	}
	return (len);
}

char	*get_word_token(const char *s, char c)
{
	int		i;
	int		flag;
	char	*buf;
	char	*word;

	flag = 0;
	word = (char *)malloc(sizeof(char) * (get_len_token(s, c) + 1));
	if (!word)
		return (NULL);
	i = 0;
	buf = word;
	while (s[i] && (ft_isspace(s[i]) != c || flag))
	{
		if (s[i] == '(' || s[i] == ')')
		{
			i++;
			continue ;
		}
		if (!devide_command((char *)(s + i), &buf, &flag, &i))
			break ;
		*buf++ = s[i++];
		get_flag_match(&flag, s[i], &buf, &i);
	}
	*buf = '\0';
	return (word);
}

void	split2(char ***split, const char *s, char c)
{
	int		i;
	int		flag;
	char	**buf;

	i = 0;
	flag = 0;
	buf = *split;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]) == c)
			i++;
		if (s[i] != '\0')
		{
			*buf = get_word_token(&s[i], c);
			buf++;
		}
		while (s[i] && (ft_isspace(s[i]) != c || flag))
		{
			if (!devide_command2((char *)(s + i), &flag, &i))
				break ;
			i++;
			get_flag_match(&flag, s[i], NULL, &i);
		}
	}
	*buf = 0;
}

char	**ft_split_token(const char *s, char c)
{
	int		strs;
	char	**split;

	strs = get_strs_token(s, c);
	split = (char **)malloc(sizeof(char *) * (strs + 1));
	split2(&split, s, c);
	return (split);
}
