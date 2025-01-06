import matplotlib.pyplot as plt

# Data
num_thread = [1,2, 4, 8, 16,32]  # X-axis: Number of pages
access_time = []  # Y-axis: Time per access (ns)

# Plot
plt.figure(figsize=(8, 6))
plt.plot(num_thread, access_time, marker='o', color='orange', linestyle='-', linewidth=2, markersize=8)

# Labels and Title
plt.title("Number of thread Vs Computation Time", fontsize=16)
plt.xlabel("Number of Threads", fontsize=14)
plt.ylabel("Computation Time", fontsize=14)
plt.xscale('log')  # Log scale for the x-axis to show growth
plt.grid(True, which="both", linestyle="--", linewidth=0.5, alpha=0.7)

# Save Plot as Image
plt.savefig("time_plote.png", dpi=300)  # Save as PNG with high resolution

# Show Plot
plt.show()
