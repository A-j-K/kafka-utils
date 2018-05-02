

CMAKE_MINIMUM_REQUIRED(VERSION 3.9)

ENABLE_TESTING()
FIND_PACKAGE(GTest REQUIRED)
FIND_PACKAGE(GMock REQUIRED)

INCLUDE_DIRECTORIES(
	"${GTEST_INCLUDE_DIRS}"
	"${GMOCK_INCLUDE_DIRS}"
	"${PROJECT_SOURCE_DIR}/src"
)

SET(lib_simple_kafka_webhook_test_SRCS
	test-jsonconfig.cpp
	test-kafka-configure.cpp
)

ADD_EXECUTABLE(lib-simple-kafka-webhook-tests
	${lib_simple_kafka_webhook_test_SRCS}
)

TARGET_LINK_LIBRARIES(lib-simple-kafka-webhook-tests
	simple_kafka_webhook_lib
	pthread
	${GTEST_LIBRARIES}
	${GTEST_MAIN_LIBRARIES}
	${GMOCK_LIBRARIES}
)

ADD_TEST(
	NAME "test-jsonconfig"
	COMMAND $<TARGET_FILE:lib-simple-kafka-webhook-tests>
)

