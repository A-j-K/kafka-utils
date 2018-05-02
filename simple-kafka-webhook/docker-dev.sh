#!/bin/bash

docker build \
	-t simple-kafka-webhook:dev \
	-f Dockerfile.dev \
	.

