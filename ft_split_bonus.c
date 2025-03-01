/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:30:52 by mohaben-          #+#    #+#             */
/*   Updated: 2025/02/14 17:56:02 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	count_words(char const *s, char c)
{
	char	quote;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		if (s[i] == '\'' || s[i] == '"')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
			if (s[i])
				i++;
		}
		while (s[i] && s[i] != c && s[i] != '\'' && s[i] != '"')
			i++;
	}
	return (count);
}

static void	free_all(char	**res, int i)
{
	while (i >= 0)
	{
		free(res[i]);
		res[i] = NULL;
		i--;
	}
	free(res);
}

void	ft_set_start_end(char const *s, char c, int *start, int *end)
{
	char	quote_char;
	int		in_quote;

	in_quote = 0;
	while (s[*end] == c)
		(*end)++;
	if (s[*end] == '\'' || s[*end] == '"')
	{
		quote_char = s[*end];
		in_quote = 1;
		(*start) = ++(*end);
		while (s[*end] && (s[*end] != quote_char || in_quote))
		{
			if (s[*end] == quote_char)
				in_quote = 0;
			else
				(*end)++;
		}
	}
	else
	{
		*start = *end;
		while (s[*end] && s[*end] != c && s[*end] != '\'' && s[*end] != '"')
			(*end)++;
	}
}

static char	**ft_fill(char **arr, char const *s, char c)
{
	int		start;
	int		end;
	int		i;

	start = 0;
	end = 0;
	i = 0;
	while (s[end] && i < count_words(s, c))
	{
		ft_set_start_end(s, c, &start, &end);
		arr[i] = ft_substr(s, start, end - start);
		if (arr[i] == NULL)
		{
			free_all(arr, i - 1);
			arr = NULL;
			return (arr);
		}
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;

	if (s == NULL)
		p_error("Malloc error", 1);
	arr = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (arr == NULL)
		p_error("Malloc error", 1);
	arr = ft_fill(arr, s, c);
	if (arr == NULL)
		p_error("Malloc error", 1);
	return (arr);
}
