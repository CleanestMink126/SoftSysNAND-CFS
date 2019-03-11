## Linux Completely Fair Scheduler
Danny Kang, Nick Sherman, Nick Steelman

## Goal
We want to implement the completely fair scheduler (CFS) of the current linux kernel. This is implemented via a Red Black tree that keeps track of runtimes of the current applications. We aim to visualize the cpu allocation of processes done by CFS through varying the priorities and IO utilization of tasks, but expect to at minimum have implemented a working Red Black tree that is compatible with scheduling requirements.

## Learning Goals
We will learn using C library to implement our code. More specifically, we will use modules related to scheduler and red black tree algorithm. Learning goal would vary depending on teammates, but they would include (not in order): Understanding the C language better Practicing C programming Understanding better how schedulers works in linux Understanding how red black tree algorithm optimizes work done by CPU Practicing visualization technique

## Resources
What we will use:

Resources for implementing Red Black Tree
Resources for understanding scheduler
Resources for showing good visualizations
All of which will be freely available online.

## Initial Steps
Define a code structure so we can effectively split up tasks. This is considered “done” if we have a sufficient breakdown of the code structure that we can begin programming it. Assigned to everyone in the group.
Ensure that all members have a complete understanding of red-black trees. This is considered “done” if every member can explain the red-black tree well enough that they could teach a current DSA student what it is. Assigned to everyone in the group.
Program a sample red-black tree. This is considered “done” if we have code that produces a red-black tree. Assigned to Nick Steelman.
Determine the best way to simulate processes running. This will be considered “done” if we have determined multiple different ways of simulating processes running but have settled on the one that we will be using for the duration of the project. Assigned to Danny Kang.
Determine the best way to visualize the RB trees. This is considered done when we have come up with reasonably recognizable graphics so that the viewer can instantly understand. Assigned to Nick Sherman
