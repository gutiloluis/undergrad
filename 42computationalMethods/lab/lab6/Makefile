all: plot.png

plot.png: plots.py
	python plots.py

plots.py: pendulum_data.dat

pendulum_data.dat: pendulum.py
	python pendulum.py 4.0 0.0
