export php_version=7.3

docker pull php:$php_version-alpine

docker run \
    -v $PWD:/usr/src/myapp \
    -w /usr/src/myapp \
    php:$php_version-alpine \
    php HelloWorld.php
