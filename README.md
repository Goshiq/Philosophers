# Philosophers

### The project is about threads and processes
We are using threads (philo_one and philo_two parts) and processes(philo_three) in this project

#### Usage:
Clone the project:
```C
git clone https://github.com/Goshiq/Philosophers.git && cd Philosophers
```
```C
make
```
cd into one of the dirs and start the program with arguments:
```C
0 - nymber of philosophers
1 - time to die without eating in ms
2 - time to eat in ms
3 - time to sleep in ms
4 - optional, number of meals
```

example:
```C
cd ./philo_three && ./philo_three 200 1000 100 100 5 && cd ..
```
