# AI Test Task: Coordinated AI Behavior

![Screenshot](https://github.com/RicardoEPRodrigues/AITestTask/raw/refs/heads/main/Media/Screenshot01.png)

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

## Implementation Details

To implement these tasks some relevant classes were created. Most of the behavior was implemented in Blueprints under `Content/AiTestTask/AI` or `Content/AiTestTask/Blueprints`. I set up base AI characters, a simple AI Controller to run the behavior trees, and a map for the example to run on. Here are the most important classes:

1. **AITestTaskCharacter** (C++): The main character class with modifications to allow for Big and Small Attacks. (I choose to extend this class' features to allow for any character to be used in the AI system.)
2. **BT_EnemyBig** and **BT_EnemySmall** (Blueprint): Behavior Trees for the Big and Small NPCs and respective behaviors. Given their similar idle behavior they used the same idle behavior tree, but used different behavior trees for the attacks (although very similar). Here we also use simple EQS queries to find the idle and attack areas. (Here we can find the implementation of Task 1 and 4.)
3. **EnemyCoordinator** (C++): An attack/idle coordinator. It determines which NPC should be attacking, making all others idle (it is scalable for multiple NPCs, although we only use 2 for now). It also deals with the dynamic difficulty adjustment and the decreasing delay. (Here we can find the implementation of Task 2 and 3. Here I was conflict between having an AI - with a behavior tree - controlling the NPCs but decided on a more traditional approach.)