

CMAKE_MINIMUM_REQUIRED(VERSION 3.9)

ENABLE_TESTING()
FIND_PACKAGE(GTest REQUIRED)
FIND_PACKAGE(GMock REQUIRED)

INCLUDE_DIRECTORIES(
	"${GTEST_INCLUDE_DIRS}"
	"${GMOCK_INCLUDE_DIRS}"
	"${PROJECT_SOURCE_DIR}/src"
)

SET(notifier_test_SRCS
	test-jsonconfig.cpp
	test-pipe.cpp
#	test-callback.cpp
)

ADD_EXECUTABLE(notifier_tests
	${notifier_test_SRCS}
)

TARGET_LINK_LIBRARIES(notifier_tests
	notifier_lib
	pthread
	${GTEST_LIBRARIES}
	${GTEST_MAIN_LIBRARIES}
	${GMOCK_LIBRARIES}
)

ADD_TEST(
	NAME "test-callback"
	COMMAND $<TARGET_FILE:notifier_tests>
)
ADD_TEST(
	NAME "test-pipe"
	COMMAND $<TARGET_FILE:notifier_tests>
)
ADD_TEST(
	NAME "test-jsonconfig"
	COMMAND $<TARGET_FILE:notifier_tests>
)

