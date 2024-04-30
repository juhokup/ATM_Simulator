const db = require('../database');

const currency = {
  getAll: function(callback) {  //haetaan currencyRatet QT:hen
    return db.query('SELECT * FROM currency WHERE currencyName IN ("EUR", "USD", "GBP", "SEK", "JPY") ORDER BY FIELD(currencyName, "EUR", "USD", "GBP", "SEK", "JPY")',
    callback);
  },
  getById: function(id, callback) {
    return db.query('select * from currency where idcurrency=?', [id], callback);
  },
   getQT: function(callback) {  //tässä pitäis olla tuo mikä on getAll:ssa... ei toimi syystä X
    return db.query('select * from currency', callback);
  },

  add: function(currency, callback) { //lisätään currency auto incrementtiä hyödyntäen
    return db.query(
      'insert into currency (currencyName, currencyRate) values(?,?)',
      [currency.currencyName, currency.currencyRate],

      callback
    );
  },
  addById: function(currency, callback) { //jos halutaan lisätä idcurrency manuaalisesti
    return db.query(
    'insert into currency (idcurrency,currencyName,currencyRate) values(?,?,?)', 
    [currency.idcurrency, currency.currencyName, currency.currencyRate],

      callback
    );
  },

  delete: function(id, callback) {
    return db.query('delete from currency where idcurrency=?', [id], callback);
  },
  
  update: function(id, currency, callback) {
    return db.query(
      'update currency set currencyName=?, currencyRate=? where idcurrency=?',
      [currency.currencyName, currency.currencyRate, id],
      callback
    );
  }
};

module.exports = currency;