def rightside_triangle(value):
    stars=1
    for x in range(int(value)):
        for x in range(stars):
            print("*",end='')
            pass
        print()
        stars=stars+1
        pass
    pass

def leftside_triangle(value):
    space=int(value)-1
    stars=1
    for x in range(int(value)):
        for x in range(space):
            print(" ",end='')
            pass
        space-=1
        for x in range(stars):
            print("*",end='')
            pass
        stars+=1
        print()
        pass
    pass

def pyramid(value):
    space=int(value)-1
    stars=1
    for x in range(int(value)):
        for x in range(space):
            print(" ",end='')
            pass
        space-=1
        for x in range(stars):
            print("* ",end='')
            pass
        stars+=1
        print()
        pass
    pass

start_value=input()

rightside_triangle(start_value)
leftside_triangle(start_value)
pyramid(start_value)