# Use an appropriate base image
FROM gcc:latest

# Set the working directory
WORKDIR /app

# Install necessary dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

# Copy files from the requirement folder to the container
COPY . /app

# Run make to build the project
RUN make

# Set the default command to run the executable
ENTRYPOINT ["./cmpsh"]