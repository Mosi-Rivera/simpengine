// #include <CUnit/Basic.h>
// #include <CUnit/CUError.h>
// #include <CUnit/CUnit.h>
// #include <CUnit/TestDB.h>
// #include <CUnit/TestRun.h>
// #include <stdio.h>
// #include "../include/scene_manager.h"
// #define SCENES_COUNT 2
//
// static int number = 0;
//
// void _update(void* state, float dt) {dt++; state = state + 0; number = 1;}
//
// void _draw(void* state) {state = state + 0; number = 2;}
//
// void _transitionIn(void* state, float progress) {progress++; state = state + 0; number = 3;}
//
// void _transitionOut(void* state, float progress) {progress++; state = state + 0; number = 4;}
//
// void _enter(void* state) { state = state + 0; number = 5;}
//
// void _sceneExit(void* state) { state = state + 0; number = 6;}
//
// void _destroy(struct Scene* scene) {}
//
// static struct Scene scenes[SCENES_COUNT] = {
// 	(struct Scene) {
// 		_update,
// 		_draw,
// 		_enter,
// 		_sceneExit,
// 		_transitionIn,
// 		_transitionOut,
// 		_destroy,
// 		1,
// 		1,
// 		0
// 	},
// 	(struct Scene) {
// 		_update,
// 		_draw,
// 		_enter,
// 		_sceneExit,
// 		_transitionIn,
// 		_transitionOut,
// 		_destroy,
// 		2,
// 		2,
// 		0
// 	}
// };
//
// void	testInitialization() {
// 	struct SceneManager* scene_manager = _getSceneManager();
//
// 	sceneManagerInitialize(scenes, SCENES_COUNT, 1);
//
// 	CU_ASSERT_PTR_EQUAL(scene_manager->current_scene, &scenes[1]);
// 	CU_ASSERT_TRUE(scene_manager->transition.state == TransitionIn);
// 	CU_ASSERT_TRUE(scene_manager->scenes_count == 2);
// }
//
// void	testSceneTransition() {
// 	struct SceneManager* scene_manager = _getSceneManager();
//
// 	sceneManagerInitialize(scenes, SCENES_COUNT, 0);
//
// 	CU_ASSERT_PTR_EQUAL(scene_manager->current_scene, &scenes[0]);
// 	CU_ASSERT_EQUAL(scene_manager->transition.state, TransitionIn);
//
// 	setScene(1);
//
// 	CU_ASSERT_PTR_EQUAL(scene_manager->current_scene, &scenes[0]);
// 	CU_ASSERT_PTR_EQUAL(scene_manager->next_scene, &scenes[1]);
// 	CU_ASSERT_EQUAL(scene_manager->transition.state, TransitionIn);
// 	CU_ASSERT_EQUAL(scene_manager->transition.progress, scenes[0].transition_in_duration);
//
// 	sceneUpdate(1.1f);
// 	CU_ASSERT_PTR_EQUAL(scene_manager->current_scene, &scenes[0]);
// 	CU_ASSERT_PTR_EQUAL(scene_manager->next_scene, &scenes[1]);
// 	CU_ASSERT_EQUAL(scene_manager->transition.state, TransitionOut);
// 	CU_ASSERT_EQUAL(scene_manager->transition.progress, scenes[0].transition_out_duration);
//
// 	sceneUpdate(1.1f);
// 	CU_ASSERT_PTR_EQUAL(scene_manager->current_scene, &scenes[1]);
// 	CU_ASSERT_PTR_EQUAL(scene_manager->next_scene, 0);
// 	CU_ASSERT_EQUAL(scene_manager->transition.state, TransitionIn);
// 	CU_ASSERT_EQUAL(scene_manager->transition.progress, scenes[1].transition_in_duration);
//
// 	sceneUpdate(2.1f);
// 	CU_ASSERT_PTR_EQUAL(scene_manager->current_scene, &scenes[1]);
// 	CU_ASSERT_EQUAL(scene_manager->transition.state, TransitionNone);
// }
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
// 	CU_add_test(suite, "Initialization", testInitialization);
//
// 	CU_add_test(suite, "Scene Transition", testSceneTransition);
//
// 	CU_basic_set_mode(CU_BRM_VERBOSE);
// 	// Run tests
// 	CU_basic_run_tests();
//
// 	// Check for initialization errors
// 	CU_ErrorCode error = CU_get_error();
// 	if (error != CUE_SUCCESS) {
// 		fprintf(stderr, "Test initialization error: %s\n", CU_get_error_msg());
// 		CU_cleanup_registry();
// 		return error;
// 	}
//
// 	// Clean up and return
// 	CU_cleanup_registry();
// 	return CU_get_error();
// }
