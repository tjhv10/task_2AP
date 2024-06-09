.PHONY: all
all: generator primeCounter newPrimeCounter

generator:  generator.c
	gcc -o randomGenerator generator.c

primeCounter:	primeCounter.c
	gcc -o primeCounter primeCounter.c

newPrimeCounter:  newPrimeCounter.c
	gcc -o newPrimeCounter newPrimeCounter.c

.PHONY: clean
clean:
	-rm randomGenerator primeCounter newPrimeCounter 2>/dev/null
