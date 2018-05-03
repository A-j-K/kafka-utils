

SET(libnotify_SRCS
	pipe.cpp
	kafka.cpp
	kafkapp.cpp
	curler.cpp
	callback.cpp
	absconfig.cpp
	jsonconfig.cpp
	configfactory.cpp
)

ADD_LIBRARY(notifier_lib
	${libnotify_SRCS}
)

TARGET_LINK_LIBRARIES(notifier_lib
	curl
	rdkafka
	pthread
	jansson
)

