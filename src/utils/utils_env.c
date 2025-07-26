/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abturan <abturan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 03:21:09 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/04 18:47:33 by abturan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

bool	will_eat(char c)
{
	if (ft_isdigit(c))
		return (true);
	if (c == '#' || c == '@' || c == '*' || c == '!')
		return (true);
	return (false);
}

int	get_valid_key_length(t_token *dollar)
{
	const char	*text;
	int			i;

	if (!dollar || dollar->type != DOLLAR)
		return (0);
	if (!dollar->next || dollar->next->type != WORD || !dollar->next->text)
		return (0);
	text = dollar->next->text;
	if (!(ft_isalpha(text[0]) || text[0] == '_'))
		return (0);
	i = 1;
	while (text[i])
	{
		if (!(ft_isalnum(text[i]) || text[i] == '_'))
			break ;
		i++;
	}
	return (i);
}

bool	is_valid_key(char *key)
{
	if (!key)
		return (false);
	if (ft_isdigit(*key))
		return (false);
	while (*key)
	{
		if (ft_isalnum(*key) || *key == '_')
			key++;
		else
			return (false);
	}
	return (true);
}
