vpath %.c src
vpath %.h include

CPPFLAGS = -I include -Wall

objects := main.o util.o tuntap_if.o

lvl-ip: $(objects)
	$(CC) $(objects) -o lvl-ip

clean:
	rm *.o lvl-ip
