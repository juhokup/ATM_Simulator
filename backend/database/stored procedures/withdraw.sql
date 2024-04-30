CREATE DEFINER=banuser01@localhost PROCEDURE withdraw(
    IN account_idaccount INT,
    IN amount DECIMAL(10, 2),
    IN currency_rate FLOAT
)
BEGIN
    DECLARE current_balance DECIMAL(10, 2);
    DECLARE credit_limit DECIMAL(10, 2);
    DECLARE new_balance DECIMAL(10, 2);
    DECLARE min_allowed_balance DECIMAL(10, 2);
    DECLARE balanceWithCurrency DECIMAL (10, 2);

    -- Haetaan accountin tämän hetkinen balance ja creditLimit
    SELECT balance, creditLimit INTO current_balance, credit_limit
    FROM account
    WHERE idaccount = account_idaccount;

    -- Laketaan uusi balance kun amount vähennetään
    SET new_balance = current_balance - (amount/currency_rate);
    SET balanceWithCurrency = (amount/currency_rate);

    -- Paljonko balance saa menna pakkaselle (negatiivinen credit_limit)
    SET min_allowed_balance = -credit_limit;

    -- tarkistetaan voidaanko balance paivitysta tehda
    IF new_balance < min_allowed_balance THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Transaction declined. Balance cannot go below the negative credit limit.';
    ELSE
        -- tehdaan balance paivitys jos se onnistui
        UPDATE account
        SET balance = new_balance
        WHERE idaccount = account_idaccount;

        -- luodaan kentta transaction tauluun
        INSERT INTO transaction (balanceChange, type, date, location, account_idaccount)
        VALUES (-balanceWithCurrency, 1, DATE_ADD(now(),interval 3 hour), "Oulu", account_idaccount);
    END IF;
END