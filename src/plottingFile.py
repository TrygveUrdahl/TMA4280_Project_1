#!/usr/local/bin/python3.6
import matplotlib.pyplot as plt
size = 1000
"""
errorZeta = open("../output/errorZeta.txt", "r")
errorMach = open("../output/errorMach.txt", 'r')
yZeta = [float(line) for line in errorZeta.readlines()]
yMach = [float(line) for line in errorMach.readlines()]
x = range(1, size + 1)



plt.plot(x, yZeta,'--', label='Zeta')
plt.plot(x, yMach, '--', label='Mach')
plt.xlabel("Iterations (n)")
plt.ylabel("Absolute error")
plt.title("Error plot")
plt.legend()
plt.savefig("error5p8.png")
plt.show()
"""

timingZeta = open("../output/timingZeta.txt", "r")
timingMach = open("../output/timingMach.txt", 'r')
yZeta = [float(line) for line in timingZeta.readlines()]
yMach = [float(line) for line in timingMach.readlines()]
x = range(1, size + 1)



plt.plot(x, yZeta,'-', label='Zeta')
plt.plot(x, yMach, '-', label='Mach')
plt.xlabel("Iterations (n)")
plt.ylabel("Time used ($\mu s$)")
plt.ylim(0, 150)
plt.title("Timing plot")
plt.legend()
plt.savefig("timing5p8.png")
plt.show()
