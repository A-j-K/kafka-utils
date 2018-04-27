

SET(libnotify_SRCS
	callback.cpp
	utils/pipe.cpp
	config/config.cpp
	config/configfactory.cpp
	config/jsonconfig.cpp
)

ADD_LIBRARY(notifier_lib
	${libnotify_SRCS}
)

TARGET_LINK_LIBRARIES(notifier_lib
	curl
	pthread
	jansson
)

