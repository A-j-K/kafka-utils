

SET(lib_simple_kafka_webhook_SRCS
	kafka.cpp
	curler.cpp
	curlerc.cpp
	config/abstract_config.cpp
	config/json_config.cpp
	config/config_factory.cpp
)

ADD_LIBRARY(simple_kafka_webhook_lib
	${lib_simple_kafka_webhook_SRCS}
)

TARGET_LINK_LIBRARIES(simple_kafka_webhook_lib
	curl
	rdkafka
	pthread
	jansson
)

