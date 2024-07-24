#ifndef MINIRT_H
# define MINIRT_H

# include <libft.h>
# include <math.h> // math
# include <stdio.h> // printf
# include <MLX42/MLX42.h> // mlx
# include <float.h>

# define WIDTH 1000
# define HEIGHT 800
# define M_PI 3.14159265358979323846

# define WORLD_UP (t_vector){0, 1, 0}

# define TEST_BG 0x000000FF
// test shapes
// # define TEST_PLANE (t_vector){4, 4, 4}, (t_vector){0, 0, 1}, (t_rgba){0, 255, 0, 255}
# define TEST_PLANE (t_vector){5, -6, 10}, (t_vector){0, 1, 0}, (t_rgba){0, 0, 255, 255}
# define TEST_CYLINDER (t_vector){0, 0, 5}, (t_vector){0, 0, 1}, 4, 6, (t_rgba){0, 255, 255, 255}
# define TEST_SPHERE (t_vector){5, -6, 32}, 4, (t_rgba){255, 0, 0, 255}
# define TEST_SPHERE2 (t_vector){4, 7, 11}, 5, (t_rgba){255, 255, 0, 255}
# define TEST_SPHERE3 (t_vector){-5, -6, 16}, 6, (t_rgba){178, 0, 55, 255}
# define TEST_SPHERE4 (t_vector){3, 2, 16}, 9, (t_rgba){255, 0, 255, 255}
//test cam
# define TEST_CAM_POS (t_vector){0, 0, -10}
# define TEST_CAM_DIR (t_vector){0, 0, 1}
# define TEST_FOV 80.0
# define FOV_STEP 10.0
# define MIN_FOV 10.0
# define MAX_FOV 170.0

# define PAN_AMOUNT M_PI / 10
# define MOVE_SPEED 5.0

//test light
# define TEST_LIGHT_DIR (t_vector){14, 22, -25}
# define TEST_LIGHT_POS (t_vector){14, 22, -25}

# define TEST_AMBIENT 0.7

typedef struct s_scene t_scene;


typedef struct s_rtx
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_list		*shapes;
	t_scene		*scene;
	int			width;
	int			height;
}	t_rtx;

typedef enum e_shape_type
{
	PLANE,
	SPHERE,
	CYLINDER
}	t_shape_type;

typedef enum e_direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
	FORWARD,
	BACK
}	t_direction;


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
	double			height;
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
	t_vector	right;
	t_vector	up;
	double		fov;
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

typedef struct s_scene
{
	t_camera	camera;
	t_light		light;
	t_amb_light	amb;
}	t_scene;

typedef struct s_intersection
{
	double	distance;
	t_shape	shape;
	int		hit;
}	t_intersection;

typedef struct s_aabb
{
	t_vector min;
	t_vector max;
}	t_aabb;

typedef struct s_bvh
{
	t_aabb			box;
	struct s_bvh	*left;
	struct s_bvh	*right;
	t_shape			*shape;
}	t_bvh;

t_vector	vector_add(t_vector a, t_vector b);
t_vector	vector_subtract(t_vector a, t_vector b);
t_vector	vector_scale(t_vector a, double scalar);
double		vector_dot(t_vector a, t_vector b);
t_vector	vector_cross(t_vector a, t_vector b);
double		vector_length(t_vector a);
t_vector	vector_normalize(t_vector a);

t_rtx		*rtx(void);
int			intersect_plane(t_ray ray, t_shape plane, double *t);
int			intersect_cylinder(t_ray ray, t_shape cylinder, double *t);
int			intersect_sphere(t_ray ray, t_shape sphere, double* t);
void		key_hook(mlx_key_data_t keydata, void* param);
void		render_scene(void);

#endif
