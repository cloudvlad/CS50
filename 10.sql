-- Write a SQL query to list the names of all people who
-- have directed a movie that received a rating of at least 9.0.


SELECT people.name FROM people
INNER JOIN
(
    SELECT DISTINCT person_id FROM directors
    JOIN ratings ON
    ratings.movie_id = directors.movie_id
    WHERE ratings.rating >= 9.0
) as a
ON people.id = a.person_id;

/*
SELECT people.name FROM people
WHERE id IN
(
    SELECT person_id FROM directors
    JOIN ratings ON
    ratings.movie_id = directors.movie_id
    WHERE ratings.rating >= 9.0
);
*/

