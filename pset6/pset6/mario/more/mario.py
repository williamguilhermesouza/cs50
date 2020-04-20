try:
    size = int(input('Height: '))

except ValueError:
    size = int(input('Height: '))

while(size <= 0 or size > 8):
    size = int(input('Height: '))

for i in range(1, size + 1):
    print(' ' * (size - i), end='')
    print('#' * i, end='  ')
    print('#' * i)