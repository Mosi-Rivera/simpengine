// #include <CUnit/Basic.h>
// #include <CUnit/CUError.h>
// #include <CUnit/CUnit.h>
// #include <CUnit/TestDB.h>
// #include <CUnit/TestRun.h>
// #include <stdlib.h>
// #include <raylib.h>
// #include <stdio.h>
// #include "../include/input_manager.h"
//
// #define SCENES_COUNT 2
//
// void	testNullTermination() {
// 	char str1[] = "numnumnumnumnum";
// 	nullTerminateLine(str1);
// 	CU_ASSERT_STRING_EQUAL(str1, "numnumnum");
// 	char str2[] = "num\nnumnumnu";
// 	nullTerminateLine(str2);
// 	CU_ASSERT_STRING_EQUAL(str2, "num");
// 	char str3[] = "numnum\0numnum";
// 	nullTerminateLine(str3);
// 	CU_ASSERT_STRING_EQUAL(str3, "numnum");
// }
//
// void	testParseSize() {
// 	FILE* file = fopen("test_assets/bindings.csv", "r");
// 	if (file == 0) {
// 		fprintf(stderr, "File open error.");
// 		return;
// 	}
// 	unsigned int size = parseSize(file);
// 	CU_ASSERT_EQUAL(size, 4);
// 	fclose(file);
// }
//
// void	testBindingsParse() {
// 	FILE* file = fopen("test_assets/bindings.csv", "r");
// 	unsigned int size_answer = 4;
// 	unsigned int keys_answer[] = {
// 		263,
// 		262,
// 		265,
// 		264
// 	};
// 	unsigned int size;
// 	KeyboardKey* keyboard_bindings;
//
// 	if (file == 0) {
// 		fprintf(stderr, "File open error.");
// 		return;
// 	}
//
// 	parseKeyboardBindings("./test_assets/bindings.csv", &keyboard_bindings, &size);
// 	CU_ASSERT_EQUAL(size, size_answer);
// 	for (unsigned int i = 0; i < size; i++) {
// 		CU_ASSERT_EQUAL(keyboard_bindings[i], keys_answer[i]);
// 	}
// 	free(keyboard_bindings);
// 	fclose(file);
// 	
// }
//
// void testSetBinding() {
// 	inputManagerInitialize("./test_assets/set_bindings.csv", 0);
// 	setAndSaveKeyboardBinding(0, 0);
// 	setAndSaveKeyboardBinding(1, 1);
// 	inputManagerUninitialize();
// 	inputManagerInitialize("./test_assets/set_bindings.csv", 0);
// 	struct InputManager* input_manager = _getInputManager();
// 	CU_ASSERT_EQUAL(input_manager->keyboard_bindings_count, 2);
// 	CU_ASSERT_EQUAL(input_manager->keyboard_bindings[0], 0);
// 	CU_ASSERT_EQUAL(input_manager->keyboard_bindings[1], 1);
// 	setAndSaveKeyboardBinding(0, 10);
// 	setAndSaveKeyboardBinding(1, 20);
// 	CU_ASSERT_EQUAL(input_manager->keyboard_bindings[0], 10);
// 	CU_ASSERT_EQUAL(input_manager->keyboard_bindings[1], 20);
// 	inputManagerUninitialize();
// 	inputManagerInitialize("./test_assets/set_bindings.csv", 0);
// 	input_manager = _getInputManager();
// 	CU_ASSERT_EQUAL(input_manager->keyboard_bindings_count, 2);
// 	CU_ASSERT_EQUAL(input_manager->keyboard_bindings[0], 10);
// 	CU_ASSERT_EQUAL(input_manager->keyboard_bindings[1], 20);
// 	inputManagerUninitialize();
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
// 	CU_add_test(suite, "Null termination.", testNullTermination);
//
// 	CU_add_test(suite, "Parse Size.", testParseSize);
//
// 	CU_add_test(suite, "Parse bindings.", testBindingsParse);
//
// 	CU_add_test(suite, "Set bindings.", testSetBinding);
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
