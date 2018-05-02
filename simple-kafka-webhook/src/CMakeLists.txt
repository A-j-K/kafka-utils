

SET(lib_SRCS
	kafka.cpp
	kafka_event_cb.cpp
	curler.cpp
	curlerc.cpp
	config/abstract_config.cpp
	config/json_config.cpp
	config/config_factory.cpp
)

ADD_LIBRARY(webhook_lib
	${lib_SRCS}
)

TARGET_LINK_LIBRARIES(webhook_lib
	curl
	rdkafka
	rdkafka++
	pthread
	jansson
)

