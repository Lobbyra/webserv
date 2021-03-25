# docker_nginx

## Introduction

A docker nginx container that build and start a fresh Nginx.

./www/ is the path that will be your website.

./nginx.conf is config file that nginx will take.
You can pass a path to a config file in argument of launch.sh

## Prerequisites

You need a working docker daemon and bash.

## Usage

`./launch.sh [path_to_config_file]`
