.read lab13.sql

CREATE TABLE su19favpets AS
  SELECT pet, COUNT(pet) AS cnt
    FROM students
GROUP BY pet
ORDER BY cnt DESC
   LIMIT 10;


CREATE TABLE su19dog AS
  SELECT pet, COUNT(pet) AS cnt
    FROM students
GROUP BY pet
  HAVING pet = 'dog';


CREATE TABLE obedienceimages AS
  SELECT seven, instructor, COUNT(instructor) AS cnt
    FROM students
   WHERE seven = '7'
GROUP BY instructor
ORDER BY instructor;
