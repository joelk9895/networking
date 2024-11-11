import numpy as np
import matplotlib.pyplot as plt

# Define the range of x values
x = np.linspace(-10, 10, 4000)  # 400 points from -10 to 10
# Compute the corresponding f(x) values
f_x = x**2

# Create the plot
plt.figure(figsize=(8, 6))
plt.plot(x, f_x, label='$f(x) = x^2$', color='blue')

# Add labels and title
plt.title('Plot of $f(x) = x^2$')
plt.xlabel('x')
plt.ylabel('$f(x)$')
plt.axhline(0, color='black',linewidth=0.5, ls='--')  # x-axis
plt.axvline(0, color='black',linewidth=0.5, ls='--')  # y-axis
plt.grid(color = 'gray', linestyle = '--', linewidth = 0.5)
plt.legend()
plt.xlim(-10, 10)
plt.ylim(0, 100)
plt.show()