FROM ubuntu:latest
LABEL authors="ilya"

WORKDIR /app
COPY sort.h .
COPY sort_parallel.cpp .
COPY test.cpp .
COPY CMakeLists.txt .

RUN apt-get update
RUN apt-get install -y cmake build-essential doctest-dev g++
RUN apt-get clean

RUN cmake -S . -B build && cd build && make
CMD ./build/project_tp