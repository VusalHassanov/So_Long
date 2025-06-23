# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/18 03:01:32 by vhasanov          #+#    #+#              #
#    Updated: 2025/06/23 15:57:46 by vhasanov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c read_map.c map_validation.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
       image_load.c render.c cleanup.c handler.c movement.c environment_setup.c key_setup.c map_check.c \
       flood_fill.c

OBJS = $(SRCS:.c=.o)
NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=42

MLX_DIR = ./minilibx-linux
MLX_REPO = https://github.com/42Paris/minilibx-linux.git
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

LIBFT_DIR = ./lib_ft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

INCLUDES = -I$(MLX_DIR) -I$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $(NAME)

$(MLX_LIB): | $(MLX_DIR)
	make -C $(MLX_DIR)

$(MLX_DIR):
	git clone $(MLX_REPO) $(MLX_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	make clean -C $(MLX_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
