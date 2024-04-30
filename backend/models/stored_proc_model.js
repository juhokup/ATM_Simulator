const db = require('../database');

const withdrawFromAccount = {
  
add: function(withdrawFromAccount, callback) {
  return db.query(
    'CALL withdraw (?,?,?)',
    [withdrawFromAccount.account_idaccount, withdrawFromAccount.amount, withdrawFromAccount.currency_rate], callback
  );
}
};

module.exports = withdrawFromAccount;