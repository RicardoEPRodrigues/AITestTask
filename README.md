# AI Test Task: Coordinated AI Behavior

This project showcases two NPCs working together in a basic combat scenario, utilizing modular AI techniques and dynamic difficulty adjustment.

This was a task proposed to me in a challenge to test my AI implementation capabilities.

## Task Details

1. Individual NPC behavior:
   1. Both NPC should have their own Behavior Tree controlling Attack and Movement.
   2. Other NPC is doing “small attack” and other one is doing “big attack”
   3. Small attack can be done from range of 200 (2m) and big attack from range of 500 (5m)
2. Coordination between NPC’s:
   1. Only one NPC should be doing an attack at a time, while the other is idle.
3. Dynamic Difficulty Adjustment:
   1. After every attack there must be delay (default 5s).
   2. Delay must decrease by 0,2s after every attack
4. NavMesh Utilization:
   1. NPC should navigate towards the blue sphere while it is attacking.
   2. NPC should navigate towards the red sphere while it is idle.

There is no need for animations, VFX or SFX. Attacking can be only shown with debug text in the screen/console. Use modular, well-structured Behavior Trees with clear tasks.

## Train of Thought

1. Create a simple scene displaying the NPCs and red and blue spheres.
2. Create two NPCs with their own Behavior Trees. There might be up to 5 different behavior trees. 1 dedicated to each NPC, 1 for movement, and 1 for each attack type.
3. Create a manager to control the NPCs. This might just be an actor in the scene or another NPC with a dedicated behavior tree. I will try the former rather than the latter.
