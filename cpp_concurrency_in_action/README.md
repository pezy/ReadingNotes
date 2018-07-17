# Notes

## About the `std::thread` object.

Once you've started your thread, you need to explicitly decide whether to
wait for it to finish (by **join**ing with it) or leave it to run on its own
(by **detach**ing it). If you don't decide before the `std::thread` object is
destoryed, then your program is terminated.

> the `std::thread` destructor calls `std::terminate()`.

Calling `detach()` on a `std::thread` object leaves the thread to run in the
backgroud, with no direct means of communicating with it.

Detached threads are often called `daemon threads` after the UNIX concept of
a daemon process that runs in the backgroud without any explicit user interface.

you detach a thread by calling the `detach()`, after the call completes, the
`std::thread` object is no longer associated with the actual thread of execution
and is therefore no longer joinable.

Rather than just passing the name of the function, you can also pass in the 
parameter.

## About the `thread_guard` class

The destructor of `thread_guard` first tests to see if the `std::thread` object 
is `joinable()` before calling `join()`. This is important, because `join()` 
can be called only once for a given thread of execution, so it would therefore 
be a mistake to do so if the thread had already been joined.

## Passing arguments to a thread function

By default, the arguments are **copied** into internal storage, where they can 
be accessed by the newly created thread of execution, even if the corresponding 
parameter in the function is expecting a reference.

Thus, consider using `std::ref` and `std::move`.

The instances of `std::thread` are **movable**, even though they aren't 
copyable. 

## Structuring code for protecting shared data

> Don't pass pointers and references to protected data outside the scope of 
the lock, whether by returning them from a function, storing them in externally 
visible memory, or passing them as arguments to user-supplied functions.