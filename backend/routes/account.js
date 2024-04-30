const express = require('express');
const router = express.Router();
//const Account = require('../models/account_model'); //<--Ei tarvita?
const account = require('../models/account_model');


router.get('/',function(request,response){
    account.getAll(function(err,dbResult){
        if(err){
            response.json(err);
        }
        else{
            response.json(dbResult);
        }
    })
    });

router.get('/:id',
    function (request, response) {
        account.getById(request.params.id, function (err, dbResult) {

            if (err) {
                response.json(err);
            } else {
                response.json(dbResult[0]);
            }
        })
    });


router.post('/', 
function(request, response) {
  account.add(request.body, function(err, dbResult) {

    if (err) {
      response.json(err);
    } else {
      //response.json(dbResult);
      response.json(dbResult.affectedRows);
    }
  });
});


router.delete('/:id', 
function(request, response) {
  account.delete(request.params.id, function(err, dbResult) {

    if (err) {
      response.json(err);
    } else {
      response.json(dbResult.affectedRows);
    }
  });
});


router.put('/:id', 
function(request, response) {
  account.update(request.params.id, request.body, function(err, dbResult) {

    if (err) {
      response.json(err);
    } else {
      response.json(dbResult.affectedRows);
    }
  });
});

router.put('withdraw/:id', 
function(request, response) {
  account.withdraw(request.params.id, request.body, function(err, dbResult) {

    if (err) {
      response.json(err);
    } else {
      response.json(dbResult.affectedRows);
    }
  });
});

router.get('/balance/:id',
 function(request, response) {
    account.retrieveBalance(request.params.id, request.body, function(err, dbResult) {
      if (err) {
        response.json(err);
      } else {
        response.json(dbResult.affectedRows);
      }
    });
  }
);



module.exports=router;
