# CS 4050 High Performance Computing

The objective of this project is to set up the environment that you will use to practicethe performance optimization techniques learned in the class, through the following steps.
1. Select the computation of your choice to try speed up. You can select any code in acompiled language such as C, C++, or Java. You can select this target computation from within the collection of benchmarks we studied in class; alternatively, you canselect code from any other sources (e.g., Github) you may find. The code you selectmust contain some significant computation and must have a clearly defined function-ality. In particular, its computation time must be at least proportional to the size ofthe input (i.e., it’s execution time cannot be bounded by a constant). If uncertain,consult the instructor for more information.

2. Set up the selected code to be tested for correctness and evaluated for efficiency. In particular, create a working directory with the following components.
    -The source file that contains the computation that you try to speed up, wrapped inside a function definition.
    
    -The source file that contains optimized code of your target computation. For this project, make it the same as the original target computation.
    
    -A tester file, which includes a main function that reads some input, invokes theoptimzied code, checks the result of computation for correctness (specifically, youcan check whether the optimized code produces the same result as the originalcode).
    
    -A timer file, which includes a main function that reads some input, invokes the optimized code, and then report the time spent in performing the computation.
    
    -A makefile with rules to build an binary executable from the sources and toevaluate the binary executables.

3. Estimate the number of floating point or integer operations performed by the target computation and the size of data accessed by it. Then, measure its performance in terms of FLOPS/IOPS by dividing the overall number of FLOP or IOP numbers over the executation time of the computation.  Try collect the performance for at least three different input data, one small size, one medium size, and one large size. How does the performance differ when using different size of data? What does it imply?

4. Construct the roofline model of the machine platform that you use to evaluate thetarget computation. Then plot the performance of your target computation over the roofline model.  What does the roofline model tell you?  What is the performance bottleneck of the computation? Please submit your project report through Blackboard and be ready to present/demo your results in class.

## Resources:
[1] S. Mortimer, “Fast Bitmap Rotation and Scaling,” Dr. Dobbs World of Software Development, Jul. 01, 2001. https://www.drdobbs.com/architecture-and-design/fast-bitmap-rotation-and-scaling/184416337 (accessed Sep. 01, 2021).