#!/bin/bash

docker build \
	-t simple-kafka-webhook:rel \
	-f Dockerfile.rel \
	.


