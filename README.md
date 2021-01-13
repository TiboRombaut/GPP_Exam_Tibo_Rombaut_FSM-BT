<h1>ResearchProjectGPP

<h3>Combination Finite State Machines and Behaviour Trees

preface

Hello in this project I wanted to learn the difference between Finite state machines and behaviour trees. I also wanted to see what te pros's and cons are of each Desicion making structure and also I want to make my own implementation of a combination between the 2 structures, I will also give some examples on how you can implement it.

Finite State machine(FSM)

a Finite state machine is a desicionn making strucrure and it is a mathematical model of computation that can be exactly in one of a finite number of states at any given time. The state of the FSM can change from state when the requirement is true, that is called a transition.
A state is something the machine will do if he is in it for example with an AI walk to a certain position. the machine starts with an initial state and it can transform to another state if the requirement for the transition is met.
There are 2 types of FSM's the deterministic FSM and the non-deteministic FSM. A deterministic finite-state machine can be constructed equivalent to any non-deterministic one.
Some of the best real world examples where FSM's are used, are really simple everday devices like a vending machine where it checks if the input (the coins you put in the machine) are the correct amount to get the product you want if tht is true it will give you the product otherwise it will give you a warning with the amount of money the machines still needs.
Some other devices are elevators and trafic lights.

Pro's FSM

Now I am gonna talk a bit of the pro's using FSM's one of the most important reasons FSM's get used is because it is easy to learn in comparison to other descicion making structures.
Finite state machines are also easier to code then other Desicsion making structures, because it is easy to learn FSM's it the perfect desicion making structure to teach to new programmers so they now how it works and then can go learn new ones like goal oriented programming(GOAP) and Behavior Tree(BT).
You can makw some member variables in the transition or states which could help you calculate stuff


Cons FSM

FSM's also have ofcourse a lot of downsides. FSM's are quite constricting in comparison to other desicion maing structures, what I mean by this is that it is hard to make changes to because if you change 1 state of transition you're entire decison making structure can change and cause issues that you didn't forsee.
Also a big problem with this structure is hard to read that means that it is not optimal to only use this in a company. You as the programmer who wrote it might perfectly understand what happens but if you colleagues can't read exactly what happens that might cause that you have a lot of issues in the company you work for.
Another downside of FSM is that the states and transitions are hard to use between projects because it is highly depent of the input you give, this isn't the biggest deal if you use it for 1 big project but for multiple small ones it is not optimal.
The pro's and cons make it obvious that FSM is perfect to make small AI but from the moment you start with more complex AI it can really start to become difficut to use. Of course some really smart poeple already made advances in this and made other structures for example Behaviour tree and Hierarchical finite state machines


Hierarchical Finite State Machines(HFSM)

The power of a HFSM are super states, that is in general a group of states, these super states also can have transitions which allows you to prevent redundant transitions bu applying him to the supder states the transitions are called generalized transitions, you apply these transistions once nto the super state instead of applying them individually to each state.
here is a simple example of clustering vs a super state, this is only with 3 states and it is already way more readable. The bigger you're FSM gets the more you will need this.
because HFSM uses state nesting this introduces behavior inheritance and this allows substates to mutate by adding new behavior by adding new states,transitions or reactions(also known as internal transitions) for events that are not recongized by super states. Or by overriding the existing behavior.
All this makes it possible to reuse transitions. But it is still not optimnal the problem is that reusing transitions isn't trivial to achieve and it requires a lot of thaught when you have to create logic for many different contexts.
Editing transitions manually is also kinda tedious this is where the behaviour tree comes in here you can focus on making individual states modular ro they can easyily be used in different parts of the logic.


Behaviour tree (BT)

Mathematical model of plan execution, describes switching between a finite set of tasks in a modular fasion. It originated in the game industry (halo, bioshock). It is a directed Acyclic graph.
It has four types of nodes:
Root Node: It is the root of the BT is has no parent and on child (ticks)
Composite Nodes: The Composite Node can have one or more children. This node is responsible to propgate the tick signal ot its children respecting some order. this order is also called l=flow control.
You have the Priority Node(also called Selector) this ticks it children sequantially until one of them return SUCCES, RUNNING or ERROR. If all the children return FAILURE the priority also returns FAILURE.
The Sequence Node: ticks its children sequentially until one of them returns FAILURE, RUNNING or ERROR. If all children return the success state, the sequence also returns SUCCESS.
The parallel Node Ticks all his children at the same time allowing them to work in parallel.
Decorator Node: These nodes are a special kind of node in the sense that thay only can have on child note. The goal of this node is to change the behaviour of the child  by manipulating the returning value or changing its ticking frequency. Some common manipulations are inverters and repeaters.
Leaf nodes: These nodes are the primitive building block of a behaviour tree they perform some computations and return a state value.You also have 2 different kind of nodes in there and that are the condition nodes , thse condition nodes check whether a conditon has been met or not. On the result of thos condition node we can use the second kind of node and that is a action node and these nodes perform computations to change the agents state.


Pro's BT

A BT is flexible to make a desicion making structure, it is easy to know what you are doing and is also easy to read on a small scale especially if you code you're tree readable. because a BT is easier to red this also causes that it is easier to make changes to if you want to do that with FSM you will need a lot of seperate states and transitions.
In a BT you also can run parallel tasks at the same time or multiple tasks in the same loop, Where as you want to do that with an FSM you need to create another machine. because of the independende of the nodes you can also reuse some nodes in seperate projects which is always usefull
If you want to make evrything more readable you can scale evrything down and divide one big tree in multiple smaller trees.


cons BT

One of the major problems aswell with behaviour trees is that it can get difficult fast. Another problem is that you need a certain mindset to read it. Because it is locked to the conditional nodes it does not provide the perfect model for improving the decision making of the AI.
If you want to process to make a good BT is is recommended to use Tool you can eiher download or buy. If you really want to understand on how BT works I would recommend that you make it yourself.


FSM and BT

BT and FSM both have some pros and cons but what if I told you you could combine these 2 decision making structures into 1 structure. Beforehand you will have more work because you need to make both the code for BT and FSM that they both work but in the end it will be a real upside of having thse 2 structures combined.
There are 2 ways of combining them: BT -> FSM and FSM -> BT

BT -> FSM

In this stucture BT descirbes the flow while FSM describes the function what this means is that you have a behaviour tree that is the root of you're AI and you use small scale state machines that perform small tasks.
I would recommend this structure for bigger and more difficult decision making structures.
A good example of this structure is that you have a BT with a conditional that will check whether an enemy is in is FOV if this condiontal return SUCCES you can then use a transitions to check if you have bullets if you have bullets you can shoot, else you shoudld evade.


FSM -> BT

This structure is the entire opposite of the last one in this structure FSM describes the flow while BT desribes the function. Here you use FSM as you're root and narrowing it down with small scale BT's that perform the tasks the AI need to do.
I would recommend this structure for smaller AI because you can then make an readable structure.
An example of this using the same structure as last time is that you check via an transition if an enemy is in his FOV if it is you go to the shootState in this shootstate you have an update function which will run you're shootBT. In this BT you will check wheter the AI has bullets if he as he can shoot if he hasn't he should flee of evade.
I would recommend here to make the default state an movement state because he will most of the time need to do this.


Implementing a combination of BT and FSM in my zombie survival game

Because the AI that we had to make the decision making structure wasn't that complex I chose for the combination FSM -> BT.
I made 2 main states the Shootstate and the movement state, If the AI has an enemy in it's FOV I will change states. The movementState was the state he started with.
The reason I went for this simple FSM is because first of all it can quickly become really unreadable with much FSM so that meant I wanted to do as much as possible in the BT, because I opted for a simple FSM I didn.t make seperate transitions and states for my inventory management but I opted tp put it in my movement BT because he will be nost of the times in that state and that is something pretty important. 
This meant I could make a couple of simple BT and a couple of small states and transitions. As mentioned above I update my BT's in an update funtion of my FSM's states.
So this means that every frame th BT will update accoring to what state the FSM is in. 
Because I first programmed my AI before I did the research project I didn't use any decorator stuff which could have been really usefull for inventory management, I also never used the RUNNING state from BT.


Conclusion

Via This research project I learned a lot of the differnce between BT and FSM. In the case of FSM I learned a lot pf different FSM structures and on what devices they get used in real life.
I also found it really interesting to read what poeple said on forums and articles about these decision making structures, I noticed that most went for BT because of it readibility but they also said that you need chose on what structure to use.
On the BT front I also learned a lot of how things work in comparison with in the beginning of the vacation. I learned how excatly the BT worked with how everything was build and I also found it difference between the nodes interesting. 
When I have time I will definitly go more in depth with BT because it is a really powerfull structure.
With al the knowledge I gathered during this project I am definitly sure that by using this hybrid it is easier to make an good working and readable AI.
In the future I also would be interested to learn on how to make the BT -> FSM part of this project because in my knowledge this is also a powerfull structure but would be better to use on more elaborate AI and not simple ones.
Making decision making structures using provided engine like UE or unity seems interesting to me because we haven't actually gone in depth with that but I have seen that there is a presence of BT and FSM in UE templating.



