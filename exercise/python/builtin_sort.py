l = []
with open('sort-rand-19999999.txt') as f:
    for line in f:
        id, value = line.strip().split(': ')
        l.append((float(value), id))
l.sort()
print('Sorted!')