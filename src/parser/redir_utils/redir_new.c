/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:52:38 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/09 04:05:50 by tuaydin          ###   ########.fr       */
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
	redir->target = NULL;
	if (target)
		redir->target = gc_track(&shell->gc, ft_strdup(target));
	redir->next = NULL;
	return (redir);
}
