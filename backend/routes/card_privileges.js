
const express = require('express');
const card_privileges = require('../models/card_privileges_model');
const router = express.Router();


router.get('/',function(request,response){
  card_privileges.getidcard(function(err,dbResult){
      if(err){
          response.json(err.code);
      }
      else{
          response.json(dbResult);
      }
  })
  });

  router.get('/:user',
  function (request, response) {
    card_privileges.getidcard(request.params.user, function (err, dbResult) {
          if (err) {
              response.json(err.code);
          } else {
              response.json(dbResult[0]);
          }
      })
  });

  router.get('/getAccountDebit/:idcard',function(request,response){
    console.log(`getAccountDebit: ${request.params.idcard}`)
    card_privileges.getAccountDebit(request.params.idcard, function(err,dbResult){
      if(err){
        response.json(err);
      }
      else{
        response.json(dbResult[0]);
      }
    })
  });
  
  router.get('/getAccountCredit/:idcard',function(request,response){
    console.log(`getAccountCredit: ${request.params.idcard}`)
    card_privileges.getAccountCredit(request.params.idcard, function(err,dbResult){
      if(err){
        response.json(err);
      }
      else{
        response.json(dbResult[0]);
      }
    })
  });
  






    /*
    router.get('/:user',
    function (request, response) {
        card.getByidaccount(request.params.user, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult[0]);
            }
        })
    });

router.post('/', 
function(request, response) {
  card_privileges.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult.affectedRows);
    }
  });
});


router.delete('/:id', 
function(request, response) {
  card_privileges.deleteByidcard(request.params.id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult.affectedRows);
    }
  });
});

router.delete('/:id', 
function(request, response) {
  card_privileges.deleteByidAccount(request.params.id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult.affectedRows);
    }
  });
});


router.put('/:id', 
function(request, response) {
  card_privileges.updateByidcard(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult.affectedRows);
    }
  });
});

router.put('/:id', 
function(request, response) {
  card_privileges.updateByidaccount(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult.affectedRows);
    }
  });
});*/

module.exports = router;