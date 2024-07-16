import sys
import os
import time
import random
from multiprocessing import Process, Lock, Condition, Value

class ExtendedCondition:
    def __init__(self, verrou):
        self.verrou = verrou
        self.priority = [Condition(verrou), Condition(verrou)]
        self.count_priority = [Value('i', 0, lock=False), Value('i', 0, lock=False)]

    def wait(self, priority=1):
        self.count_priority[priority].value += 1
        self.priority[priority].wait()
    
    def notify(self):
        if self.count_priority[0].value == 0:
            self.priority[1].notify()
            self.count_priority[1].value -= 1
        else:
            self.priority[0].notify()
            self.count_priority[0].value -= 1
    
    def isEmpty(self):
        return (self.count_priority[0].value + self.count_priority[0].value) == 0

class Isoloirs:
    def __init__(self, NBI):
        self.NBI = Value('i', NBI, lock=False)
        self.verrou = Lock()
        self.condition = ExtendedCondition(self.verrou)
        
    def enter_NBI(self, priority):
        with self.verrou:
            while self.NBI.value == 0:
                self.condition.wait(priority)
            self.NBI.value -= 1

    def exit_NBI(self):
        with self.verrou:
            self.NBI.value += 1
            self.condition.notify()
        
def voter(priority, identifier, id):
    print("\tL'electeur %d avec id : %d, de priorité %d vote ----->" % (identifier, id, priority))
    time.sleep(random.random())

def vote(priority, isoloirs, id):
    identifier = os.getpid()
    random.seed(identifier)

    print("L'electeur %d avec id : %d, Arrive ------>" % (identifier, id))
    isoloirs.enter_NBI(priority)
    voter(priority, identifier, id)
    print("\tL'electeur %d avec id : %d, a finit de voter" % (identifier, id))
    isoloirs.exit_NBI()

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage : %s <Nb vehicules sens O> <Nb vehicules sens 1> <Nb passages sur VU>" % sys.argv[0]);
        sys.exit(1)

    NBE, NBI = int(sys.argv[1]), int(sys.argv[2])
    
    isoloirs = Isoloirs(NBI=NBI)

    processes = []
    for v in range(NBE):
        v0 = Process(target=vote, args=(v % 2, isoloirs, v))
        v0.start()
        processes.append(v0)



    for process in processes:
        process.join()
        

