

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(notify)

SET(notify_SRCS
	main.cpp
)

ADD_EXECUTABLE(notify
	${notify_SRCS}
)

TARGET_LINK_LIBRARIES(notify
	libnotify
	${POCO_LIBS}
)

