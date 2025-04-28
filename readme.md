# **libft**

_magebreh_  
_Hive Helsinki, 2025_

A custom implementation of standard C library functions, including memory, string, and linked list utilities, for educational purposes.

---

## **Features**

- Reimplements essential C standard library functions (e.g., `memcpy`, `strdup`, `atoi`, `split`, etc.)
- Includes a bonus set of singly linked list utilities (`t_list` and related functions)
- Designed for portability and strict C compliance (`-Wall -Wextra -Werror`)
- No external dependencies

## **How to Run**

### _Prerequisites_

- GCC or compatible C compiler
- Make

### _Installation & Setup_

```bash
make
```

### _Running the Project_

This project builds a static library `libft.a` for use in your own C projects.  
To use it, include `libft.h` in your source and link with `libft.a`:

```bash
cc -Wall -Wextra -Werror your_program.c libft.a
```

## **Project Structure**

```
libft/
├── ft_*.c           # Source files for each function
├── libft.h          # Header file with function prototypes and t_list struct
├── Makefile         # Build script
└── readme.md        # This file
```

## **Screenshots (If Applicable)**

_(No UI; library only)_

## **Credits**

- Inspired by the 42/ Hive Helsinki curriculum
- Author: magebreh

---

### **Tips for School Projects**

✅ **Keep it short** – No need for badges or complex docs.  
✅ **Explain how to run it** – Your teacher/TA should be able to test it easily.  
✅ **Mention dependencies** – Avoid "It doesn't work on my machine" issues.  
✅ **Add screenshots** (if UI-based) – Helps visualize the output.
