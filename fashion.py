import pandas as pd
import numpy as np
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Conv2D, MaxPooling2D, Flatten

# Define the class names
class_names=['T-shirt/top', 'Trouser', 'Pullover', 'Dress', 'Coat', 'Sandal','Shirt', 'Sneaker', 'Bag', 'Ankleboot']

# Read the training data
df1 = pd.read_csv("fashion-mnist_train.csv")

# Feature Extraction by separating classes and labels from each other 
x_train = df1.drop("label", axis=1).values
y_train = df1["label"].values

# Read the validation data
df2 = pd.read_csv("fashion-mnist_test.csv")

# Feature Extraction for validation dataset
x_test = df2.drop("label", axis=1).values
y_test = df2["label"].values

# Scaling and Reshaping of the dataset
x_train = x_train.reshape(60000, 28, 28)
x_test = x_test.reshape(10000, 28, 28)
x_train = x_train/255
x_test = x_test/255
x_train = x_train.reshape(60000, 28, 28, 1)
x_test = x_test.reshape(10000, 28, 28, 1)

# Build the model
model=Sequential()
model.add(Conv2D(64, (3,3), activation='relu', input_shape=(28,28,1)))
model.add(MaxPooling2D((2,2)))
model.add(Conv2D(64, (3,3), activation='relu'))
model.add(MaxPooling2D((2,2)))
model.add(Flatten())
model.add(Dense(128,activation='relu'))
model.add(Dense(10,activation='softmax'))
model.compile(optimizer='adam', loss='sparse_categorical_crossentropy',metrics=['accuracy'])
# print(model.summary())

# Train the model
model.fit(x_train, y_train, epochs=3, verbose=1, validation_data=(x_test,y_test))

# Get predictions from the trained model
predictions = model.predict(x_test)
index=10
print(predictions[index])
final_value=np.argmax(predictions[index])
print("Actual label :",y_test[index])
print("Predicted label :",final_value)
print("Class :",class_names[final_value])

# Perform evaluation of the trained model
loss, accuracy = model.evaluate(x_test, y_test)
print("Loss :",loss)
print(f"Accuracy (Test Data) : {round(accuracy*100)} %")