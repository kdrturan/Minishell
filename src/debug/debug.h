/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 05:09:59 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/30 03:08:47 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <stdio.h>
# include <env.h>
# include <token.h>

void	debug_print_token_list(
			t_token *list);

void	debug_env_print(
			t_env *env);

#endif
