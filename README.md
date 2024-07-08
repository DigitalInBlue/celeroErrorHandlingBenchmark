# celeroErrorHandlingBenchmark
A Microbenchmark of various C++ error handling techniques.

## Example Results
This is the output from the program.  The output will change depending on your specific hardware, compiler, and compiler settings.

|     Group      |   Experiment    |   Prob. Space   |     Samples     |   Iterations    |    Baseline     |  us/Iteration   | Iterations/sec  |   RAM (bytes)   |
|:--------------:|:---------------:|:---------------:|:---------------:|:---------------:|:---------------:|:---------------:|:---------------:|:---------------:|
|ErrorHandling   | Baseline        |            Null |             100 |        10000000 |         1.00000 |         0.00335 |    298489642.41 |          671744 |
|ErrorHandling   | Expected        |            Null |              50 |        10000000 |         2.16856 |         0.00727 |    137644354.52 |          671744 |
|ErrorHandling   | ErrorCode       |            Null |              50 |        10000000 |         1.00376 |         0.00336 |    297371238.25 |          671744 |
|ErrorHandling   | Optional        |            Null |              50 |        10000000 |         1.77458 |         0.00595 |    168202920.00 |          671744 |
|ErrorHandling   | Variant         |            Null |              50 |        10000000 |         2.81980 |         0.00945 |    105854830.69 |          671744 |
|ErrorHandling   | ErrorCallback   |            Null |              50 |        10000000 |         1.31419 |         0.00440 |    227128191.15 |          671744 |
|ErrorHandling   | Exception       |            Null |              10 |            5000 |     49539.43048 |       165.96700 |         6025.29 |          679936 |

In general, this shows that `std::exception` is by far (4 orders of magnitude) the slowest way to handle errors in C++23.
