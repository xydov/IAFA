def mdt(nFich):
    ensembleMot = set()
    f = open(nFich, 'r')
    for line in f:
        for mot in line.split():
            ensembleMot.add(mot)
    f.close()
    return ensembleMot

def intersection(e1, e2):
    intersec = set()
    for i in e1:
        if i in e2:
            intersec.add(i)
    return intersec
