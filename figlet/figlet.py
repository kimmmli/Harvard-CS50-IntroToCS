from pyfiglet import Figlet
import sys

if (len(sys.argv)!=1 and len(sys.argv)!=3):
    sys.exit("Wrong input numbers.")


if (len(sys.argv)==3):
    if (sys.argv[1]!="-f" and sys.argv[1]!="--font"):
        sys.exit("Wrong input.")
    if Figlet(font=sys.argv[2]):
        keyword=input("Input: ")
        f=Figlet(font=sys.argv[2])
        print(f.renderText(keyword))
    else:
        print("Not valid font.")
else:
    keyword=input("Input: ")
    f = Figlet()
    print(f.renderText(keyword))


