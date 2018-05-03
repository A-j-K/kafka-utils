
PROJECT("kafka-urils-lib")

CMAKE_MINIMUM_REQUIRED(VERSION 3.9)

ENABLE_TESTING()
FIND_PACKAGE(GTest REQUIRED)
FIND_PACKAGE(GMock REQUIRED)

INCLUDE_DIRECTORIES(
	"${GTEST_INCLUDE_DIRS}"
	"${GMOCK_INCLUDE_DIRS}"
	"${PROJECT_SOURCE_DIR}/src"
)

SET(test_SRCS
	test-jsonconfig.cpp
	test-kafka-configure.cpp
	test-kafka-event-cb.cpp
	test-kafka-consume-cb.cpp
)

ADD_EXECUTABLE(webhook-tests
	${test_SRCS}
)

TARGET_LINK_LIBRARIES(webhook-tests
	kafka_utils_lib
	pthread
	${GTEST_LIBRARIES}
	${GTEST_MAIN_LIBRARIES}
	${GMOCK_LIBRARIES}
)

ADD_TEST(
	NAME "test-jsonconfig"
	COMMAND $<TARGET_FILE:webhook-tests>
)

ADD_TEST(
	NAME "test-kafka-configure"
	COMMAND $<TARGET_FILE:webhook-tests>
)

ADD_TEST(
	NAME: "test-kafka-event-cb"
	COMMAND $<TARGET_FILE:webhook-tests>
)

ADD_TEST(
	NAME: "test-kafka-consume-cb"
	COMMAND $<TARGET_FILE:webhook-tests>
)

