OS := $(shell uname -s)
CC = gcc
FLAGS=-Wall -Wextra -Werror -std=c11
PROJECT_NAME=s21_3d_viewer
UNIT_TESTS=tests/unit_tests.c

ifeq ($(OS), Darwin)
	RAYLIB=libs/raylib/libraylib.a
	LIBS = -lcheck
	LIBS2 = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
else
	RAYLIB=
	LIBS = -lcheck -lrt -lm -pthread -lsubunit -lraylib -ldl
	LIBS2 =
endif

SRC=$(PROJECT_NAME).c \
	libs/raygui/raygui.c \
	libs/gui_file_dialog/gui_file_dialog.c \
	modules/parser/parser.c \
	modules/parser/helpers.c \
	modules/rlwrapper/rlwrapper.c \
	view/scene.c \
	view/scene/camera.c \
	view/scene/info_panels.c \
	view/scene/model.c \
	view/scene/transform_panel.c \
	view/scene/upload_file.c \
	view/scene/vertices.c \
	view/scene/wires.c \
	view/ui.c \
	view/scene/save_settings.c \
	view/scene/bg_color.c \
	view/scene/save_picture.c

TEST_SRC =\
	modules/parser/parser.c \
	modules/parser/helpers.c

TEST_SRC_O =\
	modules/parser/parser.o \
	modules/parser/helpers.o

all: clean $(PROJECT_NAME) 
	./$(PROJECT_NAME)

dvi:
	texi2dvi dvi.tex

dist:
	rm -rf ./../s21_3d_viewer_1_0/
	mkdir ./../s21_3d_viewer_1_0/
	cp -a ./ ./../s21_3d_viewer_1_0
	tar -cvzf ./../s21_3d_viewer_1_0.tar.gz -C ./../s21_3d_viewer_1_0 .
	rm -rf ./../s21_3d_viewer_1_0/

uninstall:
	rm -rf ~/Desktop/s21_3d_viewer

install: $(PROJECT_NAME)
	cp $(PROJECT_NAME) ~/Desktop

$(PROJECT_NAME): 
	$(CC) $(FLAGS) $(LIBS2) $(RAYLIB) $(SRC) -o $(PROJECT_NAME) $(LIBS)

tests: test_lib.a
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

gcov_report:
	$(CC) $(FLAGS) --coverage modules/parser/parser.c modules/parser/helpers.c tests/unit_tests.c -o gcov_report.o -lcheck
	@./gcov_report.o
	@lcov -t gcov_report -o gcov_report.info -c -d .
	@genhtml -o gcov_report gcov_report.info
	@open ./gcov_report/index.html


clean:
	rm -rf s21_3d_viewer
	rm -rf *.o *.gch *.a *.gcda *.gcno *.info gcov_report report \
	CPPLINT.cfg *.dSYM evaluate main test gcov_test eval-test