#ifndef MINIRT_H
# define MINIRT_H

# include <libft.h>
# include <math.h> // math
# include <stdio.h> // printf
# include <MLX42/MLX42.h> // mlx
# include <float.h>

# define WIDTH 1920
# define HEIGHT 1080
# define M_PI 3.14159265358979323846

# define TEST_PLANE (t_vector){4, 4, 4}, (t_vector){0, 0, 1}, (t_rgba){0, 255, 0, 255}
# define TEST_BG 0x000000FF
# define TEST_SPHERE2 (t_vector){-5, -6, 11}, 15, (t_rgba){255, 0, 0, 255}
# define TEST_SPHERE (t_vector){-5, -6, 16}, 15, (t_rgba){255, 0, 0, 255}
# define TEST_LIGHT (t_vector){14, 22, 25}
# define TEST_FOV 70.0
# define TEST_AMBIENT 0.1

typedef struct s_rtx
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_list		*shapes;
	double		closest_point;
	int			width;
	int			height;
}	t_rtx;

typedef enum e_shape_type
{
	NOTHING,
	PLANE,
	SPHARE,
	CYLINDER
}	t_shape_type;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_rgba
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_rgba;

typedef struct s_shape
{
	t_shape_type	type;
	t_vector		pos;
	t_vector		dir;
	double			diameter;
	double			radius;
	t_rgba			color;
}	t_shape;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
} t_ray;

typedef struct s_amb_light
{
	double	amb_light;
	t_rgba	color;
}	t_amb_light;

typedef struct s_camera
{
	t_vector	pos;
	t_vector	dir;
	int			fov;
}	t_camera;

typedef struct s_light
{
	t_vector	pos;
	t_vector	dir;
	double		bright;
	t_rgba		color;
}	t_light;

typedef struct s_quadratic_coeffs
{
	double	a;
	double	b;
	double	c;
} t_quadratic_coeffs;

t_vector	vector_add(t_vector a, t_vector b);
t_vector	vector_subtract(t_vector a, t_vector b);
t_vector	vector_multiply(t_vector a, double scalar);
double		vector_dot(t_vector a, t_vector b);
t_vector	vector_cross(t_vector a, t_vector b);
double		vector_length(t_vector a);
t_vector	vector_normalize(t_vector a);

int			intersect_sphare(t_ray ray, t_shape sphere, double* t);

#endif
