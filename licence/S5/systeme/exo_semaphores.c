// contexte de mem partagée

typedef struct s_message{
    int info;
    int type;
}message;

message BUFFER[N];
int ICV;
int ICP;

void deposer_message(message m)
{
    BUFFER[ICV].info = msg.info;
    BUFFER[ICV].type = msgtype;
    ICV = (ICV + 1) % N;
}

void deposer(message m)
{
    P(Casevide);
    P(MUTEXP);
    deposer_message(msg);
    V(MUTEXP);
    V(Casepleine);
}

void retirer_message(message *m)
{
    m->info = BUFFER[ICP].info;
    m->type = BUFFER[ICP].type;
    ICP = (ICP + 1) % N;
}

void retirer(message m)
{
    P(Casepleine);
    P(MUTEXC);
    retirer_message(msg);
    V(MUTEXC);
    V(Casevide);
}

void init()
{
    ICV = 0;
    ICP = 0;
    InitSem(MUTEXP, );
    InitSem(MUTEXC, 1);
    InitSem(Casepleine, 0);
    InitSem(Casevide, N);
}