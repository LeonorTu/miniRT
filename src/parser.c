
#include <miniRT.h>

void	parse_input(int argc, char *argv[])
{
	size_t	len;
	if (argc != 2)
	{
		printf("Error\nWrong argument number!");
		exit(1);
	}
	len = ft_strlen(argv[1]);
	if (len < 3 || ft_strncmp(argv[1] + len - 3, ".rt", 4))
	{
		printf("Error\nWrong input format!");
		exit(1);
	}
	
}