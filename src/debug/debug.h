/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 05:09:59 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/28 18:24:43 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <token.h>
# include <env.h>
# include <stdio.h>

void	debug_print_token_list(t_token *list);
void	debug_env_print(t_env *env);

#endif
