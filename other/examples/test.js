const WebSocket = require('ws');
const server = new WebSocket.Server({
    port: 8080
});

server.on('connection', function(socket) {

    console.log('Got a new connection!');

    while (socket.readyState !== WebSocket.OPEN) {}

    setInterval(() => {
        socket.send('{"bye": {"url": "ws-moc-url"}}');
        console.log('sending message');
    }, 4000);

    // when you receive a message, send that message back
    // basic ping-pong echoing
    socket.on('message', function(msg) {
        console.log('Received: ' + msg);
        socket.send(Buffer.from(msg, 'hex').toString('utf8'));
    });

    // on close print a relevant message
    socket.on('close', function() {
        console.log('Closing connection: ' + socket);
    });
});
