# Multi-stage Dockerfile for Boost.MySQL Demo

# Stage 1: Build stage
FROM ubuntu:22.04 AS builder

# Avoid prompts from apt
ENV DEBIAN_FRONTEND=noninteractive

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    python3 \
    python3-pip \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Install Conan
RUN pip3 install conan

# Create and configure Conan profile manually
RUN mkdir -p ~/.conan2/profiles && \
    echo "[settings]" > ~/.conan2/profiles/default && \
    echo "arch=x86_64" >> ~/.conan2/profiles/default && \
    echo "build_type=Debug" >> ~/.conan2/profiles/default && \
    echo "compiler=gcc" >> ~/.conan2/profiles/default && \
    echo "compiler.cppstd=20" >> ~/.conan2/profiles/default && \
    echo "compiler.libcxx=libstdc++11" >> ~/.conan2/profiles/default && \
    echo "compiler.version=12" >> ~/.conan2/profiles/default && \
    echo "os=Linux" >> ~/.conan2/profiles/default && \
    echo "" >> ~/.conan2/profiles/default && \
    echo "[conf]" >> ~/.conan2/profiles/default && \
    echo "tools.system.package_manager:mode=install" >> ~/.conan2/profiles/default && \
    echo "tools.system.package_manager:sudo=True" >> ~/.conan2/profiles/default

# Create working directory
WORKDIR /app

# Copy project files
COPY conanfile.txt CMakeLists.txt main.cpp ./

# Install dependencies with Conan
WORKDIR /app/build
RUN conan install .. --build=missing -pr:b=default -s build_type=Debug

# Configure and build
WORKDIR /app/build/Debug
RUN cmake ../.. -DCMAKE_TOOLCHAIN_FILE=generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug

RUN make -j$(nproc)

# Stage 2: Runtime stage
FROM ubuntu:22.04

# Install runtime dependencies
RUN apt-get update && apt-get install -y \
    libstdc++6 \
    mariadb-client \
    && rm -rf /var/lib/apt/lists/*

# Create application directory
WORKDIR /app

# Copy the built executable from builder stage
COPY --from=builder /app/build/Debug/mysql_demo .

# Set environment variables (can be overridden at runtime)
ENV DB_HOST=host.docker.internal
ENV DB_PORT=3306
ENV DB_NAME=test_db
ENV DB_USER=test_user
ENV DB_PASS=test_pass

# Run the application
CMD ["./mysql_demo"]