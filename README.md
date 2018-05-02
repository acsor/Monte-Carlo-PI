# Monte Carlo PI

`Monte Carlo PI` explores and implements a randomized solution to the
calculation of the mathematical constant π. It uses
the Pthreads library and the [GNU Multiple Precision Arithmetic Library
(GMP)](https://gmplib.org/) for dealing with as precise as possible
floating-point numbers.

## Prerequisites
1. UNIX-like operating system supporting the Pthreads library
1. A system-wide installation of GMP
1. GNU Make

## Running instructions
Supposing all the prerequisites are set up, in order to run `Monte Carlo PI`
simply have
```
make run
```

To run the test suite, invoke instead
```
make testrun
```

## Credits
`Monte Carlo PI` was inspired by the book [Operating System
Concepts](http://codex.cs.yale.edu/avi/os-book/OS9/), 9th
edition by A. Silberschatz et al., pages 193-194.

### Problem statement
An interesting way of calculating π is to use a technique known as ***Monte
Carlo***, which involves randomization. This technique works as follows:  
Suppose you have a circle inscribed within a square, as shown in Figure 4.18.
(Assume that the radius of this circle is 1.) First, generate a series of
random points as simple *(x, y)* coordinates. These points must fall within the
Cartesian coordinates that bound the square. Of the total number of random
points that are generated, some will occur within the circle.
Next, estimate π by performing the following calculation:
```
π = 4 X (number of points in circle) / (total number of points)
```
Write a multithreaded version of this algorithm that creates a separate thread
to generate a number of random points. The thread will count the number of
points that occur within the circle and store that result in a global variable.  
When this thread has exited, the parent thread will calculate and output the
estimated value of π. It is worth experimenting with the number of random
points generated. As a general rule, the greater the number of points, the
closer the approximation to π.
In the source-code download for this text, we provide a sample program that
provides a technique for generating random numbers, as well as determining if
the random *(x, y)* point occurs within the circle.
Readers interested in the details of the Monte Carlo method for estimating π
should consult the bibliography at the end of this chapter. In Chapter 6, we
modify this exercise using relevant material from that chapter.
