/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 01:25:22 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/06 23:45:39 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

static char	*get_var_value(t_shell *shell, const char *str)
{
	char	var[4096];
	int		i = 0;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (NULL);
	while ((ft_isalnum(str[i]) || str[i] == '_') && i < 255)
	{
		var[i] = str[i];
		i++;
	}
	var[i] = '\0';
	return (env_get_value(shell, var));
}

static bool check_pipes(t_shell *shell, char *input)
{
	size_t	i;

	i = 0;
	if (!input)
		return (true);
	while (is_white_space(input[i]))
		i++;
	if (input[i] == '|')
		return ((shell->exit_status = 258), false);
	i = ft_strlen(input);
	while (i > 0 && is_white_space(input[i - 1]))
		i--;
	if (i > 0 && input[i - 1] == '|')
		return ((shell->exit_status = 258), false);
	return (true);
}

static bool	check_redirections(t_shell *shell, char *input)
{
	size_t	i;
	char	*val;

	i = 0;
	if (!input)
		return (true);
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>')
		{
			if (input[i + 1] == input[i])
				i++;
			i++;
			while (input[i] && is_white_space(input[i]))
				i++;
			if (input[i] == '\0' || input[i] == '|' || input[i] == '<' || input[i] == '>')
				return ((shell->exit_status = 258), false);
			if (input[i] == '$')
			{
				val = get_var_value(shell, &input[i + 1]);
				if (!val || val[0] == '\0')
					return ((shell->exit_status = 258), false);
			}
		}
		else
			i++;
	}
	return (true);
}

bool	validate_input(t_shell *shell, char *input)
{
	if (!check_pipes(shell, input))
		return (false);
	if (!check_redirections(shell, input))
		return (false);
	return (true);
}
