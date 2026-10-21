-- Keep a log of any SQL queries you execute as you solve the mystery.
.schema
-- First hint: the theft took place on July 28, 2025 and that it took place on Humphrey Street.
-- We search for the description of that situation
SELECT description
FROM crime_scene_reports
WHERE year = 2025 AND month = 7 AND day = 28 AND street = 'Humphrey Street';
-- We obtain the clue that 3 witnesses were interviewed and that all of them mention the bakery. Also, littering happened
-- at 16. The theft took place al 10:15 am We search in interviews for those conversations.
SELECT name, transcript
FROM interviews
WHERE year = 2025 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%';
-- We obtain important data from the 3 witnesses that allows to make the final query that will determine the thief
SELECT name
FROM people
WHERE license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2025
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute BETWEEN 15 AND 25
    AND activity = 'exit'
)
AND id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE day = 28
        AND month = 7
        AND year = 2025
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw'
    )
)
AND passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id IN (
        SELECT id
        FROM flights
        WHERE year = 2025
        AND month = 7
        AND day = 29
        AND origin_airport_id IN (
            SELECT id
            FROM airports
            WHERE city = 'Fiftyville'
        )
        ORDER BY hour ASC, minute ASC
        LIMIT 1
    )
)
AND phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE day = 28
    AND month = 7
    AND year = 2025
    AND duration < 60
);
-- Once with the name we can determine the accompliance and destination city
SELECT
    thief.name AS thief,
    accomplice.name AS accomplice,
    airports.city AS destination_city
FROM people AS thief
JOIN phone_calls ON thief.phone_number = phone_calls.caller
JOIN people AS accomplice ON phone_calls.receiver = accomplice.phone_number
JOIN passengers ON thief.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.destination_airport_id = airports.id
WHERE thief.name = 'Bruce'
AND phone_calls.year = 2025
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration < 60
AND flights.id = (
    SELECT id
    FROM flights
    WHERE year = 2025
    AND month = 7
    AND day = 29
    AND origin_airport_id = (
        SELECT id FROM airports WHERE city = 'Fiftyville'
    )
    ORDER BY hour ASC, minute ASC
    LIMIT 1
);
