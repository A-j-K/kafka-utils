#!/bin/bash

docker build \
	-t notifier-rel:latest \
	-f Dockerfile.rel \
	.


