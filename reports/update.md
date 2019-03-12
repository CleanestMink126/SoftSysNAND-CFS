
# Linux Completely Fair Scheduler
Danny Kang, Nick Sherman, Nick Steelman
Software Systems

## Goal
The goal of our project is to make a simplified version of the Linux Scheduler and then visualize it by creating from scratch a Red Black Tree and then creating a simulation environment behind it. After the prototype of the project is made, we then want to visualize it entirely in C. Stretch goals include updating the tree after each node switch and then animating the nodes as their positions are switched.

## Learning Goals
Through working on this project, we as a collective have a few main goals, with individual goals varying. These goals are:
- **Understand the C language better.**
 - We understand that we haven’t had an incredibly large amount of time to learn the C language, especially as most of our first in-depth exposure has come from Software Systems. Therefore, this project gives us an opportunity to better understand the language outside of the perspective of problem sets.
- **Practice C programming**
 - Similar to understanding the C language better, we want to practice C programming and the different conventions that differ from other languages we know, especially Java and Python. Through making a nontrivial project from scratch, we are hoping to solidify more of the C standards of programming and to become more accustomed to coding in C.
- **Understand better how schedulers work**
 - Something the three of us were curious about was how scheduling works in operating systems, as we know that processes all get different amounts of time to process data and that not all processes actually run simultaneously on the hardware. Therefore, we have begun understanding how schedulers actually work in order to implement one.
- **Understanding how red/black tree algorithm optimizes work done by the CPU**
 - In understanding schedulers, we learned that the C language implements its scheduler through a red-black tree. Therefore, we need to understand what a red/black tree is. Nick Steelman already was very well acquainted with the topic as a Data Structures and Algorithms instructor who had given the lecture on red/black trees, and he used his knowledge to help the other two understand red/black trees.
- **Practice Visualization and learn Visualization in C**
 - The final (stretch) goal of the project was to practice visualization of software and to learn how to visualize in C. Visualization is done of the completed Red/Black tree, and is completed using GTK and the cairo library. As none of us have experience in visualization in C, we performed a lot of research figuring out how to accomplish what we wanted and are in the process of combining our visualization knowledge with the red/black tree data structure we created.

## Progress
For initial steps, we divided our project conceptually into 3 parts: Red Black Trees, Workload Simulation, and Visualization. After defining some basic functionality and how they would run together, we each took a part and fleshed it out individually.
#### Red Black Tree: Nick  
Our rbtree.c now successfully can insert into a RB tree and delete the minimum from a RB tree. It also keeps a pointer to the minimum so that it can easily peek min and delete min in potentially O(1) time.
#### Workload simulation: Danny
Currently, our task.c and main.c code generates tasks in forms of struct that have associated values such as vruntime and run_state. Once created, these tasks populate the list that holds pointers to all struct instances. It is possible to keep track of and manage each tasks since they possess unique IDs in form of numbers. We were able to implement exponential arrival time of tasks and normal distribution of runtime of each tasks in at least basic form by utilizing rand() and a function that generates random normally distributed function.
#### Visualization: Nick
Our visualization process was a slower start due to all the documentation around it and the exploration into the best way to visualize something in C. After determining GTK3 was the best visualization method, we worked on visualizing nodes that could be placed reasonably to appear to be a red-black tree. Currently, singular nodes are able to be visualized with current work being done in combining the scheduler code with the visualization code so that an entire tree can be visualized at once.
#### Combination
After we had our individual pieces working we created header files, a makefile, and main.c and integrated the RB trees with Workload Simulation to achieve our MVP.
## Resources
Since our project is easily divided into 3 parts, our resources are divided into the same categories:
#### Red Black Trees:
[Example Code Base](https://gist.github.com/VictorGarritano/5f894be162d39e9bdd5c)  
[Deleting from a Rb Tree](https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/)  
[Experience as a DSA instructor](https://drive.google.com/open?id=1cR7LyDS0_BXIbnGHiTGZgxVEhrpR0cx722zy0EHlq2Q)

#### Task Management:
[Guideline to understanding how Linux CFS scheduler works]( https://notes.shichao.io/lkd/ch4/?fbclid=IwAR0h79u-eT3Ghe0TtarSvO1n4iC8OiBi0pY3uxZrgP-FQfZC2ZwdgFu1IxY)  
[Wikipedia page to exponential distribution analysis](https://en.wikipedia.org/wiki/Exponential_distribution)  
[Stackoverflow reference for generating random lognormal distributed numbers](https://stackoverflow.com/questions/9766147/generate-a-random-number-from-log-normal-distribution-in-c-c)  
[Brief documentation about core features of CFS](https://www.kernel.org/doc/Documentation/scheduler/sched-design-CFS.txt)  

#### Visualization:
[Example of Displaying Text in Cairo](http://zetcode.com/gfx/cairo/cairotext/)
[The Cairo Graphics Documentation](https://www.cairographics.org/)
[The Gnome GTK Functions’ Documentation](https://developer.gnome.org/gtk3/stable/gtk3-General.html#gtk-main)
[The Gnome’s Developer guide to GTK3’s Stable Release](https://developer.gnome.org/gtk3/stable/)  

## Future Steps
With our MVP of making a scheduler that can assign and simulate tasks, our next step is to build this functionality out into something that is interesting and interpretable. This means:
- Integrating visualization so we can see the workings of a RB Tree (Nick Sherman). This is done when we can full visualize the schedule in action through changes to the RB Tree
- Implementing different priorities of tasks and seeing the effect on the scheduler (Danny Kang/Nick Steelman). This is done when different tasks are assigned different vtime based on their priority, ideally mirroring the system of the CFS
- Adding different colorings and properties to the visualizations (Nick Steelman). This is successful if we can examine the tree over time for properties such as average interrupts time, priority, or overall runtime.
- Varying the distributions or implementations of interrupts for processes (Nick Steelman). Done if the average interrupt time for processes is not all the same
