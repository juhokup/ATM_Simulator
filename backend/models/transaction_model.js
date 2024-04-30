const db = require('../database');

const transaction = {
  getAll: function(callback) {
    return db.query('select * from transaction order by date asc limit 10', callback);
  },
  getPreviousById: function(id, callback) {
    return db.query('select * from transaction where account_idaccount=? order by date asc limit 5', [id], callback);
  },

  getNextById: function(id, callback) {
    return db.query('select * from transaction where account_idaccount=? order by date desc limit 5', [id], callback);
  },

  getNext: function(callback) {
    var ret= db.query('select * from transaction order by date asc limit 5', callback);
    return ret;
  },
  getPrevious: function(callback) {
    var ret= db.query('select * from transaction order by date desc limit 5', callback);
    return ret;
  },
  //getPrevious: function(callback) {
   // var ret= db.query('select * from transaction where account_idaccount = 4 order by date desc limit 5', callback);
   // return ret;
  //},
  getById: function(id, callback) {
    return db.query('select * from transaction where account_idaccount=? order by date desc', [id], callback);
  },
  getTransactionsByAccId: function(account_idaccount, callback) {
    return db.query('select type, date, balanceChange, location, where account_idaccount=? order by date desc',
    [account_idaccount],callback);
  },

  add: function(transaction, callback) { //lisätään transaction auto incrementtiä hyödyntäen
    return db.query(
      'insert into transaction (balanceChange, type,  date, location, account_idaccount) values(?,?, ?,?,?)',
      [transaction.balanceChange, transaction.type,  transaction.date, transaction.location, transaction.account_idaccount],

      callback
    );
  },
  addById: function(transaction, callback) { //jos halutaan lisätä idtransaction manuaalisesti
    return db.query(
      'insert into transaction (idtransaction, balanceChange, type,  date, location, account_idaccount) values(?,?,?, ?,?,?)',
      [transaction.idtransaction, transaction.balanceChange, transaction.type,  transaction.date, transaction.location, transaction.account_idaccount],

      callback
    );
  },

  delete: function(id, callback) {
    return db.query('delete from transaction where idtransaction=?', [id], callback);
  },

  update: function(id, transaction, callback) {
    return db.query(
      'update transaction set idtransaction=?, balanceChange=?, type=?,  date=?, location=?, account_idaccount=? where idtransaction=?',
      [transaction.idtransaction, transaction.balanceChange, transaction.type,  transaction.date, transaction.location, transaction.account_idaccount, id],
      callback
    );
  },

  // WITHDRAW STORED PROCEDURE:
	withdraw: function(transaction, callback) {
		return db.query('CALL withdraw(?,?)', [transaction.account_idaccount, transaction.balanceChange],
		callback
  );
}
};



// -------------

/*connection.query("CALL withdraw(?,?)", [account_idaccount, balanceChange], function (err, result) {
  if (err) {
      console.log("err:", err);
  } else {
      console.log("results:", result);
  }

});*/

module.exports = transaction;