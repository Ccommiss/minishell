
FROM ubuntu:latest
RUN mkdir pipex
ENV TZ=Europe/Minsk
RUN apt-get update -y
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get install -y build-essential valgrind clang
COPY srcs /pipex/srcs
COPY includes /pipex/includes
COPY Makefile /pipex/