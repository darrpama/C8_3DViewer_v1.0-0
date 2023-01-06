#include <check.h>

#include "../s21_3d_viewer.h"

/* Need to test 
   ParceObj() */

START_TEST(test01) {
    Obj obj = {0};
    const char *fileName = "testCube.obj";
    const char *fileText = "\
    v 0.000000 2.000000 2.000000 1\n\
    v 0.000000 0.000000 2.000000 1\n\
    v 2.000000 0.000000 2.000000 1\n\
    v 2.000000 2.000000 2.000000 1\n\
    v 0.000000 2.000000 0.000000 1\n\
    v 0.000000 0.000000 0.000000 1\n\
    v 2.000000 0.000000 0.000000 1\n\
    v 2.000000 2.000000 0.000000 1\n\
    f 1 2 3 4\n\
    f 8 7 6 5\n\
    f 4 3 7 8\n\
    f 5 1 4 8\n\
    f 5 6 2 1\n\
    f 2 6 7 3\0";

    FILE *file = fopen(fileName, "w");
    fputs(fileText, file);
    fclose(file);

    obj = ParseObj(fileName);
    ck_assert_uint_eq(obj.num_vertices, 8);

    remove(fileName);
    UnloadObj(&obj);
}
END_TEST

START_TEST(test02) {
    ck_assert_int_eq(1, 2);
}
END_TEST

int main(void) {
    Suite *s1 = suite_create("Core");
    TCase *tc1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    suite_add_tcase(s1, tc1);
    tcase_add_test(tc1, test01);
    tcase_add_test(tc1, test02);

    srunner_run_all(sr, CK_ENV);
    srunner_free(sr);
    return 0;
}