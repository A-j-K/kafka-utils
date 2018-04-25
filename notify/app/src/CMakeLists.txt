

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src")

SET(libnotify_SRCS
	app.cpp
	config/configfactory.cpp
	config/jsonconfig.cpp
)

ADD_LIBRARY(libnotify
	${libnotify_SRCS}
)

TARGET_LINK_LIBRARIES(libnotify
	${POCO_LIBS}
)

