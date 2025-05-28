# Use Ubuntu 20.04 as base image
FROM ubuntu:20.04

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    g++ \
    make \
    libsfml-dev \
    libx11-dev \
    libxrandr-dev \
    libudev-dev \
    libgl1-mesa-dev \
    libopenal-dev \
    libvorbis-dev \
    libflac-dev \
    && rm -rf /var/lib/apt/lists/*

# Create working directory
WORKDIR /app

# Copy project files
COPY . .

# Build the project
RUN make clean && make release

# Create a runtime stage (optional, for smaller final image)
FROM ubuntu:20.04 AS runtime

# Install runtime dependencies only
RUN apt-get update && apt-get install -y \
    libsfml-graphics2.5 \
    libsfml-window2.5 \
    libsfml-system2.5 \
    libsfml-audio2.5 \
    && rm -rf /var/lib/apt/lists/*

# Copy the built executable and data files
WORKDIR /app
COPY --from=0 /app/orbis-game .
COPY --from=0 /app/data ./data

# Set up display for GUI application (when running with X11 forwarding)
ENV DISPLAY=:0

# Run the game
CMD ["./orbis-game"]