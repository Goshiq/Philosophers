# Philosophers

### The project is about threads and processes
We are using threads (philo_one and philo_two parts) and processes(philo_three) int this project

#### Usage:
```C
make
```
cd into one of the dirs and start the program with arguments:
```C
0 - nymber of philosophers
1 - time to die without eating
2 - time to eat
3 - time to sleep
4 - optional, number of meals
```

example:
```C
make
cd ./philo_three && ./philo_three 200 1000 100 100 5 cd ..
```
