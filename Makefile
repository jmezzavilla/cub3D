END		= \033[0m
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
CYAN	= \033[1;36m

RM		= rm -f
NAME	= cub3D
INCLUDES = include

# Contains the X11 and MLX header files
INCLUDES_MLX = -I/usr/include -Imlx

# Link X11 and MLX
MLX_DIR = ./mlx
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11 -lm
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a

OPTFLAGS    =  -march=native -ffast-math -funsafe-math-optimizations -ffinite-math-only

DIR_LIBFT = srcs/libft
INCLUDE_LIB = $(DIR_LIBFT)/include
LIB = $(DIR_LIBFT)/libft.a
CFLAGS = -I$(INCLUDES) -I$(INCLUDE_LIB) -I $(MLX_DIR) -g -Wall -Wextra -Werror #-fsanitize=address

SRCDIR	= srcs
OBJDIR	= objs

SRC =		cub3d.c\
			build/game.c\
			build/characters.c\
			build/file.c\
			build/scene.c\
			build/door.c\
			utils/msg.c\
			utils/clean.c\
			utils/utils.c\
			utils/free_game.c\
			checker/check.c\
			checker/check_map.c\
			checker/floodfill.c\
			action/hook.c\
			action/direction.c\
			action/colision.c\
			action/mouse.c\
			draw/draw_minimap.c\
			draw/draw_pixels.c\
			draw/raycast.c\
			draw/raycast_tex.c\
			draw/draw_player.c\

SRC		:= $(addprefix srcs/,$(SRC))

OBJ		= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

all:	$(NAME)

$(LIB): | $(OBJDIR)
	@make -s -C $(DIR_LIBFT)

$(NAME): $(LIB) $(OBJ)
	@cc $(CFLAGS) $(OBJ) $(LIB) -o $(NAME) $(MLX_FLAGS)
	@echo "\n$(BLUE)$(NAME)$(END) $(GREEN)Stuff compiled 💻\n$(END)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR) $(LIB)
	@mkdir -p $(@D)
	@cc $(CFLAGS) $(OPTFLAGS) $(INCLUDES_MLX) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@$(RM) $(OBJDIR)/*.o
	@make -s -C $(DIR_LIBFT) clean

fclean:	clean
	@$(RM) $(NAME)
	@$(RM)r objs
	@make -s -C $(DIR_LIBFT) fclean
	@echo "\n$(BLUE)$(NAME)$(END) $(GREEN)All stuff removed 🗑️\n$(END)"

re:	fclean all

ARGS = maps/map_subject.cub

run: re
	@clear
	@./${NAME} ${ARGS}

VALG	= valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes# --trace-children=yes

norm:
	@norminette srcs include

v: re
	@${VALG} ./${NAME} ${ARGS}

val: re
	@output=$$(${VALG} ./${NAME} ${ARGS} 2>&1); \
	if echo "$$output" | grep -q 'freed' && echo "$$output" | grep -q '0 errors' ; then\
		echo -n "$(GREEN)"; echo "$$output" | grep -E 'freed|total|ERROR S|file descriptor' | sed 's/^[^ ]* //';\
	else\
		echo -n "$(RED)"; echo "$$output" | grep -E 'total|ERROR S|file descriptor' | sed 's/^[^ ]* //';\
	fi;

e: fclean

.PHONY:	all clean fclean re run v val e
