const express = require('express');
const http = require('http');
const { Server } = require('socket.io');

const app = express();
const server = http.createServer(app);
const io = new Server(server);

// Serve static files from current directory
app.use(express.static(__dirname));

let score = 0;

// Emit score every second
setInterval(() => {
  score += Math.floor(Math.random() * 10); // simulate score updates
  io.emit('scoreUpdate', { score });
}, 1000);

io.on('connection', socket => {
  // Send current score when a new client connects
  socket.emit('scoreUpdate', { score });
});

const PORT = process.env.PORT || 3000;
server.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
