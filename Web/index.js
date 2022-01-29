const express = require('express');
const app = express();
const enableWs = require('express-ws');

enableWs(app);
var clients =[];

/// view engine
app.set('view engine','ejs');

/// middlewares
app.use(express.static('public'));


app.get('/', (req,res) =>{
    res.render('index')
})
app.ws('/ws', (ws, req) =>{
    clients.push(ws);
    ws.on('message', (payload) =>
        {
            for(let i =1 ;i<clients.length;i++)
            {
                if(clients[i]!=ws)
                    clients[i].send(payload);
            }
        }
    )
})

server = app.listen(8080);