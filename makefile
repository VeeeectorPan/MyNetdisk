CC:=gcc
srcs:=$(wildcard ./SourceFile/*.c)
objs:=$(srcs:%.c=%.o)
out:=server
$(out):$(objs)
	$(CC) $(objs) -o $(out) 
%.o:%.c
	$(CC) -g -Wall -c $^ -o $@
.PHONY:clean rebuild
clean:
	$(RM) $(objs) $(out)
rebuild:clean $(out)
