/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 01:17:52 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/03 23:50:10 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <libft.h>

typedef enum e_mode	t_mode;

enum	e_mode
{
	INTERACTIVE,
	NONINTERACTIVE,
	HEREDOCSIGNAL
};

void	set_signals(
			t_mode mode);

#endif
