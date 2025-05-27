#!/bin/bash

echo "Waiting for DB"
STATUS="Uninitialized"

while ["$STATUS" != "1"]
do
  RESULT="$(echo "select count(*) from test_db.users;" | mysql --host mysql --user=$MARIADB_USER --password=$MARIADB_PASSWORD | fgrep -v count)"
  echo "Current status is $STATUS"
  sleep 1
done

echo "DB is ready"
touch /tmp/db_ready

echo "Wait forever to keep Docker running"
while true
do
  sleep 1 || break;
done
