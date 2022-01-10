-- SQL query to list the titles of the five highest rated movies (in order)
-- that Chadwick Boseman starred in, starting with the highest rated.

SELECT title FROM movies
JOIN
(
    SELECT mi FROM ratings
    JOIN
    (
        SELECT movie_id AS mi FROM stars WHERE person_id =
        (
            SELECT id FROM people WHERE name = "Chadwick Boseman"
        )
    ) AS cbm ON ratings.movie_id = cbm.mi
    ORDER BY rating DESC LIMIT 5
) AS cbmd ON movies.id = cbmd.mi;

/*
SELECT cbmd.mi, title, cbmd.r, year FROM movies
JOIN
(
    SELECT mi, rating AS r FROM ratings
    JOIN
    (
        SELECT movie_id AS mi FROM stars WHERE person_id =
        (
            SELECT id FROM people WHERE name = "Chadwick Boseman"
        )
    ) AS cbm ON ratings.movie_id = cbm.mi
    ORDER BY rating DESC
) AS cbmd ON movies.id = cbmd.mi;
*/

/*
SELECT title FROM movies WHERE id IN
(
    SELECT ratings.movie_id FROM ratings
    JOIN
    (
        SELECT movie_id FROM stars WHERE person_id =
        (
            SELECT id FROM people WHERE name = "Chadwick Boseman"
        )

    ) as m ON m.movie_id = ratings.movie_id
    ORDER BY rating DESC
)LIMIT 5;
*/

/*
    SELECT title FROM movies WHERE id IN
    (
        SELECT movie_id FROM ratings JOIN
        (
            SELECT id FROM movies JOIN
            (
                SELECT movie_id FROM stars WHERE person_id =
                (
                    SELECT id FROM people WHERE name = "Chadwick Boseman"
                )
            ) as mi ON movies.id = mi.movie_id
            ORDER BY year ASC
        ) as mi ON mi.id = ratings.movie_id
        ORDER BY rating DESC
    ) LIMIT 5;

*/