import numpy as np
from matplotlib import pyplot as plt


file_path = 'output/Call.csv'
data = np.genfromtxt(file_path, delimiter=";", skip_header=1)


x, y, call_value, delta, gamma, theta = data[:, 0], data[:, 1], data[:, 2], data[:, 3], data[:, 4], data[:, 5]


points = len(x)
rows = cols = int(np.sqrt(points))
if rows * cols != points:
    print("Le fichier n'a pas une grille carrée parfaite.")
    exit()

X = np.reshape(x, (rows, cols))
Y = np.reshape(y, (rows, cols))
Z_call = np.reshape(call_value, (rows, cols))
Z_delta = np.reshape(delta, (rows, cols))
Z_gamma = np.reshape(gamma, (rows, cols))
Z_theta = np.reshape(theta, (rows, cols))

# Graphique 3D pour le prix du call
fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(221, projection='3d')
surf = ax.plot_surface(X, Y, Z_call, cmap='viridis')
ax.set_title('Prix du Call')
ax.set_xlabel('Position (S)')
ax.set_ylabel('Temps (T)')
ax.set_zlabel('Prix du Call')
fig.colorbar(surf, ax=ax, shrink=0.5)

# Graphique 3D pour Delta
ax = fig.add_subplot(222, projection='3d')
surf = ax.plot_surface(X, Y, Z_delta, cmap='plasma')
ax.set_title('Delta')
ax.set_xlabel('Position (S)')
ax.set_ylabel('Temps (T)')
ax.set_zlabel('Delta')
fig.colorbar(surf, ax=ax, shrink=0.5)

# Graphique 3D pour Gamma
ax = fig.add_subplot(223, projection='3d')
surf = ax.plot_surface(X, Y, Z_gamma, cmap='coolwarm')
ax.set_title('Gamma')
ax.set_xlabel('Position (S)')
ax.set_ylabel('Temps (T)')
ax.set_zlabel('Gamma')
fig.colorbar(surf, ax=ax, shrink=0.5)

# Graphique 3D pour Theta
ax = fig.add_subplot(224, projection='3d')
surf = ax.plot_surface(X, Y, Z_theta, cmap='inferno')
ax.set_title('Theta')
ax.set_xlabel('Position (S)')
ax.set_ylabel('Temps (T)')
ax.set_zlabel('Theta')
fig.colorbar(surf, ax=ax, shrink=0.5)

plt.tight_layout()
plt.show()


