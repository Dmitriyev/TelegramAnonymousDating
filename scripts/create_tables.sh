set -e  

DATABASE="TAD"
createdb $DATABASE
psql $DATABASE -q -c "CREATE TABLE [IF NOT EXISTS] users (
    id BIGINT PRIMARY KEY NOT NULL,
    username VARCHAR(50) NOT NULL,
    age SMALLINT NOT NULL,
    sex VARCHAR(10) NOT NULL,
    orientation VARCHAR(10) NOT NULL,
    city VARCHAR(50) NOT NULL,
    bio TEXT
);"

