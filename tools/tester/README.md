# webserv/tools/tester

## launch

```
Usage: ./launch <file.req> [port=80] [ip=localhost]
```

## check_all

For every `.req` file in `requests_samples/` \
(Need the corresponding `.resp`)
```
Usage: ./check_all <ip> <port> [methods_to_test]

Exemple:
./check_all localhost 80 GET      # Check only GET/*.req
./check_all localhost 80 GET POST # Check only GET/*.req && POST/*.req
./check_all localhost 80          # Check every methods */*.req
```

## check_all_conf

Start `webserv` using each `.conf` file in `conf/` \
Then send every `.req` with each port found in the request \
(IP is set to `localhost`)
```
Usage: ./check_all_conf [conf/to/test] [...]
```
