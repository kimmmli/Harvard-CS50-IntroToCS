# TODO
import sys


def evaltype(cardnum):
    cardnum=str(cardnum)
    if len(cardnum)==15:
        if (cardnum[:2]==34 or cardnum[:2]==37):
            return ("American Express")

    if len(cardnum)==16:
        if (cardnum[:2]==51 or cardnum[:2]==52 or cardnum[:2]==53 or cardnum[:2]==54 or cardnum[:2]==55):
            return ("Master Card")

    if (len(cardnum)==13 or len(cardnum)==16):
        if (cardnum[0]=="4"):
            return ("Visa")
    return "Not Valid"


def evalvalid(cardnum):
    cardnum=str(cardnum)
    lencard=len(cardnum)
    a=0
    for i in range(lencard,-2,2):
        for j in range(len(str(2*int(cardnum[i])))):
            a+=int((2*cardnum[i])[j])
    for z in range(lencard,-1,2):
        a+=int(cardnum[z])
    if str(a)[-1]=='0':
        return True
    else:
        return False




def main():
    try:
        cardnum=int(input("Number: "))
        if evalvalid(cardnum)==True and evaltype(cardnum)!="Not Valid":
            print("Valid")
            print(evaltype(cardnum))
        else:
            print("Not Valid")
    except ValueError:
        print("Please only input numbers.")

main()