const http = require("http");
const express = require("express");
const socketio = require("socket.io");

const router = require("./utils/router");

const {initBoard, removeBoard, makeMove} = require("./utils/boards")

const { addUser, removeUser, toggleUserState, getRoomState } = require("./utils/realtimedb");

const app = express();
const server = http.createServer(app);
const io = socketio(server);

app.use(router);

app.get("/",(req, res) => {
  console.log(req);
  res.send('Buna david!');
  return res.status(200);
})
app.post("/",(req, res) => {
  console.log(req);
  res.send('Buna david!');
  return res.status(200);
})

io.on("connect", (socket) => {
  console.log("Sombody in me!!!");
  console.log(socket);
  socket.on("join", (data) => {
    const { errors, user } = addUser(JSON.parse(data));

    if (errors.hasError) {
      console.log(errors.message);
    } else {
      console.log("Room: ", user.room, "User: ", user.name);
    }
  });
  
  socket.on("startGame", (data) => {
    const user = JSON.parse(data)
    let {errors, state} = getRoomState(user);

    if(errors.hasError){
      console.log(errors.message);
    }
    else{
      if(state === "game"){
        initBoard(user.room);
      }
      else{
        console.log("Game could not be started");
      }
    }
  });

  socket.on("playerMove", (data) => {
    const move = JSON.parse(data);

    // move = {
    //   board: ...,
    //   player: ...,
    //   room: ...
    // }

    const {errors, templateBoard} = makeMove(move.board, move.player, move.room)

    if(errors.hasError){
      console.log(errors.message);
    }
    else{
      templateBoard.board.forEach(row => {
        console.log(row.toString())
      })
      socket.to(move.room).emit("boardUpdate", (templateBoard))
    }
  })

  socket.on("endGame", (data) => {
    removeBoard(JSON.parse(data).room);
  });

  socket.on("toggleUserState", (data) => {
    toggleUserState(JSON.parse(data));
  });

  socket.on("removeUser", (data) => {
    removeUser(JSON.parse(data));
  });

  socket.on("disconnect", () => {
    console.log("disconected");
  });
});

server.listen(process.env.PORT || 5000, () =>
  console.log(`Server has started. PORT: 5000`)
);
