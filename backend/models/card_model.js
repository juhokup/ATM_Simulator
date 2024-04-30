const db = require('../database');
const bcrypt = require('bcryptjs');
const saltRounds = 10;

const card = {
    getAll: function(callback) {
      return db.query('select * from card', callback);
    },

    /*getById: function(id, callback) {
      return db.query('select * from card where idcard=?', [id], callback);
    },*/
	getById: function(cardNum, callback) {
      return db.query('SELECT * FROM card WHERE cardNumber = ?', [cardNum], callback);
    },


    add: function(card, callback) { //lisätään account auto incrementtiä hyödyntäen
        bcrypt.hash(card.pin, saltRounds, function (err, hash) {

            return db.query(
                'INSERT into card (cardNumber,pin,type,cardStatus, customer_idcustomer, account_idaccount, expire, pinAttempts) values(?,?,?, ?,?,? , DATE_ADD(CURRENT_DATE(), INTERVAL 3 YEAR), ?)', 
                [card.cardNumber, hash, card.type,  card.cardStatus, card.customer_idcustomer, card.account_idaccount, card.expire, card.pinAttempts],
                callback
            );
        });
    },
    addById: function(card, callback) { //jos halutaan lisätä idcard manuaalisesti
      bcrypt.hash(card.pin, saltRounds, function (err, hash) {

          return db.query(
              'INSERT into card (idcard,cardNumber,pin,type,cardStatus, customer_idcustomer, account_idaccount, expire, pinAttempts) values(?,?,?,?, ?,?,? , DATE_ADD(CURRENT_DATE(), INTERVAL 3 YEAR, ?)', 
              [card.idcard, card.cardNumber, hash, card.type,  card.cardStatus, card.customer_idcustomer, card.account_idaccount, card.expire, card.pinAttempts],
              callback
          );
      });
  },

    delete: function(id, callback) {
      return db.query('delete from card where idcard=?', [id], callback);
    },

    update: function(id, card, callback) {
        bcrypt.hash(card.pin, saltRounds, function (err, hash) {
            return db.query(
                'UPDATE card set cardNumber=?,pin=?, type=?, cardStatus=?, expire=?, customer_idcustomer=?, account_idaccount=?, pinAttempts=? where idcard=?',
                [card.cardNumber, hash, card.type, card.cardStatus, card.expire, card.customer_idcustomer, card.account_idaccount, card.pinAttempts],
                callback
      );
    });
  }
};

module.exports = card;