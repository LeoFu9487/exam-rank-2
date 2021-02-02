/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 12:34:38 by yfu               #+#    #+#             */
/*   Updated: 2021/02/02 10:35:51 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void ft_connect(int len, char **line, char c)
{
	char *str = malloc(len * sizeof(char));
	for(int i = 0 ; i < len ; i++) str[i] = line[0][i];
	free(*line);
	*line = malloc((len + 1) * sizeof(char));
	for(int i = 0;  i < len - 1 ; i++) line[0][i] = str[i];
	line[0][len - 1] = c;
	line[0][len] = 0;
	free(str);
}

int get_next_line(char **line)
{
	char buff[1];
	*line = malloc(1 * sizeof(char));
	**line = 0;
	int len = 0;
	while (1)
	{
		int res = read(0, buff, 1);
		if (res != 1 || buff[0] == '\n')
			return (res);
		ft_connect(++len, line, buff[0]);
	}
	return (0);
}
