const db = require('../database');

const card_privileges = {
    getidcard:function (idcard, callback) {
        return db.query('SELECT account_idaccount FROM card_privileges WHERE card_idcard=?', [idcard], callback);
    },
        getAccountCredit:function (idcard, callback) {
            return db.query('SELECT account_idaccount FROM combi_card WHERE (card_idcard=? AND creditLimit > 0)', [idcard], callback);
        },
        getAccountDebit:function (idcard, callback) {
            return db.query('SELECT account_idaccount FROM combi_card WHERE (card_idcard=? AND creditLimit = 0)', [idcard], callback);
        }


	/*getByidaccount: function (account_idaccount, callback) {
        return db.query('select * from card_privileges where account_idaccount=?', [id], callback);
    }*/

	/*
	add: function (data, callback) {
        return db.query('insert into card_privileges (card_idcard, account_idaccount) values(?, ?)', 
        [data.card_idcard, data.account_idaccount], callback);
    },
	
    deleteByidcard: function (card_idcard, callback) {
        return db.query('delete from card_privileges where card_idcard=?', [id], callback);
    },
	
	deleteByidaccount: function (account_idaccount, callback) {
        return db.query('delete from card_privileges where account_idaccount=?', [id], callback);
    },
	
    updateByidcard: function (card_idcard, data, callback) {
        return db.query('update card_privileges set card_idcard=?, account_idaccount=? where card_idcard=?', 
        [data.card_idcard, data.account_idaccount, id], callback);
    },
	
	updateByidaccount: function (account_idaccount, data, callback) {
        return db.query('update card_privileges set card_idcard=?, account_idaccount=? where account_idaccount=?', 
        [data.card_idcard, data.account_idaccount, id], callback);
    }*/
    
};

module.exports = card_privileges;