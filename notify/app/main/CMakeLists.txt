

CMAKE_MINIMUM_REQUIRED(VERSION 3.11)
PROJECT(notifier)

SET(notify_SRCS
	main.cpp
)

ADD_EXECUTABLE(notifier
	${notify_SRCS}
)

TARGET_LINK_LIBRARIES(notifier
	notify
	${POCO_LIBS}
)

