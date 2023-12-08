CC  = gcc
SYS = -Wall -pedantic -DUNIX -std=gnu99
INC = -I.

SRCDIR = src
BINDIR = bin
OBJDIR = obj
FILESDIR = fichiers

OBJ_CONF   = config.o
OBJ_NET    = services_reseau.o
OBJ_TRP    = couche_transport.o
OBJ_APP_NC = appli_non_connectee.o

OBJ_COMMON = $(OBJ_CONF) $(OBJ_NET) $(OBJ_TRP)

OBJ_TDD0_E = proto_tdd_v0_emetteur.o
OBJ_TDD0_R = proto_tdd_v0_recepteur.o

OBJ_TDD1_E = proto_tdd_v1_emetteur.o
OBJ_TDD1_R = proto_tdd_v1_recepteur.o

OBJ_TDD2_E = proto_tdd_v2_emetteur.o
OBJ_TDD2_R = proto_tdd_v2_recepteur.o

OBJ_TDD3_E = proto_tdd_v3_emetteur.o
OBJ_TDD3_R = proto_tdd_v3_recepteur.o

OBJ_TDD4_E = proto_tdd_v4_emetteur.o
OBJ_TDD4_R = proto_tdd_v4_recepteur.o

# TDD v0 : pas de controle de flux, ni de reprise sur erreurs
# ------------------------------------------------------------
tdd0: $(OBJ_COMMON) $(OBJ_APP_NC) $(OBJ_TDD0_E) $(OBJ_TDD0_R)
	$(CC) -o $(BINDIR)/emetteur $(OBJ_COMMON) $(OBJ_APP_NC) $(OBJ_TDD0_E)
	$(CC) -o $(BINDIR)/recepteur $(OBJ_COMMON) $(OBJ_APP_NC) $(OBJ_TDD0_R)
	mv *.o $(OBJDIR)/

# TDD v1 : controle de flux S&W et détection d'erreurs (pas de perte)
# --------------------------------------------------------------------
tdd1: $(OBJ_COMMON) $(OBJ_APP_NC) $(OBJ_TDD1_E) $(OBJ_TDD1_R)
	$(CC) -o $(BINDIR)/emetteur $(OBJ_COMMON) $(OBJ_APP_NC) $(OBJ_TDD1_E)
	$(CC) -o $(BINDIR)/recepteur $(OBJ_COMMON) $(OBJ_APP_NC) $(OBJ_TDD1_R)
	mv *.o $(OBJDIR)/

# TDD v2 : controle de flux et reprise sur erreurs S&W (erreurs + pertes)
# ------------------------------------------------------------------------
tdd2: $(OBJ_COMMON) $(OBJ_APP_NC) $(OBJ_TDD2_E) $(OBJ_TDD2_R)
	$(CC) -o $(BINDIR)/emetteur $(OBJ_COMMON) $(OBJ_APP_NC) $(OBJ_TDD2_E)
	$(CC) -o $(BINDIR)/recepteur $(OBJ_COMMON) $(OBJ_APP_NC) $(OBJ_TDD2_R)
	mv *.o $(OBJDIR)/

# TDD v3 : controle de flux et reprise sur erreurs Go-Back-N
# ------------------------------------------------------------
tdd3: $(OBJ_COMMON) $(OBJ_APP_NC) $(OBJ_TDD3_E) $(OBJ_TDD3_R)
	$(CC) -o $(BINDIR)/emetteur $(OBJ_COMMON) $(OBJ_APP_NC) $(OBJ_TDD3_E)
	$(CC) -o $(BINDIR)/recepteur $(OBJ_COMMON) $(OBJ_APP_NC) $(OBJ_TDD3_R)
	mv *.o $(OBJDIR)/

# TDD v4 : controle de flux et reprise sur erreurs Selective Repeat
# ------------------------------------------------------------------
tdd4: $(OBJ_COMMON) $(OBJ_APP_NC) $(OBJ_TDD4_E) $(OBJ_TDD4_R)
	$(CC) -o $(BINDIR)/emetteur $(OBJ_COMMON) $(OBJ_APP_NC) $(OBJ_TDD4_E)
	$(CC) -o $(BINDIR)/recepteur $(OBJ_COMMON) $(OBJ_APP_NC) $(OBJ_TDD4_R)
	mv *.o $(OBJDIR)/

# '%' matches filename
# $@  for the pattern-matched target
# $<  for the pattern-matched dependency
%.o: $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(SYS) $(INC)

clean:
	rm -f *.o
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIR)/* $(FILESDIR)/out.*
