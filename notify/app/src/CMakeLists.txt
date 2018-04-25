

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src")

SET(kafka_notify_SRCS
	app.cpp
	config/jsonconfig.cpp
)

ADD_EXECUTABLE(kafka_notify
	${kafka_notify_SRCS}
)

TARGET_LINK_LIBRARIES(kafka_notify
	${POCO_LIBS}
	${YAMLCPP_LIBS}
)

