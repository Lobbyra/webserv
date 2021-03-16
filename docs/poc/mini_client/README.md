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

## Example

This request : `GET / HTTP/1.1\nHost: example.com\r\n\r\n`

⚠️ I added a trashy Host header cause some web servers throw error 400 without header

On example.com respond something like this :

⚠️ What is important here is that your program write datas and not stay stuck on
reading.

⚠️ You can use GNL but you must replace read() by the good function.

```text
HTTP/1.1 200 OK
Age: 529572
Cache-Control: max-age=604800
Content-Type: text/html; charset=UTF-8
Date: Mon, 15 Mar 2021 14:00:47 GMT
Etag: "3147526947+ident"
Expires: Mon, 22 Mar 2021 14:00:47 GMT
Last-Modified: Thu, 17 Oct 2019 07:18:26 GMT
Server: ECS (dcb/7ECB)
Vary: Accept-Encoding
X-Cache: HIT
Content-Length: 1256
html>
<head>
    <title>Example Domain</title>

    <meta charset="utf-8" />
    <meta http-equiv="Content-type" content="text/html; charset=utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <style type="text/css">
    body {
        background-color: #f0f0f2;
        margin: 0;
        padding: 0;
        font-family: -apple-system, system-ui, BlinkMacSystemFont, "Segoe UI", "Open Sans", "Helvetica Neue", Helvetica, Arial, sans-serif;
        
    }
    div {
        width: 600px;
        margin: 5em auto;
        padding: 2em;
        background-color: #fdfdff;
        border-radius: 0.5em;
        box-shadow: 2px 3px 7px 2px rgba(0,0,0,0.02);
    }
    a:link, a:visited {
        color: #38488f;
        text-decoration: none;
    }
    @media (max-width: 700px) {
        div {
            margin: 0 auto;
            width: auto;
        }
    }
    </style>    
</head>

<body>
<div>
    <h1>Example Domain</h1>
    <p>This domain is for use in illustrative examples in documents. You may use this
    domain in literature without prior coordination or asking for permission.</p>
    <p><a href="https://www.iana.org/domains/example">More information...</a></p>
</div>
</body>
</html>
```
