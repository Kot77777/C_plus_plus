add_test([=[RK.RK]=]  /home/kostya/Repositories/C_plus_plus/Project_3_semestr/cmake-build-release/tests/run_test_RK [==[--gtest_filter=RK.RK]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RK.RK]=]  PROPERTIES WORKING_DIRECTORY /home/kostya/Repositories/C_plus_plus/Project_3_semestr/cmake-build-release/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  run_test_RK_TESTS RK.RK)
