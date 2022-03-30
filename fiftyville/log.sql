-- Keep a log of any SQL queries you execute as you solve the mystery.

-- checking the crimes that took place on 28th july 2021
sqlite> SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28;