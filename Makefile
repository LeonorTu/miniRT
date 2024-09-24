################################################################################
# COMPILATION
################################################################################
CC				=	cc
CC_STRICT		=	-Wall -Wextra -Werror
CC_FLAGS		=	-pthread
DB_FLAGS		=	-g
HEADERS			=	-I $(LIBFT_INCLUDES) -I $(INCLUDES) -I $(MLX42_DIR)/include
OPTIMIZATION	=	-Ofast -march=native -flto -fno-signed-zeros \
					-fno-trapping-math -funroll-loops
CC_FULL			=	$(CC) $(CC_STRICT) $(CC_FLAGS) $(DB_FLAGS) $(HEADERS) $(OPTIMIZATION)

################################################################################
# LIBFT
################################################################################
LIBFT_DIR		=	./lib/libft
LIBFT			=	$(LIBFT_DIR)/libft.a
LIBFT_INCLUDES	=	$(LIBFT_DIR)

################################################################################
# MLX
################################################################################
MLX42			= $(MLX42_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
MLX42_DIR		= ./lib/MLX42
MLX_DEBUG		= -DDEBUG=0

################################################################################
# MANDATORY
################################################################################
NAME			=	miniRT
INCLUDES		=	./inc
M_HEADERS		=	$(INCLUDES)/miniRT.h \
					$(INCLUDES)/wireframe.h \
					$(INCLUDES)/structs.h \
					$(INCLUDES)/error.h \
					$(INCLUDES)/colors.h
OBJ_DIR			=	./obj
OBJECTS			=	$(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

################################################################################
# BONUS
################################################################################
B_NAME			=	miniRT_bonus
ifeq ($(filter bonus,$(MAKECMDGOALS)),bonus)
	MAIN_SRC	=	main_bonus.c
	MAIN_OBJ	=	$(OBJ_DIR)/main_bonus.o
	MAIN_NAME	=	$(B_NAME)
else
	MAIN_SRC	=	main.c
	MAIN_OBJ	=	$(OBJ_DIR)/main.o
	MAIN_NAME	=	$(NAME)
endif

SRC_DIR			=	./src
SRCS			=	error.c \
					init.c \
					ui.c \
					bvh.c \
					bvh_utils.c \
					init_utils.c \
					checkerboard.c \
					sphere.c \
					plane.c \
					cylinder.c \
					cone.c \
					aabb_boxes.c \
					threads.c \
					render.c \
					intersect_bvh.c \
					aabb_intersect.c \
					intersect.c \
					normal.c \
					reflections.c \
					material.c \
					lighting.c \
					color.c \
					color_utils.c \
					color_utils2.c \
					color_gray.c \
					vector_calculation.c \
					vector_utils.c \
					mlx_image.c \
					hooks.c \
					keys.c \
					clamp.c \
					uv.c \
					uv_utils.c \
					translate.c \
					rotate.c \
					scale.c \
					aabb_generate_rays.c \
					aabb_intersect_line.c \
					wireframe.c \
					parser.c \
					lalloc.c \
					lalloc_utils.c \
					ft_atof.c \
					parse_scene.c \
					parse_shapes.c \
					parser_utils.c \
					check.c \
					check_utils.c \
					ft_split_new.c \
					parse_bonus.c \


################################################################################
# RULES
################################################################################
vpath %.c	$(SRC_DIR) \
			$(SRC_DIR)/wireframe \
			$(SRC_DIR)/bvh \
			$(SRC_DIR)/pixel_color \
			$(SRC_DIR)/parser \
			$(SRC_DIR)/math \
			$(SRC_DIR)/init \
			$(SRC_DIR)/mlx \
			$(SRC_DIR)/reflections \
			$(SRC_DIR)/shapes \
			$(SRC_DIR)/utils \
			$(SRC_DIR)/uv \
			$(SRC_DIR)/transformations \

all: libmlx $(MAIN_NAME)

libmlx:
	cmake $(MLX42_DIR) $(MLX_DEBUG) -B $(MLX42_DIR)/build && make -C $(MLX42_DIR)/build -j4

$(MAIN_NAME): $(LIBFT) $(OBJECTS) $(MAIN_OBJ)
	$(CC_FULL) $(OBJECTS) $(MAIN_OBJ) $(LIBFT) $(MLX42) -o $(MAIN_NAME)

$(MAIN_OBJ): $(MAIN_SRC) $(M_HEADERS)
	mkdir -p $(@D)
	$(CC_FULL) -c $< -o $@

$(OBJ_DIR)/%.o: %.c $(M_HEADERS)
	mkdir -p $(@D)
	$(CC_FULL) -c $< -o $@

$(LIBFT): libft_force
	make -C $(LIBFT_DIR)

bonus: all

libft_force:
	@true

clean:
	@rm -rf $(NAME).dSYM/ $(B_NAME).dSYM/ $(OBJECTS) $(OBJ_DIR)
	@rm -rf $(MLX42_DIR)/build
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) $(B_NAME) $(OBJ_DIR)
	make fclean -C $(LIBFT_DIR)

re: fclean all

################################################################################
# NORM
################################################################################
norm:
	norminette $(SRC_DIR) $(M_HEADERS) | grep -v "OK!" || true

norm2:
	norminette $(SRC_DIR) $(M_HEADERS)

################################################################################
# PROFILE
################################################################################
PROF_NAME = $(NAME)_profile
PROF_OUT = gprof_analysis.txt
GMON_OUT = gmon.out

profile: $(OBJECTS)
	$(CC_FULL) -pg $(OBJECTS) $(LIBFT) $(MLX42) -o $(PROF_NAME)
	./$(PROF_NAME)
	gprof $(NAME)_profile $(GMON_OUT) > $(PROF_OUT)

pclean:
	rm -f $(PROF_NAME) $(PROF_OUT) $(GMON_OUT)

################################################################################
# VALGRIND
################################################################################
VG = valgrind

VG_FLAGS =	--leak-check=full \
			--track-fds=yes \
			# --suppressions=suppressions

VG_CC = $(CC) $(CC_FLAGS) $(HEADERS)

VG_LOG_FLAGS =	$(VG_FLAGS) \
				--log-file=$(VG_LOG) \
				--track-origins=yes \
				--show-leak-kinds=all \
				--verbose \
				--gen-suppressions=all \
				# --suppressions=suppressions

VG_LOG = valgrind_leaks.log

VG_ARGS = "scenes/rt_sample.rt"

vg: vg_build
	$(VG) $(VG_FLAGS) ./$(NAME) $(VG_ARGS)

vglog: vg_build
	$(VG) $(VG_LOG_FLAGS) ./$(NAME) $(VG_ARGS)

vg_build: $(OBJECTS) $(LIBFT) libmlx
	$(VG_CC) $(OBJECTS) $(LIBFT) $(MLX42) -o $(NAME)

vglog_clean: fclean
	rm -f $(VG_LOG)

################################################################################
# PHONY
################################################################################
.PHONY: all bonus re clean fclean libft_force libmlx db vg vglog vglog_clean norm norm2

################################################################################
# Colors
################################################################################
# Black, Red, Green, Yellow, Blue, Purple, Cyan, White
BK = \033[0;30m
R = \033[0;31m
G = \033[0;32m
Y = \033[0;33m
B = \033[0;34m
P = \033[0;35m
C = \033[0;36m
W = \033[0;37m
# Bold
BKB = \033[1;30m
RB = \033[1;31m
GB = \033[1;32m
YB = \033[1;33m
BB = \033[1;34m
PB = \033[1;35m
CB = \033[1;36m
WB = \033[1;37m
# Reset Color
RC = \033[0m
