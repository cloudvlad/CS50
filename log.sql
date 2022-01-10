-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Shows the street and the descrption of all reports for 28-th of July, 2020.
SELECT street, description FROM crime_scene_reports WHERE year = 2020 AND month = 7 AND day = 28;

-- Shows the street and the descrption of all reports for 28-th of July, 2020 ONLY for "Chamberlin street"
SELECT description FROM crime_scene_reports WHERE year = 2020 AND month = 7 AND day = 28
AND street = "Chamberlin Street";

-- Extracts the names and the transcripts of the witnesses at that specific date
SELECT name, transcript FROM interviews WHERE year = 2020 AND month = 7 AND day = 28
AND transcript LIKE "%courthouse%" OR transcript LIKE "%Courthouse%";




-- Select data for call under 1 minute on that day
SELECT caller, receiver, duration FROM phone_calls
WHERE day = 28 AND month = 7 AND year = 2020
AND duration <= 60;

-- Calls around 1 minute on that day
SELECT name, phone_number, passport_number FROM
people JOIN phone_calls ON
people.phone_number = phone_calls.caller
WHERE day = 28 AND month = 7 AND year = 2020
AND duration <= 60;

SELECT phone_number, name, passport_number FROM
people JOIN phone_calls ON
people.phone_number = phone_calls.receiver
WHERE day = 28 AND month = 7 AND year = 2020
AND duration <= 60;


-- Calls around 1 minute on that day
SELECT caller, people.name, duration FROM people
JOIN
(
SELECT people.name as caller, receiver, duration FROM phone_calls
JOIN people ON people.phone_number = phone_calls.caller
WHERE day = 28 AND month = 7 AND year = 2020
AND duration <= 60
) as r
ON people.phone_number = r.receiver;







-- Account numbers for people that withdraw from ATM on Fifer Street
SELECT account_number FROM atm_transactions WHERE atm_location = "Fifer Street" AND day = 28
AND month = 7 AND year = 2020 AND transaction_type = "withdraw";

SELECT people.name, people.id, people.phone_number, people.passport_number, people.license_plate FROM
people JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_location = "Fifer Street" AND day = 28
AND month = 7 AND year = 2020 AND transaction_type = "withdraw";

-- Gets the IDs of bank account users this day
SELECT bank_accounts.person_id FROM bank_accounts
JOIN atm_transactions ON
bank_accounts.account_number = atm_transactions.account_number
WHERE atm_location = "Fifer Street" AND day = 28 AND month = 7
AND year = 2020 AND transaction_type = "withdraw";

-- People that withdraw at that day from the ATM at
-- Fifer Street
SELECT name, phone_number, passport_number
FROM people
WHERE id IN (SELECT bank_accounts.person_id FROM bank_accounts
JOIN atm_transactions ON
bank_accounts.account_number = atm_transactions.account_number
WHERE atm_location = "Fifer Street" AND day = 28 AND month = 7
AND year = 2020 AND transaction_type = "withdraw");





-- Cars exited the courthouse between 22 and 30 minute after
-- the theft
SELECT hour, minute, license_plate
FROM courthouse_security_logs
WHERE year = 2020 AND month = 7 AND day = 28
AND activity = "exit"
AND hour = 10 AND (minute >= 20 AND minute <= 30);

-- People, exited the courthouse at specific time period
SELECT name, phone_number, passport_number FROM
people JOIN courthouse_security_logs ON
people.license_plate = courthouse_security_logs.license_plate
WHERE year = 2020 AND month = 7 AND day = 28
AND activity = "exit"
AND hour = 10 AND (minute >= 15 AND minute <= 30);






-- Shows the id, abbreviation, full name and city
-- for destination airports this the next day
SELECT flights.id, destination_airport_id, abbreviation, full_name, city, hour, minute
FROM airports JOIN flights ON airports.id = flights.destination_airport_id
WHERE year = 2020 AND month = 7 AND day = 29 ORDER BY hour,
minute ASC;


SELECT name FROM people
JOIN passengers ON
passengers.passport_number = people.passport_number
WHERE flight_id = 36 AND year = 2020 AND month = 7 AND day = 29 ORDER BY hour, minute ASC;


SELECT people.name, people.phone_number, people.passport_number FROM
people JOIN passengers ON
people.passport_number = passengers.passport_number
WHERE passengers.flight_id = (SELECT flights.id
FROM airports JOIN flights ON airports.id = flights.destination_airport_id
WHERE year = 2020 AND month = 7 AND day = 29 ORDER BY hour,
minute ASC LIMIT 1);



-- Nested query...

SELECT * FROM people WHERE id IN
(
SELECT id FROM
    (SELECT id FROM
    (
        (SELECT id FROM
        (
            SELECT people.id as id FROM
            people JOIN bank_accounts ON people.id = bank_accounts.person_id
            JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
            WHERE atm_location = "Fifer Street" AND day = 28
            AND month = 7 AND year = 2020 AND transaction_type = "withdraw"
        ) as a
        WHERE a.id IN
        (
            SELECT people.id FROM
            people JOIN phone_calls ON
            people.phone_number = phone_calls.caller
            WHERE day = 28 AND month = 7 AND year = 2020
            AND duration <= 60
        )
        ) as ids
    )
    WHERE ids.id IN
    (
        SELECT people.id FROM
        people JOIN courthouse_security_logs ON
        people.license_plate = courthouse_security_logs.license_plate
        WHERE year = 2020 AND month = 7 AND day = 28
        AND activity = "exit"
        AND hour = 10 AND (minute >= 15 AND minute <= 30)
    )
    ) as ids
WHERE ids.id IN
(
    SELECT people.id FROM
    people JOIN passengers ON
    people.passport_number = passengers.passport_number
    WHERE passengers.flight_id = (SELECT flights.id
    FROM airports JOIN flights ON airports.id = flights.destination_airport_id
    WHERE year = 2020 AND month = 7 AND day = 29 ORDER BY hour,
    minute ASC LIMIT 1)
)
);


SELECT * FROM
people JOIN phone_calls ON
people.phone_number = phone_calls.receiver
WHERE day = 28 AND month = 7 AND year = 2020
AND duration <= 60 AND phone_calls.caller = (
SELECT people.phone_number FROM people
WHERE people.id = (
    SELECT id FROM people WHERE id IN
(
SELECT id FROM
    (SELECT id FROM
    (
        (SELECT id FROM
        (
            SELECT people.id as id FROM
            people JOIN bank_accounts ON people.id = bank_accounts.person_id
            JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
            WHERE atm_location = "Fifer Street" AND day = 28
            AND month = 7 AND year = 2020 AND transaction_type = "withdraw"
        ) as a
        WHERE a.id IN
        (
            SELECT people.id FROM
            people JOIN phone_calls ON
            people.phone_number = phone_calls.caller
            WHERE day = 28 AND month = 7 AND year = 2020
            AND duration <= 60
        )
        ) as ids
    )
    WHERE ids.id IN
    (
        SELECT people.id FROM
        people JOIN courthouse_security_logs ON
        people.license_plate = courthouse_security_logs.license_plate
        WHERE year = 2020 AND month = 7 AND day = 28
        AND activity = "exit"
        AND hour = 10 AND (minute >= 15 AND minute <= 30)
    )
    ) as ids
WHERE ids.id IN
(
    SELECT people.id FROM
    people JOIN passengers ON
    people.passport_number = passengers.passport_number
    WHERE passengers.flight_id = (SELECT flights.id
    FROM airports JOIN flights ON airports.id = flights.destination_airport_id
    WHERE year = 2020 AND month = 7 AND day = 29 ORDER BY hour,
    minute ASC LIMIT 1)
)
)
)
);

-- Evidences ----------------------------------------------
/*
    People used the ATM at Fifer Street:
       *Bobby     | (826) 555-1652 | 9878712108
        Elizabeth | (829) 555-5269 | 7049073643
        Victoria  | (338) 555-6650 | 9586786673
        Madison   | (286) 555-6063 | 1988161715
        Roy       | (122) 555-4581 | 4408372428
        Danielle  | (389) 555-5198 | 8496433585
        Russell   | (770) 555-1861 | 3592750733
    ****Ernest    | (367) 555-5533 | 5773159633

    Calls that was under(equal or less) 1 minute:
        caller    | name           | duration
        Roger     | Jack           | 51
        Evelyn    | Larry          | 36
    ****Ernest    | Berthold       | 45
        Kathryn   | Danielle       | 60
        Evelyn    | Melissa        | 50
        Madison   | James          | 43
        Russell   | Philip         | 49
        Kimberly  | Jacqueline     | 38
        Bobby     | Doris          | 55
        Victoria  | Anna           | 54

    Left the courhouse at the same time:
        Patrick   | (725) 555-4692 | 2963008352
    ****Ernest    | (367) 555-5533 | 5773159633
        Amber     | (301) 555-4174 | 7526138472
        Danielle  | (389) 555-5198 | 8496433585
        Roger     | (130) 555-0289 | 1695452385
        Elizabeth | (829) 555-5269 | 7049073643
        Russell   | (770) 555-1861 | 3592750733
        Evelyn    | (499) 555-9472 | 8294398571

    People, who are gonna take the first flight out of
    Fiftyville on 29-th July:

        Doris     | (066) 555-9701 | 7214083635
        Roger     | (130) 555-0289 | 1695452385
    ****Ernest    | (367) 555-5533 | 5773159633
        Edward    | (328) 555-1152 | 1540955065
        Evelyn    | (499) 555-9472 | 8294398571
        Madison   | (286) 555-6063 | 1988161715
        Bobby     | (826) 555-1652 | 9878712108
        Danielle  | (389) 555-5198 | 8496433585


*/