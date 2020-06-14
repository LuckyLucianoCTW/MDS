const { initBoard, removeBoard } = require("./boards");

const rooms = [];
const users = [];

const addUser = ({ name, room }) => {
  name = name.trim();
  room = room.trim();

  user = {
    name: name,
    room: room,
    ready: false,
  };

  roomTemplate = {
    name: room,
    users: [name],
    state: "lobby",
  };

  let errors = {
    message: "",
    hasError: false,
  };

  const u_index = users.findIndex(
    (user) => user.name === name && user.room === room
  );

  if (u_index == -1) {
    const r_index = rooms.findIndex((roomObj) => roomObj.name === room);

    if (r_index == -1) {
      users.push(user);
      rooms.push(roomTemplate);
    } else {
      if (rooms[r_index].users.length < 2) {
        users.push(user);
        rooms[r_index].users.push(user.name);
      } else {
        errors.message = "Room is full";
        errors.hasError = true;
        return { errors, user };
      }
    }
  } else {
    errors.message = "User already exists";
    errors.hasError = true;
    return { errors, user };
  }

  return { errors, user };
};

const removeUser = ({ name, room }) => {
  const u_index = users.findIndex(
    (user) => user.name === name && user.room === room
  );

  if (u_index !== -1) {
    let room = users[u_index].room;
    users.splice(u_index, 1);

    const r_index = rooms.findIndex((roomObj) => roomObj.name === room);

    if (r_index !== -1) {
      if (rooms[r_index].users.length === 1) {
        rooms.splice(r_index, 1);
      } else {
        const ru_index = rooms[r_index].users.findIndex(
          (user) => user === name
        );

        if (ru_index !== -1) {
          rooms[r_index].users.splice(ru_index, 1);
        } else {
          console.log("User not found in room!");
        }
      }
    } else {
      console.log("Room not found!");
    }
  } else {
    console.log("User not found!");
  }

  console.log("Users db");
  console.log(users);
  console.log("Rooms db");
  console.log(rooms);
};

const getRoomUsers = ({ room }) => {
  let errors = {
    message: "",
    hasError: false,
  };

  let roomUsers = [];

  const r_index = rooms.findIndex((roomObj) => roomObj.name === room);

  if (r_index !== -1) {
    rooms[r_index].users.forEach((user) => {
      let exists = users.find(
        (userObj) =>
          userObj.name == user && (userObj.room == rooms[r_index]).name
      );

      if (exists) {
        roomUsers.push(exists);
      }
    });
  } else {
    errors.message = "Room not found!";
    errors.hasError = true;
  }

  return { errors, users };
};

const getRoomState = ({ room }) => {
  let errors = {
    message: "",
    hasError: false,
  };

  let state = false;

  const r_index = rooms.findIndex((roomObj) => roomObj.name === room);

  if (r_index !== -1) {
    state = rooms[r_index].state;
  } else {
    errors.message = "Room not found!";
    errors.hasError = true;
  }

  return { errors, state };
};

const updateRoomState = (room) => {
  let state = "lobby";

  r_index = rooms.findIndex((roomObj) => roomObj.name === room);

  if (r_index !== -1) {
    roomName = rooms[r_index].name;
    roomUsrs = rooms[r_index].users;

    const u1 = users.find(
      (user) => user.name === roomUsrs[0] && user.room === roomName
    );
    const u2 = users.find(
      (user) => user.name === roomUsrs[1] && user.room === roomName
    );
    console.log(u1)
    console.log(u2)
    if (u1 && u2) {
      if (u1.ready && u2.ready) {
        state = "game";
      }
    }
    rooms[r_index].state = state;
  }
};

const toggleUserState = ({ name, room }) => {
  const u_index = users.findIndex(
    (user) => user.name === name && user.room === room
  );

  if (u_index !== -1) {
    users[u_index].ready = !users[u_index].ready;
    updateRoomState(room);
  }

  console.log("Users db");
  console.log(users);
  console.log("Rooms db");
  console.log(rooms);
};

exports.addUser = addUser;
exports.removeUser = removeUser;
exports.getRoomState = getRoomState;
exports.getRoomUsers = getRoomUsers;
exports.toggleUserState = toggleUserState;

exports.users = users;
exports.rooms = rooms;
