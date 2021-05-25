NAME = sudoku_solver
SRCS = sudoku.c preparing.c validating.c solving.c
CC = gcc
CFLAGS = -I. -Wall -Werror -Wextra
AS = -I. -Wall -Werror -Wextra -g -fsanitize=address -O1 -fno-omit-frame-pointer
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -I. $(SRCS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@rm -f *.o
	@rm -f sudoku_solver

re: fclean all

sudoku: all
	./sudoku_solver "4.129..75 2..3..8.. .7..8...6 ...1.3.62 1.5...4.3 73.6.8... 6...2..3. ..7..1..4 89..651.7"

medium: all
	# ./sudoku_solver ".1....47. .....53.. 7..2.89.. ....27.94 .2.59...3 .4.813... 9.......8 1..73.... 3....265."
	./sudoku_solver "96...8.35 7.5.1.9.. ..2..9... 819...754 .......9. ...89..1. 2.3...54. .54.73... .....51.3"
	# medium is not working
unsolvable: all
	./sudoku_solver "516849732 3.76.5... 8.97...65 135.6.9.7 472591..6 96837..5. 253186.74 6842.75.. 791.5.6.8"