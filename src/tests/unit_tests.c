#include <check.h>

#include "../s21_3d_viewer.h"

START_TEST(test01) {

}
END_TEST

int main(void) {
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, test01);

    srunner_run_all(sr, CK_ENV);
    srunner_free(sr);
    return 0;
}