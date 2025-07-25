/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuaydin <tuaydin@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:16:45 by tuaydin           #+#    #+#             */
/*   Updated: 2025/07/14 02:26:48 by tuaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

int	ft_getpid(void)
{
	int		fd;
	char	buf[32];
	ssize_t	n;
	int		pid;
	int		i;

	pid = 0;
	i = 0;
	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
		return (-1);
	n = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (n <= 0)
		return (-1);
	buf[n] = '\0';
	while (buf[i] >= '0' && buf[i] <= '9')
	{
		pid = pid * 10 + (buf[i] - '0');
		i++;
	}
	return (pid);
}
