# Dining Philosophers 💭🍴 (42 Project)

![Stars](https://img.shields.io/github/stars/babapuissance/42_Philosopher?style=social)
![Last Commit](https://img.shields.io/github/last-commit/babapuissance/42_Philosopher)
![Language](https://img.shields.io/badge/language-C-blue)
![Multithreading](https://img.shields.io/badge/feature-pthreads-yellow)
![License](https://img.shields.io/github/license/babapuissance/42_Philosopher)
![Build](https://github.com/babapuissance/42_Philosopher/actions/workflows/build.yml/badge.svg)

> A multithreaded simulation of the **Dining Philosophers Problem** 🧵🍽️  
> Includes a mini **quiz** at the end to test your understanding!

![Demo](docs/demo.gif)

---

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

## 📝 Quiz

To make this project more interactive, I created a **short quiz**:  
- Test your knowledge about philosophers, threads, and mutexes.  
- Questions go from basics to tricky edge cases.  

👉 **Launch the quiz with:** `make quiz`

---

## Disclaimer

This project was developed for **42 School**.  
It follows the [Norm](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf).