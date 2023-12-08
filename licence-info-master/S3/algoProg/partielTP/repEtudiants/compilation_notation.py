#!/usr/bin/env python3


import subprocess
import sys


NULL = open("/dev/null", "w")

def say(m):
	sys.stdout.write(m)
	sys.stdout.flush()


def noter():
    note=0
    note0=0
    rc_base = subprocess.call("gcc -o notation1 notation1.c sudoku.c",shell = True, stdout = NULL, stderr = NULL)

    if rc_base == 0:
        say("Notation partie 1 compilee\n")
        process=subprocess.Popen("./notation1",shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE, bufsize=1)
        (out,err)=process.communicate()
        if(process.returncode==0):
                print(out.decode('utf-8'))
                note0+=(float(err.decode('utf-8'))/900)
                #print(err.decode('utf-8'))
    else:
        say("Echec de compilation partie 1\n")
        #sys.exit(1)
    
    rc_base = subprocess.call("gcc -o notation2 notation2.c sudoku.c",shell = True, stdout = NULL, stderr = NULL)

    if rc_base == 0:
        say("Notation partie 2 compilee\n")
        process=subprocess.Popen("./notation2",shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE, bufsize=1)
    
        (out,err)=process.communicate()
        if(process.returncode==0):
                print(out.decode('utf-8'))
                note0=max((float(err.decode('utf-8'))/100),note0)
                #print(str(note))
    else:
        say("Echec de compilation partie 2\n")
        #print("Note provisoire : "+str(note))
        #sys.exit(1)    
        
    rc_base = subprocess.call("gcc -o notation3 notation3.c sudoku.c",shell = True, stdout = NULL, stderr = NULL)

    if rc_base == 0:
        say("Notation partie 3 compilee\n")
        process=subprocess.Popen("./notation3",shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE, bufsize=1)
    
        (out,err)=process.communicate()
        if(process.returncode==0):
                print(out.decode('utf-8'))
                note+=(6*(float(err.decode('utf-8'))/100))
                #print(str(note))

    else:
        say("Echec de compilation partie 3\n")
        #print("Note provisoire : "+str(note))
        #sys.exit(1)
    note = max(0,note) + (4*note0)
    print("\nNote provisoire : "+str(note)+"/10")
noter()
