import os

def getTrainingSet():
        l = os.listdir( os.getcwd() )
        print l

def main():
        getTrainingSet()

if __name__ == "__main__":
        main()
