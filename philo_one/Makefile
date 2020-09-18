# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/07 12:03:13 by fulldemo          #+#    #+#              #
#    Updated: 2020/04/16 12:03:42 by fulldemo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	philo_one

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