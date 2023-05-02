# Safety
In order to make the language easy to use you should not have to worry about concurrency or dangling pointers.

## Concurrency
Concurrency is handled implicitly by the job scheduling.
All actions that occur by the user are done in a job that reads and writes specific resources.
A job will read all resources specified by its parameters and write to all resources specified by the return type.
Consider the following example:
```
#Update
function firstJob(c1: Component1) -> Component2 {
  // This job reads from Component1 and writes to Component2
}

#Update
function secondJob(c1: Component1) -> Component3 {
  // This job reads from Component1 and writes to Component3
}

#Update
function thirdJob(c2: Component2) -> Component4 {
  // This job reads from Component2 and writes to Component4
}
```
The scheduler will carefully inspect all jobs and to which resources they read from / write to.
Multiple jobs can read from the same resource simultaneously, so it will happily run `firstJob` and `secondJob` simultaneously as they read the same resources and write two different ones.
However, `thirdJob` reads from `Component2` which `firstJob` writes to, thus, the scheduler will wait for `firstJob` to finish before running `thirdJob`.
This way, the user does not have to think about synchronizing access to the individual resources and as the scheduler will make sure there are no race conditions.
However, the user should still have the scheduling concepts in mind when writing jobs, as they might create unwanted bottlenecks.
In general, it is preferable to have multiple jobs with fewer resource dependencies than one large job.

**Furthermore, there are no global variables** because accessing them inside a job would also create a race condition, in addition to the fact that it would contradict the definiton of jobs (or systems in proper ECS terms) to have no state of its own.

## Memory management
Memory management is very simple: from the point of view of the user, there is only the stack and no references to to objects outside of function parameters.
This makes it impossible to access an object that has already been deleted.
E.g., in contrast to other programming languages the following code copies the list instead of having two values that reference the same list:
```
let some_list = [0, 1, 2, 3]
let other_list = some_list
```

### Long-Term Object Storage
Not having a user-accessible heap and no global variables in general, would usually make it impossible to have objects live longer than a function call.
However, as the whole language is built around the concept of ECS, the idea is to store **all** the state in scene/entity/viewport components.
So, if you want to have something available for multiple frames, write it to a component and you can happily read from it the following frame(s).
