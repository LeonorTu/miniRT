#include <miniRT.h>

/*
returns a normalized t_color from memory location at x y of image img
*/
static t_color	get_pixel(mlx_image_t *img, uint32_t x, uint32_t y)
{
	uint8_t	*start;
	t_color	color;

	start = img->pixels + (y * img->width + x) * 4;
	color.r = (double)*(start) / 255.0;
	color.g = (double)*(start + 1) / 255.0;
	color.b = (double)*(start + 2) / 255.0;
	return (color);
}

static int wrap_coordinate(int value, int max)
{
	value = value % max;
	if (value < 0)
		value += max;
	return (value);
}

static t_color	get_texture_uv(mlx_image_t *image, double u, double v)
{
	int		x;
	int		y;
	int		width;
	int		height;

	width = image->width - 1;
	height = image->height - 1;
	x = (int)(width * u);
	y = (int)(height * v);
	x = wrap_coordinate(x, width);
	y = wrap_coordinate(y, height);
	return (get_pixel(image, x, y));
}

t_color	add_material(t_hit *hit)
{
	if (hit->shape->image)
		return (get_texture_uv(hit->shape->image, hit->u, hit->v));
	else
		return (hit->shape->color);
}