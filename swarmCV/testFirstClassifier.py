from collections import Counter
import numpy as np

class KNN:
    def __init__(self, k=3, distance='euclidean'):
        self.k = k
        self.distance = distance

    def fit(self, X_train, Y_train):
        self.X_train = X_train
        self.Y_train = Y_train

    def predict(self, X_test):
        y_pred = []

        for x in X_test:
            if self.distance == 'euclidean':
                distances = np.linalg.norm(self.X_train - x, axis=1)
            elif self.distance == 'manhattan':
                distances = np.sum(np.abs(self.X_train - x), axis=1)
            else:
                distances = np.power(np.sum(np.power(np.abs(self.X_train - x), self.distance), axis=1), 1/self.distance)

            nearest_indicies = np.argsort(distances)[:self.k]
            nearest_labels = self.Y_train[nearest_indicies]

            label = Counter(nearest_labels).most_common(1)[0][0]
            y_pred.append(label)

        return np.array(y_pred)


print("KNN classifier is ready to use.")