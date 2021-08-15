FROM ubuntu:latest 

RUN apt-get -y update && \
    apt-get install -y cmake g++ libgtest-dev libgmp-dev

ADD . /src/testing

WORKDIR /src/testing/build

RUN cmake .. && \
    cmake --build .
