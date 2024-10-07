import numpy as np

class RegressionMetrics:

    @staticmethod
    def rmse(y_true, y_pred):
        if y_true.shape != y_pred.shape:
            raise Exception("Expected data shape doesn't match with actual data shape!")
        
        return np.sqrt(RegressionMetrics.mse(y_true, y_pred))
    
    @staticmethod
    def mae(y_true, y_pred):
        if y_true.shape != y_pred.shape:
            raise Exception("Expected data shape doesn't match with actual data shape!")
        
        number_of_data_points = y_pred.shape[0]
        return np.sum(np.abs((y_true - y_pred) / number_of_data_points))
    
    @staticmethod
    def mse(y_true, y_pred):
        if y_true.shape != y_pred.shape:
            raise Exception("Expected data shape doesn't match with actual data shape!")
        
        number_of_data_points = y_pred.shape[0]
        return np.sum((y_true - y_pred)**2 / number_of_data_points)
    
    @staticmethod
    def r2(y_true, y_pred):
        if y_true.shape != y_pred.shape:
            raise Exception("Expected data shape doesn't match with actual data shape!")
        
        true_mean = np.mean(y_true)
        sstot = np.sum((y_true - true_mean)**2)
        ssres = np.sum((y_true - y_pred)**2)
        return 1 - (ssres / sstot)