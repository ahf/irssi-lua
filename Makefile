CFLAGS = -Wall -O2 -g
LDFLAGS = -avoid-version -module

OBJECTS = lua_loader.o lua_core.o lua_commands.o

IRSSI_DIST = /usr/include/irssi/

IRSSI_INCLUDE = -I$(IRSSI_DIST) -I$(IRSSI_DIST)/src -I$(IRSSI_DIST)/src/fe-common/core \
				-I$(IRSSI_DIST)/src/core -I$(IRSSI_DIST)/src/fe-text -I$(IRSSI_DIST)/src/irc \
				-I$(IRSSI_DIST)/src/irc/core -I$(IRSSI_DIST)/src/irc/dcc -I$(IRSSI_DIST)/src/irc/notifylist

GLIB_CFLAGS = $(shell pkg-config glib-2.0 --cflags)
LUA_LIBS = $(shell pkg-config lua --libs)

all: liblua.so

%.o: %.c
	$(CC) $(CFLAGS) $(GLIB_CFLAGS) $(IRSSI_INCLUDE) -I. -fPIC -c $<

liblua.so: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LUA_LIBS) -fPIC -shared $(OBJECTS) -o $@

install: liblua.so
	install $< ~/.irssi/modules/

clean:
	rm -rf *~ *.o *.so core || true

.default: all

.phony: clean install
