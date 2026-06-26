-- Author: Marko Solajic
-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Crime committed on July 28, 2025, at 10:15am, Humphrey Street bakery.
SELECT * FROM crime_scene_reports WHERE year = 2025 AND month = 7 AND day = 28 AND street = 'Humphrey Street';
-- I got the time 10:15am and that it happened in bakery. Interviews with 3 witnesses.
SELECT * FROM interviews WHERE year = 2025 AND month = 7 AND day = 28;
-- Ruth: within 10 min of theft, thief got into a car in the bakery parking lot and drove away, so 10:15 - 10:25
-- Eugene: earlier this morning the thief was withdrawing money on Leggett Street
-- Raymond: the tief called someone after leaving bakery, call lasted < 60s, earliest flight out of Fiftyville tommorow, accomplice purchased the tickets
SELECT * FROM bakery_security_logs WHERE year = 2025 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25; -- I got possible license plates
-- +-----+------+-------+-----+------+--------+----------+---------------+
-- | id  | year | month | day | hour | minute | activity | license_plate |
-- +-----+------+-------+-----+------+--------+----------+---------------+
-- | 260 | 2025 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
-- | 261 | 2025 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
-- | 262 | 2025 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
-- | 263 | 2025 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
-- | 264 | 2025 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
-- | 265 | 2025 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
-- | 266 | 2025 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
-- | 267 | 2025 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
-- +-----+------+-------+-----+------+--------+----------+---------------+
SELECT * FROM atm_transactions WHERE year = 2025 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'; -- I got possible account numbers
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+
-- | id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+
-- | 246 | 28500762       | 2025 | 7     | 28  | Leggett Street | withdraw         | 48     |
-- | 264 | 28296815       | 2025 | 7     | 28  | Leggett Street | withdraw         | 20     |
-- | 266 | 76054385       | 2025 | 7     | 28  | Leggett Street | withdraw         | 60     |
-- | 267 | 49610011       | 2025 | 7     | 28  | Leggett Street | withdraw         | 50     |
-- | 269 | 16153065       | 2025 | 7     | 28  | Leggett Street | withdraw         | 80     |
-- | 288 | 25506511       | 2025 | 7     | 28  | Leggett Street | withdraw         | 20     |
-- | 313 | 81061156       | 2025 | 7     | 28  | Leggett Street | withdraw         | 30     |
-- | 336 | 26013199       | 2025 | 7     | 28  | Leggett Street | withdraw         | 35     |
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+
SELECT * FROM phone_calls WHERE year = 2025 AND month = 7 AND day = 28 AND duration < 60; -- I got possible phone numbers
-- +-----+----------------+----------------+------+-------+-----+----------+
-- | id  |     caller     |    receiver    | year | month | day | duration |
-- +-----+----------------+----------------+------+-------+-----+----------+
-- | 221 | (130) 555-0289 | (996) 555-8899 | 2025 | 7     | 28  | 51       |
-- | 224 | (499) 555-9472 | (892) 555-8872 | 2025 | 7     | 28  | 36       |
-- | 233 | (367) 555-5533 | (375) 555-8161 | 2025 | 7     | 28  | 45       |
-- | 251 | (499) 555-9472 | (717) 555-1342 | 2025 | 7     | 28  | 50       |
-- | 254 | (286) 555-6063 | (676) 555-6554 | 2025 | 7     | 28  | 43       |
-- | 255 | (770) 555-1861 | (725) 555-3243 | 2025 | 7     | 28  | 49       |
-- | 261 | (031) 555-6622 | (910) 555-3251 | 2025 | 7     | 28  | 38       |
-- | 279 | (826) 555-1652 | (066) 555-9701 | 2025 | 7     | 28  | 55       |
-- | 281 | (338) 555-6650 | (704) 555-2131 | 2025 | 7     | 28  | 54       |
-- +-----+----------------+----------------+------+-------+-----+----------+
SELECT * FROM people
JOIN bank_accounts ON person_id = people.id
WHERE phone_number IN
(SELECT caller FROM phone_calls WHERE year = 2025 AND month = 7 AND day = 28 AND duration < 60)
AND bank_Accounts.account_number IN
(SELECT account_number FROM atm_transactions WHERE year = 2025 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw')
AND license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE year = 2025 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25);
-- I am now sure that the thief is either Bruce or Diana
-- +--------+-------+----------------+-----------------+---------------+----------------+-----------+---------------+
-- |   id   | name  |  phone_number  | passport_number | license_plate | account_number | person_id | creation_year |
-- +--------+-------+----------------+-----------------+---------------+----------------+-----------+---------------+
-- | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       | 49610011       | 686048    | 2010          |
-- | 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       | 26013199       | 514354    | 2012          |
-- +--------+-------+----------------+-----------------+---------------+----------------+-----------+---------------+

SELECT name FROM people WHERE phone_number = '(375) 555-8161';
-- If Bruce is the thief, his accomplice is Robin
SELECT name FROM people WHERE phone_number = '(725) 555-3243';
-- If Diana is the thief, her accomplice is Philip

SELECT name, city FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
JOIN airports ON airports.id = destination_airport_id
WHERE (name = 'Bruce' OR name = 'Diana')
AND flights.year = 2025
AND flights.month = 7
AND flights.day = 29
ORDER BY flights.hour, flights.minute;
-- Because I ordered by time, I know that Bruce's flight was earlier than Diana's, therefore Bruce is the thief and his accomplice is Robin.
-- +-------+---------------+
-- | name  |     city      |
-- +-------+---------------+
-- | Bruce | New York City |
-- | Diana | Boston        |
-- +-------+---------------+

-- Final answers:
-- Thief: Bruce
-- Accomplice: Robin
-- Thief escaped to: New York City
