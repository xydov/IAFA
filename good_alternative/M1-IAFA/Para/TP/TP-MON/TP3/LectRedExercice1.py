import sys
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
        return (self.count_priority[0].value == 0 + self.count_priority[0].value) == 0
    

class RW:
    def __init__(self):
        self.verrou = Lock()
        self.condition = ExtendedCondition(self.verrou)
        self.isWriting = Value('i', 0, lock=False)
        self.nb_readers = Value('i', 0, lock=False)


    def start_read(self):
        with self.verrou:
            while bool(self.isWriting.value):
                self.condition.wait()
            self.nb_readers.value += 1
            self.condition.notify()

    def end_read(self):
        with self.verrou:
            self.nb_readers.value -= 1
            if self.nb_readers.value == 0:
                self.condition.notify()

    def start_write(self):
        with self.verrou:
            count = 1
            while self.nb_readers.value != 0:
                self.condition.wait(count)
                count = 0
            self.isWriting.value = 1

    def end_write(self):
        with self.verrou:
            self.isWriting.value = 0
            self.condition.notify()


def process_writer(identifier, synchro):
    synchro.start_write()
    for _ in range(5):
        with open('LectRed_shared', 'a') as file_id:
            txt=' '+str(identifier)
            file_id.write(txt)
            print('Writer', identifier, 'just wrote', txt)
        time.sleep(.1 + random.random())            
    synchro.end_write()
    
def process_reader(identifier, synchro):
    synchro.start_read()
    position = 0
    result = ''
    while True:
        time.sleep(.1 + random.random())            
        with open('LectRed_shared', 'r') as file_id:
            file_id.seek(position, 0)
            txt = file_id.read(1)
            if len(txt) == 0:
                break
            print('Reader', identifier, 'just read', txt)
            result += txt
            position+=1
    print(str(identifier)+':',result)
    synchro.end_read()
        
if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: %s <Nb reader> <Nb writer> \n" % sys.argv[0])
        sys.exit(1)

    nb_reader = int(sys.argv[1])
    nb_writer = int(sys.argv[2])

    synchro = RW()

    # To initialize the common data
    with open('LectRed_shared', 'w') as file_id:
        file_id.write('')
    
    processes = []
    for id_writer in range(nb_writer):
        writer = Process(target=process_writer, args=(id_writer,synchro))
        writer.start()
        processes.append(writer)

    for id_reader in range(nb_reader):
        reader = Process(target=process_reader, args=(id_reader,synchro))
        reader.start()
        processes.append(reader)

    for process in processes:
        process.join()
