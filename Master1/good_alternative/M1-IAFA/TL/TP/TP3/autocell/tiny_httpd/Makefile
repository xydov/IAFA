
# OCAML configuration
OCAML_PREFIX=
OCAMLC=$(OCAML_PREFIX)ocamlc


# definitions
LIB=tiny_httpd
SOURCES=\
	src/Tiny_httpd_util.ml \
	src/Tiny_httpd.ml
INT_SOURCES=\
	src/Tiny_httpd_util.mli \
	src/Tiny_httpd.mli
OBJECTS=$(SOURCES:.ml=.cmo)
INT_OBJECTS=$(INT_SOURCES:.mli=.cmi)
CFLAGS=-I +threads -I src
LDFLAGS=unix.cma threads.cma

# rules
all: $(LIB).cma

$(LIB).cma: $(INT_OBJECTS) $(OBJECTS)
	$(OCAMLC) $(CFLAGS) -a -o $@ $(LDFLAGS) $(OBJECTS) 

clean:
	rm -rf $(OBJECTS) $(INT_OBJECTS) $(tiny_httpd).cma

%.cmo: %.ml
	$(OCAMLC) $(CFLAGS) -o $@ -c $<

%.cmi: %.mli
	$(OCAMLC) $(CFLAGS) -o $@ -c $<

