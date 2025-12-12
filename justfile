
build:
    mkdir -p bin
    clang -nostdlib -o bin/my_program src/echo.c

run recipe:
    just build
    ./bin/{{recipe}}
