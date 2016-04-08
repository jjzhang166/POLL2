poll:poll.c
	gcc -o poll poll.c
.PHONY:clean
clean:
	rm -rf poll
