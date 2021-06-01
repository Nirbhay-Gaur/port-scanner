# Port Scanner
A port scanner is a program which probes a server for open ports by attempting a connection to the server via each port in turn. The program usually then reports which ports were open and which were closed. Open ports may constitute security vulnerabilities as they allow remote machines to connect. Unexpectedly-open ports may indicate malicious software listening for instructions.

This is a simple command line tool that determines which ports on the server is open.

## Prerequisite
Port scanner uses SFML Network Module to check if the port is open or not.

**SFML** [[documentation]](https://www.sfml-dev.org/documentation/2.5.1/) [[download]](https://www.sfml-dev.org/download.php)

**S**imple and **F**ast **M**ultimedia **L**ibrary is a cross-platform software development library designed to provide a simple application programming interface to various multimedia components in computers.

> For this tool to work properly, make sure you have SFML installed on your computer system.

## Installation
The output file `scanport` is provided but if you wish to compile the program from the source code, run the following command:
`g++ main.cpp -o scanport -lsfml-network -lsfml-system`
> For compiling in windows, please refer SFML documentation.

## Usage
Using port scanner is very simple but if you need any help, run the following command: `./scanport -h`

To start port scanner, simply run `./scanport` in the terminal. The tool will ask for the address of the network and port(s) to scan.

Port scanner also support single line command: `./scanport [address] [port(s)]`

