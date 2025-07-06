/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 05:07:09 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/07 00:19:58 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdbool.h>
# include <token.h>
# include <libft.h>
# include <env.h>

# define E_ARG0 ": too many arguments\n"
# define E_ARG1 ": numeric argument required\n"
# define E_ARG2 ": not a valid identifier\n"

# define E_FILE0 ": No such file or directory\n"
# define E_FILE1 ": Not a directory\n"
# define E_FILE2 ": Is a directory\n"

# define E_PERM0 ": Permission denied\n"

# define E_CMD0 ": command not found\n"

int		is_white_space(
			int c);

char	*str_change(
			char *dst,
			char *src,
			size_t idx,
			size_t len);

int		get_valid_key_length(
			t_token *dollar);

bool	will_eat(
			char c);

bool	validate_input(
			t_shell *shell,
			char *input);

t_token	*skip_ws(
			t_token *tok);

char	*get_prompt(
			int status);

bool	ft_isnumeric(const char *str);
void	print_error(bool b_flag, char *sec0, char *sec1, const char *error);
#endif