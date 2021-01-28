#include "get_next_line.h"

int	ft_connect(char **line, char c, int len)
{
	char	*str;
	int		ct;

	if (!(str = malloc((len + 1) * sizeof(char))))
		return (0);
	ct = -1;
	while (++ct < len - 1)
		str[ct] = line[0][ct];
	str[ct++] = c;
	str[ct] = '\0';
	free(*line);
	*line = str;
	return (1);
}

int	get_next_line(char **line)
{
	int		res[2];
	char	buff[1];

	if (!line)
		return (-1);
	*line = malloc(1 * sizeof(char));
	**line = 0;
	res[0] = 1;
	res[1] = 0;
	while (res[0])
	{
		res[0] = read(0, buff, 1);
		if (res[0] != 1)
			return (res[0]);
		if (buff[0] == '\n')
			return (1);
		if (!(ft_connect(line, buff[0], ++res[1])))
			return (-1);
	}
	return (1);
}
