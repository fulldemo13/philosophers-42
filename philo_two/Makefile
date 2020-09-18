# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/15 16:17:53 by fulldemo          #+#    #+#              #
#    Updated: 2020/05/15 16:18:10 by fulldemo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_two

SRCDIR	=	./src
INCDIR	=	./includes
OBJDIR	=	./obj

SRC		=	main.c \
			init.c \
			philosophers.c \
			libft.c \
			utils.c

OBJ		=	$(addprefix $(OBJDIR)/,$(SRC:.c=.o))

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -I
LIBS	=	-lpthread

all: obj $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCDIR) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:		all clean fclean re obj