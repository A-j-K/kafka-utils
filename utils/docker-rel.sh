#!/bin/bash

COMMITHASH=$(git rev-parse --short=12 --verify HEAD)
VERSION=$(grep VERSION generic-kafka-webhook/version.h | awk '{print $3}' | tr -d /\"//)

docker build \
	-t generic-kafka-webhook:rel-v${VERSION}--${COMMITHASH} \
	-f Dockerfile.rel \
	.

echo "docker tag generic-kafka-webhook:rel-v${VERSION}--${COMMITHASH} andykirkham/generic-kafka-webhook:v${VERSION}--${COMMITHASH}"
echo "docker push andykirkham/generic-kafka-webhook:v${VERSION}--${COMMITHASH}"


