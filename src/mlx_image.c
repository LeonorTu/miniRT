#include <miniRT.h>

mlx_image_t	*png_to_image(mlx_t *mlx, char *path, bool to_grayscale)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;
	mlx_image_t		*gray;

	texture = mlx_load_png(path);
	if (!texture)
		error();
	image = mlx_texture_to_image(mlx, texture);
	if (!image)
	{
		mlx_delete_texture(texture);
		error();
	}
	mlx_delete_texture(texture);
	if (to_grayscale)
	{
		gray = mlx_image_gray(mlx, image);
		mlx_delete_image(mlx, image);
		return (gray);
	}
	return (image);
}
