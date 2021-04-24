CC:=gcc
srcs:=$(wildcard ./SourceFile/*.c)
objs:=$(srcs:%.c=%.o)
srcs2:=$(wildcard ./clientSrc/*.c)
objs2:=$(srcs2:%.c=%.o)
out:=server
out2:=client
all:$(out) $(out2)
$(out2):$(objs2)
	$(CC) $(objs2) -o $(out2) -pthread
%.o:%.c
	$(CC) -g -Wall -c $^ -o $@ -pthread
$(out):$(objs)
	$(CC) $(objs) -o $(out) -pthread
%.o:%.c
	$(CC) -g -Wall -c $^ -o $@ -pthread
.PHONY:clean rebuild
clean:
	$(RM) $(objs) $(out) $(objs2) $(out2)
rebuild:clean all
