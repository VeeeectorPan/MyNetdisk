CC:=gcc
srcs:=$(wildcard ./SourceFile/*.c)
objs:=$(srcs:%.c=%.o)
out:=main
$(out):$(objs)
	$(CC) $(objs) -o $(out) 
%.o:%.c
	$(CC) -c $^ -o $@
.PHONY:clean rebuild
clean:
	$(RM) $(objs) $(out)
rebuild:clean $(out)
