if(EXISTS "/Users/apple/Downloads/2134f/3/build/tests[1]_tests.cmake")
  include("/Users/apple/Downloads/2134f/3/build/tests[1]_tests.cmake")
else()
  add_test(tests_NOT_BUILT tests_NOT_BUILT)
endif()
