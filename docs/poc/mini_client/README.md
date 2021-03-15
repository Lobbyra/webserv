# Notes about mini\_client

## Purpose

The goal is to write a program that take an IP and request a GET on the root to this IP on the network.

For example, to get the ip of www.google.com, ping the url.
or do this :

```bash
nslookup www.google.com | grep Address | tail -n +2 | cut -d ':' -f 2 | cut -c2-
```

## Notions

*These are the notions to study, in order, to code this program.*

- Reference video : [Video](https://www.youtube.com/watch?v=bdIiTxtMaKA&list=PL9IEJIKnBJjH_zM5LnovnoaKlXML5qh17&index=2)
- Send Recv ressources : [Link](https://bousk.developpez.com/cours/reseau-c++/TCP/05-envoi-reception-serveur/)

- Socket function to create a socket. (man socket)
- sockaddr\_in struct
  - sin\_family
  - sin\_port
  - sin\_addr
- Connect function to connect the socket to the IP.
- Send the request to the socket fd with the send function.
- Recieve the response by recv function.
- Print the response to STDOUT.

## Usage

*Usage of the PORT argument is to fit with the mini_serv. You should be able to test your mini_serv with your mini_client.*

./mini\_client [IP] [PORT]

## Expected behavior

If a syscall fail, it will print the syscall involved and exit the program.

Else, it will display on STDOUT the FULL response in ASCII that he recieved.

Code is to put in ./login/\*.
