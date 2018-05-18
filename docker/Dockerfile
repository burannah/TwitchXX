FROM ubuntu
RUN apt-get update && \ 
    apt-get install build-essential \
                    software-properties-common \
                    git \
                    cmake \
                    libboost-regex-dev \
                    libboost-system-dev \
                    libboost-thread-dev \
                    libboost-test-dev \
                    libboost-random-dev \
                    libcpprest-dev \
                    libgtest-dev -y \
    && rm -rf /var/lib/apt/lists/*
RUN cd /usr/src/gtest \
    && cmake CMakeLists.txt \
    && make && cp *.a /usr/lib
