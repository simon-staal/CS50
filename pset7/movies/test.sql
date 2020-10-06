SELECT * FROM
    (SELECT * FROM stars WHERE person_id = (SELECT id FROM people WHERE name = "Johnny Depp"))
WHERE movie_id IN
(SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = "Helena Bonham Carter"))
--SELECT * FROM stars WHERE person_id = (SELECT id FROM people WHERE name = "Johnny Depp")