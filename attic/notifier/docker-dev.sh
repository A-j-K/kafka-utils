#!/bin/bash

docker build \
	-t notifier-dev:latest \
	-f Dockerfile.dev \
	.

