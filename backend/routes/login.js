const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const login = require('../models/login_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

router.post('/', 
  function(request, response) {
    if(request.body.cardNumber && request.body.pin){
      const user = request.body.cardNumber;
      const pass = request.body.pin;

      login.checkPassword(user, function(err, dbResult) {        
        if(err){
          response.json(err.code);
        }
        else{
          if (dbResult.length > 0) {
            bcrypt.compare(pass,dbResult[0].pin, function(err ,compareResult) {
              if(compareResult) {
                console.log("success");

                login.expireCheck(user, function(err, dbResult) {
                  if(err) response.json(err.code);
                  else console.log("cardStatus set 0 if card expired");
                
                login.resetAttempts(user, function(err, dbResult) {
                  if(err) response.json(err.code);
                  else console.log("attempts reset to 3 if cardStatus =1");
                });

                  //response.json(dbResult.affectedRows);
                  //expireResult = dbResult.affectedRows;
                });

                const token = generateAccessToken({ cardNumber: user });
                console.log(token);
                response.send(token);
              }
              else {
                  console.log("wrong password");

                  login.cardWrongPass(user, function(err, dbResult) {
                    if (err) {
                        console.error("Error updating pinAttempts and cardStatus:", err);
                        response.status(500).json({ error: "Internal Server Error" });
                    } else {
                        console.log("wrong pass: attempts decreased if (> 0) AND cardStatus changed to 0 if pinAttempts = 0");
                    }
                });
/*                   login.cardNoAttemptsLeft(user, function(err, dbResult) {
                    if(err) response.json(err.code);
                    else console.log("cardStatus set 0 if (pinAtts = 0)");
                  }); */
                  
                  // gets from card the current values in order to be sent to Qt and show according msg-boxes there:
                  login.checkCard(user, function(err, dbResult) {
                    if(err) response.json(err.code);
                    else {
                      response.json(dbResult[0]); // sends current pinAttempts and cardStatus
                    }
                  });
                }
            }
            );
        }

        else{
          console.log("user does not exist");
          response.send(false);
        }
      }
      }
    );
  }
else{
  console.log("username or password missing");
  response.send(false);
}
}
);

function generateAccessToken(cardNumber) {
dotenv.config();
return jwt.sign(cardNumber, process.env.MY_TOKEN, { expiresIn: '600s' }); // 600s
}

module.exports=router;