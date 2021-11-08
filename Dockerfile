FROM ubuntu:latest
RUN mkdir minishell
ENV TZ=Europe/Minsk
RUN apt-get update -y
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get install -y build-essential valgrind clang libreadline 
COPY srcs /minishell/srcs
COPY includes /minishell/includes
COPY libft /minishell/libft
COPY Makefile /minishell/
