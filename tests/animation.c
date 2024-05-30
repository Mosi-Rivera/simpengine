#include <CUnit/Basic.h>
#include <CUnit/CUError.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <CUnit/TestRun.h>
#include <raylib.h>
#include <stdio.h>
#include "../include/animation.h"
#define FRAME_COUNT 5
#define TEST_ITERATIONS 2

void	testPauseAnimation() {
	struct Animation animation = {0};

	animationInitialize(&animation, ANIMATION_PAUSE, FRAME_COUNT, 8);
	unsigned int i = 0;

	do {
		animationUpdate(&animation, animation.time_to_next_frame + 1);
		CU_ASSERT_EQUAL(animation.current_frame, 0);
		i++;
	} while (i < FRAME_COUNT);
	animationUpdate(&animation, animation.time_to_next_frame + 1);
	CU_ASSERT_EQUAL(animation.current_frame, 0);
}

void	testSimpleAnimation() {
	struct Animation animation = {0};

	animationInitialize(&animation, ANIMATION_SIMPLE, FRAME_COUNT, 8);
	unsigned int i = 0;

	do {
		CU_ASSERT_EQUAL(animation.current_frame, i++);
		animationUpdate(&animation, animation.time_to_next_frame + 1);
	} while (i < FRAME_COUNT);
	animationUpdate(&animation, animation.time_to_next_frame + 1);
	CU_ASSERT_EQUAL(animation.current_frame, FRAME_COUNT - 1);
}

void	testRepeatAnimation() {
	struct Animation animation = {0};

	animationInitialize(&animation, ANIMATION_REPEAT, FRAME_COUNT, 8);

	for (unsigned int j = 0; j < TEST_ITERATIONS; j++) {
		unsigned int i = 0;
		do {
			CU_ASSERT_EQUAL(animation.current_frame, i++);
			animationUpdate(&animation, animation.time_to_next_frame + 1);
		} while (i < FRAME_COUNT);
		CU_ASSERT_EQUAL(animation.current_frame, 0);
	}
}

void	testReverseAnimation() {
	struct Animation animation = {0};

	animationInitialize(&animation, ANIMATION_REVERSE, FRAME_COUNT, 8);

	for (unsigned int i = FRAME_COUNT; i--;) {
		CU_ASSERT_EQUAL(animation.current_frame, i);
		animationUpdate(&animation, animation.time_to_next_frame + 1);
	}
	CU_ASSERT_EQUAL(animation.current_frame, 0);
}

void	testRepeateReverseAnimation() {
	struct Animation animation = {0};

	animationInitialize(&animation, ANIMATION_REVERSE_REPEAT, FRAME_COUNT, 8);

	for (unsigned int j = 0; j < TEST_ITERATIONS; j++) {
		for (unsigned int i = FRAME_COUNT; i--;) {
			CU_ASSERT_EQUAL(animation.current_frame, i);
			animationUpdate(&animation, animation.time_to_next_frame + 1);
		}
		CU_ASSERT_EQUAL(animation.current_frame, FRAME_COUNT - 1);
	}
}

void	testYoyoAnimation() {
	struct Animation animation = {0};

	animationInitialize(&animation, ANIMATION_YOYO, FRAME_COUNT, 8);

	for (unsigned int j = 0; j < TEST_ITERATIONS; j++) {
		for (unsigned int i = 0; i < FRAME_COUNT; i++) {
			CU_ASSERT_EQUAL(animation.current_frame, i);
			animationUpdate(&animation, animation.time_to_next_frame + 1);
		}
		for (unsigned int i = FRAME_COUNT - 1; i-- > 1;) {
			CU_ASSERT_EQUAL(animation.current_frame, i);
			animationUpdate(&animation, animation.time_to_next_frame + 1);
		}
	}
}

int initSuite() {
	return 0;
}

int	cleanSuite() {
	return 0;
}

int	main(void) {
	CU_initialize_registry();

	CU_pSuite suite = CU_add_suite("Scene Manager Tests", initSuite, cleanSuite);

	CU_add_test(suite, "testYoyoAnimation", testYoyoAnimation);
	CU_add_test(suite, "testRepeateReverseAnimation", testRepeateReverseAnimation);
	CU_add_test(suite, "testReverseAnimation", testReverseAnimation);
	CU_add_test(suite, "testRepeatAnimation", testRepeatAnimation);
	CU_add_test(suite, "testSimpleAnimation", testSimpleAnimation);
	CU_add_test(suite, "testPauseAnimation", testPauseAnimation);

	CU_basic_set_mode(CU_BRM_VERBOSE);

	CU_basic_run_tests();

	CU_ErrorCode error = CU_get_error();
	if (error != CUE_SUCCESS) {
		fprintf(stderr, "Test initialization error: %s\n", CU_get_error_msg());
		CU_cleanup_registry();
		return error;
	}

	CU_cleanup_registry();
	return CU_get_error();
}
