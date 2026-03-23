/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 18:23:50 by egaziogl          #+#    #+#             */
/*   Updated: 2026/03/22 21:15:50 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*read_all(int fd, int bufsiz)
{
	int		bytes_read;
	char	*buffer;
	char	*result;

	buffer = ft_calloc(bufsiz, 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, bufsiz);
	result = ft_calloc(bytes_read + 1, 1);
	if (!result)
		return (free(buffer), NULL);
	ft_strlcpy(result, buffer, bytes_read);
	while (bytes_read)
	{
		bytes_read = read(fd, buffer, bufsiz);
		result = ft_strnjoin(result, buffer, bytes_read, true);
	}
	return result;
}

int	main(void)
{
	char	*str;

	str = read_all(0, 12);
	ft_printf("%s\n", str);
	free(str);
}