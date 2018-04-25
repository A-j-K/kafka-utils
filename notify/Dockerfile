FROM andykirkham/kafka-utils-base:0.1

RUN	DEBIAN_FRONTEND=noninteractive apt-get update \
	&& DEBIAN_FRONTEND=noninteractive apt-get install -y \
		$DEPS_DEV_TOOLS $DEPS_BUILD_TOOLS --no-install-recommends \

	&& mkdir -p /tmp/build && cd /tmp/build \
	&& curl -sSL https://github.com/edenhill/librdkafka/archive/v${RDKAFKA_VERSION}.zip > librdkafka.zip \
	&& unzip librdkafka.zip && rm -f librdkafka.zip \
	&& cd librdkafka-${RDKAFKA_VERSION} \
	&& ./configure --prefix=/usr/local && make all install \
	&& cp examples/rdkafka_consumer_example /usr/local/bin/rdkafka_consumer \
	&& cp examples/rdkafka_example  /usr/local/bin/rdkafka \
	&& cp examples/rdkafka_simple_producer /usr/local/bin/rdkafka_producer \
	&& cp examples/rdkafka_performance /usr/local/bin/rdkafka_performance \
	&& cp examples/kafkatest_verifiable_client /usr/local/bin/kafkatest_verifiable_client \
	&& cd /tmp && rm -rf build \
	&& mkdir -p /tmp/build && cd /tmp/build \
	&& curl -sSL https://pocoproject.org/releases/poco-${POCO_VER}/poco-${POCO_VER}-all.tar.gz > poco.tar.gz \
	&& tar -zxf poco.tar.gz && rm -f poco.tar.gz \
	&& cd poco-${POCO_VER}-all && mkdir cmake-build && cd cmake-build \
	&& cmake .. \
		-DCMAKE_BUILD_TYPE=Release \
		-DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS} \
		-DENABLE_DATA_ODBC=Off \
	&& make && make install \
	&& cd /tmp && rm -rf build \
	&& mkdir -p /tmp/build && cd /tmp/build \
	&& curl -sSL https://github.com/aws/aws-sdk-cpp/archive/${AWS_SDK_CPP_VERSION}.zip > aws-sdk-cpp-${AWS_SDK_CPP_VERSION}.zip \
	&& unzip aws-sdk-cpp-${AWS_SDK_CPP_VERSION}.zip \
	&& rm -f aws-sdk-cpp-${AWS_SDK_CPP_VERSION}.zip \
	&& cd aws-sdk-cpp-${AWS_SDK_CPP_VERSION} && mkdir build && cd build \
	&& cmake \
                -DCMAKE_BUILD_TYPE=Release \
		-DBUILD_ONLY="sqs;s3;transfer;dynamodb;s3-encryption;apigateway" \
                -DENABLE_TESTING=OFF \
                -DAUTORUN_UNIT_TESTS=OFF \
                -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS} \
                .. \
        && make \
        && make install \
	&& cd /tmp && rm -rf build \
	&& DEBIAN_FRONTEND=noninteractive apt-get remove -y $DEPS_TEMP $DEPS_TOOLS \
	&& DEBIAN_FRONTEND=noninteractive apt -y autoremove \
	&& rm -r /var/lib/apt/lists/*


