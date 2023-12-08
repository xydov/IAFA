#!/usr/bin/env python3


import subprocess
import sys


NULL = open("/dev/null", "w")

def say(m):
	sys.stdout.write(m)
	sys.stdout.flush()


def noter():
    note=0
    rc_base = subprocess.call("gcc -o notation0 notation0.c sudoku.c",shell = True, stdout = NULL, stderr = NULL)

    if rc_base == 0:
        say("Notation partie 0 compilee\n")
    else:
        say("Echec de compilation partie 0\nNote provisoire : 0\n")
        sys.exit(1)
    process=subprocess.Popen("./notation0",shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE, bufsize=1)
    (out,err)=process.communicate()
    if(process.returncode==0):
        print(out.decode('utf-8'))
        note+=2*(float(err.decode('utf-8'))/172)
        #print(err.decode('utf-8'))
    rc_base = subprocess.call("gcc -o notation1 notation1.c sudoku.c",shell = True, stdout = NULL, stderr = NULL)

    if rc_base == 0:
        say("Notation partie 1 compilee\n")
    else:
        say("Echec de compilation partie 1\n")
        print("Note provisoire : "+str(note))
        sys.exit(1)
    process=subprocess.Popen("./notation1",shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE, bufsize=1)
    
    (out,err)=process.communicate()
    if(process.returncode==0):
        print(out.decode('utf-8'))
        note+=2*(float(err.decode('utf-8'))/100)
        #print(str(note))
        
    rc_base = subprocess.call("gcc -o notation2 notation2.c sudoku.c",shell = True, stdout = NULL, stderr = NULL)

    if rc_base == 0:
        say("Notation partie 2 compilee\n")
    else:
        say("Echec de compilation partie 2\n")
        print("Note provisoire : "+str(note))
        sys.exit(1)
    process=subprocess.Popen("./notation2",shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE, bufsize=1)
    
    (out,err)=process.communicate()
    if(process.returncode==0):
        print(out.decode('utf-8'))
        note+=3*(float(err.decode('utf-8'))/100)
        #print(str(note))

    rc_base = subprocess.call("gcc -o notation3 notation3.c sudoku.c",shell = True, stdout = NULL, stderr = NULL)

    if rc_base == 0:
        say("Notation partie 3 compilee\n")
    else:
        say("Echec de compilation partie 3\n")
        print("Note provisoire : "+str(note))
        sys.exit(1)
    process=subprocess.Popen("./notation3",shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE, bufsize=1)
    
    (out,err)=process.communicate()
    if(process.returncode==0):
        print(out.decode('utf-8'))
        note+=3*(float(err.decode('utf-8'))/100)
        #print(str(note))



    rc_base = subprocess.call("gcc -o notation4 notation4.c sudoku.c",shell = True, stdout = NULL, stderr = NULL)

    if rc_base == 0:
        say("Notation partie 4 compilee\n")
    else:
        say("Echec de compilation partie 4\n")
        print("Note provisoire : "+str(note))
        sys.exit(1)
    process=subprocess.Popen("./notation4",shell=True,stdout=sys.stdout,stderr=subprocess.PIPE, bufsize=1)
    (out,err)=process.communicate()
    if(process.returncode==0):
        #print(out.decode('utf-8'))
        note+=3*(float(err.decode('utf-8'))/10)

    print("\nNote provisoire : "+str(note)+"/10")
noter()
