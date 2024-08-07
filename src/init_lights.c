#include <miniRT.h>

t_light	*make_light(char **element)
{
	t_light	*new_light;

	new_light = ft_calloc(1, sizeof(t_light));
	new_light->pos = pos;
	new_light->color = color_scale(color, 1.0 / 255.0);
	new_light->bright = birght;
	return (new_light);
}

void	get_lights(void)
{
	ft_lstadd_back(&rtx()->scene->lights, ft_lstnew(make_light(TEST_LIGHT)));
	// ft_lstadd_back(&rtx()->scene->lights, ft_lstnew(make_light(TEST_LIGHT2)));
	// ft_lstadd_back(&rtx()->scene->lights, ft_lstnew(make_light(TEST_LIGHT2)));
	// ft_lstadd_back(&rtx()->scene->lights, ft_lstnew(make_light(TEST_LIGHT3)));
}