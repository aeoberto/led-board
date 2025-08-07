const express = require('express')
const mysql = require('mysql2')
const app = express()
const port = 3001
app.use(express.json());


const connection = mysql.createConnection({
  host:'localhost',
  user:'myuser',
  password:'mypassword',
  database:'users',
  waitForConnections: true,
  connectionLimit: 10,
  queueLimit: 0
})

async function verify_user(email, pass) {
  return new Promise((resolve, reject) => {
    connection.query("SELECT * FROM user", function (err, data, _fields) {
      if (err) return reject(err);
      for (const item of data) {
        if (email === item.Email && pass === item.Password) {
          return resolve(true);
        }
      }
      resolve(false); 
    });
  });
}
async function create_user(email, password, id) {
  const x = [{ message: "", color: "" }];
  const payload = JSON.stringify(x);
  const pre = [{ 1: "Im eating lunch", 2: "Im running late", 3:"Im working from home" }];
  const prelist = JSON.stringify(pre);
  return new Promise((resolve, reject) => {
    connection.query("SELECT * FROM user", function (err, data, _fields) {
      if (err) return reject(err);
      for (const item of data) {
        if (email === item.Email) {
          return resolve(false);
        }
      }
    });
    const insertQuery = "INSERT INTO user (Email, Password, Id, Payload, Preset) VALUES (?, ?, ?, ?, ?)";
    const values = [email, password, id, payload, prelist];

    connection.query(insertQuery, values, function (err, result) {
        if (err) return reject(err);
        resolve(true);
    });
  });
}


async function set_message(message, email, Color) {
  const x = [{ message: message, color: Color }];
  const payload = JSON.stringify(x);
  return new Promise((resolve, reject) => {
    connection.query("UPDATE user SET Payload = ? WHERE Email = ?", [payload, email], function (err, data, _fields) {
      if (err) return reject(err);
      resolve(message); 

    });
  });
}



async function get_all() {
  return new Promise((resolve, reject) => {
    connection.query("SELECT Email, Password, Id FROM user", function (err, data, _fields) {
      if (err) return reject(err);
      console.log(data)
      resolve(data); 

    });
  });
}

async function get_message(id) {
  return new Promise((resolve, reject) => {
    connection.query("SELECT * FROM user", function (err, data, _fields) {
      if (err) return reject(err);
      for (const item of data) {
        if (id === item.Id) {
          if(item.choice === 0){
            return resolve(item.Payload);}
          else{

          }
        }
      }
      resolve(false); 
    });
  });
}
async function get_pre(mail) {
  return new Promise((resolve, reject) => {
    connection.query("SELECT * FROM user", function (err, data, _fields) {
      if (err) return reject(err);
      for (const item of data) {
        if (mail === item.Email) {
          return resolve(item.Preset);
        }
      }
      resolve(false); 
    });
  });
}
async function edit_pre(num, message, mail) {
  let str = await get_pre(mail)
  let obj  = JSON.parse(str);
  obj[0][num] = message
  let payload = JSON.stringify(obj);
  console.log("UPDATE user SET Preset = ?, WHERE Email = ?", [obj, mail]);
  return new Promise((resolve, reject) => {
    connection.query("UPDATE user SET Preset = ? WHERE Email = ?", [payload, mail], function (err, data, _fields) {
      if (err) return reject(err);
      resolve(true);
    });
  });
}
edit_pre(4, "test", "TEST@GMAIL.COM")
async function delete_user(mail) {
  return new Promise((resolve, reject) => {
    connection.query(
      "DELETE FROM user WHERE Email = ?",
      [mail],
      function (err, result) {
        if (err) return reject(err);
        if (result.affectedRows === 0) {
          return resolve(false); 
        }
        resolve(true); 
      }
    );
  });
}
async function clear_message(mail) {
  const x = [{ message: "", color: "" }];
  const payload = JSON.stringify(x);
  return new Promise((resolve, reject) => {
    connection.query(
      "UPDATE user SET Payload = "+ "'" + payload +"'"+ " WHERE Email = " + "'" + mail+"'",
      function (err, result) {
        if (err) return reject(err);
        
        resolve(true); 
      }
    );
  });
}
app.get('/hey/:id', async(req, res) => {
 let id = req.params.id;
 let result = await get_message(id)
 result  = JSON.parse(result);
 let re = result[0].message + "*" + result[0].color;
 if(result != false)
  return res.send(re);
})



app.get('/verify/:email/:password', async(req, res) => {
  let email = req.params.email;
  let pass = req.params.password;
  let test = await verify_user(email, pass)

if(test){
  return res.send("Verified")
}
else{
  return res.send("failed")
}

})

app.get('/getall', async(req, res) => {
 
  let re = await get_all()


  return res.send(re)


})

app.get('/getpre/:email', async(req, res) => {
 
  let email = req.params.email;
  let pre = await get_pre(email)
  let re = JSON.parse(pre)

  return res.send(re)


})

app.put('/setmes/:message/:color/:email', async (req, res) => {
    let message = req.params.message;
    let mail = req.params.email;
    let color = req.params.color;
    let mess = await set_message(message, mail, color)

    return res.send("Message recived")
})
app.put('/edit_pre/:message/:num/:email', async (req, res) => {
    let message = req.params.message;
    let mail = req.params.email;
    let num = req.params.num;
    let mess = await edit_pre(num, message, mail)
    if(!mess){
      return res.send("There was an error")}
    else
      return res.send("Preset edited")

})


app.put('/newacc/:email/:password/:id', async (req, res) => {
    let email = req.params.email;
    let password = req.params.password;
    let id = req.params.id;
    let c = await create_user(email, password, id)
    if(!c){
      return res.send("bad")}
    else
      return res.send("good")

})

app.put('/delete/:email', async (req, res) => {
    let email = req.params.email;
  
    let c = await delete_user(email)
    if(!c){
      return res.send("This email is invalid or does not exist")}
    else
      return res.send("Account deleted")

})
app.put('/clear/:email', async (req, res) => {
    let email = req.params.email;
    
    let c = await clear_message(email)
    
    return res.send("Cleared")
  

})
app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})
