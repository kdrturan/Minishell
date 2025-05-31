/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrturan <kdrturan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:45:07 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/31 14:11:56 by kdrturan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include <minishell.h>
# include <env.h>
# include <signal_handler.h>

void	init_shell(
			t_shell *shell,
			char **env_data);

#endif
