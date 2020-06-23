SELECT title FROM movies
INNER JOIN stars ON movies.id=stars.movie_id
INNER JOIN people ON stars.person_id=people.id
WHERE name='Johnny Depp'
INTERSECT
SELECT title FROM movies
INNER JOIN stars ON movies.id=stars.movie_id
INNER JOIN people ON stars.person_id=people.id
WHERE name='Helena Bonham Carter'
;