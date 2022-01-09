

def main():
    x = int(input("x: "))
    y = int(input("y: "))
    z = maximum(x, y)
    print(z)


def maximum(a, b):
    if a > b:
        return a
    else:
        return b



main()