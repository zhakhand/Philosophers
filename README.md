Project revolving around solving Dining Philosophers Problem using threads or semaphores.
Rules are:
1. There are N philosophers at the table.
2. Each philosopher bring a fork
3. In order to eat each philosopher has to have fork in each hand
4. Philosopher can only take his and his right hand neighbours fork
5. Philosophers have time to eat, sleep and die
6. If philosophers don't eat or sleep, they think
7. Philosophers have to wait for forks to be free in order to eat
8. If philosopher doesn't eat for "time to die" amount of time, the program stops
9. If each philosopher eats minimal required meals (OPTIONAL), program stops.
10. Philosophers should avoid death.

Tried Solutions:
1. Make odd numbered philosophers wait for a "time to eat" amount of time.
2. Each philosopher starts to pick the fork in front of them, except for the last one, who picks it from his right hand neighbour.
3. My final method: assign different way of picking up the forks for even and odd philosophers, i.e. Philosopher No2(Even) picks the fork in front of him first,
   while his left(Odd) neighbour tries to pick his fork (which is already locked), and then picks the fork of his right hand neighbour
   (who tries to pick the fork from him(if Even) or right hand neighbour(if Odd) and also fails). The way of letting go of the forks can also vary, but it doesn't affect the synchronization that much.

Monitoring:
1. Possible to implement a thread that can act as an Observer that constantly checks if one of the Philosophers died or they all ate minimal amount of meals.
2. Instead of thread also possible to create a function which will do the same.
3. Adding one of the functions to monitor death or goal (Meals) also helps to visualize timings better. Although in visualizer last actions could be possibly ignored.

In order to survive Philosophers need:
1. Time to die == Time to Eat + Time to sleep + 10 (If even)
2. Time to die == (Time to Eat * 4) + 10 (If odd)

Solving data races:
Create a mutex for each important part of the information: output, incrementing meals eaten, state of the Philosopher and state of the Program.
