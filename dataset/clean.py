# Program to setup the dataset file 'cohn_data.txt'

def main():
    f = open("cohn_data.txt")
    
    l = f.readlines()
    t = [x[:9] + "000000" + x[9:] for x in l]
    t = [x.upper() for x in t]

    o = open("cohn_data_final.txt", 'w')
    
    for item in t:
        o.write(item)

if __name__ == "__main__":
    main()
