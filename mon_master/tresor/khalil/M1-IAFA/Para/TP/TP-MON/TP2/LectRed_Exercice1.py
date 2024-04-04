import sys
import time
import random
from multiprocessing import Process, Lock, Condition, Value

class RW:
    def __init__(self):
        self.is_writing = Value('i', 0, lock=False)
        self.nb_waiting_writers = Value('i', 0, lock=False)
        self.nb_readers = Value('i', 0, lock=False)
        self.verrou = Lock()
        self.acces = [Condition(self.verrou), Condition(self.verrou)]

    def start_read(self):
        with self.verrou:
            while bool(self.is_writing.value) or self.nb_waiting_writers.value != 0:
                self.acces[1].wait()
            self.nb_readers.value += 1
            self.acces[1].notify()

    def end_read(self):
        with self.verrou:
            self.nb_readers.value -= 1
            if self.nb_readers.value == 0:
                self.acces[0].notify()

    def start_write(self):
        with self.verrou:
            while bool(self.is_writing.value) or self.nb_readers.value != 0:
                self.nb_waiting_writers.value += 1
                self.acces[0].wait()
                self.nb_waiting_writers.value -= 1
            self.is_writing.value = 1

    def end_write(self):
        with self.verrou:
            self.is_writing.value = 0
            if self.nb_waiting_writers.value == 0:
                self.acces[1].notify()
            else:
                self.acces[0].notify()


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
