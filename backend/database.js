const mysql=require('mysql2');
const connection=mysql.createPool({ 
    host: 'localhost',
    user: 'bankuser01',
    password: 'bankpassword01',
    database: 'atm'
});

module.exports = connection;