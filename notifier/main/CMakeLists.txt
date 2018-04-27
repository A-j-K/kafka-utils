
PROJECT(notifier)

SET(notify_SRCS
        main.cpp
)
ADD_EXECUTABLE(notifier
        ${notify_SRCS}
)

TARGET_LINK_LIBRARIES(notifier
	notifier_lib
)

INSTALL(PROGRAMS ${PROJECT_BINARY_DIR}/notifier
	DESTINATION /usr/bin
)
	
