CC = gcc
FLAGS=-Wall -Wextra -Werror -std=c11
LIBS=-lcheck
EVAL_TEST=tests/eval_tests.c
RPN_TEST=tests/rpn_tests.c
PROJECT_NAME=s21_3d_viewer
RAYLIB=libs/raylib/libraylib.a

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
	$(CC) $(FLAGS) -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL $(RAYLIB) $(SRC) -o $(PROJECT_NAME)

clean:
	rm -rf s21_3d_viewer
