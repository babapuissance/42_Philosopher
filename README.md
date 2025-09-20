# 42 - Philosophers 💭🍴

## Description

This project is a simulation of the famous **Dining Philosophers Problem**.  
It introduces **multithreading** and **mutex synchronization**, two key concepts for concurrent programming.  

Philosophers alternate between:
- **Eating** (each needs two forks = two mutexes),
- **Sleeping** (resting after eating),
- **Thinking** (waiting for the next meal).

A **monitor thread** checks in real time:
- If a philosopher has not eaten in `time_to_die` ms → he dies and the simulation ends,
- Or if all philosophers ate `must_eat_count` times → simulation stops successfully.

---

## Features

- ✅ One **thread per philosopher**  
- ✅ One **mutex per fork**  
- ✅ A **print mutex** to avoid garbled output  
- ✅ Monitor thread to check end conditions  

---

## Usage

```bash
# Compile
make

# Run with 5 philosophers, time_to_die=800ms, time_to_eat=200ms, time_to_sleep=200ms
./philo 5 800 200 200

# Run with optional must_eat_count (ex: each philosopher must eat 7 times)
./philo 5 800 200 200 7

### Example output
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
200 2 has taken a fork
…

---

## Project Structure
- `main.c` → program entry, setup + cleanup
- `parsing.c` → parse and validate arguments
- `init_*.c` → initialization (forks, philosophers, mutexes)
- `philosopher.c` → actions (eat, sleep, think)
- `routine_philo.c` → routine executed by each philosopher thread
- `monitor.c` → monitor thread (detects death or end condition)
- `utils.c` → helpers (time, sleep, status printing)

---

## Disclaimer

This project was developed for **42 School**.  
It follows the [Norm](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf).