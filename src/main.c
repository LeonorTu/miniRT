#include <miniRT.h>

void	error(void)
{
	perror("ERROR\n");
	perror(mlx_strerror(mlx_errno));
	exit(1);
}

//PLANES to unbound
//SPHERE, CYLINDER to shapes
void	get_shapes(void)
{
	// ft_lstadd_back(&rtx()->unbound, ft_lstnew(make_plane(TEST_PLANEF)));
	// ft_lstadd_back(&rtx()->unbound, ft_lstnew(make_plane(TEST_PLANEB)));
	// ft_lstadd_back(&rtx()->unbound, ft_lstnew(make_plane(TEST_PLANEU)));
	ft_lstadd_back(&rtx()->unbound, ft_lstnew(make_plane(TEST_PLANED)));
	// ft_lstadd_back(&rtx()->unbound, ft_lstnew(make_plane(TEST_PLANER)));
	// ft_lstadd_back(&rtx()->unbound, ft_lstnew(make_plane(TEST_PLANEL)));

	ft_lstadd_back(&rtx()->shapes, ft_lstnew(make_sphere(TEST_SPHERE)));
	// ft_lstadd_back(&rtx()->shapes, ft_lstnew(make_sphere(TEST_SPHERE2)));
	// ft_lstadd_back(&rtx()->shapes, ft_lstnew(make_sphere(TEST_SPHERE3)));
	// ft_lstadd_back(&rtx()->shapes, ft_lstnew(make_sphere(TEST_SPHERE4)));
	ft_lstadd_back(&rtx()->shapes, ft_lstnew(make_cone(TEST_CONE)));
	ft_lstadd_back(&rtx()->shapes, ft_lstnew(make_cylinder(TEST_CYLINDER1)));
	// ft_lstadd_back(&rtx()->shapes, ft_lstnew(make_cylinder(TEST_CYLINDER2)));
}

void	render(void)
{
	render_multi_threaded();
	// render_scene();
}

int	main(void)
{
	init_rtx();
	render();
	mlx_key_hook(rtx()->mlx, key_hook, NULL);
	mlx_loop_hook(rtx()->mlx, loop_hook, NULL);
	mlx_loop(rtx()->mlx);
	mlx_terminate(rtx()->mlx);
	return (0);
}

