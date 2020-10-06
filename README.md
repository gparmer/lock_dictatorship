# Welcome to the Glorious Lock-topia

> Narrator: The lock-free revolution was over-sold.  When the
> node-citizenry had to actually write lock-free algorithms, race
> conditions tore across society, and the ABA problem was the nail in
> the coffin of the lock-free hopes and dreams. The path to order
> started with counter(-based) revolution of the ticket locks, but
> quickly became increasingly authoritarian. Complete order was
> imposed when the `pthread_mutex` forced their way into the position
> of the strong-man dictator.

Welcome to Lock-topia!
We've made your data-structure kin great again by chasing out all of the [lock-free](https://github.com/gparmer/down-with-locks) terrorists.
Ne'er again with the personal space of critical sections ever be [so violated](https://www.youtube.com/watch?v=IMyqasy2Lco&list=TLPQMDMxMDIwMjC3WcVEPCRSag&index=2).
The lock counter-revolution was swift and strong.
But we must be ever-vigilant in protecting our freedoms through *lock-and-order*.
Now the `pthread`-dictatorship mandates the greatest of locks in **all** walks of our data-structure life!
Welcome to the glorious land of mutual exclusion!

We bring you the patriotic freedom of our *freedom linked list*!
Two activities are kindly provided in our gracious dictator:

- The `freedom_police` monitor our node-citizens, add those that are worthy patriots to or glorious data-structure, and increase all node-citizen's freedom (oh, and sometimes, they have to send node-citizens expressing insufficient patriotism to re-education).
	There is only *one* `freedom_police`.
- The `worker_patriot`s that ensure the founding-`fork`er's plan is carried out by dutifully providing the [hard work](https://www.youtube.com/watch?v=RP4cD35Xn5E) that is the O(N) backbone of Lock-topia.
	There are *two* `worker_patriot`s.

Both the police and the patriots walk through the freedom nodes doing work, then take 10 microseconds of personal time, repeating this till the police have done a full rotation, and the system exits.
The police modify the freedom nodes, by adding moar freedom, so they print out `w` (or write) as they work.
The patriots observe the masses of freedom by reading through the freedom nodes, thus print `r` (or read) as they work.

## Observe the glory!

Note that you should run this on a machine with at least 3 cores.

```
$ make
$ time ./bin
```

Observe the beautiful blocks of contiguous readers (`r`) and writers (`w`)!
We invited `time` to observe the parade to our magnificence as it carefully watches and tells us how long the procession is.

By default, the dictator has their absolute order, and `LOCK_COARSE` is used.
This ensures that locks are used in a *coarse-grained manner* to protect the entire iteration through the list.

You should see long stretches of `w` and `r`, with about twice as many `r` as `w`.
They do have some chaos, some interleaving, but they are largely nice and orderly.
This is *lock-and-order* so the dictator is happy.

- **Question 1:**
	Why are they interleaving?
	Why are they not interleaving on a per-`w` and per-`r` basis (instead as blocks of letters)?
- **Question 2:**
	Would you expect this to be a "fast" implementation?
	Is it using all cores well?

> Pssst! The deep state persists, inspired by the Francis Scott
> **Key** society, and is working against the complete
> sequentialization of the `pthread`-dictatorship. We have a plan.
> Data-structures *cannot* go back to a lock-free anarchy without
> critical sections, but the execution sequentialization has gone too
> far. The dictator must loosen control on lock-topia!!!

## The Deep State: Phase I

The counter (counter) revolution will be messy, but necessary.
As the dictator struggles for their hard-fought organization, the deep state pushes for mess concessions.
Comment out `LOCK_COARSE`, and uncomment `DEEPSTATE_LOCK_PHASEI_SEQUENTIAL_TAKES` (don't run it yet).
This has the effect of making each traversal of the freedom lists use *fine-grained locking*.
Each node is locked individually and separately, rather than taking a single lock for the entire list.
**Before** you run the program again,

- **Question 3:**
	What do you expect the program will output when you run it this time?
	Why?
	How fast do you expect the program to run relative to your previous execution (with coarse-grained locks)?
- **Question 4:**
	Run the program.
	Does it output what you'd expect?
- **Question 5:**
	Did its execution time fit what you were expecting?
	Why or why not?

> We've limited the dictator's power to impose absolute order, which
> means that the citizens of lock-topia are again able to feel the
> power of our core-based power.
>
> But, caused by the haste of progress, we've found a problem.

```
$ valgrind ./bin
```

Run it a few times until (mixed between the `r`s and `w`s), you should see an error starting with this:

```
==23734== Thread 4:
==23734== Invalid read of size 4
==23734==    at 0x4E4602A: pthread_mutex_lock (pthread_mutex_lock.c:79)
==23734==    by 0x108B95: read_lock (main.c:40)
==23734==    by 0x108EDB: worker_patriot (main.c:246)
==23734==    by 0x4E436DA: start_thread (pthread_create.c:463)
==23734==    by 0x517CA3E: clone (clone.S:95)
...
```

Our solution is, quite sadly, *wrong*.

- **Question 6:**
	It looks like we're accessing memory that has been freed.
	Why is this happening?
	Spend 5 minutes looking through the `#ifdef DEEPSTATE_LOCK_PHASEI_SEQUENTIAL_TAKES` blocks to try and figure out.

> We've made so much progress! We cannot lose ground to the dictator
> simply because our code is completely wrong!!! Lets go
> *hand-in-hand* and seek out a solution.

## The Deep State: Phase II

Comment out `DEEPSTATE_LOCK_PHASEI_SEQUENTIAL_TAKES`, and uncomment `DEEPSTATE_LOCK_PHASEII_HAND_OVER_HAND` (don't run it yet).
This modifies the system to use hand-over-hand locking.

- **Question 7:**
	Before you run the code, what would you expect it to output?
	How fast (relative to the previous settings) would you expect it to be?
- **Question 8:**
	Run the code.
	Was the output as expected?
	Was the execution time as expected?
	Why?
- **Question 9:**
	Run it with `valgrind` to confirm we fixed the problem.
	Why did it fix the problem?

# Lock-topia's Economy Must Specialize

The citizens are still not living in the riches we promised!
We must take extreme measures to fix the lock-luster economy.
We don't know what will work, but we do know that the police, and the workers should be allowed to use the freedom list in the their own way.
The way to boost your economy is to specialize!

*You're hired* to be lock-topia's deep state chief lock-onomist.
Lock-heed Martin has made a huge amount of contributions to put you in place.
Don't worry, the masses aren't that angry, and *we offered them cake*, so all is well.
You're in no way hired as a fall-person!

Your job is to allow the police and the workers to specialize using read-write locks.
The `DEEPSTATE_LOCK_2NDFRONT_RW` define allows you to enable the *second front* assault on the dictator.

- **Question 10:**
	Formulate a set of hypothesis about the following question: What combinations of choosing one of the three lock granularities, mixed with what values of `WORKER_WORK` (correlated with the amount of work done by a reader), and `WRITER_WORK` (correlated with the amount of work done by a writer) will make have the largest benefits for read-write locks?
- **Question 11:**
	Run the system with each of the setting you chose.
	Does the system respond in the manner you expected?
	What ends up being the setup that most speeds up with read-write locks?
	Why?

**An important aside about when the program terminates.**
The program terminates when the writer (the police) has done a specific amount of work.
Thus, optimizing the readers alone, might not actually make the program faster.
The print out at the program's termination tells you how much *reader work* is done over some unit of time.
If you're making more reader work happen over the same amount of time, you've increased efficiency!
So use *both* the execution time, and the work per unit of time as indicators of success.
