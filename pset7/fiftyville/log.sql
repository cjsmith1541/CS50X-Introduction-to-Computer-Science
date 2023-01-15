-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Wanted to see the whole of the database
.schema
-- Searched the crime_scene_reports for all crimes on 28/07/2021
SELECT *
    FROM crime_scene_reports
    WHERE year = 2021
        AND month = 7
        AND day = 28;
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
SELECT description
    FROM crime_scene_reports
    WHERE Street = 'Humphrey Street'
        AND year = 2021
        AND month = 7
        AND day = 28;
--Next I checked for interview that have taken place on the same day as the theft.
SELECT *
    FROM interviews
    WHERE year = 2021
        AND month = 7
        AND day = 28;
-- More than three options so made sure it only shows interviews that mention bakerys.
SELECT transcript
    FROM interviews
    WHERE year = 2021
        AND month = 7
        AND day = 28
        AND transcript LIKE '%bakery%';
-- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
.schema bakery_security_logs
-- Checked what happend in bakery_security_logs on the day of the crime.
SELECT *
    FROM bakery_security_logs
    WHERE year = 2021
        AND month = 7
        AND day = 28;
-- refined the search to the 10 min after 10:15
SELECT *
    FROM bakery_security_logs
    WHERE year = 2021
        AND month = 7
        AND day = 28
        AND hour = 10
        AND minute > 15
        AND minute < 25;
-- checking ATM transactions that happend on legget street on that day
.schema atm_transactions
SELECT *
    FROM atm_transactions
    WHERE year = 2021
        AND month = 7
        AND day = 28
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw';

-- Checking all phone calls that lasted less than 1 minute on that day.
.schema phone_calls
SELECT *
    FROM phone_calls
    WHERE year = 2021
        AND month = 7
        AND day = 28
        AND duration < 60;
-- Checking the names of people who have a licence plate of a car that left the bakery withing 10
-- min of the theft
SELECT name
    FROM people
    WHERE license_plate
        IN (SELECT license_plate
                FROM bakery_security_logs
                WHERE year = 2021
                    AND month = 7
                    AND day = 28
                    AND hour = 10
                    AND minute > 15
                    AND minute < 25);
-- Getting their phone numbers
SELECT phone_number
    FROM people
    WHERE license_plate
        IN (SELECT license_plate
                FROM bakery_security_logs
                WHERE year = 2021
                    AND month = 7
                    AND day = 28
                    AND hour = 10
                    AND minute > 15
                    AND minute < 25);
-- Finding out who out of these people made a call under 6 min on that day.
SELECT *
    FROM phone_calls
    WHERE caller
        IN (SELECT phone_number
                FROM people
                WHERE license_plate
                    IN (SELECT license_plate
                            FROM bakery_security_logs
                            WHERE year = 2021
                                AND month = 7
                                AND day = 28
                                AND hour = 10
                                AND minute > 15
                                AND minute < 25))
            AND year = 2021
            AND month = 7
            AND day = 28
            AND duration < 60;
-- checking the first flight the next day
.schema flights
SELECT *
    FROM flights
    WHERE year = 2021
        AND month = 7
        AND day = 29;
-- finding out all the flights that are leaving not arriving at fiftyvile
SELECT *
    FROM flights
    WHERE year = 2021
        AND month = 7
        AND day = 29
        AND NOT destination_airport_id = 8;
-- Found out the destination of the next flight out of the city which is New York City
SELECT city
    FROM airports
    WHERE id = (SELECT destination_airport_id
                    FROM flights
                    WHERE year = 2021
                        AND month = 7
                        AND day = 29
                        AND NOT destination_airport_id = 8
                        AND hour = 8);
-- find passengers of flight 36 leaving to NYC
SELECT *
    FROM passengers
    WHERE flight_id = (SELECT id
                            FROM flights
                            WHERE year = 2021
                                AND month = 7
                                AND day = 29
                                AND NOT destination_airport_id = 8
                                AND hour = 8);
-- found out whos phone number and licence plate matches previous suspects
SELECT *
    FROM people
    WHERE phone_number
        IN (SELECT caller
                FROM phone_calls
                WHERE caller
                    IN (SELECT phone_number
                            FROM people
                            WHERE license_plate
                                IN (SELECT license_plate
                                        FROM bakery_security_logs
                                        WHERE year = 2021
                                            AND month = 7
                                            AND day = 28
                                            AND hour = 10
                                            AND minute > 15
                                            AND minute < 25))
                                            AND year = 2021
                                            AND month = 7
                                            AND day = 28
                                            AND duration < 60)
        AND passport_number
            IN (SELECT passport_number
                FROM passengers
                WHERE flight_id = (SELECT id
                                        FROM flights
                                        WHERE year = 2021
                                            AND month = 7
                                            AND day = 29
                                            AND NOT destination_airport_id = 8
                                            AND hour = 8));
-- put all previous info to narrow down who did it with ATM

SELECT name
    FROM people, bank_accounts
    WHERE people.id = person_id
        AND id IN(SELECT id
                    FROM people
                    WHERE phone_number
                        IN (SELECT caller
                                FROM phone_calls
                                WHERE caller
                                    IN (SELECT phone_number
                                            FROM people
                                            WHERE license_plate
                                                IN (SELECT license_plate
                                                        FROM bakery_security_logs
                                                        WHERE year = 2021
                                                            AND month = 7
                                                            AND day = 28
                                                            AND hour = 10
                                                            AND minute > 15
                                                            AND minute < 25))
                                                AND year = 2021
                                                AND month = 7
                                                AND day = 28
                                                AND duration < 60)
                        AND passport_number
                            IN (SELECT passport_number
                                    FROM passengers
                                    WHERE flight_id = (SELECT id
                                                            FROM flights
                                                            WHERE year = 2021
                                                                AND month = 7
                                                                AND day = 29
                                                                AND NOT destination_airport_id = 8
                                                                AND hour = 8)))
        AND account_number
            IN (SELECT account_number
                    FROM atm_transactions
                    WHERE year = 2021
                        AND month = 7
                        AND day = 28
                        AND atm_location = 'Leggett Street'
                        AND transaction_type = 'withdraw');
-- And finding out the acomlice though his number in the call
SELECT name
    FROM people
    WHERE phone_number
        IN (SELECT receiver
                FROM phone_calls
                WHERE caller
                    IN (SELECT phone_number
                            FROM people
                            WHERE license_plate
                                IN (SELECT license_plate
                                        FROM bakery_security_logs
                                        WHERE year = 2021
                                            AND month = 7
                                            AND day = 28
                                            AND hour = 10
                                            AND minute > 15
                                            AND minute < 25))
                    AND year = 2021
                    AND month = 7
                    AND day = 28
                    AND duration < 60
                    AND caller = '(367) 555-5533');