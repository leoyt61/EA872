import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import subprocess

subprocess.run(['g++', '-omain', 'main.cpp', 'sistema.cpp', 'mola.cpp', 'massa.cpp', 'amortecedor.cpp'])
result = subprocess.run(['./main'], stdout=subprocess.PIPE)
out = str(result.stdout).split("'")[1].split(";")

times = []
distances = []
speeds = []

for i in range(len(out)-1):
    t = []
    s1 = []
    s2 = []
    out2 = out[i].split("|")
    for j in range(len(out2)-1):
        res = out2[j].split("/")
        t.append(float(res[0]))
        s1.append(float(res[1]))
        s2.append(float(res[2]))
    times.append(t)
    distances.append(s1)
    speeds.append(s2)

    

# Note that even in the OO-style, we use `.pyplot.figure` to create the figure.
fig, ax = plt.subplots()  # Create a figure and an axes.
ax.plot(times[0], distances[0], label='Sem amortecimento')  # Plot some data on the axes.
ax.plot(times[1], distances[1], label='Subamortecido')  # Plot more data on the axes...
ax.plot(times[2], distances[2], label='Superamortecido')  # ... and some more.
ax.set_xlabel('Tempo (s)')  # Add an x-label to the axes.
ax.set_ylabel('Distância (m)')  # Add a y-label to the axes.
ax.set_title("Sistema MMA")  # Add a title to the axes.
ax.legend()  # Add a legend.

fig.tight_layout()  # otherwise the right y-label is slightly clipped
fig.savefig("chart1.png")
plt.show()

# Note that even in the OO-style, we use `.pyplot.figure` to create the figure.
fig, ax = plt.subplots()  # Create a figure and an axes.
ax.plot(times[0], speeds[0], label='Sem amortecimento')  # Plot some data on the axes.
ax.plot(times[1], speeds[1], label='Subamortecido')  # Plot more data on the axes...
ax.plot(times[2], speeds[2], label='Superamortecido')  # ... and some more.
ax.set_xlabel('Tempo (s)')  # Add an x-label to the axes.
ax.set_ylabel('Velocidade (m/s)')  # Add a y-label to the axes.
ax.set_title("Sistema MMA")  # Add a title to the axes.
ax.legend()  # Add a legend.

fig.tight_layout()  # otherwise the right y-label is slightly clipped
fig.savefig("chart2.png")
plt.show()