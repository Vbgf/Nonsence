# Optional

CREATE DATABASE test;
USE test;

# creates.sql Creates

CREATE TABLE Article_5(
	id INT AUTO_INCREMENT NOT NULL,
	content LONG VARCHAR,
	published_on TIMESTAMP,
	url VARCHAR(255),
	PRIMARY KEY(id)
);

CREATE TABLE Category(
	id INT AUTO_INCREMENT NOT NULL,
	description LONG VARCHAR,
	date_created_on TIMESTAMP,
	PRIMARY KEY(id)
);

CREATE TABLE User(
	id INT AUTO_INCREMENT NOT NULL,
	income FLOAT,
	twitter VARCHAR(255),
	password VARCHAR(255),
	PRIMARY KEY(id)
);

CREATE TABLE Tag(
	id INT AUTO_INCREMENT NOT NULL,
	name VARCHAR(255),
	priority INT,
	PRIMARY KEY(id)
);

# creates.sql Links

CREATE TABLE TagArticle(
	id INT AUTO_INCREMENT PRIMARY KEY NOT NULL,
	tag INT NOT NULL,
	article INT NOT NULL,
	FOREIGN KEY (tag) REFERENCES Tag(id),
	FOREIGN KEY (article) REFERENCES Article_5(id)
);

CREATE TABLE ArticleUser(
	id INT AUTO_INCREMENT PRIMARY KEY NOT NULL ,
	article INT NOT NULL ,
	user INT NOT NULL ,
	FOREIGN KEY ( article ) REFERENCES Article_5( id ) ,
	FOREIGN KEY ( user ) REFERENCES User( id )
);

CREATE TABLE UserCategory(
	id INT AUTO_INCREMENT PRIMARY KEY NOT NULL ,
	user INT NOT NULL,
	category INT NOT NULL,
	FOREIGN KEY ( user ) REFERENCES User( id ) ,
	FOREIGN KEY ( category ) REFERENCES Category( id )
);

# inserts.sql Inserts

INSERT INTO Article_5 (content, url)
VALUES ("This is the first page", "http://www.elsys-bg.org/1/p1"),
("This is the second page", "http://www.elsys-bg.org/1/p2");

INSERT INTO Category (description)
VALUES ("This is the first category description"),
("This is the second category description");

INSERT INTO User (income, twitter, password)
VALUES (10, "@gosho", "1234"),
(100, "@business", "29304857209345782039457849056873456");

INSERT INTO Tag (name, priority)
VALUES ("action", 1),
("adventure", 3);

INSERT INTO TagArticle (tag, article)
VALUES (1,1),
(1,2);

INSERT INTO ArticleUser (article, user)
VALUES (2,1),
(2,2);

INSERT INTO UserCategory( user, category ) 
VALUES ( 2, 2 ) , ( 1, 1 );

# selects1.sql Query1

SELECT DISTINCT user, tag
FROM ArticleUser, TagArticle;

# Export1

mysqldump -u root -p DBANME > database.sql

# migrates.sql Migrates

CREATE TABLE Article_5_part1(
	id INT AUTO_INCREMENT NOT NULL,
	content LONG VARCHAR,
	PRIMARY KEY(id)
);

CREATE TABLE Article_5_part2(
	id INT,
	published_on TIMESTAMP,
	url VARCHAR( 255 ) ,
	FOREIGN KEY ( id ) REFERENCES Article_5_part1( id )
);

ALTER TABLE ArticleUser DROP FOREIGN KEY ArticleUser_ibfk_1;
ALTER TABLE TagArticle DROP FOREIGN KEY TagArticle_ibfk_2;

SET FOREIGN_KEY_CHECKS=0;

ALTER TABLE ArticleUser
ADD FOREIGN KEY (article)
REFERENCES Article_5_part1(id);

ALTER TABLE TagArticle
ADD FOREIGN KEY (article)
REFERENCES Article_5_part1(id);

SET FOREIGN_KEY_CHECKS=1;

DROP TABLE Article_5;

# Export2

mysqldump -u root -p DBANME > database.sql

# selects2.sql Query2

SELECT DISTINCT category, article FROM UserCategory, ArticleUser;

# capture.png Database pioture

# Vasil_Kolev_12B_06.zip Archive all