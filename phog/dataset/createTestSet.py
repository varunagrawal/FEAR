import os
import random
import shutil

def test_set():
    test = []
    
    with open("cohn_data_final.txt") as f:
        l = f.readlines()

        for i in range(80):
            rand = random.choice(l)
            test.append(rand)

            del l[l.index(rand)]

    with open("cohn_train_set.txt", 'w') as train_file:
        for i in l:
            train_file.write(i)
            
    with open("cohn_test_set.txt", 'w') as test_file:
        for i in test:
            test_file.write(i)

            name = i[:-3] + ".png"
            #shutil.move("Images/" + name, "Images/test/" + name)

    

if __name__ == "__main__":
    test_set()
