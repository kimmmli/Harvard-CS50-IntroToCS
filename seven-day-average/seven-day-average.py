import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    newdict={}
    prevdict={}
    for row in reader:
        state=row["state"]
        case=int(row["cases"])

        if state not in prevdict:
            prevdict[state]= case
            newdict[state]=[]
        else:
            new_case=case-prevdict[state]
            prevdict[state]=case
            if len(newdict[state])>=14:
                newdict[state].pop(0)
            newdict[state].append(new_case)

    return newdict




# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for state in states:
        avgnewlist=new_cases[state][:7]
        avgoldlist=new_cases[state][-7:]
        newsum=0
        oldsum=0
        for i in range(7):
            newsum+=avgnewlist[i]
            oldsum+=avgoldlist[i]

        avgnew=newsum/len(avgnewlist)
        avgold=oldsum/len(avgoldlist)


        diff=avgnew-avgold

        if diff>0:
            msg="increase"
        elif diff<0:
            msg="decrease"

        try:
            rate=diff/avgold
        except ZeroDivisionError:
            raise ValueError

        print(state," had a 7-day average of ",round(avgnew,2), " and an ",msg ," of ",round(rate*100,2),"%.")



main()
