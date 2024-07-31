#ifndef MINIRT_H
# define MINIRT_H

# include <libft.h>
# include <math.h> // math
# include <stdio.h> // printf
# include <MLX42/MLX42.h> // mlx
# include <float.h>
# include <colors.h> //colors
# include <struct.h> //colors


# define VV (t_vector){0, 0, 0} //dummy 0 vector for initializationsõ

# define LINE_THICKNESS 0.45

# define WIDTH 800
# define HEIGHT 600
# define M_PI 3.14159265358979323846

# define EPSILON 1e-6

# define BOUNCE 2

# define WORLD_UP (t_vector){0, 1, 0}

# define AXIS_X 1
# define AXIS_Y 2
# define AXIS_Z 3

// # define TEST_PLANE (t_vector){4, 4, 4}, (t_vector){0, 0, 1}, (t_color){0, 255, 0, 255}
# define TEST_BG 0x000000FF

# define WALL_COLOR COLOR_WHITE
# define TEXT_COLOR COLOR_METALLIC_GOLD
# define LIGHT_COLOR COLOR_WARM_WHITE
// # define WALL_COLOR COLOR_SKY_BLUE
// # define TEXT_COLOR COLOR_CORAL_PINK
// # define LIGHT_COLOR COLOR_SOFT_LAVENDER
// # define WALL_COLOR COLOR_PURE_WHITE
// # define TEXT_COLOR COLOR_MATTE_BLACK
// # define LIGHT_COLOR COLOR_SOFT_GRAY
// # define WALL_COLOR COLOR_ROYAL_PURPLE
// # define TEXT_COLOR COLOR_NEON_YELLOW
// # define LIGHT_COLOR COLOR_ELECTRIC_BLUE
// # define WALL_COLOR COLOR_CHARCOAL_GRAY
// # define TEXT_COLOR COLOR_BRIGHT_WHITE
// # define LIGHT_COLOR COLOR_SOFT_TEAL

// HAPPY (centered around x = 0)
# define LH1 (t_vector){-12, 3, 0}, (t_vector){-12, 10, 0}, RGBA(TEXT_COLOR)
# define LH2 (t_vector){-12, 7, 0}, (t_vector){-9, 7, 0}, RGBA(TEXT_COLOR)
# define LH3 (t_vector){-9, 3, 0}, (t_vector){-9, 10, 0}, RGBA(TEXT_COLOR)

# define LA1 (t_vector){-7, 3, 0}, (t_vector){-5.5, 10, 0}, RGBA(TEXT_COLOR)
# define LA2 (t_vector){-5.5, 10, 0}, (t_vector){-4, 3, 0}, RGBA(TEXT_COLOR)
# define LA3 (t_vector){-6.25, 6.5, 0}, (t_vector){-4.75, 6.5, 0}, RGBA(TEXT_COLOR)

# define LP1 (t_vector){-2, 3, 0}, (t_vector){-2, 10, 0}, RGBA(TEXT_COLOR)
# define LP2 (t_vector){-2, 10, 0}, (t_vector){0, 10, 0}, RGBA(TEXT_COLOR)
# define LP3 (t_vector){0, 10, 0}, (t_vector){0, 6.5, 0}, RGBA(TEXT_COLOR)
# define LP4 (t_vector){0, 6.5, 0}, (t_vector){-2, 6.5, 0}, RGBA(TEXT_COLOR)

# define LP5 (t_vector){2, 3, 0}, (t_vector){2, 10, 0}, RGBA(TEXT_COLOR)
# define LP6 (t_vector){2, 10, 0}, (t_vector){4, 10, 0}, RGBA(TEXT_COLOR)
# define LP7 (t_vector){4, 10, 0}, (t_vector){4, 6.5, 0}, RGBA(TEXT_COLOR)
# define LP8 (t_vector){4, 6.5, 0}, (t_vector){2, 6.5, 0}, RGBA(TEXT_COLOR)

# define LY1 (t_vector){6, 10, 0}, (t_vector){8, 6.5, 0}, RGBA(TEXT_COLOR)
# define LY2 (t_vector){8, 6.5, 0}, (t_vector){8, 3, 0}, RGBA(TEXT_COLOR)
# define LY3 (t_vector){10, 10, 0}, (t_vector){8, 6.5, 0}, RGBA(TEXT_COLOR)

// BIRTHDAY (centered around x = 0, moved down)
# define LB1 (t_vector){-17, -3, 0}, (t_vector){-17, -10, 0}, RGBA(TEXT_COLOR)
# define LB2 (t_vector){-17, -3, 0}, (t_vector){-15, -3, 0}, RGBA(TEXT_COLOR)
# define LB3 (t_vector){-15, -3, 0}, (t_vector){-15, -6.5, 0}, RGBA(TEXT_COLOR)
# define LB4 (t_vector){-15, -6.5, 0}, (t_vector){-17, -6.5, 0}, RGBA(TEXT_COLOR)
# define LB5 (t_vector){-17, -6.5, 0}, (t_vector){-15, -6.5, 0}, RGBA(TEXT_COLOR)
# define LB6 (t_vector){-15, -6.5, 0}, (t_vector){-15, -10, 0}, RGBA(TEXT_COLOR)
# define LB7 (t_vector){-15, -10, 0}, (t_vector){-17, -10, 0}, RGBA(TEXT_COLOR)

# define LI1 (t_vector){-13, -3, 0}, (t_vector){-13, -10, 0}, RGBA(TEXT_COLOR)

# define LR1 (t_vector){-11, -3, 0}, (t_vector){-11, -10, 0}, RGBA(TEXT_COLOR)
# define LR2 (t_vector){-11, -3, 0}, (t_vector){-9, -3, 0}, RGBA(TEXT_COLOR)
# define LR3 (t_vector){-9, -3, 0}, (t_vector){-9, -6.5, 0}, RGBA(TEXT_COLOR)
# define LR4 (t_vector){-9, -6.5, 0}, (t_vector){-11, -6.5, 0}, RGBA(TEXT_COLOR)
# define LR5 (t_vector){-11, -6.5, 0}, (t_vector){-9, -10, 0}, RGBA(TEXT_COLOR)

# define LT1 (t_vector){-7, -3, 0}, (t_vector){-5, -3, 0}, RGBA(TEXT_COLOR)
# define LT2 (t_vector){-6, -3, 0}, (t_vector){-6, -10, 0}, RGBA(TEXT_COLOR)

# define LH4 (t_vector){-3, -3, 0}, (t_vector){-3, -10, 0}, RGBA(TEXT_COLOR)
# define LH5 (t_vector){-3, -6.5, 0}, (t_vector){-1, -6.5, 0}, RGBA(TEXT_COLOR)
# define LH6 (t_vector){-1, -3, 0}, (t_vector){-1, -10, 0}, RGBA(TEXT_COLOR)

# define LD1 (t_vector){1, -3, 0}, (t_vector){1, -10, 0}, RGBA(TEXT_COLOR)
# define LD2 (t_vector){1, -3, 0}, (t_vector){3, -3, 0}, RGBA(TEXT_COLOR)
# define LD3 (t_vector){3, -3, 0}, (t_vector){3, -10, 0}, RGBA(TEXT_COLOR)
# define LD4 (t_vector){1, -10, 0}, (t_vector){3, -10, 0}, RGBA(TEXT_COLOR)

# define LA5 (t_vector){5, -10, 0}, (t_vector){6.5, -3, 0}, RGBA(TEXT_COLOR)
# define LA6 (t_vector){6.5, -3, 0}, (t_vector){8, -10, 0}, RGBA(TEXT_COLOR)
# define LA7 (t_vector){5.75, -6.5, 0}, (t_vector){7.25, -6.5, 0}, RGBA(TEXT_COLOR)

# define LY4 (t_vector){10, -3, 0}, (t_vector){12, -6.5, 0}, RGBA(TEXT_COLOR)
# define LY5 (t_vector){12, -6.5, 0}, (t_vector){12, -10, 0}, RGBA(TEXT_COLOR)
# define LY6 (t_vector){14, -3, 0}, (t_vector){12, -6.5, 0}, RGBA(TEXT_COLOR)
// test shapes
// # define TEST_PLANE (t_vector){4, 4, 4}, (t_vector){0, 0, 1}, (t_rgba){0, 255, 0, 255}
# define TEST_PLANEF (t_vector){0, 0, 30}, (t_vector){0, 0, -1}, RGBA(WALL_COLOR)
# define TEST_PLANEB (t_vector){0, 0, -65}, (t_vector){0, 0, 1}, RGBA(WALL_COLOR)
# define TEST_PLANEU (t_vector){0, 30, 0}, (t_vector){0, -1, 0}, RGBA(WALL_COLOR)
# define TEST_PLANED (t_vector){0, -30, 0}, (t_vector){0, 1, 0}, RGBA(WALL_COLOR)
# define TEST_PLANER (t_vector){30, 0, 0}, (t_vector){-1, 0, 0}, RGBA(WALL_COLOR)
# define TEST_PLANEL (t_vector){-30, 0, 0}, (t_vector){1, 0, 0}, RGBA(WALL_COLOR)
# define TEST_CYLINDER (t_vector){0, 0, 0}, (t_vector){0.1, 0, 0}, 4, 6, RGBA(COLOR_WHITE)
# define TEST_SPHERE2 (t_vector){0, 0, 15}, 21, RGBA(TEXT_COLOR)
# define TEST_SPHERE (t_vector){28, 0, 11}, 12, RGBA(COLOR_RED)
# define TEST_CONE (t_vector){0, 0, 0}, (t_vector){1, 1, 0.000000}, 6, 7, RGBA(COLOR_MAGENTA)
# define TEST_SPHERE4 (t_vector){-4, 2, 5}, 4, RGBA(COLOR_BLACK)
# define TEST_SPHERE3 (t_vector){0, -2, 5}, 2, RGBA(COLOR_RED)
//test cam
# define TEST_CAM_POS (t_vector){15, 0, 0}
# define TEST_CAM_DIR (t_vector){0.25, -0.26, 0.93}
# define TEST_FOV 80.0
# define FOV_STEP 10.0
# define MIN_FOV 10.0
# define MAX_FOV 170.0

# define PAN_AMOUNT M_PI / 48
# define MOVE_SPEED 2.0

//test light
# define TEST_LIGHT (t_vector){-1, -1, -20}, RGBA(LIGHT_COLOR), 1.0
# define TEST_LIGHT2 (t_vector){0, -7, -8}, RGBA(COLOR_PASTEL_ORANGE), 1.0
# define TEST_LIGHT3 (t_vector){10, 10, 0}, RGBA(COLOR_GREEN), 1.0

# define TEST_AMBIENT_COL RGBA(COLOR_WHITE)
# define TEST_AMBIENT_INT 0.1

typedef struct s_scene t_scene;
typedef struct s_bvh t_bvh;
typedef struct s_aabb t_aabb;

// parsing
t_vector	check_dir(t_vector dir);

//basic vector equation
t_vector		vector_add(t_vector a, t_vector b);
t_vector		vector_subtract(t_vector a, t_vector b);
t_vector		vector_scale(t_vector a, double scalar);
double			vector_dot(t_vector a, t_vector b);
t_vector		vector_cross(t_vector a, t_vector b);
double			vector_length(t_vector a);
t_vector		vector_normalize(t_vector a);
double			vector_length_squared(t_vector a);
t_vector		vector_min(t_vector a, t_vector b);
t_vector		vector_max(t_vector a, t_vector b);

//clamp
int				clampi(int value, int min, int max);
double			clampd(double value, double min, double max);

//lights
t_color			get_diffuse(t_hit *hit);

void			fix_hit_normal(t_hit *hit);
//colors
t_color			get_pixel_color(t_ray *ray, t_hit *hit, int depth);
int				color_to_int(t_color c);
t_color			color_from_int(int r, int g, int b);
t_color			color_from_hex(unsigned int hex);
t_color			color_clamp(t_color c);
t_color			color_scale(t_color c, double scale);
t_color			color_multiply(t_color c1, t_color c2);
t_color			color_subtract(t_color c1, t_color c2);
t_color			color_add(t_color c1, t_color c2);
t_color			color_create(double r, double g, double b);

//init
void			fix_camera(void);
void			render(void);

//rtx
void			render_multi_threaded(void);
void			render_scene(void);
t_rtx			*rtx(void);
bool			intersect_sphere(t_ray ray, t_shape *sphere, double* t);
void			key_hook(mlx_key_data_t keydata, void* param);
bool			intersect(t_shape *shape, t_ray ray, double *t);
t_color			trace_ray (t_ray *ray, int depth);

//lighting
t_lighting		calc_lighting(t_hit *hit, int depth);

t_ray			generate_ray(int x, int y);

int				intersect_plane(t_ray ray, t_shape plane, double *t);
int				intersect_cylinder(t_ray ray, t_shape cylinder, double *t);


//bvh
t_bvh			*bvh(t_list *shapes);
bool			intersect_bvh(t_bvh *node, t_ray ray, t_hit *hit);
bool			check_unbound(t_ray *ray, t_hit *hit);

//shapes
t_shape			*make_cone(t_vector pos, t_vector dir, double diameter, double height, t_color color);
int				intersect_cone(t_ray ray, t_shape *cone, double *t);
t_shape			*make_plane(t_vector pos, t_vector dir, t_color color);
t_shape			*make_cylinder(t_vector pos, t_vector dir, double diameter, double height, t_color color);

//axis-aligned bounding boxes
bool			intersect_aabb(t_ray ray, t_aabb box, double max_t);
t_aabb			box_sphere(t_shape sphere);
t_aabb			box_cylinder(t_shape cylinder);
t_aabb			box_line(t_shape line);
t_aabb			box_cone(t_shape *cone);



//testing
void			make_aabb_line(t_list **lines, t_vector start, t_vector end, t_color color, t_shape_type type);
bool			intersect_aabb_line(t_ray ray, t_shape *line, double *t);
void			generate_aabb_lines(t_bvh *node, int depth, t_list **lines);

#endif
