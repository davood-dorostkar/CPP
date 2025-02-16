# Concurrency vs Parallelism

## Intro

Concurrency is the ability to perform multiple tasks at once, though the order of execution may vary due to shared resources. Parallelism, on the other hand, means executing multiple tasks truly simultaneously without waiting on shared resources.

## Key Points:
1. **Definition of Concurrency**  
   - The occurrence of two or more events at the same time.  
   - Computers can multitask efficiently, unlike humans.

2. **Why Concurrency Matters**  
   - Traditionally, software runs sequentially, executing one instruction at a time.  
   - Concurrency allows multiple parts of a program to execute simultaneously, improving performance.

3. **Concurrency vs. Parallelism**  
   - **Concurrency:** Tasks can run simultaneously but may need to wait on shared resources.  
   - **Parallelism:** Tasks run truly simultaneously without waiting.  
   - Illustrated using an analogy of a **coffee shop**:  
     - **Parallelism:** Two separate coffee machines serve two customers simultaneously.  
     - **Concurrency:** Two customers line up, but only one can use the coffee machine at a time.

4. **Real-World Examples of Concurrency**  
   - **Orchestra:** Musicians play in sync, sometimes taking turns.  
   - **Dinner conversation:** People take turns speaking while also eating and using their phones.  
   - **Computer applications:** Memory allocation, file systems, and network requests all require concurrency.

5. **Hardware Support for Concurrency**  
   - Modern **multi-core CPUs** enable concurrency by executing different tasks on separate cores.  
   - Moore’s Law (more transistors over time) has led to multi-core processors instead of faster single cores.  
   - **Dennard Scaling**: As transistors shrink, power consumption increases exponentially, creating heat issues.

6. **Concurrency in Modern Computing**  
   - Today’s devices (PCs, gaming consoles, phones) have **multi-core processors** to support concurrency.  
   - **Supercomputers have long used concurrency**, but now everyday programmers must learn it.