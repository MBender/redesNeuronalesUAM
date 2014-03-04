/* 
 * File:   test_cargar.c
 * Author: HollyBuster
 *
 * Created on 1 de marzo de 2014, 17:48
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * Simple C Test Suite
 */

void test1() {
    //carga nand
    Test t = cargar("test/nand.txt");
    printf("test_cargar test 1\n");
}

void test2() {
    printf("test_cargar test 2\n");
    printf("%%TEST_FAILED%% time=0 testname=test2 (test_cargar) message=error message sample\n");
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% test_cargar\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test1 (test_cargar)\n");
    test1();
    printf("%%TEST_FINISHED%% time=0 test1 (test_cargar) \n");

    printf("%%TEST_STARTED%% test2 (test_cargar)\n");
    test2();
    printf("%%TEST_FINISHED%% time=0 test2 (test_cargar) \n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
