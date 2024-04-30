const express = require('express');
const transaction = require('../models/transaction_model');
const router = express.Router();

router.get('/getAll',function(request,response){
  console.log(`getAll:`)
  transaction.getAll(function(err,dbResult){
    if(err){
      response.json(err);
    }
    else{
      response.json(dbResult);
    }
  })
});

router.get('/getNext',function(request,response){
  console.log(`getNext:`)
  transaction.getNext(function(err,dbResult){
    if(err){
      response.json(err);
    }
    else{
      response.json(dbResult);
    }
  })
});


router.get('/getPrevious',function(request,response){
  console.log(`getPrevious:`)
  transaction.getPrevious(function(err,dbResult){
    if(err){
      response.json(err);
    }
    else{
      response.json(dbResult);
    }
  })
});

router.get('/getById/:id',function(request,response){
  console.log(`getById: ${request.params.id}`)
  transaction.getById(request.params.id, function(err,dbResult){
    if(err){
      response.json(err);
    }
    else{
      response.json(dbResult);
    }
  })
});

router.post('/',
function(request, response) {
  transaction.withdraw(request.body, function(err, dbResult) {
    if (err) {
      response.json(err.code);
    }
    else {
      //response.json(dbResult);
      response.json(dbResult.affectedRows);
    }
  });
});



router.get('/getPreviousById/:id',function(request,response){
  console.log(`getPreviousById: ${request.params.id}`)
  transaction.getPreviousById(request.params.id, function(err,dbResult){
    if(err){
      response.json(err);
    }
    else{
      response.json(dbResult);
    }
  })
});

router.get('/getNextById/:id',function(request,response){
  console.log(`getNextById: ${request.params.id}`)
  transaction.getNextById(request.params.id, function(err,dbResult){
    if(err){
      response.json(err);
    }
    else{
      response.json(dbResult);
    }
  })
});








    router.get('/:user',
    function (request, response) {
        transaction.getById(request.params.user, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult);
            }
        })
    });


router.post('/', 
function(request, response) {
  transaction.add(request.body, function(err, dbResult) {
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
  transaction.delete(request.params.id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult.affectedRows);
    }
  });
});


router.put('/:id', 
function(request, response) {
  customer.update(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult.affectedRows);
    }
  });
});

module.exports = router;