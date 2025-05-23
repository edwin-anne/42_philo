# NAME
NAME	= philo

INC = include/
OBJS_DIR = obj/
SRC_DIR = srcs/

CC	= cc
CFLAGS	=  -Wall -Wextra -Werror -I$(INC)
RM	= rm -f

SRCS = $(SRC_DIR)/error.c $(SRC_DIR)/init.c  $(SRC_DIR)/main.c  $(SRC_DIR)/monitor.c $(SRC_DIR)/monitor2.c $(SRC_DIR)/clean.c $(SRC_DIR)/utils.c $(SRC_DIR)/utils2.c  $(SRC_DIR)/execute.c  

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: $(BONUS_DIR)/%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(OBJS_DIR)

fclean: clean 
	@$(RM) $(NAME)
	@$(RM) $(BONUS_NAME)

re: fclean all 

.PHONY : all clean fclean re bonus
