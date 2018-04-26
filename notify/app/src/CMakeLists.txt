

CMAKE_MINIMUM_REQUIRED(VERSION 3.11)

INCLUDE_DIRECTORIES(
	"${PROJECT_SOURCE_DIR}/src"
)

SET(libnotify_SRCS
	app.cpp
	utils/pipe.cpp
	config/config.cpp
	config/configfactory.cpp
	config/jsonconfig.cpp
)

ADD_LIBRARY(notify
	${libnotify_SRCS}
)

TARGET_LINK_LIBRARIES(notify
	${POCO_LIBS}
	${JANSSON_LIBRARIES}
)

