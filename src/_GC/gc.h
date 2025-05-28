/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:59:51 by tuaydin           #+#    #+#             */
/*   Updated: 2025/05/28 21:22:51 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include <stdlib.h>

typedef struct s_gc	t_gc;

typedef struct s_gc_node {
	void				*ptr;
	struct s_gc_node	*next;
}	t_gc_node;

struct s_gc {
	t_gc_node	*head;
};

void	gc_init(t_gc *gc);
void	*gc_malloc(t_gc *gc, size_t size);
void	gc_free_all(t_gc *gc);

#endif