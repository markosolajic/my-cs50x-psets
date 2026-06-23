-- 9. Names of all people who starred in a movie released in 2004, ordered by birth year

SELECT DISTINCT people.id,
                name
FROM people
JOIN stars ON people.id = person_id
JOIN movies ON movies.id = movie_id
WHERE "year" = 2004
ORDER BY birth;
