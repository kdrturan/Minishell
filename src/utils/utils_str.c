/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 05:07:07 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/09 03:51:46 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

int	is_white_space(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static void	copy_prefix_and_insert(char *dst, char *src,
		char *insert, size_t idx)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < idx && dst[i])
	{
		src[i] = dst[i];
		i++;
	}
	j = 0;
	while (insert[j])
	{
		src[i + j] = insert[j];
		j++;
	}
}

char	*str_change(char *dst, char *src, size_t idx, size_t len)
{
	char	*value;
	size_t	k;
	size_t	m;
	size_t	alloc_len;

	alloc_len = idx + ft_strlen(src);
	if (ft_strlen(dst) > idx + len)
		alloc_len += ft_strlen(dst) - (idx + len);
	value = malloc(alloc_len + 1);
	if (!value)
		return (NULL);
	copy_prefix_and_insert(dst, value, src, idx);
	k = idx + len;
	m = idx + ft_strlen(src);
	while (dst[k])
		value[m++] = dst[k++];
	value[alloc_len] = '\0';
	return (value);
}

bool	ft_isnumeric(const char *str)
{
	int	i;

	if (!str || *str == '\0')
		return (false);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (false);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}
