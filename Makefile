# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lduboulo <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/27 18:29:51 by lduboulo          #+#    #+#              #
#    Updated: 2022/11/03 13:55:29 by lduboulo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLORS -----------------------------------------------------------------------

GREEN		= \033[1;32m
RED			= \033[1;31m
ORANGE	= \033[1;33m
BUILD		= \e[38;5;225m
SEP			= \e[38;5;120m
DUCK		= \e[38;5;227m
RESET		= \033[0m
TSEP		= ${SEP}=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=${RESET}

# COLORS -----------------------------------------------------------------------
# UTILS ------------------------------------------------------------------------

AR						= ar rcs
MKDIR					= mkdir -p
RM						= rm -rf

# UTILS ------------------------------------------------------------------------
# DIRECTORIES ------------------------------------------------------------------

SRCS_DIR			= src
O_DIR					= objs
DIRS					= ${O_DIR}

# DIRECTORIES ------------------------------------------------------------------
# FILES ------------------------------------------------------------------------

SRCS_FILES		= main.cpp \
								Shader.cpp \

# FILES ------------------------------------------------------------------------
# COMPILATION ------------------------------------------------------------------

NAME						= scop
CXX							= c++
C								= gcc
CXXFLAGS				= -Wall -Wextra -Werror -std=c++17 -I/usr/local/include
OGLFLAGS				= -L/usr/local/lib -lrt -lm -lXrandr -lXrender -lXi -lXfixes -lXxf86vm -lXext -lX11 -lpthread -lxcb -lXau -lXdmcp -lGL -ldl -lglfw
DEBUG_CXXFLAGS	= -g3 -fsanitize=address -fno-omit-frame-pointer

# COMPILATION ------------------------------------------------------------------
# RULES ------------------------------------------------------------------------

OBJS_FILES		:= ${SRCS_FILES:.cpp=.o}
HEADERS			  = include

SRCS					= $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS					= $(addprefix $(O_DIR)/, $(OBJS_FILES))

# RULES ------------------------------------------------------------------------


all:	${NAME}

${NAME}: ${OBJS} GLAD
	@printf "\n"
	@${CXX} -o ${NAME} ${OBJS} ${O_DIR}/glad.o ${OGLFLAGS}
	@printf "${GREEN}💻 Successfully created ${NAME} executable${RESET} ✅\n"

${OBJS}: ${O_DIR}/%.o : ${SRCS_DIR}/%.cpp ${DIRS}
	@${CXX} ${CXXFLAGS} -o $@ -c $<
	@printf "\e[1k\r${BUILD}🚧 $@ from $< 🚧${RESET}"

GLAD:
	@${C} -o ${O_DIR}/glad.o -c ${SRCS_DIR}/glad.c

${O_DIR}:
	@${MKDIR} ${O_DIR}
	@printf "${BUILD}${O_DIR} Directory Created 📎${RESET}\n\n"

clean :
	@${RM} ${O_DIR}
	@printf "\n${RED} 🧹 Deleted ${NAME} .o's${RESET} ❌\n\n"

fclean : clean
	@${RM} ${NAME} ${NAME}.dSYM
	@printf "${RED} 💥 Deleted ${NAME} files${RESET} ❌\n\n"

re : fclean all

.PHONY : all clean fclean re
