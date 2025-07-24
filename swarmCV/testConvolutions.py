import numpy as np

class CONV2D:
    def __init__(self, kernel_size=3, padding=0):
        self.kernel_size = kernel_size
        self.padding = padding

    def convolve(self, X, kernel):
        if self.padding > 0:
            X = np.pad(X, (self.padding, ), mode='constant', constant_values=0)
        Y = np.zeros(((X.shape[0] - self.kernel_size + 1),(X.shape[1] - self.kernel_size + 1)))

        for i in range(X.shape[0] - kernel.shape[0] + 1):
            for j in range(X.shape[1] - kernel.shape[1] + 1):
                curRegion = X[i:(i + kernel.shape[0]),j:(j + kernel.shape[1])]
                Y[i, j] = np.sum(curRegion * kernel)

        return Y;

