-- SQL query to list the names of all people who starred in Toy Story.

SELECT people.name FROM people
WHERE people.id IN
(
    SELECT person_id FROM stars WHERE movie_id =
    (
        SELECT id FROM movies WHERE title = "Toy Story"
    )
);