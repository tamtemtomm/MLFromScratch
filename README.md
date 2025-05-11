# 🧠 Machine Learning From Scratch (in C)

Welcome to **Machine Learning From Scratch**, a collection of machine learning algorithms implemented entirely in **C**. This project is focused on understanding the inner workings of ML models by building them from the ground up — no external libraries, just pure C.

## 📚 Implemented Models

| Model               | Description                          | Status      |
|--------------------|--------------------------------------|-------------|
| 🧮 Linear Regression | Predict continuous values            | ✅ Completed |
| 📍 K-Nearest Neighbors | Classification via proximity       | 🚧 In Progress |
| 📐 Support Vector Machine | Max-margin classifier           | 🚧 In Progress |
| 🌳 Decision Tree     | Rule-based classification/regression | 🧪 Planned    |

> ✅ = Implemented, 🚧 = In Progress, 🧪 = Planned

## 🗂️ Repository Structure

```
MLFromScratch/
├── src/
    ├── linear_regression/   # Linear Regression implementation
    ├── knn/                 # K-Nearest Neighbors implementation
    ├── svm/                 # Support Vector Machine implementation
    ├── decision_tree/       # Decision Tree implementation
    ├── utils/
        ├── cnumpy/ # 2D numpy implementation
        ├── csv/ & Module to open the csv file 
└── main.c
└── README.md            # This file
```

Each folder contains:

- `main.c` – Program entry point and demo
- `model.c/.h` – Model logic and functions
- `README.md` – Model-specific documentation

## 🏃‍♂️ How to Run

Change the model in main.c file and Run the main.c file:

```bash
./build.bat
```

## 🎯 Goals

- Learn and teach the fundamentals of ML by implementing core ideas in a low-level language.
- Keep each implementation readable and modular.
- Avoid using libraries like NumPy or scikit-learn — everything is handcrafted.

## 🧪 Testing & Datasets

Minimal datasets are embedded or loaded from simple `.csv` files. You are encouraged to add your own and test model behavior.

## 🙋‍♂️ Author

**Timo Widyanvolta**  
Learning, building, and exploring ML fundamentals — one line of C at a time.

---

Feel free to ⭐ star the repo if you like the idea or want to follow the journey!
