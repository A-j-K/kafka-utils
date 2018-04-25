FROM debian:stretch-slim

ENV	POCO_VER="1.9.0" \
	RDKAFKA_VERSION="0.11.4" \
 	AWS_SDK_CPP_VERSION="1.4.37" \
	YAML_CPP_VER="0.6.2" \
	GTEST_VER="1.8.0" \
	CMAKE_VER="3.11" \
	CMAKE_VERSION="3.11.1"

ENV DEPS_BUILD_TOOLS \
	build-essential \
	autoconf \
	g++ \
	gcc \
	make 

ENV DEPS_DEV_TOOLS \
	apt-utils \
	pkg-config \
	mlocate \
	vim \
	ssh \
	wget \
	xz-utils \
	unzip \
	file \
	git

ENV DEPS \
	curl \
	tar \
	python \
	ca-certificates \
	libargon2-0-dev \
	libc-dev \
	libffi-dev \
	libssl-dev \
	libxslt1-dev \
	libxml2 \
	libxml2-dev \
	libcurl3 \
	libedit2 \
	libsqlite3-0 \
	default-libmysqlclient-dev \
	mysql-client \
	libbison-dev \
	libcurl4-gnutls-dev \
	libedit-dev \
	libev-dev \
	libzip-dev \
	zlib1g-dev \
	libsodium-dev \
	libmbedtls-dev \
	libyaml-dev

RUN	DEBIAN_FRONTEND=noninteractive apt-get update \
	&& DEBIAN_FRONTEND=noninteractive apt-get install -y \
		$DEPS $DEPS_DEV_TOOLS $DEPS_BUILD_TOOLS --no-install-recommends \
	&& mkdir -p /tmp/build && cd /tmp/build \
	&& curl -sSL https://cmake.org/files/v${CMAKE_VER}/cmake-${CMAKE_VERSION}-Linux-x86_64.tar.gz > cmake-${CMAKE_VERSION}-Linux-x86_64.tar.gz \
	&& tar -v -zxf cmake-${CMAKE_VERSION}-Linux-x86_64.tar.gz \
	&& rm -f cmake-${CMAKE_VERSION}-Linux-x86_64.tar.gz \
	&& cd cmake-${CMAKE_VERSION}-Linux-x86_64 \
	&& cp -rp bin/* /usr/local/bin/ \
	&& cp -rp share/* /usr/local/share/ \
	&& cd /tmp && rm -rf build \
	&& mkdir -p /tmp/build && cd /tmp/build \
	&& curl -sSL https://github.com/google/googletest/archive/release-${GTEST_VER}.zip > gtest.zip \
	&& unzip gtest.zip && rm -f gtest.zip \
	&& cd googletest-release-${GTEST_VER} && mkdir build && cd build \
	&& cmake .. && make && make install \
	&& cd /tmp && rm -rf build \
	&& mkdir -p /tmp/build && cd /tmp/build \
	&& curl -sSL https://github.com/jbeder/yaml-cpp/archive/yaml-cpp-${YAML_CPP_VER}.zip > yaml-cpp.zip \
	&& unzip yaml-cpp.zip && rm -f yaml-cpp.zip \
	&& cd yaml-cpp-yaml-cpp-${YAML_CPP_VER} \
	&& mkdir build.dir && cd build.dir \
	&& cmake .. \
		-DCMAKE_BUILD_TYPE=Release \
		-DBUILD_SHARED_LIBS=ON \
		-DYAML_CPP_BUILD_TESTS=OFF \
	&& make && make install \
	&& cd /tmp && rm -rf build \
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
	&& cd /tmp && rm -rf build 
	&& DEBIAN_FRONTEND=noninteractive apt-get remove -y $DEPS_BUILD_TOOLS $DEPS_TOOLS \
	&& DEBIAN_FRONTEND=noninteractive apt -y autoremove \
	&& rm -r /var/lib/apt/lists/*

#	&& mkdir -p /tmp/build && cd /tmp/build \
#	&& curl -sSL https://github.com/aws/aws-sdk-cpp/archive/${AWS_SDK_CPP_VERSION}.zip > aws-sdk-cpp-${AWS_SDK_CPP_VERSION}.zip \
#	&& unzip aws-sdk-cpp-${AWS_SDK_CPP_VERSION}.zip \
#	&& rm -f aws-sdk-cpp-${AWS_SDK_CPP_VERSION}.zip \
#	&& cd aws-sdk-cpp-${AWS_SDK_CPP_VERSION} && mkdir build && cd build \
#	&& cmake .. \
#               -DCMAKE_BUILD_TYPE=Release \
#		-DBUILD_ONLY="sqs;s3;transfer;dynamodb;s3-encryption;apigateway" \
#                -DENABLE_TESTING=OFF \
#                -DAUTORUN_UNIT_TESTS=OFF \
#                -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS} \
#        && make \
#        && make install \
#	&& cd /tmp && rm -rf build \


