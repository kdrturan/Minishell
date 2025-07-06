/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:01:26 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/06 21:54:19 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gc.h>
#include <minishell.h>

void	gc_init(t_shell *shell)
{
	shell->gc.head = NULL;
	shell->env_gc.head = NULL;
	shell->exec_gc.head = NULL;
}

void	*gc_track(t_gc *gc, void *ptr)
{
	t_gc_node	*node;

	if (!ptr)
		return (NULL);
	node = malloc(sizeof(t_gc_node));
	if (!node)
		return (NULL);
	node->ptr = ptr;
	node->next = gc->head;
	gc->head = node;
	return (ptr);
}

void	**gc_track_array(t_gc *gc, void **array)
{
	size_t	i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i])
	{
		gc_track(gc, array[i]);
		i++;
	}
	gc_track(gc, array);
	return (array);
}

void	gc_free_all(t_gc *gc)
{
	t_gc_node	*current;
	t_gc_node	*tmp;

	current = gc->head;
	while (current)
	{
		if (current->ptr)
			free(current->ptr);
		current->ptr = NULL;
		tmp = current;
		current = current->next;
		if (tmp)
			free(tmp);
		tmp = NULL;
	}
	gc->head = NULL;
}

