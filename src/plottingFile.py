#!/usr/local/bin/python3.6
import matplotlib.pyplot as plt
size = 24
errorZeta = open("../output/errorZeta.txt", "r")
errorMach = open("../output/errorMach.txt", 'r')
yZeta = [float(line) for line in errorZeta.readlines()]
yMach = [float(line) for line in errorMach.readlines()]
x = range(24)



plt.plot(x, yZeta,'--', label='Zeta')
plt.plot(x, yMach, '--', label='Mach')
plt.xlabel("Iterations (k)")
plt.ylabel("Absolute error")
plt.title("Error plot")
plt.legend()
plt.savefig("error.png")
plt.show()
