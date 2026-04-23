NAME      = ft_ls

CC        = cc
CFLAGS    = -Wall -Werror -Wextra

SRC_DIR   = src
INC_DIR   = include
OBJ_DIR   = .obj

LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

vpath %.c $(SRC_DIR)
vpath %.h $(INC_DIR) libft/

SRC_FILES  = main.c

OBJS      := $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

HEADERS = $(LIBFT_DIR)/include/libft.h Makefile
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)/include/

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re $(LIBFT)