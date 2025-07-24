import testFirstClassifier
import testConvolutions
import numpy as np

from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

iris = load_iris()

X_train, X_test, Y_train, Y_test = train_test_split(iris.data, iris.target, test_size=0.2, random_state=42)

knn = testFirstClassifier.KNN(k = 5, distance='euclidean')

knn.fit(X_train, Y_train)

y_pred = knn.predict(X_test)

accuracy = accuracy_score(Y_test, y_pred)
print(f"Accuracy: {accuracy}")

conV = testConvolutions.CONV2D(kernel_size=3, padding=2)

X = np.array([1, 2, 3, 4, 5, 6])

for _ in range(5):
    X = np.concatenate((X, np.array([1, 2, 3, 4, 5, 6])))

X = X.reshape((6,6))

kernel = np.array([[0, 1, 0], [0, 0, 1], [-1, 0, 1]])

Y = conV.convolve(X, kernel)

print(Y)