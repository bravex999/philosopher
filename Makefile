NAME        = philo
CC          = cc
CFLAGS      = -Wall -Werror -Wextra -g2 -O0 -fsanitize=address,undefined -pthread
INCLUDES    = -I includes

SRCS = free.c main.c utils.c init_setup.c time.c

OBJS    = $(SRCS:.c=.o)

HEADERS = philo.h philo_types.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

