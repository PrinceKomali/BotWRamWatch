const express = require("express")
const ws = require("ws");
const app = express();
const ews = require("express-ws")(app)
const EE = require("events");
app.use(express.static(__dirname))
// const wss = new ws.Server({ noServer: true });
const e = new EE;

const wsc = new ws("ws://localhost:3002/ws");
wsc.on('open', _ =>{
    wsc.send("foo")
})

app.use(require('body-parser').urlencoded());
app.post("/", (req, res) => {
    if(req.body.health) e.emit("msg", JSON.stringify(req.body));   
    else console.log(req.body.text);
    res.sendStatus(200)
})
app.get("/", (req, res) => {
    res.sendFile(__dirname + "/post.html");
})
app.ws("/ws", (w,r)=>{
    e.on("msg",m => {
        w.send(m)
    })
    w.on('message', msg=>{
        w.send("hi")
    })
})
const server = app.listen(3002)
// server.on('upgrade', (req, sock, head) => {
//     wss.handleUpgrade(req, sock, head, sock => {
//         wss.emit('connection', sock, req);
//     })
// })