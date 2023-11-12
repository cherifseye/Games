import matplotlib.pyplot as plt
import numpy as np
"""img = plt.imread("graphics/background.png")
print(img.shape)
x = np.linspace(0, 300, 100)
y = np.tan(1.10714871779409)* x - np.tan(1.10714871779409)*x**2/300
print(y)
plt.plot(x, y)
plt.show()"""


g = 9.81
Rm = 300 
theta = 1.10714871779409
u = np.sqrt((g * Rm) / np.sin(2*theta))
print(Rm / (u  * np.cos(theta)))
t = np.linspace(0, 11, 1000)
x = u*np.cos(theta) * t
y = u*np.sin(theta) * t - 0.5*g*t**2
plt.plot(x, y)
plt.show()
