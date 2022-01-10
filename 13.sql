-- SQL query to list the names of all people who starred in a movie in which Kevin Bacon(1958) also starred.

SELECT name FROM people WHERE id IN
(
    SELECT person_id FROM stars
    JOIN
    (
        SELECT movie_id FROM stars WHERE person_id =
        (
            SELECT id FROM people WHERE name = "Kevin Bacon" AND birth = 1958
        )
    ) AS kbm ON stars.movie_id = kbm.movie_id
)
AND id <> (SELECT id FROM people WHERE name = "Kevin Bacon" AND birth = 1958);