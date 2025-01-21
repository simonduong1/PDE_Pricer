import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Chemin du fichier CSV
file_path = 'output/CallBarrierKO.csv'

# Chargement des données
call_barrier_data = np.genfromtxt(file_path, delimiter=";", skip_header=1)

# Vérification de la structure des données
if call_barrier_data.ndim != 2 or call_barrier_data.shape[1] < 6:
    raise ValueError("Les données ne contiennent pas suffisamment de colonnes.")

# Extraction des colonnes
x, y, value, delta, gamma, theta = call_barrier_data[:, 0], call_barrier_data[:, 1], call_barrier_data[:, 2], call_barrier_data[:, 3], call_barrier_data[:, 4], call_barrier_data[:, 5]

# Vérification des dimensions pour garantir une grille carrée
points = len(x)
rows = cols = int(np.sqrt(points))
if rows * cols != points:
    raise ValueError("Le fichier n'a pas une grille carrée parfaite.")

# Reshape des données pour former des grilles 2D
X = np.reshape(x, (rows, cols))
Y = np.reshape(y, (rows, cols))
Z_value = np.reshape(value, (rows, cols))
Z_delta = np.reshape(delta, (rows, cols))
Z_gamma = np.reshape(gamma, (rows, cols))
Z_theta = np.reshape(theta, (rows, cols))

# Création de la figure
fig = plt.figure(figsize=(15, 12))

# Surface pour Value
ax = fig.add_subplot(221, projection='3d')
surf = ax.plot_surface(X, Y, Z_value, cmap='viridis')
ax.set_title('Prix de l\'option Call Barrier KO)')
ax.set_xlabel('Position (S)')
ax.set_ylabel('Temps (T)')
ax.set_zlabel('Valeur')
fig.colorbar(surf, ax=ax, shrink=0.5)

# Surface pour Delta
ax = fig.add_subplot(222, projection='3d')
surf = ax.plot_surface(X, Y, Z_delta, cmap='plasma')
ax.set_title('Delta')
ax.set_xlabel('Position (S)')
ax.set_ylabel('Temps (T)')
ax.set_zlabel('Delta')
fig.colorbar(surf, ax=ax, shrink=0.5)

# Surface pour Gamma
ax = fig.add_subplot(223, projection='3d')
surf = ax.plot_surface(X, Y, Z_gamma, cmap='coolwarm')
ax.set_title('Gamma')
ax.set_xlabel('Position (S)')
ax.set_ylabel('Temps (T)')
ax.set_zlabel('Gamma')
fig.colorbar(surf, ax=ax, shrink=0.5)

# Surface pour Theta
ax = fig.add_subplot(224, projection='3d')
surf = ax.plot_surface(X, Y, Z_theta, cmap='inferno')
ax.set_title('Theta')
ax.set_xlabel('Position (S)')
ax.set_ylabel('Temps (T)')
ax.set_zlabel('Theta')
fig.colorbar(surf, ax=ax, shrink=0.5)

# Ajustement de l'espace entre les sous-graphiques
plt.tight_layout()
plt.show()