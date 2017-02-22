import subprocess
import matplotlib.pyplot as plt
import numpy as np
from timeit import default_timer as timer

ALGMAX = 2

def systemCall(h, w, seed, a):
	command = "./maze.o -s "+str(seed)+"-h "+str(h)+"-w"+str(w)+"-a"+str(a)
	p = subprocess.Popen([command], stdout=subprocess.PIPE, shell=True)
	return p.stdout.read()

def mapOverhead(h, w, seed):
	command = "./maze.o -s "+str(seed)+"-h "+str(h)+"-w"+str(w)+"-a 0"
	p = subprocess.Popen([command], stdout=subprocess.PIPE, shell=True)
	return p.stdout.read()

def main():
	avgTimes = []
	stdErr = []
	dims = range(5,40,10)
	labels = ["Depth First"]
	for dim in dims:
		for seed in range(0,11*10,11):
			times = []
			for algorithm in range(1, len(labels)+1):
				start = timer()
				systemCall(dim,dim,seed,algorithm)
				end = timer()
				times.append(end - start)
		avgTimes.append(np.mean(times))
		stdErr.append(np.std(times))
	for i in range(len(labels)):
		plt.errorbar(dims,avgTimes,yerr=stdErr,label=labels[i], linestyle="none")
	plt.show()

'''

overhead = []
for i in range(10):
	start = timer()
	mapOverhead(dim,dim,seed)
	end = timer()
	overhead.append(end - start)
overheadMean = np.mean(overhead)
'''

main()