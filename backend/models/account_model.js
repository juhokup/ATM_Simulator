const db = require('../database');

const account = {
  getAll: function(callback) {
    return db.query('select * from account', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from account where idaccount=?', [id], callback);
  },

  add: function(account, callback) { //lisätään account auto incrementtiä hyödyntäen
    return db.query(
      'insert into account (accountNumber,balance,creditLimit, currency_idcurrency) values(?,?,?,?)', //<--idaccount poistettu, auto increment
      [account.accountNumber, account.balance, account.creditLimit, account.currency_idcurrency],

      callback
    );
  },
  addById: function(account, callback) { //jos halutaan lisätä idaccount manuaalisesti
    return db.query(
    'insert into account (idaccount,accountNumber,balance,creditLimit) values(?,?,?,?)', 
    [account.idAccount, account.accountNumber, account.balance, account.creditLimit],

      callback
    );
  },

  delete: function(id, callback) {
    return db.query('delete from account where idaccount=?', [id], callback);
  },
  
  update: function(id, account, callback) {
    return db.query(
      'update account set accountNumber=?,balance=?, creditLimit=?, currency_idcurrency=? where idaccount=?',
      [account.accountNumber, account.balance, account.creditLimit, account.currency_idcurrency, id],
      callback
    );
  },

  withdraw: function(id, account, callback) {
    if (creditLimit==null){
    return db.query('update account set balance = balance - ? where idaccount=?',
      [account.balance, id],callback);
    } else {
      return db.query('update account set creditLimit = creditLimit - ? where idaccount=?',
      [account.creditLimit, id],callback);
    }
  },

  retrieveBalance: function (id, account, callback) {
		if (creditLimit == null) {
			return db.query('select balance from account where idaccount = ?', 
      [id], callback);
		} else {
			return db.query('select creditLimit from account where idaccount = ?', 
      [id], callback);
		}
  }

};
module.exports = account;