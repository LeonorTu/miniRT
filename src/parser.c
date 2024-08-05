
#include <miniRT.h>

void	error_exit(char *err_msg)
{
	printf(err_msg);
	exir(EXIT_FAILURE);
}

void	parse_element(char *line)
{
	if (*line == 'A')
		set_ambient();
	else if (*line == 'C')
		set_camera();
	else if (*line == 'L')
		set_light();
	else if (ft_strncmp(line, "sp", 2) == 0)
		set_sphere();
	else if (ft_strncmp(line, "pl", 2) == 0)
		set_plane();
	else if (ft_strncmp(line, "cy", 2) == 0)
		set_cylinder();
	else if (ft_strncmp(line, "cn", 2) == 0)
		set_cone();
}

void	parse_input(int argc, char *argv[])
{
	size_t	len;
	int		fd;
	char	*line;

	if (argc != 2)
		error_exit("Error\nWrong argument number!");
	len = ft_strlen(argv[1]);
	if (len < 3 || ft_strncmp(argv[1] + len - 3, ".rt", 4))
		error_exit("Error\nWrong input format!");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_exit("Error\nOpen failed!");
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n')
			parse_element(line);
		free(line);
		line = get_next_line(fd);
	}
}
