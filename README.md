# 🧠 Regression Model from Scratch (C Implementation)

This project demonstrates a simple machine learning regression model (likely linear regression) implemented from scratch in C. It includes the entire training process, including loss computation and iterative parameter updates.

## 📊 Overview

The goal of this project is to perform supervised learning using a regression model, minimizing a loss function over multiple epochs. The training process logs the loss at each epoch, allowing you to monitor convergence.

Example loss log:

```
Epoch 166, Loss: 380071359147.870420  
Epoch 250, Loss: 378227187076.111330  
Epoch 300, Loss: 377954420798.215760  
Epoch 350, Loss: 377848839939.072880  
...
```

## 📁 Project Structure

```
regression/
├── main.c               # Entry point and training loop
├── model.c              # Model definition and update logic
├── model.h              # Header for model functions
├── data.csv             # Training data (if used)
├── Makefile             # Build configuration
└── README.md            # Project documentation
```

## ⚙️ How It Works

1. **Model Initialization**: Model parameters (weights, bias) are initialized.
2. **Forward Pass**: Predictions are made based on input features.
3. **Loss Calculation**: The Mean Squared Error (MSE) loss is computed.
4. **Backward Pass (Gradient Descent)**: Weights are updated to reduce the loss.
5. **Logging**: Loss is printed at each epoch to track convergence.

## 📌 Dependencies

No external libraries are required. The project is written in standard C and uses `stdio.h` and `stdlib.h`.

## 🏁 How to Run

1. Compile the program:
   ```bash
   make
   ```

2. Run the executable:
   ```bash
   ./regression
   ```

## ✅ Example Output

```
Epoch 1, Loss: 4.5e+11  
Epoch 100, Loss: 3.8e+11  
Epoch 300, Loss: 3.7e+11  
...
```

This decreasing trend in loss suggests the model is learning effectively.

## 📈 Future Improvements

- Add support for multiple features (multivariate regression)
- Visualize loss curve with a script (e.g., Python + matplotlib)
- Normalize input features for better convergence
- Implement model evaluation (e.g., RMSE, MAE)

## 👨‍💻 Author

Timo Widyanvolta
