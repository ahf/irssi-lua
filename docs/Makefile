LUADOCS = $(shell ls *.luadoc)

index.html: $(LUADOCS)
	luadoc *.luadoc

all: index.html

clean:
	rm -rf *.html *.css modules/ files/ || true

upload: index.html
	scp -r index.html files/ modules/ luadoc.css dev.exherbo.org:public_html/pub/software/docs/lua-irssi/

.default: all

.phony: all clean upload
