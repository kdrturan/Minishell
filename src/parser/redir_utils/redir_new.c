/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:52:38 by tuaydin           #+#    #+#             */
/*   Updated: 2025/06/03 00:54:10 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_redir	*redir_new(t_shell *shell, t_redir_type type, char *target)
{
	t_redir	*redir;

	if (!shell)
		return (NULL);
	redir = gc_track(&shell->gc, malloc(sizeof(t_redir)));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->target = target;
	redir->next = NULL;
}
