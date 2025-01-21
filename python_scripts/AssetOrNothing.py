import numpy as np
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

file_path = 'output/AssetOrNothing.csv'
data = np.genfromtxt(file_path, delimiter=";", skip_header=1)

if data.ndim != 2 or data.shape[1] < 6:
    raise ValueError("Les données ne contiennent pas suffisamment de colonnes.")

x, y, put_value, delta, gamma, theta = data[:, 0], data[:, 1], data[:, 2], data[:, 3], data[:, 4], data[:, 5]

points = len(x)
rows = cols = int(np.sqrt(points))
if rows * cols != points:
    raise ValueError("Le fichier n'a pas une grille carrée parfaite.")

X = np.reshape(x, (rows, cols))
Y = np.reshape(y, (rows, cols))
Z_put = np.reshape(put_value, (rows, cols))
Z_delta = np.reshape(delta, (rows, cols))
Z_gamma = np.reshape(gamma, (rows, cols))
Z_theta = np.reshape(theta, (rows, cols))

fig = plt.figure(figsize=(15, 12))

ax = fig.add_subplot(221, projection='3d')
surf = ax.plot_surface(X, Y, Z_put, cmap='viridis')
ax.set_title('Prix de l\'option Asset-or-Nothing')
ax.set_xlabel('Position (S)')
ax.set_ylabel('Temps (T)')
ax.set_zlabel('Valeur')
fig.colorbar(surf, ax=ax, shrink=0.5)

ax = fig.add_subplot(222, projection='3d')
surf = ax.plot_surface(X, Y, Z_delta, cmap='plasma')
ax.set_title('Delta')
ax.set_xlabel('Position (S)')
ax.set_ylabel('Temps (T)')
ax.set_zlabel('Delta')
fig.colorbar(surf, ax=ax, shrink=0.5)

ax = fig.add_subplot(223, projection='3d')
surf = ax.plot_surface(X, Y, Z_gamma, cmap='coolwarm')
ax.set_title('Gamma')
ax.set_xlabel('Position (S)')
ax.set_ylabel('Temps (T)')
ax.set_zlabel('Gamma')
fig.colorbar(surf, ax=ax, shrink=0.5)

ax = fig.add_subplot(224, projection='3d')
surf = ax.plot_surface(X, Y, Z_theta, cmap='inferno')
ax.set_title('Theta')
ax.set_xlabel('Position (S)')
ax.set_ylabel('Temps (T)')
ax.set_zlabel('Theta')
fig.colorbar(surf, ax=ax, shrink=0.5)

plt.tight_layout()
plt.show()
