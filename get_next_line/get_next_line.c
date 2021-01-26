#include "get_next_line.h"

int     ft_strlen(char *s)
{
    return (*s ? 1 + ft_strlen(s + 1) : 0);
}

int     ft_connect(char **line, char c)
{
    char    *str;
    int     len;
    int     ct;

    if (c == '\n')
        return (1);
    len = ft_strlen(*line) + 1;
    if (!(str = (char*)malloc((1 + len) * sizeof(char))))
        return (-1);
    ct = -1;
    while (++ct < len - 1)
        str[ct] = line[0][ct];
    str[ct++] = c;
    str[ct] = '\0';
    free(*line);
    *line = str;
    return (0);
}

int     get_next_line(char **line)
{
    char    buff[1];
    int     res;
    int     fyp;

    res = 1;
    if (!(*line = (char*)malloc(1 * sizeof(char))))
        return (-1);
    **line = 0;
    while (res)
    {
        res = read(0, (char*)buff, 1);
        if (res <= 0)
            return (res);
        fyp = ft_connect(line, buff[0]);
        if (fyp != 0)
            return (fyp);
    }
    return (0);
}
