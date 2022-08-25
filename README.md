# CS433 Programming Assignments
 This repository contains the starter code for programming assignments in CS433.
 ## Get Started
 1. Clone the repository
 ```
 git clone https://github.com/csusm-cs/cs433_assign_starter.git
 ```
 2. Develop your program in a Linux system
The assignments are designed to compile and run on a Linux environement. You can use the cs433.cs.csusm.edu server or set up your own Linux environment. Contact the instructor if you need help on using Linux.

## Submission
The completed source code should be submitted to Gradescope. Gradescope will auto-grade your submission and give you immediate feedback. You can submit as many times as you want before the due date.  See each assignment instruction for more details.

## Program Design Guidelines
your programs are to be structured and implemented according to common programming guidelines, including but not limited to

- Check for validity of input data to program and functions to prevent abnormal behaviors,
e.g. program shouldn’t just crash if input values are invalid, but should exit graciously and
print clear error information.

- Programs should not be built around a specific dataset but should work correctly for any
reasonable test dataset.
- Programs that use threads should ensure that their functions are re-entrant.
- Programs should be robust, for example to avoid comparing equality of floating point
numbers.
- Function coherence: each function should correspond to one sub-task in the overall algorithm
to solve the problem.
- Function independence: each function should be independent, i.e., it should be self-contained
and it should perform its task successfully without needing to know the inner workings of
the calling function.
- Use appropriate parameters rather than global variables (stay away from global variables
whenever possible). Avoid side effects.

## Documentation and Report
Code comments and a written report will count for 20% of programming assignments.
### Code Comments
You must provide sufficient comments in your code so that others can understand what you have done. 
- Each function should have a brief comment explaining the purpose of the function, input parameters to the function, and output. The comments might also state the limitations of the function using possibly pre-conditions and post-conditions.
- Most variables should have a brief comment explaining their purpose. Looping control variables such as: “x” or “i” need not be commented.
- Comment your code to explain tricky and important points (not every line).
- Comments should be comprehensible and useful. Comments such as: “This adds 1 to Count” are trivial and should be avoided.
- Comments should be clearly organized and easily distinguishable from the actual code.
 
### Report
You should also write a report for each programming assignment and submit it in PDF format. If applicable, your report should include any results for the assignment, the features implemented or missing from the submission, and describe the design decisions and implementation choices you made for the project and lessons learned from this assignment. You should give references to the code you used from online/book resources and explain your contributions. You may also discuss extra things you have done in the project, future improvements to your program, and any comments about the project that you want to communicate to the instructor. Your reports are usually expected to be 2 to 4 pages and contain sufficient details.

## Academic Honesty
Students must follow the Campus Academic Integrity and Student Conduct Policies. The following are what is allowed and not allowed for completing the assignments. 
### Allowed:
- Talking about general strategy including general class design and general algorithms. Though it's definitely better if you try to come up with these on your own first.
- Using general C++ code you find online for common operations like:
  - General input/output
  - Using the STL classes
### NOT Allowed:
- Designing "pseudocode" together such that your pseudocode is directly translatable to C++
- Even LOOKING at code which is a solution or partial solution to your assignments
- Posting your code publicly or showing it to anyone else

