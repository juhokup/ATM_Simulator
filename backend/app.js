var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
const bodyParser = require('body-parser');
var logger = require('morgan');
const dotenv=require('dotenv');
const jwt = require('jsonwebtoken');

var currencyRouter = require('./routes/currency');
var accountRouter = require('./routes/account');
var cardRouter = require('./routes/card');
var customerRouter = require('./routes/customer');
var transactionRouter = require('./routes/transaction');
var loginRouter = require('./routes/login');
var card_privilegesRouter = require('./routes/card_privileges');

var storedProcRouter = require('./routes/stored_proc');


var app = express();
dotenv.config();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(bodyParser.json());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/login', loginRouter);

app.use(authenticateToken);
app.use('/card', cardRouter);
app.use('/currency', currencyRouter);
app.use('/customer', customerRouter);
app.use('/account', accountRouter);
app.use('/Transaction', transactionRouter);
app.use('/card_privileges', card_privilegesRouter);
app.use('/stored_proc', storedProcRouter);




function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization']
    const token = authHeader && authHeader.split(' ')[1]
  
    console.log("token = "+token);
    if (token == null) return res.sendStatus(401)
  
    jwt.verify(token, process.env.MY_TOKEN, (err, user) => {
      console.log(err)
  
      if (err) return res.sendStatus(403)
  
      req.user = user
  
      next()
    })
  }



module.exports = app;
