-- SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.

SELECT title FROM movies WHERE id IN
(
    SELECT jdm FROM
    (
        SELECT stars.movie_id AS jdm FROM stars WHERE person_id =
        (
            SELECT id FROM people WHERE name = "Johnny Depp"
        )
    ) AS jd
    INNER JOIN
    (
        SELECT stars.movie_id AS hbcm FROM stars WHERE person_id =
        (
            SELECT id FROM people WHERE name = "Helena Bonham Carter"
        )
    ) AS hbc ON hbc.hbcm = jd.jdm
);