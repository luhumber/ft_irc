# Project ft_irc

## Introduction
Welcome to the ft_irc project at 42 School. This project involves creating an IRC (Internet Relay Chat) server and client using sockets. The goal is to implement basic principles of network communication and develop an application that allows users to connect, chat, and interact in real-time.

## Features
- **IRC Server:** Implementation of an IRC server capable of managing multiple chat channels concurrently using ***Hexchat***.
- **IRC Commands:** Setup of basic commands such as JOIN, PART, PRIVMSG, etc.
- **User Management:** Handling user authentication and their participation in channels.

## Commands
The IRC server implements various commands to manage user interactions and the state of the server. Here is a brief overview of the implemented commands:

- **CAP:** Capability negotiation between the client and server.
- **PASS:** Authenticate with a server password.
- **JOIN:** Join a specific channel.
- **PART:** Leave a channel.
- **QUIT:** Disconnect from the server.
- **NICK:** Set or change your nickname.
- **USER:** Specify username, hostname, servername, and realname.
- **KICK:** Remove a user from a channel.
- **MODE:** Set channel or user modes.
- **WHO:** Display information about users.
- **TOPIC:** Set or display the topic of a channel.
- **INVITE:** Invite a user to a channel.
- **PRIVMSG:** Send a private message to a user or a message to a channel.

These commands are crucial for managing the server, channels, and user interactions. Each command serves a specific purpose, contributing to the functionality of the IRC server.
