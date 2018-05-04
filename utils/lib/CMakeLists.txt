
INCLUDE_DIRECTORIES(
	"${PROJECT_SOURCE_DIR}/lib"
)

SET(lib_SRCS
	kafka_conf.cpp
	kafka_event_cb.cpp
	kafka_consume_cb.cpp
	curler.cpp
	curlerc.cpp
	hexdump.cpp
	config/abstract_config.cpp
	config/json_config.cpp
	config/config_factory.cpp
)

ADD_LIBRARY(kafka_utils_lib
	${lib_SRCS}
)

TARGET_LINK_LIBRARIES(kafka_utils_lib
	curl
	rdkafka
	rdkafka++
	pthread
	jansson
)

