

CMAKE_MINIMUM_REQUIRED(VERSION 3.11)

ENABLE_TESTING()
FIND_PACKAGE(GTest REQUIRED)

INCLUDE_DIRECTORIES(
	"${GTEST_INCLUDE_DIRS}"
	"${PROJECT_SOURCE_DIR}/src"
)

FILE(GLOB libnotify_test_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/test-*.cpp"
)

ADD_EXECUTABLE(libnotify_tests
	${libnotify_test_SRCS}
)

TARGET_LINK_LIBRARIES(libnotify_tests
	gtest
	gtest_main
	pthread
	libnotify
)

ADD_TEST(
	NAME "test-jsonconfig"
	COMMAND $<TARGET_FILE:libnotify_tests>
)

