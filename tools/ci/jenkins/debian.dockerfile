FROM ubuntu:bionic

# Needed for dependencies like "tzdata" which might ask for some interactive input (besides yes and no)
ENV DEBIAN_FRONTEND=noninteractive

# Load dependencies
# Note:
# - python - required to run python files, eventhough a python toolchain is installed,
#            to run a script using this python toolchain, a startup python script needs
#            to be executed to discover binaries.
# - gpgv - needed add the key to apt.
# - libxml2-dev - needed for LLVM (need to be removed).
# - openjdk-11-jdk, unzip, zip are used by bazel
RUN apt-get update && apt-get install -y git sudo build-essential unzip zip gzip libc6-dev curl gpgv python libxml2-dev openjdk-11-jdk

# Add Jenkins user
RUN sudo groupadd -g 1000 1000
RUN sudo useradd -u 1000 -s /bin/sh -g 1000 1000
RUN sudo mkdir -p /home/1000
RUN sudo chown -R 1000:1000 /home/1000
