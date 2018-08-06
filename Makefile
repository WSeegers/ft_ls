# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/30 19:53:02 by wseegers          #+#    #+#              #
#    Updated: 2018/08/06 16:56:58 by wseegers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
CC = clang
CFLAGS = -Werror -Wall -Wextra 
INC = -I libwtcc/include
LIB = -L libwtcc -lwtcc 

SRC_PATH = src
ALL_SRC = count_digits.c exec_ls.c ft_ls.c g_months.c get_file_list.c \
		  print_col.c print_long.c print_simple.c sort.c to_str.c
SRC = $(ALL_SRC:src/%=%)
BIN_PATH = bin
BIN := $(SRC:%.c=$(BIN_PATH)/%.o)
DOS := $(sh uname)EP := $(BIN:%.o=%.d)
OS := $(shell uname)

all : make_LIB $(NAME)
	@echo "wseegers" > author

make_LIB :
	make -C libwtcc -j4

$(NAME) : $(BIN)
	$(CC) $(CFLAGS) $(INC) -o $@ $^ $(LFLAGS) $(LIB)

$(BIN_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(BIN_PATH)
	$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@

-include $(DEP)

clean :
	rm -rf $(BIN_PATH)

fclean : clean
	rm -f $(NAME)
	make fclean -C libwtcc -j4

re : fclean all

run : all
	./$(NAME)

.PHONEY : usage all make_all  clean  fclean  re