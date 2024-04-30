const express = require('express');
const router = express.Router();
const storedProcModel = require('../models/stored_proc_model');

router.post('/', 
function(request, response) {
  storedProcModel.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err.code);
    } else {
      response.json(dbResult.affectedRows);
    }
  });
});

module.exports = router;