#include <unistd.h>

int	main(int argc, char **argv)
{
	int		ascii[257];
	char	*str;

	if (argc == 3)
	{
		ascii[256] = -1;
		while (++ascii[256] < 256)
			ascii[ascii[256]] = 0;
		str = argv[2];
		while (*str)
			ascii[(int)*(str++)] = 1;
		str = argv[1];
		while (*str)
		{
			if (ascii[(int)*str])
				write(1, str, 1);
			ascii[(int)*(str++)] = 0;
		}
	}
	write(1, "\n", 1);
}
