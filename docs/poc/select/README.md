# Notes about mini\_client

## Purpose

The goal of this Proof Of Concept is to reach the goal and the power of asynchronous programming.
Select will give the power to check if a socket is ready to read in it.

In our project we will use non-blocking FD by changing it with fcntl(fd, F_SETFL, O_NONBLOCK).
With a non-blocking socket, accept() will not block the process until a new connection.
It will be usefull to manage incomming requests and work to do in the task stack.

We could be to accept new connections and response to many clients in a non-blocking system.

To resume, select save us the time between a new connection and the full reception of the client-request.

## Subject

This is simple, a program that print "Hello !" every seconds.

Buuuuuuuuuuut when a client is trying to connect to your program, it print "\*Toc toc\*" on stdout.

## Notions

*These are the notions to study, in order, to code this program.*

Various ressources :

man select
https://stackoverflow.com/questions/12861956/is-it-possible-and-safe-to-make-an-accepting-socket-non-blocking
https://forum.hardware.fr/hfr/Programmation/C-2/select-avec-socket-sujet_86547_1.htm
https://notes.shichao.io/unp/ch6/#chapter-6-io-multiplexing-the-select-and-poll-functions

## Usage

## Expected behavior

## Example

