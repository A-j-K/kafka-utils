
PROJECT("simple-kafka-webhook")

SET(simple_kafka_webhook_SRCS
        main.cpp
)

ADD_EXECUTABLE("simple-kafka-webhook"
        ${simple_kafka_webhook_SRCS}
)

TARGET_LINK_LIBRARIES("simple-kafka-webhook"
	simple_kafka_webhook_lib
)

INSTALL(PROGRAMS ${PROJECT_BINARY_DIR}/simple-kafka-webhook
	DESTINATION /usr/bin
)
	
