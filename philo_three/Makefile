CC		= gcc

DIR		= ./srcs/

HEADER	= ./includes/

NAME	= philo_three

HFILES	= my_math.h\
		  parser.h\
		  phil.h\
		  utils.h

FLAGS	= -Wall -Wextra -Werror

SRCS	= free_all.c\
		  ft_err.c\
		  life_circle.c\
		  main.c\
		  my_math.c\
		  parser.c\
		  utils.c

OBJ_DIR	= ./objects/

OBJWDIR	= $(addprefix $(OBJ_DIR), $(OBJS))

vpath %.h	$(HEADER)
vpath %.o	$(OBJ_DIR)
vpath %.c	$(DIR)

OBJS		= $(SRCS:.c=.o)

%.o:		%.c $(HFILES) | $(OBJ_DIR)
			$(CC) $(FLAGS) -c $< -I$(HEADER) -o $(OBJ_DIR)$@

$(NAME):	$(OBJS)
			$(CC) $(OBJWDIR) -I$(HEADER) -o $@

all:		$(NAME) | $(OBJ_DIR)

$(OBJ_DIR):
			mkdir -p $@

clean:
			rm -rf $(OBJ_DIR)

fclean:		clean
			rm -f $(NAME)

re:			fclean
			make $(NAME)

.PHONY:		all clean fclean re
