// #include <CUnit/Basic.h>
// #include <CUnit/CUError.h>
// #include <CUnit/CUnit.h>
// #include <CUnit/TestDB.h>
// #include <CUnit/TestRun.h>
// #include <stdlib.h>
// #include <raylib.h>
// #include <stdio.h>
// #include "../include/state_manager.h"
//
// void start(void* data) {}
//
// void finish(void* data) {}
//
// void update(void* data, float dt) {}
//
// void draw(void* data) {}
//
// struct State*	initState(struct State* state) {
// 	state->start = start;
// 	state->finish = finish;
// 	state->update = update;
// 	state->draw = draw;
// 	return state;
// }
//
// void	testStateHistory() {
// 	struct StateManager state_manager = {0};
// 	struct State states[MAX_HISTORY_SIZE] = {0};
//
// 	for (unsigned int i = 0; i < MAX_HISTORY_SIZE; i++) {
// 		states[i] = *initState(&(struct State){0});
// 	}
//
// 	stateManagerInitialize(&state_manager, states, 5);
//
// 	stateManagerSetState(&state_manager, 0, 0);
// 	stateManagerSetState(&state_manager, 1, 0);
// 	stateManagerSetState(&state_manager, 2, 0);
// 	stateManagerSetState(&state_manager, 3, 0);
// 	stateManagerSetState(&state_manager, 4, 0);
// 	CU_ASSERT_EQUAL(state_manager.active_state, 4);
// 	stateManagerPopStateHistory(&state_manager);
// 	CU_ASSERT_EQUAL(state_manager.active_state, 3);
// 	stateManagerPopStateHistory(&state_manager);
// 	CU_ASSERT_EQUAL(state_manager.active_state, 2);
// 	stateManagerSetState(&state_manager, 4, 0);
// 	CU_ASSERT_EQUAL(state_manager.active_state, 4);
// 	stateManagerPopStateHistory(&state_manager);
// 	CU_ASSERT_EQUAL(state_manager.active_state, 2);
// 	stateManagerPopStateHistory(&state_manager);
// 	CU_ASSERT_EQUAL(state_manager.active_state, 1);
// 	stateManagerPopStateHistory(&state_manager);
// 	CU_ASSERT_EQUAL(state_manager.active_state, 0);
// 	stateManagerPopStateHistory(&state_manager);
// 	CU_ASSERT_EQUAL(state_manager.active_state, 0);
// }
//
//
// int initSuite() {
// 	return 0;
// }
//
// int	cleanSuite() {
// 	return 0;
// }
//
// int	main(void) {
// 	CU_initialize_registry();
//
// 	CU_pSuite suite = CU_add_suite("Scene Manager Tests", initSuite, cleanSuite);
//
// 	CU_add_test(suite, "State History Test", testStateHistory);
//
// 	CU_basic_set_mode(CU_BRM_VERBOSE);
//
// 	CU_basic_run_tests();
//
// 	CU_ErrorCode error = CU_get_error();
// 	if (error != CUE_SUCCESS) {
// 		fprintf(stderr, "Test initialization error: %s\n", CU_get_error_msg());
// 		CU_cleanup_registry();
// 		return error;
// 	}
//
// 	CU_cleanup_registry();
// 	return CU_get_error();
// }
