const db = require('../database');
const dotenv = require('dotenv');

const login = {
    checkPassword:function(cardNumber, callback){
        return db.query('SELECT pin FROM card WHERE cardNumber=?', cardNumber, callback);
    },

    expireCheck:function(cardNum, callback){
        return db.query('UPDATE card SET cardStatus=0, pinAttempts=0 WHERE(cardNumber = ? AND expire < CURRENT_DATE())', cardNum, callback);
    },

    resetAttempts:function(cardNum, callback){
        return db.query('UPDATE card SET pinAttempts = 3 WHERE(cardNumber = ? AND cardStatus != 0)', cardNum, callback);
    },

    cardWrongPass: function(cardNum, callback) {
        return db.query(
            //-NEW, updates the cardStatus in same statement as pinAttempts. Prevents miscommunication between QT and REST API
            'UPDATE card SET pinAttempts = CASE WHEN pinAttempts > 0 THEN pinAttempts - 1 ELSE pinAttempts END, cardStatus = CASE WHEN pinAttempts > 1 THEN 1 WHEN pinAttempts = 0 THEN 0 ELSE cardStatus END WHERE cardNumber = ?',
            [cardNum],callback
            
            //-OLD, wont be used
            //return db.query('UPDATE card SET pinAttempts = pinAttempts-1 WHERE(cardNumber = ? AND pinAttempts > 0)', 
            //[cardNum], callback); 
        );
    }, 
    // get the attempts in Qt and check there?  Decreasing works with Qt input
    
/*     cardNoAttemptsLeft:function(cardNum, callback) {
        return db.query('UPDATE card SET cardStatus=0 WHERE(cardNumber = ? AND pinAttempts = 0)', [cardNum], callback);
    }, */

    checkCard: function(cardNum, callback) {
        return db.query('SELECT cardStatus, pinAttempts FROM card WHERE cardNumber = ?', [cardNum], callback);
    }
      // 1st check: cardStatus; if 1 continue. 
      // 2nd check: expire; compare with mysql and if more than curdate() continue. 
      // create a stored procedure?
      
      // because atm is in use in the database file, simply call the procedure in a similar fashion
      // ex. CALL loginproc()
}

module.exports = login;
