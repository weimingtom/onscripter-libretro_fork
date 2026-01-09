#!/bin/sh
set -eu
./update-deps.sh

TOOLCHAIN_IMAGE=ghcr.io/onionui/miyoomini-toolchain
docker run --rm -i -v $(pwd):/build ${TOOLCHAIN_IMAGE} /bin/bash <<EOF
set -eu
cd /build
source ~/setup-env.sh
make platform=miyoomini clean all -j4
EOF
