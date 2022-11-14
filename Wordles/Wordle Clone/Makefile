CC = clang

# Make sure to use the full CFLAGS before turning in. Uncomment this for lax
# checking during development, if you need to.
# CFLAGS = -g

# You can comment this out and use the above CFLAGS instead if you need to,
# during development.
CFLAGS = -Wall -Wpedantic -Werror -Wextra -g


all: hw5

hw5: hw5.c
	$(CC) $(CFLAGS) hw5.c -o hw5

clean:
	rm -f hw5

format:
	clang-format -i -style=file *.[ch]
