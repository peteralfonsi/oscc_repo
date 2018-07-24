import csv
with open("torque_test_space214.csv", "r+") as csvfile:
    reader = csv.DictReader(csvfile)
    for row in reader:
        print(row['first_name'], row['last_name'])
print(row)
OrderedDict([('first_name', 'John'), ('last_name', 'Cleese')])
