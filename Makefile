GREEN = \033[0;92m

NAME = so_long
CC = cc
CFLAGS = -g -Wall -Wextra -Werror
DFLAGS = -MMD -MP -I include -I $(MLX_DIR)/include

SRCDIR = src
OBJDIR = obj
LIBFT_DIR = libft
MLX_DIR = MLX42
MLX_BUILD = $(MLX_DIR)/build
LIBFT_A = $(LIBFT_DIR)/libft.a

SRCS = $(addprefix $(SRCDIR)/,\
		main.c \
		utils.c \
		check_map.c \
		map_path.c \
		render_game.c \
)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEPS = $(OBJS:.o=.d)

all: $(MLX_DIR) $(NAME)

$(LIBFT_A):
		make -s -C $(LIBFT_DIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
		mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_A) $(MLX_DIR)/build/libmlx42.a
		@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -L$(MLX_DIR)/build -lmlx42 -ldl -lglfw -pthread -lm -o $(NAME)
		@echo "$(GREEN) Compiled!$(DEF_COLOR)"

$(MLX_DIR):
	git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR)

$(MLX_DIR)/build/libmlx42.a: | $(MLX_DIR)
	cmake -B $(MLX_BUILD) -S $(MLX_DIR)
	make -C $(MLX_BUILD) -j4

clean:
		rm -rf $(OBJDIR) $(MLX_DIR)
		make clean -s -C $(LIBFT_DIR)

fclean: clean
		rm -rf $(NAME)
		make fclean -s -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY:$(OBJS)
-include $(DEPS)