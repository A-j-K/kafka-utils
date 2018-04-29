

SET(libnotify_SRCS
	curler.cpp
	callback.cpp
	pipe.cpp
	absconfig.cpp
	configfactory.cpp
	jsonconfig.cpp
)

ADD_LIBRARY(notifier_lib
	${libnotify_SRCS}
)

TARGET_LINK_LIBRARIES(notifier_lib
	curl
	pthread
	jansson
)

