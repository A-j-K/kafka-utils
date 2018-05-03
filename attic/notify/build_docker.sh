#!/bin/bash

VERSION="0.1"

docker build \
	-t kafka-notify:$VERSION \
	. 
echo "docker tag kafka-notify:$VERSION andykirkham/kafka-notify:$VERSION"
echo "docker push andykirkham/kafka-notify:$VERSION"

