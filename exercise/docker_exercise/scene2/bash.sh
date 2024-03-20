docker run --name ex-app-db \
    -e MARIADB_ROOT_PASSWORD=exroot \
    -d mariadb:latest

docker run --name ex-app-myadmin \
    --link ex-app-db:db \
    -d -p 8000:8080 \
    adminer
