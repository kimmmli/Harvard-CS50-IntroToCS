import sys

if len(sys.argv)!=1:
    sys.exit("Usage: python tournament.py")

keyword=input("Have a guess: ")
keyword=keyword.lower()
if (keyword[:5]=="hello"):
    print("You get $0.")
elif(keyword[0]=="h" and keyword[:5]!="hello"):
    print("You get $20.")
else:
    print("You get $100.")

