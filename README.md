# Åboat VRGP adapter

This repository contains the code for the `adapter` service that translates
calls from the [VRGP specification](https://github.com/aboamare/vrgp-specifications) into Åboat specific calls. This is only
needed for the Åboat, since the [VRGP service](https://github.com/RemoteBoatX/vrgp-service) implementation is supposed to be
as generic as possible. Other boats can directly hook into the VRGP service,
but since Åboat has its own communication protocol, it has to be adapted to
the VRGP protocol.

## How it works, what it does

The service is constantly listening to the VRGP service. When it receives a
request for anything (such as sensor data), it gets the data from the OpenDLV
sessions, and then sends it back to the VRGP service.

The adapter can also initiate calls on its own (for example to initiate a
connection to an MOC). It can then contact one of the VRGP service's endpoints.

The communication happens through WebSockets between the adapter and the VRGP
service, and trough OD4 Sessions between the adapter and the boat.

## WebSockets solution

The service is using [WebSocket++](https://github.com/zaphoyd/websocketpp) as a WebSockets solution.

## Building the project

### Dependencies

You need to have Docker installed for this to work.

---

To build the project, simply do:
`docker build -f Dockerfile.amd64 --tag="remoteboatx/aboat-vrgp-adapter:latest" .`

This should build an image called `remoteboatx/aboat-vrgp-adapter:latest`.

To run the image in a container (interactively, useful for inputting text at
the keyboard):
`docker run -it --rm remoteboatx/aboat-vrgp-adapter:latest`

The last command above runs the service in a container, until it is stopped.

## Test server

A test NodeJS server can be found in `examples/`. The server can be started by
running `node test.js`. It listens by default to WebSocket connections on port
8080.

To interface with it from the application that runs inside the Docker
container, the host network has to be exposed to the container. This can be
achieved in the following way for Linux:
- in the list of commands to `docker run`, `--network="host"` can be added.
  This exposes `localhost` within the Docker container as well, allowing the
  application to connect to the test server at the address
  `ws://localhost:8080/`.
