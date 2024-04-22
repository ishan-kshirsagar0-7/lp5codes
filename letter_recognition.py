import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from ucimlrepo import fetch_ucirepo
from sklearn.preprocessing import LabelEncoder
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout


# Fetch the letter recognition data from the UCI Machine Learning Repository
letter_recognition = fetch_ucirepo(id=59)

# Split the dataset into X, Y, training and testing sets
X = letter_recognition["data"]["features"]
Y = letter_recognition["data"]["targets"]
# print(np.unique(Y)) -- to print all target classes
x_train, x_test, y_train, y_test = train_test_split(X, Y, test_size=0.2)

# Perform scaling on the dataset
x_train = x_train/255
x_test = x_test/255
encoder = LabelEncoder()
y_train = encoder.fit_transform(y_train)
y_test = encoder.fit_transform(y_test)

# Build the model
model = Sequential()
model.add(Dense(512, activation='relu', input_shape=(16,)))
model.add(Dropout(0.2))
model.add(Dense(256, activation='relu'))
model.add(Dropout(0.2))
model.add(Dense(26, activation='softmax'))
model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
print(model.summary())

# Train the model
model.fit(x_train, y_train, epochs=50, batch_size=128, verbose=1, validation_data=(x_test, y_test))

# Inference on the trained model
predictions = model.predict(x_test)
index=10
class_names=['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']
print(predictions[index])
final_value=np.argmax(predictions[index])
print("Actual label :",y_test[index])
print("Predicted label :",final_value)
print("Class (A-Z) :",class_names[final_value])

# Evaluation of the trained model
loss, accuracy = model.evaluate(x_test, y_test)
print("Loss :",loss)
print(f"Accuracy (Test Data) :{round(accuracy*100)}%")