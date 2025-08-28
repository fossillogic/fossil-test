# Base image
FROM ubuntu:22.04

# Set environment variables to avoid interaction
ENV DEBIAN_FRONTEND=noninteractive \
    TZ=UTC

# Install system dependencies and clean up
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    clang \
    gcc \
    g++ \
    gdb \
    llvm \
    libstdc++-10-dev \
    wget \
    python3 \
    python3-pip \
    git \
    tzdata && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

RUN python3 -m pip install --no-cache-dir meson==1.8.0 ninja==1.10.2

# Set workdir
WORKDIR /app

# Copy source code
COPY . /app

# Build project
RUN meson setup builddir && meson compile -C builddir

# Copy dist archives into container
RUN mkdir -p /dist && cp builddir/meson-dist/* /dist/

# Default command (optional)
CMD ["bash"]
