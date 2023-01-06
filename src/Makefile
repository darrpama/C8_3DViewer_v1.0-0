OS := $(shell uname -s)
CC = gcc
FLAGS=-Wall -Wextra -Werror -std=c11
PROJECT_NAME=s21_3d_viewer
RAYLIB=libs/raylib/libraylib.a
UNIT_TESTS=tests/unit_tests.c

ifeq ($(OS), Darwin)
	LIBS = -lcheck
	LIBS2 = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
else
	LIBS = -lcheck -lrt -lm -pthread -lsubunit -lraylib -ldl
	LIBS2 =
endif

SRC=$(PROJECT_NAME).c \
	libs/raygui/raygui.c \
	libs/gui_file_dialog/gui_file_dialog.c \
	modules/parser/parser.c \
	modules/parser/helpers.c \
	view/scene.c \
	view/scene/camera.c \
	view/scene/info_panels.c \
	view/scene/model.c \
	view/scene/transform_panel.c \
	view/scene/upload_file.c \
	view/ui.c

TEST_SRC =\
	modules/parser/parser.c \
	modules/parser/helpers.c

TEST_SRC_O =\
	modules/parser/parser.o \
	modules/parser/helpers.o

all: clean $(PROJECT_NAME) 
	./$(PROJECT_NAME)

$(PROJECT_NAME): 
	$(CC) $(FLAGS) $(LIBS2) $(RAYLIB) $(SRC) -o $(PROJECT_NAME) $(LIBS)

test: test_lib.a
	$(CC) $(FLAGS) tests/unit_tests.c test_lib.a -o unit_tests.out $(LIBS)

parser.o:
	$(CC) $(FLAGS) -c modules/parser/parser.c

helpers.o:
	$(CC) $(FLAGS) -c modules/parser/helpers.c -c

unit_tests.o:
	$(CC) $(FLAGS) -c tests/unit_tests.c -o unit_tests.o $(LIBS)

test_lib.a: parser.o helpers.o
	ar rcs test_lib.a parser.o helpers.o
	ranlib test_lib.a

clean:
	rm -rf s21_3d_viewer