OS := $(shell uname -s)
CC = gcc
FLAGS=-Wall -Wextra -Werror -std=c11
EVAL_TEST=tests/eval_tests.c
RPN_TEST=tests/rpn_tests.c
PROJECT_NAME=s21_3d_viewer
RAYLIB=libs/raylib/libraylib.a

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
	view/scene.c \
	view/scene/camera.c \
	view/scene/info_panels.c \
	view/scene/model.c \
	view/scene/transform_panel.c \
	view/scene/upload_file.c \
	view/ui.c

all: clean $(PROJECT_NAME) 
	./$(PROJECT_NAME)


$(PROJECT_NAME): 
	$(CC) $(FLAGS) $(LIBS2) $(RAYLIB) $(SRC) -o $(PROJECT_NAME) $(LIBS)

clean:
	rm -rf s21_3d_viewer