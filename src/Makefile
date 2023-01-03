CC = gcc
FLAGS=-Wall -Wextra -Werror -std=c11
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
	view/ui.c

all: clean $(PROJECT_NAME) 
	./$(PROJECT_NAME)


$(PROJECT_NAME): 
	$(CC) $(FLAGS) $(LIBS2) $(RAYLIB) $(SRC) -o $(PROJECT_NAME) $(LIBS)

clean:
	rm -rf s21_3d_viewer
