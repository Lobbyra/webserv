FROM	httpd:2.4

RUN		apt update && \
		apt install -y	\
		vim	curl zsh

# Install CGI requirements
RUN		apt install -y	\
		php7.3			\
		php7.3-fpm

ARG		APACHE_ROOT="/usr/local/apache2"

COPY	temp.conf ${APACHE_ROOT}/conf/httpd.conf
