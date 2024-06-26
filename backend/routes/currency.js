const express = require('express');
const currency = require('../models/currency_model');
const router = express.Router();



router.get('/',function(request,response){
    currency.getAll(function(err,dbResult){
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
        currency.getById(request.params.id, function (err, dbResult) {

            if (err) {
                response.json(err);
            } else {
                response.json(dbResult[0]);
            }
        })
    });

    router.get('/:user',function(request,response){
      currency.getQT(function(err,dbResult){
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
  currency.add(request.body, function(err, dbResult) {

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
  currency.delete(request.params.id, function(err, dbResult) {

    if (err) {
      response.json(err);
    } else {
      response.json(dbResult.affectedRows);
    }
  });
});


router.put('/:id', 
function(request, response) {
  currency.update(request.params.id, request.body, function(err, dbResult) {

    if (err) {
      response.json(err);
    } else {
      response.json(dbResult.affectedRows);
    }
  });
});

module.exports = router;