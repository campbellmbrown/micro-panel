FROM debian:bullseye-slim

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install --no-install-recommends -y \
    bzip2 \
    ca-certificates \
    git \
    git-lfs \
    make \
    ssh \
    wget \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /opt

# Install ARM GCC Toolchain
RUN wget -qO- https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 \
    | tar xj -C /opt/

ENV PATH=${PATH}:/opt/gcc-arm-none-eabi-10.3-2021.10/bin

# Install CMake (apt version is too old)
RUN mkdir -p /opt/cmake \
    && wget -qO- https://github.com/Kitware/CMake/releases/download/v4.2.0/cmake-4.2.0-linux-x86_64.tar.gz \
    | tar --strip-components=1 -xz -C /opt/cmake

ENV PATH=${PATH}:/opt/cmake/bin

# Set up git and use a non-root user
RUN git config --global --add safe.directory '*' \
    && useradd -ms /bin/bash runner

USER runner

WORKDIR /project
