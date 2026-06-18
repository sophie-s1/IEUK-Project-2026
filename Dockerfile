# ==========================================
# Stage 1: Build Environment
# ==========================================
FROM gcc:15.3.0-trixie AS builder

# install CMake dep
RUN apt-get update && apt-get install -y cmake

WORKDIR /app

# Copy the source code
COPY src CMakeLists.txt ./

# Build with CMake
RUN mkdir build && cd build \
    && cmake -DCMAKE_BUILD_TYPE=Release .. \
    && make

# ==========================================
# Stage 2: Runtime Environment
# ==========================================
# Switch to the ultra-minimal busybox image
FROM busybox

WORKDIR /app

# Copy the statically linked binary from the builder stage
COPY --from=builder /app/build/turbine_analysis .

# Copy the data file into the container
COPY ["telemetry_data(in).csv", "."]

# Run the program
CMD ["./turbine_analysis"]
