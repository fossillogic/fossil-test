# Base image
FROM ubuntu:22.04

# Install build dependencies
RUN apt-get update && apt-get install -y \
    python3 python3-pip meson ninja-build build-essential git curl \
    && rm -rf /var/lib/apt/lists/*

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
