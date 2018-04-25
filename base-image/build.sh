#!/bin/bash

VERSION="0.1"

docker build \
	-t kafka-utils-base:$VERSION \
	. 

echo "docker tag kafka-utils-base:$VERSION andykirkham/kafka-utils-base:$VERSION"
echo "docker push andykirkham/kafka-utils-base:$VERSION"

