SRCS =  main.c \
		common_functions.c \
		read_map.c \
		draw.c \
		draw_utils.c \
		hooks.c \
		get_next_line.c \
		get_next_line_utils.c

CC = gcc

FLAGS = -Wall -Wextra -Werror

ADD_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

INCLUDES = fdf.h get_next_line.h libft/libft.h mlx/mlx.h

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx.a

NAME = fdf

$(NAME): $(OBJS) $(INCLUDES) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(FLAGS) $(ADD_FLAGS) -o $(NAME) $(OBJS) $(LIBFT_LIB) $(MLX_LIB)

$(LIBFT_LIB): libft ;

$(MLX_LIB): libmlx ;

%.o:%.c
		gcc ${FLAGS} -o $@ -c $<

libft:
	make -C $(LIBFT_DIR)

libmlx:
	make -C $(MLX_DIR)

all : $(NAME)

clean :
	rm -rf $(OBJS)
	make -C libft clean
	make -C mlx clean

fclean : clean
	rm -rf $(NAME) libft/libft.a
	rm -rf $(NAME) mlx/libmlx.a

re : fclean all

.PHONY: all libft libmlx clean fclean re