### OPERATING SYSTEM ###
OS			:=	$(shell uname -s)

### EXECUTABLE ###
NAME		:=	cub3d

### COMPILATION ###
CC			:=	gcc
CFLAGS		:=	-Wall -Werror -Wextra -g -fsanitize=address
#CFLAGS		:=	-g -fsanitize=address

### PATHS ###
LIBFT_PATH	:=	./libft/
INCL_PATH	:=	incl/
SRCS_PATH	:=	src/
OBJS_PATH	:=	obj/
ifeq ($(OS), Linux)
	MLX_PATH:=	./minilibx-linux/
else
	MLX_PATH:=	./minilibx_macos/
endif

### SOURCE FILES ###
SRC_NAME	:=	$(NAME).c
#SRC_BONUS=	$(NAME)_bonus.c
SRCS		:=	get_next_line.c \
				structs.c \
				arg_check.c \
				map_checker.c \
				map_create.c \
				utils.c \
				error_handling.c \
				textures_checker.c \
				generate_map.c

SRCS_NAME	:=	$(addprefix $(SRCS_PATH), $(SRC_NAME) $(SRCS))
#SRCS_BONUS=	$(addprefix $(SRCS_PATH), $(SRC_BONUS) $(SRCS))

### OBJECT FILES ###
OBJ_NAME	:=	$(SRC_NAME:.c=.o)
#OBJ_BONUS	:=	$(SRC_BONUS:.c=.o)
OBJS		:=	$(SRCS:.c=.o)
OBJS_NAME	:=	$(addprefix $(OBJS_PATH), $(OBJ_NAME) $(OBJS))
#OBJS_BONUS	:=	$(addprefix $(OBJS_PATH), $(OBJ_BONUS) $(OBJS))

### LIBFT ###
LIBFTMAKE	:=	make bonus --silent -C $(LIBFT_PATH)
LIBFT		:=	-L$(LIBFT_PATH) -lft

### MLXLIB ###
MLXMAKE		:=	make --silent -C $(MLX_PATH)
ifeq ($(OS), Linux)
	MLX		:=	-L$(MLX_PATH) -lmlx_Linux -lX11 -lXext -lm -lz -O3
else
	MLX		:=	-L$(MLX_PATH) -lmlx -lm -framework OpenGL -framework AppKit -O3
endif

### INCLUDES ###
INC			:=	-I $(LIBFT_PATH)$(INCL_PATH) -I $(INCL_PATH) -I $(MLX_PATH)

### COLOURS ###
ifeq ($(OS), Linux)
	ECHO	:=	echo "
else
	ECHO	:=	echo "
endif
GREEN= $(addprefix $(ECHO), \033[1;32m)
RED= $(addprefix $(ECHO), \033[1;31m)
DEFAULT= \033[0m"

### IMPLICT RULES ###
%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

### ACTIVE RULES ###
all: $(NAME) ## compiles cub3d with mandatory requirements

bonus: $(NAME) ## compiles cub3d with bonus requirements

$(NAME): $(OBJS_PATH) $(OBJS_NAME)
	@$(LIBFTMAKE)
	@$(MLXMAKE)
	@$(CC) $(CFLAGS) $(OBJS_NAME) $(INC) $(LIBFT) $(MLX) -o $(NAME)
	@$(GREEN)$(NAME) Program created$(DEFAULT)

$(OBJS_PATH):
	@mkdir -p $@

clean: ## removes object files
	@make bonus $@ --silent -C $(LIBFT_PATH)
	@rm -rf $(OBJS_PATH)
	@$(RED)Object files removed$(DEFAULT)

fclean: clean ## removes object files and binary
	@make $@ --silent -C $(LIBFT_PATH)
	@$(RED)Libft removed$(DEFAULT)
	@rm -f $(NAME)
	@$(RED)$(NAME) Program removed$(DEFAULT)

re: fclean all ## recompiles cub3d

### NORMINETTE ###
norm: ## checks norminette requirements
	@norminette -R CheckForbiddenSourceHeader $(SRCS_PATH)
	@norminette -R CheckForbiddenSourceHeader $(INCL_PATH)
	@norminette -R CheckDefine $(SRCS_PATH)
	@norminette -R CheckDefine $(INCL_PATH)

### HELP ###
help:  ## show this help
	@echo "usage: make [target]"
	@echo ""
	@egrep "^(.+)\:\ .*##\ (.+)" ${MAKEFILE_LIST} | sed 's/:.*##/#/' | column -t -c 2 -s '#'

### PHONY RULE ###
.PHONY:	all help bonus clean fclean re norm
