build = gcc -o main main.c -Wall -Wextra -Wpedantic
run = $(build) && ./main

run:
	$(run)

watch:
	clear; $(run) ;\
	reflex --decoration=none -r '.*\.c' -- zsh -c 'clear; $(run)'


