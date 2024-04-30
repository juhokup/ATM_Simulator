const db = require('../database');

const customer = {
  getAll: function(callback) {
    return db.query('select * from customer', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from customer where idcustomer=?', [id], callback);
  },

  add: function(customer, callback) { //lisätään customer auto incrementtiä hyödyntäen
    return db.query(
      'insert into customer (fname, lname) values(?,?)',
      [customer.fname, customer.lname],

      callback
    );
  },
  addById: function(customer, callback) { //jos halutaan lisätä idcustomer manuaalisesti
    return db.query(
      'insert into customer (idcustomer, fname, lname) values(?,?,?)',
      [customer.idcustomer, customer.fname, customer.lname],

      callback
    );
  },

  delete: function(id, callback) {
    return db.query('delete from customer where idcustomer=?', [id], callback);
  },
  update: function(id, customer, callback) {
    return db.query(
      'update customer set idcustomer=?,fname=?, lname=? where idcustomer=?',
      [customer.idcustomer, customer.fname, customer.lname, id],
      callback
    );
  }
};
module.exports = customer;